#include "core/frame_timer.hpp"

double FrameTimer::push(float dt) {
    sum            -= samples[index];
    sum            += dt;
    samples[index]  = dt;
    index           = ++index % N;
    if (count < N)
        ++count;
    return sum / count;
};

float FrameTimer::calc_dt() {
    float current_frame = glfwGetTime();
    delta_time          = current_frame - last_frame;
    last_frame          = current_frame;
    return delta_time;
}

float FrameTimer::fps_to_ft(const int fps) {
    return static_cast<float>(1.0 / fps);
}
int FrameTimer::ft_to_fps(const float ft) {
     return static_cast<int>(1.0 / ft); 
}

void FrameTimer::busy_wait(const double seconds) {
    double start = glfwGetTime();
    while (glfwGetTime() - start < seconds) {}
}
