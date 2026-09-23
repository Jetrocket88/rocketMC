#pragma once

#include "core/window.hpp"
#include "assets/asset_manager.hpp"
#include "renderer/shader.hpp"
#include "renderer/vertex.hpp"

#include <glad/glad.h>
#include <glfw3.h>
#include <queue>
#include <fstream>
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
};

class Renderer {
  public:
    void init();
    void begin_frame();
    void render();
    void end_frame();
    void viewport(const int width, const int height);
    void submit(const RenderCommand &cmd);
    static GPUMesh create_gpu_mesh(const std::vector<Vertex> &vertices,
                                   const std::vector<uint32_t> &indices);
  private:

    //std::unordered_map <std::string, std::shared_ptr<Shader>> map;
    Shader voxel_shader{};
    RenderCommand cmd{};
    GPUMesh test_mesh{};
    std::queue<RenderCommand> m_render_queue{};
};
