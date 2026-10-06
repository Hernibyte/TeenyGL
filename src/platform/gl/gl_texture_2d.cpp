#include "platform/gl/gl_texture_2d.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "glad/gl.h"
#include "platform/assert.h"
#include "platform/log.h"

namespace TGL::GL
{
    gl_texture_2d::gl_texture_2d(const std::string& file_path)
    {
        stbi_set_flip_vertically_on_load(true);
        
        i32 width, height, channels;
        stbi_uc* data = stbi_load(file_path.c_str(), &width, &height, &channels, 0);
        TGL_CORE_ASSERT_LOG(data, "Failed to load image!");
        m_width = width; m_height = height;
        
        glGenTextures(1, &m_id);
        glBindTexture(GL_TEXTURE_2D, m_id);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        
        stbi_image_free(data);
    }

    gl_texture_2d::~gl_texture_2d()
    {
        glDeleteTextures(1, &m_id);
    }

    void gl_texture_2d::bind(u32 slot) const
    {
        glBindTextureUnit(slot, m_id);
    }
    
}
