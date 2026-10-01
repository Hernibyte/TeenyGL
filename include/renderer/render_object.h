#pragma once

#include "glm/glm.hpp"
#include "glm/gtx/transform.hpp"

#include "platform/log.h"
#include "renderer/vertex_array.h"
#include "renderer/buffers.h"

namespace TGL::GFX
{
    
    struct transform
    {
    public:
        transform() = default;
        transform(const glm::mat4& transform) : m_transform_matrix(transform) {}
        
        void set_transform(const glm::mat4& transform) { m_transform_matrix = transform; }
        
        void translate(const glm::vec3& translate)
        {
            m_position = translate;
            m_transform_matrix = glm::translate(m_transform_matrix, translate);
        }
        
        void rotate(const f32 angle, const glm::vec3& axis)
        {
            m_rotation = axis * angle;
            m_transform_matrix = glm::rotate(m_transform_matrix, glm::radians(angle), axis);
        }
        
        void rotate(const glm::vec3& rotation)
        {
            m_rotation = rotation;
            
            m_transform_matrix = glm::rotate(m_transform_matrix, glm::radians(rotation.x), {1.f, 0.f, 0.f});
            m_transform_matrix = glm::rotate(m_transform_matrix, glm::radians(rotation.y), {0.f, 1.f, 0.f});
            m_transform_matrix = glm::rotate(m_transform_matrix, glm::radians(rotation.z), {0.f, 0.f, 1.f});
        }
        
        void scale(const glm::vec3& scale)
        {
            m_scale = scale;
            m_transform_matrix = glm::scale(m_transform_matrix, scale);
        }
        
        glm::mat4 get_transform_matrix() const { return m_transform_matrix; }
        
        glm::vec3 get_position() const { return m_position; }
        glm::vec3 get_rotation() const { return m_rotation; }
        glm::vec3 get_scale() const { return m_scale; }
        
    private:
        glm::mat4 m_transform_matrix = glm::mat4(1.0f);
        
        glm::vec3 m_position = glm::vec3(0.0f);
        glm::vec3 m_rotation = glm::vec3(0.0f);
        glm::vec3 m_scale = glm::vec3(1.0f);
        
    };
    
    class render_object
    {
    public:
        render_object();
        ~render_object();
        
        void add_vertex_buffer(const std::shared_ptr<vertex_buffer>& vertex_buffer);
        void add_vertex_buffer(const vertex_buffer::vertex_buffer_info& vertex_buffer_info);
        
        void set_index_buffer(const std::shared_ptr<index_buffer>& index_buffer);
        void set_index_buffer(const index_buffer::index_buffer_info& index_buffer_info);
        
        void set_transform(const transform& new_transform) { m_transform = new_transform; }
        transform get_transform() const { return m_transform; }
        
        void translate(const glm::vec3& translation);
        void rotate(const f32 angle, const glm::vec3& axis);
        void rotate(const glm::vec3& rotation);
        void scale(const glm::vec3& scale);
        
        void bind() const;
        void unbind() const;
        
        buffer_id get_buffer_id() const
        {
            if (m_vertex_array)
                return m_vertex_array->get_id();
            
            TGL_CORE_ERROR("VERTEX ARRAY IS NULL");
            return -1;
        }
        
        i32 get_index_count() const  { return m_index_buffer->get_count(); }
        
    private:
        std::unique_ptr<vertex_array> m_vertex_array;
        std::vector<std::shared_ptr<vertex_buffer>> m_vertex_buffers;
        std::shared_ptr<index_buffer> m_index_buffer;
        
        transform m_transform;
        
    };
    
}
