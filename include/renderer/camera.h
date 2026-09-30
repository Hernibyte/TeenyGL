#pragma once 

#include "platform/default_types.h"
#include "glm/glm.hpp"
#include "glm/detail/type_quat.hpp"

namespace TGL::GFX
{
     enum camera_projection_type
     {
         PERSPECTIVE,
         ORTHOGRAPHIC
     };
    
    class camera
    {
    public:
        camera() = delete;
        camera(const f32 fov, const f32 aspect, const f32 near, const f32 far);
        camera(const f32 left, const f32 right, const f32 bottom, const f32 top, const f32 near, const f32 far);
        
        void set_position(const glm::vec3& position);
        
        void set_rotation(const f32 pitch, const f32 yaw, const f32 roll);
        void rotate_xy(const f32 delta_pitch, const f32 delta_yaw);
        
        void set_projection(const glm::mat4& projection);
        
        glm::vec3 get_front() const { return m_rotation * glm::vec3(0.f, 0.f, -1.f); }
        glm::vec3 get_right() const { return m_rotation * glm::vec3(1.f, 0.f, 0.f); }
        glm::vec3 get_up() const { return m_rotation * glm::vec3(0.f, 1.f, 0.f); }
        
        glm::mat4 get_projection() const { return m_projection_matrix; };
        glm::mat4 get_view() const { return m_view_matrix; };
        
        camera_projection_type get_projection_type() const { return m_projection_type; };
        
    protected:
        void update_view_matrix();
        
        camera_projection_type m_projection_type;
        
        glm::vec3 m_position { 0.0f, 0.0f, 3.0f };
        
        glm::quat m_rotation = glm::quat();
        
        glm::mat4 m_projection_matrix = glm::mat4(1.0f);
        glm::mat4 m_view_matrix = glm::mat4(1.0f);
    };
    
}
