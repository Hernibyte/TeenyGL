#pragma once 

#include "render_object.h"
#include "shader.h"
#include "core/window.h"
#include "platform/default_types.h"
#include "renderer/renderer_api.h"
#include "renderer/camera.h"

namespace TGL::GFX
{
    
    class renderer
    {
    public:
        renderer() = delete;
        renderer(CORE::window* in_window);
        
        void submit(const std::shared_ptr<render_object>& render_object, const std::shared_ptr<shader_program>& shader_program) const;
        
        void set_camera(const std::shared_ptr<camera>& in_camera);
        
        void clear_color(const  f32 red, const f32 green, const f32 blue, const f32 alpha) const;
        void clear(const  i32 mask) const;
        
        std::shared_ptr<camera> get_camera() const { return m_camera; };
        
    private:
        std::unique_ptr<renderer_api> m_renderer_api;
        
        CORE::window* m_window;
        std::shared_ptr<camera> m_camera;
    };

}
