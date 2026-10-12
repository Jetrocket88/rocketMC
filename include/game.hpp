#pragma once

#include <iostream>
#include <thread>
#include <chrono>


#include <glad/glad.h>
#include <glfw3.h>

#include "assets/asset_manager.hpp"
#include "core/input.hpp"
#include "core/window.hpp"
#include "gameplay/world.hpp"
#include "renderer/camera.hpp"
#include "renderer/renderer.hpp"
#include "core/frame_timer.hpp"

class Game {
  private:
    Window window{};
    Renderer renderer{};
    Input input{};
    AssetManager asset_manager{};
    Camera cam{};
    World world{};
    FrameTimer frame_timer{};

    const int m_window_width{1920};
    const int m_window_height{1080};
    bool debug {0};

  public:
    void init();
    void run();
    void update();
    void end();
    void shutdown();
};
