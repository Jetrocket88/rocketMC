#include "game.hpp"
#include "gameplay/chunk.hpp"

void Game::init() {
    window.init(m_window_width, m_window_height);
    renderer.init();
    renderer.viewport(m_window_width, m_window_height);
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

void Game::end() { window.close_window(); }

void Game::shutdown() {
    glfwDestroyWindow(window.window);
    window.window = nullptr;
    glfwTerminate();
}

// TODO:
// Change "Mesh" to ChunkMesh which contains: vertices and indexes **
// Implement a GPUMesh which contains: VAO, VBO, IBO **
// After we have the ChunkMesh, we should make some function in the renderer, which converts the
// ChunkMesh into GPUMesh
// After that, we can reword the renderer pipeline to take in the GPUMesh
// After that, we can implement the VAO, IBO and VBO systems correctly either within the renderer
// See green_eng for how to do this
// After that, we should see a triangle on the screen
// After that, we can work on implementing the camera, see openGL and green_eng
// Those are the goals for tomorrwo
//
//
// Note:
// We pass in the ChunkMesh to the renderer to be converted to a gpu mesh
