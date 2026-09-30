#pragma once

#include "renderer/render_object.h"
#include "renderer/shader.h"

namespace TGL::GFX::UTILS
{
    
    class render_object_preset
    {
    public:
        void set_shader_program_id(const shader_id shader_program_id) { m_shader_program_id = shader_program_id; }
        
        [[nodiscard]] std::shared_ptr<GFX::render_object> get_render_object() const { return m_render_object; }
        [[nodiscard]] shader_id get_shader_program_id() const { return m_shader_program_id; }
        
    protected:
        std::shared_ptr<GFX::render_object> m_render_object;
        shader_id m_shader_program_id = 0;
    };
    
    class triangle : public render_object_preset
    {
    public:
        explicit triangle();
    };
    
    class square : public render_object_preset
    {
    public:
        explicit square();
    };
    
    class cube : public render_object_preset
    {
    public:
        explicit cube();
    };
    
}
