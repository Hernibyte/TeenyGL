#pragma once

#include "platform/default_types.h"
#include "events/event.h"
#include "glm/gtx/io.hpp"

struct GLFWwindow;

namespace TGL::CORE
{

    struct window_info
    {
        i32 width;
        i32 height;
        const char* title;
    };

    class window
    {
    public:
        window(i32 width, i32 height, cstr_ptr title);
        explicit window(window_info& info);
        ~window();
        
        void set_on_event_callback(event::callback_fn callback) { m_window_props.on_event = callback; }
        
        void close();
        bool should_close();
        
        void swap_buffers() const;
        void poll_events() const;
        
        void* get_process_address() const;

        bool get_key_pressed(i32 keycode) const;
        bool get_key_released(i32 keycode) const;
        bool get_mouse_button_pressed(i32 button) const;
        bool get_mouse_button_released(i32 button) const;
        std::pair<f64, f64> get_mouse_position() const;
        f64 get_mouse_x() const { return get_mouse_position().first; }
        f64 get_mouse_y() const { return get_mouse_position().second; }
        
        i32 get_width() const { return m_window_props.width; };
        i32 get_height() const { return m_window_props.height; };

    private:
        struct window_props
        {
            GLFWwindow* window = nullptr;
            i32 width;
            i32 height;
            i32 framebuffer_width;
            i32 framebuffer_height;
            const char* title;
            event::callback_fn on_event;
        };
        window_props m_window_props;

        void init();
    };
    
}