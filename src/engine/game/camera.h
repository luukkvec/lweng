#pragma once

#include <glm.hpp>

namespace lweng
{
    class Camera
    {
    public:
        Camera();

        void set_position(const glm::vec3& position);
        void set_rotation(float yaw, float pitch);

        void move(const glm::vec3& offset); // offset in world space
        void rotate(float yaw_delta, float pitch_delta);

        void set_perspective(float fov_degrees, float aspect_ratio, float near_plane, float far_plane);
        void set_aspect_ratio(float aspect_ratio);

        glm::mat4 get_view_matrix() const;
        glm::mat4 get_projection_matrix() const;

        const glm::vec3& get_position() const;
        glm::vec3 get_forward() const;
        glm::vec3 get_right() const;
        glm::vec3 get_up() const;

    private:
        void update_vectors();

        glm::vec3 m_position;
        glm::vec3 m_forward;
        glm::vec3 m_right;
        glm::vec3 m_up;

        float m_yaw;   // degrees, rotation around Y (left/right)
        float m_pitch; // degrees, rotation around X (up/down)

        float m_fov;
        float m_aspect_ratio;
        float m_near;
        float m_far;

        static constexpr glm::vec3 WORLD_UP = glm::vec3(0.0f, 1.0f, 0.0f);
        static constexpr float MAX_PITCH = 89.0f;
    };
}