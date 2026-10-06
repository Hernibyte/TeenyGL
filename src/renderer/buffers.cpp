#include "renderer/buffers.h"

#include "glad/gl.h"

#include "platform/assert.h"
#include "platform/log.h"
#include "renderer/renderer_api.h"
#include "platform/gl/gl_buffers.h"

namespace TGL::GFX
{
    
    u32 shader_data_type_size(const shader_data_type type)
    {
        switch (type)
        {
            case shader_data_type::none:    return 0;
            case shader_data_type::float_1: return 4;
            case shader_data_type::float_2: return 4 * 2;
            case shader_data_type::float_3: return 4 * 3;
            case shader_data_type::float_4: return 4 * 4;
            case shader_data_type::mat_3:   return 4 * 3 * 3;
            case shader_data_type::mat_4:   return 4 * 4 * 4;
            case shader_data_type::int_1:   return 4;
            case shader_data_type::int_2:   return 4 * 2;
            case shader_data_type::int_3:   return 4 * 3;
            case shader_data_type::int_4:   return 4 * 4;
            case shader_data_type::bool_1:  return 1;
        }
        
        TGL_CORE_ASSERT(false, "Unknown shader data type");
        return 0;
    }
    
    u32 shader_data_type_to_glsl_type(const shader_data_type type)
    {
        switch (type)
        {
            case shader_data_type::none:    return 0;
            case shader_data_type::float_1: return GL_FLOAT;
            case shader_data_type::float_2: return GL_FLOAT;
            case shader_data_type::float_3: return GL_FLOAT;
            case shader_data_type::float_4: return GL_FLOAT;
            case shader_data_type::mat_3:   return GL_FLOAT;
            case shader_data_type::mat_4:   return GL_FLOAT;
            case shader_data_type::int_1:   return GL_INT;
            case shader_data_type::int_2:   return GL_INT;
            case shader_data_type::int_3:   return GL_INT;
            case shader_data_type::int_4:   return GL_INT;
            case shader_data_type::bool_1:  return GL_BOOL;
        }
        
        TGL_CORE_ASSERT(false, "Unknown shader data type");
        return 0;
    }
    
    vertex_attributes::vertex_attributes(const shader_data_type type, const std::string& name, const bool normalized)
        : m_name(name), m_type(type), m_normalized(normalized), m_size(shader_data_type_size(type)), m_offset(0) {}

    
    /////////////////////////////////////////////////////////////////
    // VERTEX BUFFER ////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////

    std::shared_ptr<vertex_buffer> vertex_buffer::create(const vertex_buffer_info& info)
    {
        return create(info.vertices, info.size, info.layout);
    }
    
    std::shared_ptr<vertex_buffer> vertex_buffer::create(const f32* vertices, const i32 size, const vertex_attributes_layout& attributes_layout)
    {
        switch (renderer_api::get_api())
        {
        case GFX::renderer_api::gfx_api::none:
            TGL_ASSERT_LOG(false, "RENDER BUFFER: [NONE] Platform not supported!");
            break;
        
        case GFX::renderer_api::gfx_api::opengl:
            //
            return std::make_shared<GL::gl_vertex_buffer>(vertices, size, attributes_layout);
            break;
        
        default:
            TGL_ASSERT_LOG(false, "RENDER BUFFER: Platform not supported!");
            break;
        }
            
        return nullptr;
    }
    
    /////////////////////////////////////////////////////////////////
    // INDEX BUFFER /////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////
    
    std::shared_ptr<index_buffer> index_buffer::create(const index_buffer_info& info)
    {
        return create(info.indices, info.count);
    }
    
    std::shared_ptr<index_buffer> index_buffer::create(const i32* indices, const i32 count)
    {
        switch (renderer_api::get_api())
        {
        case GFX::renderer_api::gfx_api::none:
            TGL_ASSERT_LOG(false, "RENDER BUFFER: [NONE] Platform not supported!");
            break;
        
        case GFX::renderer_api::gfx_api::opengl:
            //
            return std::make_shared<GL::gl_index_buffer>(indices, count);
            break;
        
        default:
            TGL_ASSERT_LOG(false, "RENDER BUFFER: Platform not supported!");
            break;
        }
            
        return nullptr;
    }

}