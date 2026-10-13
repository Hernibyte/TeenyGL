#include "renderer/renderer.h"

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

    void renderer::begin_scene()
    {
        
    }

    void renderer::end_scene()
    {
        flush();
        m_render_objects.clear();
        m_shader_programs.clear();
    }

    void renderer::submit(const std::shared_ptr<render_object>& render_object, const std::shared_ptr<shader_program>& shader_program)
    {
        m_render_objects.insert({ render_object->get_buffer_id(), { render_object, shader_program->get_shader_program_id() } });
        m_shader_programs.insert({ shader_program->get_shader_program_id(), shader_program });
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

    void renderer::set_viewport(const i32 x, const i32 y, const i32 width, const i32 height) const
    {
        m_renderer_api->set_viewport(x, y, width, height);
    }

    void renderer::flush()
    {
        for (auto& shader_program : m_shader_programs)
        {
            shader_program.second->bind();
            
            shader_program.second->set_matrix4fv("u_view", m_camera->get_view());
            shader_program.second->set_matrix4fv("u_projection", m_camera->get_projection());
            
            for (auto& render_object : m_render_objects)
            {
                if (render_object.second.second != shader_program.first) continue;
                
                 shader_program.second->set_matrix4fv("u_model", render_object.second.first->get_transform()->get_transform_matrix());
                 shader_program.second->set_vec4f("u_color", render_object.second.first->get_color());
                
                render_object.second.first->bind();
                
                m_renderer_api->draw_indexed(render_object.second.first->get_index_count());
            }
        }
    }
    
}
