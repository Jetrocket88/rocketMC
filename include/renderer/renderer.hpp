#pragma once

#include "core/window.hpp"
#include "assets/asset_manager.hpp"
#include "renderer/shader.hpp"
#include "renderer/vertex.hpp"
#include "renderer/camera.hpp"
#include "renderer/texture.hpp"

#include <glad/glad.h>
#include <glfw3.h>
#include <queue>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <sstream>

using MeshID = std::size_t;
using TexID = std::size_t;

struct GpuMesh {
    GLuint vao, ibo, vbo;
    GLsizei index_count;
};

struct RenderCommand {

    MeshID mesh_id;
    glm::mat4 transform;
    std::string shader_name;
    std::string texture_name;
    // const Material* material;
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
    void load_texture(const std::string& name, unsigned char* data, int width, int height, int nrChannels, int image_type);
    MeshID create_gpu_mesh(const std::vector<Vertex> &vertices,
                                   const std::vector<uint32_t> &indices);
    static std::vector<float> tile_uv(int col, int row, float tile, float atlas);
  private:

    MeshID m_mesh_counter {};
    RenderCommand cmd{}; //TEMP
    MeshID test_mesh_id{}; //TEMP
    std::queue<RenderCommand> m_render_queue{};
    std::unordered_map<std::string, Shader> m_shader_map{};
    std::unordered_map<MeshID, GpuMesh> m_mesh_map{};
    std::unordered_map<std::string, TexID> m_tex_map{};
};
