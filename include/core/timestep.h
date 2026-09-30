#pragma once
#include <memory>

#include "renderer/camera.h"

namespace CORE::TIME
{
    
    class timestep
    {
    public:
        timestep(float time = 0.f) : m_time(time) {}

        operator float() const { return m_time; }
        
        [[nodiscard]] float get_seconds() const { return m_time; }
        [[nodiscard]] float get_milliseconds() const { return m_time * 1000.f; }
        
    private:
        float m_time;
        
    };
    
}
