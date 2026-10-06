#include "renderer/shader.h"

#include "platform/gl/gl_shader.h"
#include "renderer/renderer.h"
#include "platform/assert.h"

namespace TGL::GFX
{
    
    std::shared_ptr<shader_program> shader_program::create(cstr_ptr vertex_source, cstr_ptr fragment_source)
    {
        switch (renderer_api::get_api())
        {
            case GFX::renderer_api::gfx_api::none:
                TGL_ASSERT_LOG(false, "SHADER PROGRAM: [NONE] Platform not supported!");
            break;
            
        case GFX::renderer_api::gfx_api::opengl:
                return std::make_shared<GL::gl_shader>(vertex_source, fragment_source);
            break;

            default:
                TGL_ASSERT_LOG(false, "SHADER PROGRAM: Platform not supported!");
                break;
        }
        
        return nullptr;
    }
    
}
