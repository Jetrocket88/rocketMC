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
    bool close { false };
    GLFWwindow* window {};


    int init(const int width = 800, const int height = 600);
    void close_window();
};
