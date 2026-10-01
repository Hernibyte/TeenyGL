#include "core/render_window.h"

namespace TGL::CORE
{
    
    render_window::render_window(i32 width, i32 height, cstr_ptr title)
    {
        m_window = std::make_shared<CORE::window>(width, height, title);
        m_renderer = std::make_shared<GFX::renderer>(m_window.get());
        
        const std::string vertex_shader_source = R"(
            #version 330 core

            layout (location = 0) in vec3 a_position;

            uniform mat4 u_projection;
            uniform mat4 u_view;
            uniform mat4 u_model;

            void main()
            {
                gl_Position = u_projection * u_view * u_model * vec4(a_position, 1.0);
            }
        )";
    
        const std::string fragment_shader_source = R"(
            #version 330 core

            out vec4 out_Color;
            
            void main()
            {
                out_Color = vec4(0.8, 0.2, 0.3, 1.0);
            }
        )";
        
        m_default_shader_program = GFX::shader_program::create(vertex_shader_source.c_str(), fragment_shader_source.c_str());
        
        triangle_shape = std::make_shared<GFX::UTILS::triangle>();
        triangle_shape->set_shader_program_id(m_default_shader_program->get_shader_program_id());
        
        square_shape = std::make_shared<GFX::UTILS::square>();
        square_shape->set_shader_program_id(m_default_shader_program->get_shader_program_id());
    }

    render_window::~render_window()
    {
        
    }

    void render_window::draw_triangle(f32 x, f32 y, f32 z) const
    {
        m_renderer->submit(
            triangle_shape,
            m_default_shader_program
        );
    }

    void render_window::draw_square(f32 x, f32 y, f32 z) const
    {
        m_renderer->submit(
            square_shape,
            m_default_shader_program
        );
    }
    
}
