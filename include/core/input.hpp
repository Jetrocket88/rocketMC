#pragma once

#include <glfw3.h>
#include <cstring>

class Input {
private:
    bool  m_keys      [GLFW_KEY_LAST] = {};
    bool  m_prev_keys [GLFW_KEY_LAST] = {};
    float m_mouse_x {};
    float m_mouse_y {};
    float m_scroll_delta {};

public:
    void init();
    void poll_input(GLFWwindow* window);
    bool key_pressed(int key) const;
    bool key_active (int key) const; 
};
