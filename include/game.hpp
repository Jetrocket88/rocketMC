#pragma once

#include <iostream>

#include <glad/glad.h>
#include <glfw3.h>

#include "core/input.hpp"
#include "core/window.hpp"
#include "renderer/renderer.hpp"
#include "assets/asset_manager.hpp"
#include "renderer/camera.hpp"

class Game {
  private:
    Window window{};
    Renderer renderer{};
    Input input{};
    AssetManager asset_manager{};
    Camera cam{};

    const int m_window_width {1920};
    const int m_window_height{1080};

    float delta_time{0.0f};
    float last_frame{0.0f};

    void calc_dt();

  public:
    void init();
    void run();
    void update();
    void end();
    void shutdown();
};
