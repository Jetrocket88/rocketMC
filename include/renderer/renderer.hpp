#pragma once

#include "core/window.hpp"
#include "assets/asset_manager.hpp"
#include "renderer/shader.hpp"
#include "renderer/vertex.hpp"
#include "renderer/camera.hpp"

#include <glad/glad.h>
#include <glfw3.h>
#include <queue>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <sstream>

struct GPUMesh {
    GLuint vao, ibo, vbo;
    GLsizei index_count;
};

struct RenderCommand {
    const GPUMesh *gpu_mesh;
    // const Material* material;
    glm::mat4 transform;
    std::string shader_name;
};

class Renderer {
  public:
    void init();
    void begin_frame();
    void render(const Camera& cam);
    void end_frame();
    void viewport(const int width, const int height);
    void submit(const RenderCommand &cmd);
    void load_shader(const std::string& name, const std::string& vsource, const std::string& fsource);
    static GPUMesh create_gpu_mesh(const std::vector<Vertex> &vertices,
                                   const std::vector<uint32_t> &indices);
  private:

    Shader voxel_shader{}; //TEMP
    RenderCommand cmd{}; //TEMP
    GPUMesh test_mesh{}; //TEMP
    std::queue<RenderCommand> m_render_queue{};
    std::unordered_map<std::string, Shader> m_shader_map{};

};
