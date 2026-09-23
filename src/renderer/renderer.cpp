#include "renderer/renderer.hpp"

void Renderer::init() {

    //Init the shaders
    std::string vertex_source =   AssetManager::load_txt_file("assets/shaders/simple_vertex.shader");
    std::string fragment_source = AssetManager::load_txt_file("assets/shaders/simple_fragment.shader");

    voxel_shader.init(vertex_source, fragment_source);
    voxel_shader.bind();
    //TODO, add a shader map to the renderer

    // Testing the renderer first so we can setup a camera
    std::vector<Vertex> vertices = {
        {{-0.5f, -0.5f, 0.0f}, {0.0f, 0.0f}},
        {{0.5f, -0.5f, 0.0f}, {1.0f, 0.0f}},
        {{0.0f, 0.5f, 0.0f}, {0.5f, 1.0f}},
    };

    std::vector<uint32_t> indices = {0, 1, 2};

    test_mesh = Renderer::create_gpu_mesh({vertices}, {indices});

    this->cmd.gpu_mesh = &test_mesh;
    this->cmd.transform = glm::mat4(1.0f);
};

void Renderer::begin_frame() {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    
    this->submit(this->cmd);
}

void Renderer::render() {
    while (!m_render_queue.empty()) {
        auto& cmd = m_render_queue.front();
        m_render_queue.pop();
        std::cout << "The cmd has been popped from the queue\n";

        voxel_shader.bind();
        glBindVertexArray(cmd.gpu_mesh->vao);
        cmd.transform = glm::mat4(0.5f);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        std::cout << "The cmd should have been drawn\n";
    }
}

void Renderer::end_frame() {
}

void Renderer::viewport(const int width, const int height) { glViewport(0, 0, width, height); }

void Renderer::submit(const RenderCommand& cmd) {
    m_render_queue.push(cmd);
}


GPUMesh Renderer::create_gpu_mesh(const std::vector<Vertex> &vertices,
                               const std::vector<uint32_t> &indices) {
    GPUMesh gpu_mesh;
    auto& vbo = gpu_mesh.vbo;
    auto& vao = gpu_mesh.vao;
    auto& ibo = gpu_mesh.ibo;

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    //Could cause a problem, taking an address of a reference
    constexpr size_t vertices_size = sizeof(Vertex) * sizeof(vertices);
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, vertices_size, vertices.data(), GL_STATIC_DRAW);

    //0 is the layout(location)
    //3 is the vector size of the elements being passed in {x, y ,z}
    //GL_float is the type
    //GL_FALSE is something to do with it being normalised
    //3 * sizeof(float) is the stride length in bytes
    //(void*)0 is inital offset for the stride
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)offsetof(Vertex, uv));
    glEnableVertexAttribArray(1);

    //Unbind it because we don't need to be bound now
    //and will be bound again when we draw
    glBindVertexArray(0);

    return gpu_mesh;
}
