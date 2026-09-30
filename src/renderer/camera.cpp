#include "renderer/camera.h"

#include "glm/ext/quaternion_trigonometric.hpp"
#include "glm/gtx/transform.hpp"
#include "glm/gtx/vector_angle.hpp"

namespace TGL::GFX
{
    camera::camera(const f32 fov, const f32 aspect, const f32 near, const f32 far)
    {
        m_projection_type = PERSPECTIVE;
        
        m_projection_matrix = glm::perspective(glm::radians(fov), aspect, near, far);
        
        update_view_matrix();
    }

    camera::camera(const f32 left, const f32 right, const f32 bottom, const f32 top, const f32 near, const f32 far)
    {
        m_projection_type = ORTHOGRAPHIC;
        
        m_projection_matrix = glm::ortho(left, right, bottom, top, near, far);
        
        update_view_matrix();
    }

    void camera::set_position(const glm::vec3& position)
    {
        m_position = position;
        
        update_view_matrix();
    }

    void camera::set_rotation(const f32 pitch, const f32 yaw, const f32 roll)
    {
        m_rotation = glm::quat(glm::vec3(
            glm::radians(pitch),
            glm::radians(yaw),
            glm::radians(roll)
        ));
        m_rotation = glm::normalize(m_rotation);
        
        update_view_matrix();
    }

    void camera::rotate_xy(const f32 delta_pitch, const f32 delta_yaw)
    {
        glm::quat q_pitch = glm::angleAxis(glm::radians(delta_pitch), glm::vec3(1.f, 0.f, 0.f));
        glm::quat q_yaw = glm::angleAxis(glm::radians(delta_yaw), glm::vec3(0.f, 1.f, 0.f));
        
        m_rotation = q_yaw * m_rotation * q_pitch;
        m_rotation = glm::normalize(m_rotation);
        
        update_view_matrix();
    }

    void camera::set_projection(const glm::mat4& projection)
    {
        m_projection_matrix = projection;
    }

    void camera::update_view_matrix()
    {
        m_view_matrix = glm::mat4_cast(glm::conjugate(m_rotation)) * glm::translate(glm::mat4(1.f), -m_position);
    }
    
}
