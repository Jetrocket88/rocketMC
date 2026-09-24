#include "game.hpp"
#include "gameplay/chunk.hpp"

void Game::init() {
    window.init(m_window_width, m_window_height);
    renderer.init();
    renderer.viewport(m_window_width, m_window_height);
    input.init(window.window);
    cam.init(m_window_width, m_window_height);
    window.hide_cursor();
}

void Game::run() {
    while (!window.should_close()) {
        window.poll_events(); // Triggers callbacks
        input.poll_input(window.window);
        this->calculate_dt();

        glm::vec2 mouse_delta = input.get_mouse_delta();
        cam.update(mouse_delta, delta_time);
        cam.handle_movement(input, delta_time);

        renderer.begin_frame();
        renderer.render(cam);
        renderer.end_frame();

        if (input.key_pressed(GLFW_KEY_ESCAPE)) {
            this->end();
        }

        input.end_frame();
        window.swap_buffers();
    }
}

void Game::update() {}

void Game::end() { window.close_window(); }

void Game::shutdown() {
    glfwDestroyWindow(window.window);
    window.window = nullptr;
    glfwTerminate();
}

void Game::calculate_dt() {
    float current_frame = glfwGetTime();
    delta_time          = current_frame - last_frame;
    last_frame          = current_frame;
}
