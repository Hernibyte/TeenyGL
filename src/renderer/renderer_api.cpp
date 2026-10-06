#include "renderer/renderer_api.h"

#include "platform/assert.h"
#include "platform/log.h"
#include "platform/gl/gl_renderer_api.h"

namespace TGL::GFX
{
    renderer_api::gfx_api renderer_api::s_gfx_api = gfx_api::opengl;

    renderer_api::~renderer_api()
    {
        
    }

    std::unique_ptr<renderer_api> renderer_api::create()
    {
        switch (renderer_api::get_api())
        {
        case GFX::renderer_api::gfx_api::none:
            TGL_ASSERT_LOG(false, "RENDER BUFFER: [NONE] Platform not supported!");
            break;
        
        case GFX::renderer_api::gfx_api::opengl:
            //
            return std::make_unique<GL::gl_renderer_api>();
            break;
        
        default:
            TGL_ASSERT_LOG(false, "RENDER BUFFER: Platform not supported!");
            break;
        }
            
        return nullptr;
    }
    
}
