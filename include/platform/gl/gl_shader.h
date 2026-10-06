#pragma once

#include "platform/default_types.h"
#include "renderer/shader.h"

namespace TGL::GL
{
    class gl_shader : public GFX::shader_program
    {
    public:
        virtual ~gl_shader() override;
        
        gl_shader(cstr_ptr vertex_source, cstr_ptr fragment_source);
        
        virtual void clear() override;
        virtual void bind() override;
        virtual void unbind() override;
        
        virtual bool set_matrix4fv(cstr_ptr name, const glm::mat4& matrix) override;
        virtual bool set_vec4f(cstr_ptr name, const glm::vec4& vector) override;
        virtual bool set_int(cstr_ptr name, const int& num) override;
        
    };
}
