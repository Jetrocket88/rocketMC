#pragma once

#include "core/window.hpp"
#include "renderer/vertex.hpp"

 
#include <glfw3.h>
#include <glad/glad.h>
#include <queue>
#include <vector>

struct Mesh {
    std::vector<Vertex> vertices;
    std::vector<uint32_t> indices;
};

struct RenderCommand {
    const Mesh* mesh;
    //const Material* material;
    glm::mat4 transform;
};

class Renderer {
public:
    void init();
    void begin_frame();
    void render();
    void end_frame();
    void viewport(const int width, const int height);
    void submit(const RenderCommand& cmd);
private:
    std::queue<RenderCommand> m_render_queue {};

};
