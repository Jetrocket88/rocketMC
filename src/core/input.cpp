#include "core/input.hpp"

void Input::init() {

};

bool Input::key_pressed(int key) const {
    return m_keys[key] && !m_prev_keys[key];
}

bool Input::key_active(int key) const {
    return m_keys[key]; 
}

void Input::poll_input(GLFWwindow* window) {
    glfwPollEvents();
    memcpy(m_prev_keys, m_keys, sizeof(m_keys));
    for (int key = 0; key < GLFW_KEY_LAST; key++) {
        m_keys[key] = glfwGetKey(window, key) == GLFW_PRESS;
    }
}
