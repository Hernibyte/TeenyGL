#include "renderer/shader.h"

#include "platform/gl/gl_shader.h"
#include "renderer/renderer.h"
#include "platform/assert.h"

namespace TGL::GFX
{
    
    shader_program::shader_program(cstr_ptr vertex_source, cstr_ptr fragment_source)
    {
        
        m_vertex_source = vertex_source;
        m_fragment_source = fragment_source;

        switch (renderer_api::get_api())
        {
            case GFX::renderer_api::gfx_api::none:
                TGL_ASSERT_LOG(false, "RENDER CONTEXT: [NONE] Platform not supported!");
            break;
            
            case GFX::renderer_api::gfx_api::opengl:
                m_shader_program_id = GL::gl_shader::create(vertex_source, fragment_source);
            break;

            default:
                break;
        }
    }

    shader_program::~shader_program()
    {
        switch (renderer_api::get_api())
        {
            case GFX::renderer_api::gfx_api::none:
                TGL_ASSERT_LOG(false, "RENDER CONTEXT: [NONE] Platform not supported!");
            break;
            
            case GFX::renderer_api::gfx_api::opengl:
                GL::gl_shader::clear(m_shader_program_id);
            break;

            default:
                break;
        }
    }

}