#include "renderer/render_objects/render_object_presets.h"

namespace TGL::GFX::UTILS
{
    
    triangle::triangle()
    {
        float vertices[3 * 3] = {
            -0.5f, -0.5f, 0.0f,
             0.5f, -0.5f, 0.0f,
             0.0f,  0.5f, 0.0f
        };  
    
        i32 indices[3] = {
            0, 1, 2
        };
    
        TGL::GFX::vertex_buffer::vertex_buffer_info vertex_buffer_info = {
            vertices,
            9 * sizeof(float),
{ {TGL::GFX::shader_data_type::float_3, "a_position"} }
        };
        
        TGL::GFX::index_buffer::index_buffer_info index_buffer_info = {
            indices, 
            3 * sizeof(u32)
        };
        
        m_render_object = std::make_shared<GFX::render_object>();
        m_render_object->add_vertex_buffer(vertex_buffer_info);
        m_render_object->set_index_buffer(index_buffer_info);
    }
    
    square::square()
    {
        float vertices[4 * 3] = {
            0.5f, 0.5f, 0.0f,
            0.5f, -0.5f, 0.0f,
            -0.5f,  -0.5f, 0.0f,
            -0.5f, 0.5f, 0.0f
        };
    
        i32 indices[3 * 2] = {
            0, 1, 3,
            1, 2, 3
        };
    
        TGL::GFX::vertex_buffer::vertex_buffer_info vertex_buffer_info = {
            vertices, 
            12 * sizeof(float),
            { { TGL::GFX::shader_data_type::float_3, "a_position" } }
        };
        
        TGL::GFX::index_buffer::index_buffer_info index_buffer_info = {
            indices, 
            6 * sizeof(i32)
        };
        
        m_render_object = std::make_shared<GFX::render_object>();
        m_render_object->add_vertex_buffer(vertex_buffer_info);
        m_render_object->set_index_buffer(index_buffer_info);
    }
    
    cube::cube()
    {
        f32 vertices[8 * 3] = {
            -0.5f, -0.5f,  0.5f,
             0.5f, -0.5f,  0.5f,
             0.5f,  0.5f,  0.5f,
            -0.5f,  0.5f,  0.5f,

            -0.5f, -0.5f, -0.5f,
             0.5f, -0.5f, -0.5f,
             0.5f,  0.5f, -0.5f,
            -0.5f,  0.5f, -0.5f
        };

        i32 indices[12 * 3] = {
            0, 1, 2,
            2, 3, 0,

            1, 5, 6,
            6, 2, 1,

            5, 4, 7,
            7, 6, 5,

            4, 0, 3,
            3, 7, 4,

            3, 2, 6,
            6, 7, 3,

            4, 5, 1,
            1, 0, 4
        };
        
        TGL::GFX::vertex_buffer::vertex_buffer_info vertex_buffer_info = {
            vertices, 
            sizeof(vertices),
            { { TGL::GFX::shader_data_type::float_3, "a_position" } }
        };
        
        TGL::GFX::index_buffer::index_buffer_info index_buffer_info = {
            indices, 
            sizeof(indices)
        };
        
        m_render_object = std::make_shared<GFX::render_object>();
        m_render_object->add_vertex_buffer(vertex_buffer_info);
        m_render_object->set_index_buffer(index_buffer_info);
    }
    
}