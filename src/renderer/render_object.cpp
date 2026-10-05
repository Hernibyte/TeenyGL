#include "renderer/render_object.h"

#include "glm/gtx/transform.hpp"

namespace TGL::GFX
{
    
    render_object::render_object()
    {
        m_vertex_array = vertex_array::create();
        m_vertex_array->bind();
        m_vertex_array->unbind();
    }

    render_object::~render_object()
    {
        
    }

    void render_object::add_vertex_buffer(const std::shared_ptr<vertex_buffer>& vertex_buffer)
    {
        bind();
        m_vertex_buffers.push_back(vertex_buffer);
        unbind();
    }

    void render_object::add_vertex_buffer(const vertex_buffer::vertex_buffer_info& vertex_buffer_info)
    {
        bind();
        m_vertex_buffers.push_back(vertex_buffer::create(vertex_buffer_info));
        unbind();
    }

    void render_object::set_index_buffer(const std::shared_ptr<index_buffer>& index_buffer)
    {
        bind();
        m_index_buffer = index_buffer;
        unbind();
    }

    void render_object::set_index_buffer(const index_buffer::index_buffer_info& index_buffer_info)
    {
        bind();
        m_index_buffer = index_buffer::create(index_buffer_info);
        unbind();
    }

    void render_object::translate(const glm::vec3& translation)
    {
        m_transform.translate(translation);
    }

    void render_object::set_position(const glm::vec3& position)
    {
        m_transform.set_position(position);
    }

    void render_object::rotate(const f32 angle, const glm::vec3& axis)
    {
        m_transform.rotate(angle, axis);
    }

    void render_object::rotate(const glm::vec3& rotation)
    {
        m_transform.rotate(rotation);
    }

    void render_object::scale(const glm::vec3& scale)
    {
       m_transform.scale(scale);
    }

    void render_object::bind() const
    {
        m_vertex_array->bind();
    }

    void render_object::unbind() const
    {
        m_vertex_array->unbind();
    }
    
}
