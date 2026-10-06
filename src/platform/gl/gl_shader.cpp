#include "platform/gl/gl_shader.h"

#include "glad/gl.h"
#include "glm/gtc/type_ptr.hpp"

#include "platform/log.h"

namespace TGL::GL
{
    
    gl_shader::gl_shader(cstr_ptr vertex_source, cstr_ptr fragment_source)
    {
        m_vertex_source = vertex_source;
        m_fragment_source = fragment_source;
        
        shader_id shader_vertex_id = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(shader_vertex_id, 1, &vertex_source, NULL);
        glCompileShader(shader_vertex_id);
        
        shader_id shader_fragment_id = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(shader_fragment_id, 1, &fragment_source, NULL);
        glCompileShader(shader_fragment_id);
        
        i32 success = true;
        glGetShaderiv(shader_vertex_id, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            char info_log[512];
            glGetShaderInfoLog(shader_vertex_id, 512, NULL, info_log);
            TGL_CORE_ERROR("Vertex shader compilation failed: {0}", info_log);
        }
        
        glGetShaderiv(shader_fragment_id, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            char info_log[512];
            glGetShaderInfoLog(shader_fragment_id, 512, NULL, info_log);
            TGL_CORE_ERROR("Fragment shader compilation failed: {0}", info_log);
        }
        
        shader_id shader_program_id = glCreateProgram();
        glAttachShader(shader_program_id, shader_vertex_id);
        glAttachShader(shader_program_id, shader_fragment_id);
        glLinkProgram(shader_program_id);

        glGetProgramiv(shader_program_id, GL_LINK_STATUS, &success);
        if (!success)
        {
            char info_log[512];
            glGetProgramInfoLog(shader_program_id, 512, NULL, info_log);
            TGL_CORE_ERROR("Shader program linking failed: {0}", info_log);
        }

        glDeleteShader(shader_vertex_id);
        glDeleteShader(shader_fragment_id);

        m_shader_program_id = shader_program_id;
    }
    
    gl_shader::~gl_shader()
    {
        gl_shader::clear();
    }

    void gl_shader::clear()
    {
        glDeleteProgram(m_shader_program_id);
    }

    void gl_shader::bind()
    {
        glUseProgram(m_shader_program_id);
    }

    void gl_shader::unbind()
    {
        glUseProgram(0);
    }

    bool gl_shader::set_matrix4fv(cstr_ptr name, const glm::mat4& matrix)
    {
        const i32 u_location = glGetUniformLocation(m_shader_program_id, name);
        if (u_location == -1) return false;
        
        glUniformMatrix4fv(u_location, 1, GL_FALSE, glm::value_ptr(matrix));
        return true;
    }

    bool gl_shader::set_vec4f(cstr_ptr name, const glm::vec4& vector)
    {
        const i32 u_location = glGetUniformLocation(m_shader_program_id, name);
        if (u_location == -1) return false;
        
        glUniform4f(u_location, vector.x, vector.y, vector.z, vector.w);
        return true;
    }

    bool gl_shader::set_int(cstr_ptr name, const int& num)
    {
        const i32 u_location = glGetUniformLocation(m_shader_program_id, name);
        if (u_location == -1) return false;
        
        glUniform1i(u_location, num);
        return true;
    }
}
