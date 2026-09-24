#include "renderer/camera.hpp"

void Camera::init(const size_t width, const size_t height) {
    m_camera_pos   = glm::vec3(0.0f, 0.0f, 3.0f);
    m_camera_front = glm::vec3(0.0f, 0.0f, -1.0f);
    m_camera_up    = glm::vec3(0.0f, 1.0f, 0.0f);
    m_up           = glm::vec3(0.0f, 1.0f, 0.0f);
    m_yaw          = -90.0f;
    m_pitch        = 0.0f;
    m_cam_speed    = 1.127f;
    first_mouse    = true;
    m_lastX = m_lastY = 0.0f;

    m_projection = glm::perspective(
        glm::radians(45.0f),                                    // FOV
        static_cast<float>(width) / static_cast<float>(height), // aspect ratio (width / height)
        0.1f,                                                   // near clip
        100.0f                                                  // far clip
    );

};

void Camera::update(glm::vec2& mouse_delta, float dt) {

    // Apply the mouse deltas
    float sensitivity  = 0.07f;
    mouse_delta.x     *= sensitivity;
    mouse_delta.y     *= sensitivity;

    m_yaw   += mouse_delta.x;
    m_pitch += mouse_delta.y;

    if (m_pitch > 89.0f)
        m_pitch = 89.0f;
    if (m_pitch < -89.0f)
        m_pitch = -89.0f;

    glm::vec3 front;
    front.x        = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
    front.y        = sin(glm::radians(m_pitch));
    front.z        = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
    m_camera_front = glm::normalize(front);

    m_camera_right = glm::normalize(glm::cross(m_camera_front, m_up));
    m_camera_up    = glm::normalize(glm::cross(m_camera_right, m_camera_front));

    m_view = glm::lookAt(m_camera_pos, m_camera_pos + m_camera_front, m_camera_up);
    //std::cerr << "m_camera_front: (x, y, z): (" << m_camera_front.x << ", " << m_camera_front.y << ", " << m_camera_front.z << ")\n";
    //std::cerr << "m_up: (x, y, z): (" << m_up.x << ", " << m_up.y << ", " << m_up.z << ")\n";
}

void Camera::on_mouse_move(double x, double y) {

    if (first_mouse) {
        m_lastX     = x;
        m_lastY     = y;
        first_mouse = false;
    }

    float xoffset = x - m_lastX;
    float yoffset = m_lastY - y;
    m_lastX       = x;
    m_lastY       = y;

    float sensitivity  = 0.1f;
    xoffset           *= sensitivity;
    yoffset           *= sensitivity;

    m_yaw   += xoffset;
    m_pitch += yoffset;

    if (m_pitch >= 89.0f)
        m_pitch = 89.0f;
    if (m_pitch <= -89.0f)
        m_pitch = -89.0f;

    glm::vec3 direction;
    direction.x    = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
    direction.y    = sin(glm::radians(m_pitch));
    direction.z    = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
    m_camera_front = glm::normalize(direction);
}

// Fix: the camera should not be able to move, only the player
void Camera::handle_movement(const KeyData &inputs, float dt) {
    if (Input::key_active(inputs, GLFW_KEY_W)) {
        m_camera_pos.x += m_cam_speed * m_camera_front.x * dt;
        m_camera_pos.z += m_cam_speed * m_camera_front.z * dt;
    }
    if (Input::key_active(inputs, GLFW_KEY_S)) {
        m_camera_pos.x -= m_cam_speed * m_camera_front.x * dt;
        m_camera_pos.z -= m_cam_speed * m_camera_front.z * dt;
    }

    if (Input::key_active(inputs, GLFW_KEY_D)) {
        m_camera_pos += m_cam_speed * m_camera_right * dt;
    }
    if (Input::key_active(inputs, GLFW_KEY_A)) {
        m_camera_pos -= m_cam_speed * m_camera_right * dt;
    }

    if (Input::key_active(inputs, GLFW_KEY_LEFT_SHIFT)) {
        m_camera_pos -= m_cam_speed * m_camera_up * dt;
    }
    if (Input::key_active(inputs, GLFW_KEY_SPACE)) {
        std::cout << "Space pressed!\n";
        m_camera_pos += m_cam_speed * m_camera_up * dt;
    }

    if (Input::key_pressed(inputs, GLFW_KEY_LEFT_CONTROL)) {
        if (m_movement_type == WALK) {
            m_movement_type  = MovementType::SPRINT;
            m_cam_speed     *= m_sprint_speed;
        } else if (m_movement_type == SPRINT) {
            m_movement_type  = MovementType::WALK;
            m_cam_speed     /= m_sprint_speed;
        }
    }
}
