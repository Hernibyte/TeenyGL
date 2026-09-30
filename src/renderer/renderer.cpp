#include "renderer/renderer.h"

#include "glad/gl.h"
#include "glm/gtc/type_ptr.hpp"

namespace TGL::GFX
{

    renderer::renderer(CORE::window* in_window)
    {
        m_window = in_window;
        
        m_renderer_api = renderer_api::create();
        m_renderer_api->init(m_window->get_process_address());
        
        m_camera = std::make_shared<camera>(45.f, (float)m_window->get_width() / (float)m_window->get_height(), 0.1f, 100.f);
        //m_camera = std::make_shared<camera>(-1.f, 1.f, -1.f, 1.f, -100.f, 100.f);
    }

    void renderer::draw_indexed(buffer_id vertex_array_id, i32 index_count, shader_id shader_program_id) const
    {
        glUseProgram(shader_program_id);
        
        // set camera
        i32 u_view_location = glGetUniformLocation(shader_program_id, "u_view");
        i32 u_projection_location = glGetUniformLocation(shader_program_id, "u_projection");
        
        glUniformMatrix4fv(u_view_location, 1, GL_FALSE, glm::value_ptr(m_camera->get_view()));
        glUniformMatrix4fv(u_projection_location, 1, GL_FALSE, glm::value_ptr(m_camera->get_projection()));
        
        m_renderer_api->draw_indexed(vertex_array_id, index_count);
    }

    void renderer::set_camera(const std::shared_ptr<camera>& in_camera)
    {
        m_camera = in_camera;
    }

    void renderer::clear_color(const f32 red, const f32 green, const f32 blue, const f32 alpha) const
    {
        m_renderer_api->clear_color(red, green, blue, alpha);
    }

    void renderer::clear(const i32 mask) const
    {
        m_renderer_api->clear(mask);
    }
    
}
