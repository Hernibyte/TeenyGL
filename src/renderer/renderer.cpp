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

    void renderer::submit(const std::shared_ptr<render_object>& render_object, const std::shared_ptr<shader_program>& shader_program) const
    {
        shader_program->bind();
        
        shader_program->set_uniform_matrix4fv("u_view", m_camera->get_view());
        shader_program->set_uniform_matrix4fv("u_projection", m_camera->get_projection());
        shader_program->set_uniform_matrix4fv("u_model", render_object->get_transform().get_transform_matrix());
        
        render_object->bind();
        m_renderer_api->draw_indexed(render_object->get_index_count());
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
