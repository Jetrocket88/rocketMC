#pragma once

#include "core/window.hpp"

class Renderer {
public:
    void init();
    void begin_frame();
    void render();
    void end_frame();
private:
};
