#include "renderer/renderer.hpp"

void Renderer::init() {}

void Renderer::begin_frame() {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::render() {
    while (!m_render_queue.empty()) {
        auto& cmd = m_render_queue.front();
        m_render_queue.pop();
    }

}

void Renderer::end_frame() {}

void Renderer::viewport(const int width, const int height) { glViewport(0, 0, width, height); }

void Renderer::submit(const RenderCommand& cmd) {
    m_render_queue.push(cmd);
}
