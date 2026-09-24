#include "core/input.hpp"

void Input::init(GLFWwindow *window) {
    glfwSetWindowUserPointer(window, this);
    glfwSetCursorPosCallback(window, Input::mouse_pos_callback);
    glfwSetScrollCallback(window, Input::scroll_callback);
};

bool Input::key_pressed(int key) const { return m_keys[key] && !m_prev_keys[key]; }

bool Input::key_active(int key) const { return m_keys[key]; }

void Input::poll_input(GLFWwindow *window) {
    glfwPollEvents();
    memcpy(m_prev_keys, m_keys, sizeof(m_keys));
    for (int key = 0; key < GLFW_KEY_LAST; key++) {
        m_keys[key] = glfwGetKey(window, key) == GLFW_PRESS;
    }
}

bool Input::key_pressed(const KeyData &data, int key) {
    return data.keys[key] && !data.prev_keys[key];
}

bool Input::key_active(const KeyData &data, int key) { return data.keys[key]; }

void Input::mouse_pos_callback(GLFWwindow *window, double xpos, double ypos) {
    auto *self = static_cast<Input *>(glfwGetWindowUserPointer(window));
    //std::cout << "xpos: " << xpos << " ypos: " << ypos << '\n';
    if (!self)
        return;
    if (self->first_mouse) {
        self->m_last_mouse_x = xpos;
        self->m_last_mouse_y = ypos;
        self->first_mouse    = false;
    }
    self->m_mouse_delta_x += xpos - self->m_last_mouse_x;
    self->m_mouse_delta_y += self->m_last_mouse_y - ypos; // flip y: screen-space grows downward
    self->m_last_mouse_x   = xpos;
    self->m_last_mouse_y   = ypos;
};

void Input::scroll_callback(GLFWwindow *window, double xoffset, double yoffset) {
    auto *self = static_cast<Input *>(glfwGetWindowUserPointer(window));
    if (!self)
        return;
    self->m_scroll_delta += yoffset;
};

void Input::end_frame() {
    m_mouse_delta_x = 0.0f;
    m_mouse_delta_y = 0.0f;
    m_scroll_delta  = 0.0f;
}
