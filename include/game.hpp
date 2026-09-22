#pragma once

#include <iostream>

#include <glad/glad.h>
#include <glfw3.h>

#include "core/input.hpp"
#include "core/window.hpp"
#include "renderer/renderer.hpp"

class Game {
  private:
    Window window{};
    Renderer renderer{};
    Input input{};

    const int m_window_width {1920};
    const int m_window_height{1080};

  public:
    void init();
    void run();
    void update(float dt = 0.0f);
    void end();
    void shutdown();
};
