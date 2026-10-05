#include "TinyGL.h"
#include "core/timestep.h"
#include "events/app_event.h"
#include "events/key_event.h"
#include "events/mouse_event.h"

namespace
{
    bool on_window_resize(const TGL::window_resize_event& resize_event)
    {
        TGL_INFO("Window resized to: x={0}, y={1}", resize_event.get_width(), resize_event.get_height());
        return true;
    }
    
    bool on_key_pressed(const TGL::key_pressed_event& key_event)
    {
        TGL_INFO("Key pressed: {0}", key_event.get_keycode());
        return true;
    }
    
    bool on_mouse_moved(const TGL::mouse_moved_event& mouse_event)
    {
        TGL_INFO("Mouse move to: x={0}, y={1}", mouse_event.get_x(), mouse_event.get_y());
        return true;
    }
    
    bool on_mouse_scrolled(const TGL::mouse_scrolled_event& scroll_event)
    {
        TGL_INFO("Mouse scrolled by: x={0}, y={1}", scroll_event.get_x_offset(), scroll_event.get_y_offset());
        return true;
    }
    
    bool on_mouse_button_pressed(const TGL::mouse_button_pressed_event& button_event)
    {
        TGL_INFO("Mouse button pressed: {0}", button_event.get_mouse_button());
        return true;
    }
    
    bool on_mouse_button_released(const TGL::mouse_button_released_event& button_event)
    {
        TGL_INFO("Mouse button released: {0}", button_event.get_mouse_button());
        return true;
    }
    
    bool on_window_framebuffer_resize(const TGL::window_framebuffer_resize_event& framebuffer_event)
    {
        TGL_INFO("Window framebuffer resized to: x={0}, y={1}", framebuffer_event.get_width(), framebuffer_event.get_height());
        return true;
    }

    void on_event(TGL::event& e)
    {
        TGL::event_handler handler(e);
        
        handler.dispatch<TGL::window_resize_event>(on_window_resize);
        handler.dispatch<TGL::key_pressed_event>(on_key_pressed);
        handler.dispatch<TGL::mouse_moved_event>(on_mouse_moved);
        handler.dispatch<TGL::mouse_scrolled_event>(on_mouse_scrolled);
        handler.dispatch<TGL::mouse_button_pressed_event>(on_mouse_button_pressed);
        handler.dispatch<TGL::mouse_button_released_event>(on_mouse_button_released);
        handler.dispatch<TGL::window_framebuffer_resize_event>(on_window_framebuffer_resize);
    }
    
}

int main()
{
    TGL::CORE::render_window app{800, 600, "TinyGL Example"};
    app.get_window()->set_on_event_callback(on_event);
    
    float last_frame_time = 0.f;
    
    while (!app.get_window()->should_close())
    {
        float time = (float)app.get_window()->get_time();
        CORE::TIME::timestep ts = time - last_frame_time;
        last_frame_time = time;
        
        TGL_INFO("Delta time: {0}s ({1}ms)", ts.get_seconds(), ts.get_milliseconds());
        
        // Render your scene here
        app.get_renderer()->clear_color(0.2f, 0.3f, 0.3f, 1.0f);
        app.get_renderer()->clear(TGL_COLOR_BUFFER_BIT | TGL_DEPTH_BUFFER_BIT);
        app.draw_triangle(.0f, 1.0f, .0f);
        //app.draw_square(-1.0f, -1.0f, -1.0f);
        
        app.get_window()->swap_buffers();
        app.get_window()->poll_events();
    }

    return 0;
}
