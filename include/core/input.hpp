#pragma once

#include <cstring>
#include <glfw3.h>
#include <iostream>
#include <glm/glm.hpp>

struct KeyData {
    bool *keys;
    bool *prev_keys;
};

class Input {
  private:
    bool m_keys[GLFW_KEY_LAST]      = {};
    bool m_prev_keys[GLFW_KEY_LAST] = {};

    static void mouse_pos_callback(GLFWwindow *window, double xpos, double ypos);
    static void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);

  public:
    void init(GLFWwindow *window);
    void poll_input(GLFWwindow *window);

    KeyData get_key_data() { return (KeyData){.keys = m_keys, .prev_keys = m_prev_keys}; };

    bool key_pressed(int key) const;
    bool key_active(int key) const;

    static bool key_pressed(const KeyData &data, int key);
    static bool key_active(const KeyData &data, int key);

    void end_frame();

    float m_mouse_delta_x{};
    float m_mouse_delta_y{};
    float m_scroll_delta{};

    float m_last_mouse_x{};
    float m_last_mouse_y{};

    bool first_mouse{};

    glm::vec2 get_mouse_delta() const { return {m_mouse_delta_x, m_mouse_delta_y}; };
};
