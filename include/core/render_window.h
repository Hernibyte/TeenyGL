#pragma once

#include "core/window.h"
#include "renderer/renderer.h"
#include "platform/default_types.h"
#include "renderer/render_objects/render_object_presets.h"

namespace TGL::CORE
{
    
    class render_window
    {
    public:
        render_window(i32 width, i32 height, cstr_ptr title);
        ~render_window();
        
        void draw_triangle(f32 x, f32 y, f32 z) const;
        void draw_square(f32 x, f32 y, f32 z) const;
        
        std::shared_ptr<CORE::window> get_window() const { return m_window; };
        std::shared_ptr<GFX::renderer> get_renderer() const { return m_renderer; };
        
    private:
        std::shared_ptr<CORE::window> m_window;
        std::shared_ptr<GFX::renderer> m_renderer;
        
        std::shared_ptr<GFX::shader_program> m_default_shader_program;
        std::shared_ptr<GFX::UTILS::triangle> triangle_shape;
        std::shared_ptr<GFX::UTILS::square> square_shape;
        
    };
    
}
