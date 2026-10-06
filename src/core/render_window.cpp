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

            out vec4 color;

            uniform vec4 u_color;
            
            void main()
            {
                color = u_color;
            }
        )";
        
        m_default_shader_program = GFX::shader_program::create(vertex_shader_source.c_str(), fragment_shader_source.c_str());
        
        const std::string texture_vertex_shader_source = R"(
            #version 330 core

            layout (location = 0) in vec3 a_position;
            layout (location = 1) in vec2 a_texture_coord;

            out vec2 v_texture_coord;

            uniform mat4 u_projection;
            uniform mat4 u_view;
            uniform mat4 u_model;

            void main()
            {
                v_texture_coord = a_texture_coord;
                gl_Position = u_projection * u_view * u_model * vec4(a_position, 1.0);
            }
        )";
    
        const std::string texture_fragment_shader_source = R"(
            #version 330 core

            out vec4 color;

            in vec2 v_texture_coord;

            uniform sampler2D u_texture;
            
            void main()
            {
                color = texture(u_texture, v_texture_coord);
            }
        )";
        
        m_textured_shader_program = GFX::shader_program::create(texture_vertex_shader_source.c_str(), texture_fragment_shader_source.c_str());
        
        triangle_shape = std::make_shared<GFX::UTILS::triangle>();
        triangle_shape->set_shader_program_id(m_default_shader_program->get_shader_program_id());
        
        square_shape = std::make_shared<GFX::UTILS::square>();
        square_shape->set_shader_program_id(m_default_shader_program->get_shader_program_id());
        
        //square_sprite = std::make_shared<GFX::UTILS::sprite>("pnggato.png");
        //square_sprite->set_shader_program_id(m_textured_shader_program->get_shader_program_id());
    }

    render_window::~render_window()
    {
        
    }

    void render_window::draw_triangle(f32 x, f32 y, f32 z, f32 r, f32 g, f32 b, f32 a) const
    {
        triangle_shape->set_position( { x, y, z } );
        triangle_shape->set_color( { r, g, b, a } );
        m_renderer->submit(
            triangle_shape,
            m_default_shader_program
        );
    }

    void render_window::draw_square(f32 x, f32 y, f32 z, f32 r, f32 g, f32 b, f32 a) const
    {
        square_shape->translate( { x, y, z } );
        square_shape->set_color( { r, g, b, a } );
        m_renderer->submit(
            square_shape,
            m_default_shader_program
        );
    }

    //void render_window::draw_sprite(f32 x, f32 y, f32 z, f32 r, f32 g, f32 b, f32 a) const
    //{
    //    square_sprite->set_position( { x, y, z } );
    //    square_sprite->set_color( { r, g, b, a } );
    //    square_sprite->bind_texture();
    //    m_textured_shader_program->set_int("u_texture", 0);
    //    m_renderer->submit(square_sprite, m_textured_shader_program);
    //}
    
}
