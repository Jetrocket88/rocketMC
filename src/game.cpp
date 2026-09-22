#include "game.hpp"

void Game::init() {
    window.init();
}

void Game::run() {
    while (!window.should_close()) {
        window.poll_events();
        input.poll_input(window.window);

        update();

        renderer.begin_frame();
        renderer.render();
        renderer.end_frame();

        window.swap_buffers();
    }
}


void Game::update(float dt) {
    if (input.key_pressed(GLFW_KEY_ESCAPE)) {
        end();
    }

}

void Game::end() {
    window.close_window();
}

void Game::shutdown() {
    glfwDestroyWindow(window.window);
    window.window = nullptr;
    glfwTerminate();
}
