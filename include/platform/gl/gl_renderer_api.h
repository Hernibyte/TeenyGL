#pragma once 

#include "renderer/renderer_api.h"

namespace TGL::GL
{
    
    class gl_renderer_api : public GFX::renderer_api
    {
    public:
        virtual void init(void* process_address_ptr) const override;
        
        virtual void draw_indexed(const i32 index_count) const override;
        
        virtual void clear_color(const f32 red, const f32 green, const f32 blue, const f32 alpha) const override;
        virtual void clear(const i32 mask) const override;
        
    };
    
}