#pragma once 

#include <memory>

#include "platform/default_types.h"

#define TGL_COLOR_BUFFER_BIT 0x00004000
#define TGL_DEPTH_BUFFER_BIT 0x00000100
#define TGL_STENCIL_BUFFER_BIT 0x00000400

namespace TGL::GFX
{
    
    class renderer_api
    {
    public:
        enum class gfx_api
        {
            none = 0,
            opengl = 1
        };
        
        virtual ~renderer_api();
        
        virtual void init(void* process_address_ptr) const = 0;
        virtual void draw_indexed(buffer_id vertex_array_id, i32 index_count) const = 0;
        virtual void clear_color(const  f32 red, const f32 green, const f32 blue, const f32 alpha) const = 0;
        virtual void clear(const  i32 mask) const = 0;
        
        static std::unique_ptr<renderer_api> create();
        static gfx_api get_api() { return s_gfx_api; }
        
    private:
        static gfx_api s_gfx_api;
        
    };
    
}
