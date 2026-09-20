#include "camera.h"

#include <gtc/matrix_transform.hpp>
#include <algorithm>

namespace lweng
{
    Camera::Camera() :
        m_position(0.0f, 0.0f, 3.0f),
        m_yaw(-90.0f),   // looks into the scene not backward
        m_pitch(0.0f),
        m_fov(45.0f),
        m_aspect_ratio(16.0f / 9.0f),
        m_near(0.1f),
        m_far(100.0f)
    {
        update_vectors();
    }

    void Camera::set_position(const glm::vec3& position)
    {
        m_position = position;
    }

    void Camera::set_rotation(float yaw, float pitch)
    {
        m_yaw = yaw;
        m_pitch = std::clamp(pitch, -MAX_PITCH, MAX_PITCH);
        update_vectors();
    }

    void Camera::move(const glm::vec3& offset)
    {
        m_position += offset;
    }

    void Camera::rotate(float yaw_delta, float pitch_delta)
    {
        m_yaw += yaw_delta;
        m_pitch = std::clamp(m_pitch + pitch_delta, -MAX_PITCH, MAX_PITCH);
        update_vectors();
    }

    void Camera::set_perspective(float fov_degrees, float aspect_ratio, float near_plane, float far_plane)
    {
        m_fov = fov_degrees;
        m_aspect_ratio = aspect_ratio;
        m_near = near_plane;
        m_far = far_plane;
    }

        void Camera::set_aspect_ratio(float aspect_ratio)
    {
        m_aspect_ratio = aspect_ratio;
    }

    glm::mat4 Camera::get_view_matrix() const
    {
        return glm::lookAt(m_position, m_position + m_forward, m_up);
    }

    glm::mat4 Camera::get_projection_matrix() const
    {
        return glm::perspective(glm::radians(m_fov), m_aspect_ratio, m_near, m_far);
    }

    const glm::vec3& Camera::get_position() const
    {
        return m_position;
    }

    glm::vec3 Camera::get_forward() const
    {
        return m_forward;
    }

    glm::vec3 Camera::get_right() const
    {
        return m_right;
    }

    glm::vec3 Camera::get_up() const
    {
        return m_up;
    }

    void Camera::update_vectors()
    {
        glm::vec3 forward;
        forward.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
        forward.y = sin(glm::radians(m_pitch));
        forward.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));

        m_forward = glm::normalize(forward);
        m_right = glm::normalize(glm::cross(m_forward, WORLD_UP));
        m_up = glm::normalize(glm::cross(m_right, m_forward));
    }
}