#include "renderer/renderer.hpp"

void Renderer::init() {

    // Init the shaders
    std::string vertex_source = AssetManager::load_txt_file("assets/shaders/simple_vertex.shader");
    std::string fragment_source =
        AssetManager::load_txt_file("assets/shaders/simple_fragment.shader");
    load_shader("voxel", vertex_source, fragment_source);

    // Testing the renderer first so we can setup a camera
    std::vector<Vertex> vertices = {
        {{0.5f, 0.5f, 0.0f}, {0.0f, 0.0f}},
        {{0.5f, -0.5f, 0.0f}, {1.0f, 0.0f}},
        {{-0.5f, -0.5f, 0.0f}, {0.5f, 1.0f}},
        {{-0.5f, 0.5f, 0.0f}, {0.5f, 1.0f}},
    };

    std::vector<uint32_t> indices = {
        0, 1, 3,
        1, 2, 3
    };

    test_mesh = Renderer::create_gpu_mesh({vertices}, {indices});

    this->cmd.gpu_mesh    = &test_mesh;
    this->cmd.transform   = glm::mat4(1.0f);
    this->cmd.shader_name = "voxel";
};

void Renderer::begin_frame() {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    this->submit(this->cmd);
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

        glBindVertexArray(cmd.gpu_mesh->vao);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0); 
    }
}

void Renderer::end_frame() {}

void Renderer::viewport(const int width, const int height) { glViewport(0, 0, width, height); }

void Renderer::submit(const RenderCommand &cmd) { m_render_queue.push(cmd); }

GPUMesh Renderer::create_gpu_mesh(const std::vector<Vertex> &vertices,
                                  const std::vector<uint32_t> &indices) {
    GPUMesh gpu_mesh;
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
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(uint32_t), indices.data(), GL_STATIC_DRAW);

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

    return gpu_mesh;
}

// creates the shader and compiles it and everything and then adds it to the shader map
void Renderer::load_shader(const std::string &name, const std::string &vsource,
                           const std::string &fsource) {
    Shader shader{};
    shader.init(vsource, fsource);
    m_shader_map[name] = shader;
}
