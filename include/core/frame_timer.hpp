#pragma once

#include <array>
#include <cstddef>
#include <glfw3.h>

class FrameTimer {
  private:
    static constexpr size_t N{100};
    std::array<double, N> samples{};
    size_t index = 0;
    size_t count = 0;
    double sum   = 0.0;

    float delta_time{0.0f};
    float last_frame{0.0f};

  public:
    double push(float dt);
    float calc_dt();
    static float fps_to_ft(const int fps);
    static int ft_to_fps(const float ft);
    static void busy_wait(const double seconds);
};
