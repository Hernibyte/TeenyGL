#pragma once

#include <memory>
#include <string>

#include "platform/default_types.h"

namespace TGL::GFX
{
    
    class texture
    {
    public:
        virtual ~texture() = default;
        
        virtual i32 get_width() const { return m_width; };
        virtual i32 get_height() const { return m_height; };
        
        virtual void bind(u32 slot = 0) const = 0;
    
    protected:
        std::string m_file_path;
        
        i32 m_width = 0;
        i32 m_height = 0;
        u32 m_id = -1;
    };
    
    class texture_2d : public texture
    {
    public:
        static std::shared_ptr<texture_2d> create(const std::string& file_path);
    };
    
}
