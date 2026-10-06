#include "renderer/texture.h"

#include "platform/assert.h"
#include "platform/log.h"
#include "platform/gl/gl_texture_2d.h"
#include "renderer/renderer_api.h"

namespace TGL::GFX
{
    std::shared_ptr<texture_2d> texture_2d::create(const std::string& file_path)
    {
        switch (renderer_api::get_api())
        {
        case GFX::renderer_api::gfx_api::none:
            TGL_ASSERT_LOG(false, "RENDER BUFFER: [NONE] Platform not supported!");
            break;
        
        case GFX::renderer_api::gfx_api::opengl:
            //
            return std::make_shared<GL::gl_texture_2d>(file_path);
            break;
        
        default:
            TGL_ASSERT_LOG(false, "RENDER BUFFER: Platform not supported!");
            break;
        }
            
        return nullptr;    
    }
    
}
