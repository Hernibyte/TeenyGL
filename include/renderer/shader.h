#pragma once

#include <memory>
#include <string>

#include "glm/fwd.hpp"
#include "platform/default_types.h"

namespace TGL::GFX
{

    class shader_program
    {
    public:
        virtual ~shader_program() {};

        static std::shared_ptr<shader_program> create(cstr_ptr vertex_source, cstr_ptr fragment_source);
        
        virtual void clear() = 0;
        virtual void bind() = 0;
        virtual void unbind() = 0;
        
        virtual bool set_matrix4fv(cstr_ptr name, const glm::mat4& matrix) = 0;
        virtual bool set_vec4f(cstr_ptr name, const glm::vec4& vector) = 0;
        
        shader_id get_shader_program_id() const { return m_shader_program_id; }
        std::string get_vertex_source() const { return m_vertex_source; }
        std::string get_fragment_source() const { return m_fragment_source; }

    protected:
        shader_id m_shader_program_id = -1;
        
        std::string m_vertex_source;
        std::string m_fragment_source;
    };

}