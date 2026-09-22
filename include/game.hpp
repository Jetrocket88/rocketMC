#pragma once

#include <iostream>

#include <glad/glad.h>
#include <glfw3.h>

#include "renderer/renderer.hpp"
#include "core/window.hpp"
#include "core/input.hpp"


class Game {
private:
    Window window {};
    Renderer renderer {};
    Input input {};

public:
    void init();
    void run();
    void update(float dt = 0.0f);
    void end();
    void shutdown();
};
