#include "renderer/renderer.hpp"


void Renderer::init() {

    // Init the shaders
    std::string vertex_source = AssetManager::load_txt_file("assets/shaders/simple_vertex.shader");
    std::string fragment_source =
        AssetManager::load_txt_file("assets/shaders/simple_fragment.shader");

    load_shader("voxel", vertex_source, fragment_source);

    int width, height, nrChannels{};
    unsigned char *data =
        AssetManager::load_texture_file("assets/textures/atlas.png", &width, &height, &nrChannels);
    load_texture("brick-wall", data, width, height, nrChannels, GL_RGBA);

    std::vector<float> uvs {tile_uv(0, 0, 16.0f, 256.0f)};

    std::vector<Vertex> vertices = {
        {{0.5f, 0.5f, 0.0f},   {uvs[0], uvs[3]}},
        {{0.5f, -0.5f, 0.0f},  {uvs[2], uvs[3]}},
        {{-0.5f, -0.5f, 0.0f}, {uvs[2], uvs[1]}},
        {{-0.5f, 0.5f, 0.0f},  {uvs[0], uvs[1]}},
    };

    std::vector<uint32_t> indices = {0, 1, 3, 1, 2, 3};

    test_mesh_id = Renderer::create_gpu_mesh({vertices}, {indices});

    this->cmd.mesh_id      = test_mesh_id;
    this->cmd.transform    = glm::mat4(1.0f);
    this->cmd.shader_name  = "voxel";
    this->cmd.texture_name = "brick-wall";
};

void Renderer::begin_frame() {
    glClearColor(0.1f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    this->submit(this->cmd); // TEMP
}

void Renderer::render(const Camera &cam) {

    while (!m_render_queue.empty()) {
        auto &cmd = m_render_queue.front();
        m_render_queue.pop();

        auto &shader = m_shader_map[cmd.shader_name];
        shader.bind();

        glm::mat4 view_matrix = cam.get_view_matrix();
        shader.set_mat4f("view", &view_matrix);

        glm::mat4 projection_matrix = cam.get_projection_matrix();
        shader.set_mat4f("projection", &projection_matrix);

        cmd.transform = glm::mat4(1.0f);
        shader.set_mat4f("model", &cmd.transform);

        auto &gpu_mesh = m_mesh_map[cmd.mesh_id];

        TexID &texture_id = m_tex_map["brick-wall"];
        glBindTexture(GL_TEXTURE_BINDING_2D, texture_id);

        glBindVertexArray(gpu_mesh.vao);
        glDrawElements(GL_TRIANGLES, gpu_mesh.index_count, GL_UNSIGNED_INT, 0);
    }
}

void Renderer::end_frame() {}

void Renderer::viewport(const int width, const int height) { glViewport(0, 0, width, height); }

void Renderer::submit(const RenderCommand &cmd) { m_render_queue.push(cmd); }

MeshID Renderer::create_gpu_mesh(const std::vector<Vertex> &vertices,
                                 const std::vector<uint32_t> &indices) {
    GpuMesh gpu_mesh;
    auto &vbo = gpu_mesh.vbo;
    auto &vao = gpu_mesh.vao;
    auto &ibo = gpu_mesh.ibo;

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    // Could cause a problem, taking an address of a reference
    const size_t vertices_size = sizeof(Vertex) * vertices.size();
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, vertices_size, vertices.data(), GL_STATIC_DRAW);

    glGenBuffers(1, &ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(uint32_t), indices.data(),
                 GL_STATIC_DRAW);

    // 0 is the layout(location)
    // 3 is the vector size of the elements being passed in {x, y ,z}
    // GL_float is the type
    // GL_FALSE is something to do with it being normalised
    // 3 * sizeof(float) is the stride length in bytes
    //(void*)0 is inital offset for the stride
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, uv));
    glEnableVertexAttribArray(1);

    // Unbind it because we don't need to be bound now
    // and will be bound again when we draw
    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    gpu_mesh.index_count       = indices.size();
    m_mesh_map[m_mesh_counter] = gpu_mesh;
    return m_mesh_counter++;
}

// creates the shader and compiles it and everything and then adds it to the shader map
void Renderer::load_shader(const std::string &name, const std::string &vsource,
                           const std::string &fsource) {
    Shader shader{};
    shader.init(vsource, fsource);
    m_shader_map[name] = shader;
}

// You should pass in either GL_RGB OR GL_RGBA as the imagetype
// Will work on some system to make this easier
void Renderer::load_texture(const std::string &name, unsigned char *data, int width, int height,
                            int nrChannels, int image_type) {
    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);   // safe for RGB data with odd row sizes
    glTexImage2D(GL_TEXTURE_2D, 0, image_type, width, height, 0, image_type, GL_UNSIGNED_BYTE, data);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 4);  // 16px tiles: stop before tiles

    glGenerateMipmap(GL_TEXTURE_2D);

    AssetManager::image_free(data);
    m_tex_map[name] = texture;
}

//tile and atlas are the tile size and atlas size in pixels
std::vector<float> Renderer::tile_uv(int col, int row, float tile, float atlas) {
    float s = tile / atlas;
    float e = 0.5f / atlas;           // half a texel
    std::vector<float> out{};
    out.push_back(col * s + e);       // u0
    out.push_back(row * s + e);       // v0
    out.push_back((col + 1) * s - e); // u1
    out.push_back((row + 1) * s - e); // v1
    return out;
}
