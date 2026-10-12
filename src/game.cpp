#include "game.hpp"

void Game::init() {
    window.init(m_window_width, m_window_height);
    window.hide_cursor();

    input.init(window.window);

    renderer.init();
    renderer.viewport(m_window_width, m_window_height);

    cam.init(m_window_width, m_window_height);

    world.init();
}

void Game::run() {
    while (!window.should_close()) {
        window.poll_events(); // Triggers callbacks
        input.poll_input(window.window);

        float dt     = frame_timer.calc_dt();
        float avg_ft = frame_timer.push(dt);
        int i{0};
        if (i++ % 10000 == 0 && this->debug) {
            std::cout << "average fps: " << FrameTimer::ft_to_fps(avg_ft) << '\n';
            std::cout << "average frame_time: " << avg_ft << '\n';
        }

        glm::vec2 mouse_delta = input.get_mouse_delta();
        cam.update(mouse_delta, dt);
        cam.handle_movement(input, dt);

        for (size_t i{0}; i < world.num_chunks; i++) {
            auto &chunk = world.chunks[i];
            chunk.generate_chunk_mesh();
            ChunkMesh chunk_mesh{chunk.get_chunk_mesh()};
            MeshID mesh_id = renderer.create_gpu_mesh(chunk_mesh.vertices, chunk_mesh.indices);
            RenderCommand render_cmd = {
                .mesh_id = mesh_id,
                .transform = glm::mat4(1.0f),
                .shader_name = "voxel"};
            renderer.submit(render_cmd);
        }

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

// TODO: implement MeshID
// Functionality: renderer.create_gpu_mesh returns a MeshID class / type
// the GpuMesh struct holds this ID (lightweight int / class).
// When drawing, the renderer performs a lookup
// on the meshID for the currently loaded MeshID's (unordered map).
// The map: std::unordered_map<ID, GPUMesh> mesh_map;
//
//   MeshID gpu_mesh = renderer.create_gpu_mesh(
//       chunk_mesh.vertices,
//       chunk_mesh.indices
//   );
//
//   renderer.submit({
//       .mesh = gpu_mesh,
//       .transform = glm::mat4(1.0f),
//       .shader_name = "voxel"
//   })
//
// FIX: Mouse jumping when moving after not being on the window, should have been fixed my first
// mouse shennanigans but isn't for some reason
