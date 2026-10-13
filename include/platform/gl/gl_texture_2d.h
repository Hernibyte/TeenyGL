#pragma once
#include "renderer/texture.h"

namespace TGL::GL
{
    
    class gl_texture_2d : public GFX::texture_2d
    {
    public:
        explicit gl_texture_2d(const std::string& file_path);
        virtual ~gl_texture_2d() override;
        
        virtual void bind(const u32 slot = 0) const override;
    };
    
}
