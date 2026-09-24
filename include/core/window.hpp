#pragma once

#include <iostream>
#include <glad/glad.h>
#include <glfw3.h>
#include <assert.h>

class Window {
private:
    int init_glfw() const;
    int init_glad() const;

public:
    bool should_close();
    void poll_events();
    void swap_buffers();
    void hide_cursor();
    void show_cursor();
    bool close { false };
    GLFWwindow* window {};


    int init(const int width = 800, const int height = 600);
    void set_mouse_callback(void (*mouse_callback)(GLFWwindow* window, double xpos, double ypos));
    void close_window();
};
