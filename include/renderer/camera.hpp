#pragma once

#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


#include "core/input.hpp"

enum MovementType { SPRINT, WALK };

class Camera {
  public:
    void init(const size_t width, const size_t height);
    void update(glm::vec2& mouse_delta, float dt);
    void on_mouse_move(double x, double y);
    void handle_movement(const Input& inputs, float dt); //BAD

    glm::mat4 get_view_matrix() const { return m_view; }
    glm::mat4 get_projection_matrix() const { return m_projection; }

    float m_cam_speed          = 0.05f;
    float m_cam_vertical_speed = 0.025f;
    float fov                  = 45.0f;
    glm::vec3 m_camera_pos;
    bool first_mouse;

  private:
    glm::vec3 m_camera_front, m_camera_up, m_up, m_camera_right;

    glm::mat4 m_view       = glm::mat4(1.0f);
    glm::mat4 m_projection = glm::mat4(1.0f);

    float m_lastX, m_lastY, m_pitch, m_yaw;

    const float m_sprint_speed   = 5;
    MovementType m_movement_type = MovementType::WALK;
};
