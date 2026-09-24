#include "core/window.hpp"

int Window::init(const int width, const int height) {
    assert(this->init_glfw() != -1 && "Glfw failed to init");

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    this->window = glfwCreateWindow(width, height, "Testing", NULL, NULL);
    if (!this->window) {
        std::cout << "Window was unable to be created!\n";
        return -1;
    }
    std::cout << "Window created successfully!\n";
    glfwMakeContextCurrent(this->window);

    assert(this->init_glad() != -1 && "Glfw failed to init");
    return 0;
}

int Window::init_glfw() const {
    if (!glfwInit()) {
        std::cout << "GLFW Unable to init successfully!\n";
        return -1;
    }
    return 0;
}
int Window::init_glad() const {
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    return 0;
}

bool Window::should_close() { return glfwWindowShouldClose(this->window); }
void Window::poll_events() { glfwPollEvents(); }
void Window::swap_buffers() { glfwSwapBuffers(this->window); }

void Window::close_window() { glfwSetWindowShouldClose(this->window, GL_TRUE); }


void Window::hide_cursor() {
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

}
void Window::show_cursor() {
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}

/*
void Window::set_mouse_callback(void (*mouse_callback)(GLFWwindow* window, double xpos, double ypos)) {
    glfwSetCursorPosCallback(window, mouse_callback);
}
*/
