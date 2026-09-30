#include "core/window.h"

#include <glad/gl.h>

#include "events/app_event.h"
#include "events/key_event.h"
#include "events/mouse_event.h"
#include "GLFW/glfw3.h"

#include "platform/log.h"
#include "platform/assert.h"

namespace TGL::CORE
{
    
    window::window(int width, int height, const char* title)
    {
        m_window_props.title = title;
        m_window_props.height = height;
        m_window_props.width = width;

        init();
    }

    window::window(window_info& info)
    {
        m_window_props.width = info.width;
        m_window_props.height = info.height;
        m_window_props.title = info.title;

        init();
    }
    
    window::~window()
    {
        if (m_window_props.window)
        {
            glfwDestroyWindow(m_window_props.window);
            glfwTerminate();
        }
    }
    
    void window::init()
    {
        LOG::logger::init();

        if (!glfwInit())
        {
            TGL_CORE_ASSERT_LOG(false, "Failed to initialize GLFW!");
        }
        TGL_CORE_INFO("GLFW initialized successfully!");
        
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

        // create window
        m_window_props.window = glfwCreateWindow(m_window_props.width, m_window_props.height, m_window_props.title, NULL, NULL);
        if (!m_window_props.window)
        {
            TGL_CORE_ASSERT_LOG(false, "Failed to create GLFW window!");
            glfwTerminate();
        }
        TGL_CORE_INFO("GLFW window created successfully!");
        
        glfwMakeContextCurrent(m_window_props.window);
        glfwSetWindowUserPointer(m_window_props.window, &m_window_props);
        
        // glfw callbacks
        glfwSetWindowSizeCallback(m_window_props.window, [](GLFWwindow* window, i32 width, i32 height)
        {
            window_props& props = *(window_props*)glfwGetWindowUserPointer(window);
            props.width = width;
            props.height = height;

            window_resize_event event(width, height);
            props.on_event(event);
        });

        glfwSetFramebufferSizeCallback(m_window_props.window, [](GLFWwindow* window, i32 width, i32 height)
        {
            window_props& props = *(window_props*)glfwGetWindowUserPointer(window);
            props.framebuffer_width = width;
            props.framebuffer_height = height;

            window_framebuffer_resize_event event(width, height);
            props.on_event(event);
        });

        glfwSetWindowCloseCallback(m_window_props.window, [](GLFWwindow* window)
        {
            window_props& props = *(window_props*)glfwGetWindowUserPointer(window);

            window_close_event event;
            props.on_event(event);
        });

        glfwSetWindowFocusCallback(m_window_props.window, [](GLFWwindow* window, i32 focused)
        {
            window_props& props = *(window_props*)glfwGetWindowUserPointer(window);

            if (focused)
            {
                TGL_CORE_INFO("Window gained focus");
            }
            else
            {
                TGL_CORE_INFO("Window lost focus");
            }

            window_focus_event event(focused);
            props.on_event(event);
        });

        glfwSetKeyCallback(m_window_props.window, [](GLFWwindow* window, i32 key, i32 scancode, i32 action, i32 mods)
        {
            window_props& props = *(window_props*)glfwGetWindowUserPointer(window);

            switch (action)
            {
                case GLFW_PRESS:
                {
                    key_pressed_event event(key, 0);
                    props.on_event(event);
                    break;
                }
                case GLFW_RELEASE:
                {
                    key_released_event event(key);
                    props.on_event(event);
                    break;
                }
                case GLFW_REPEAT:
                {
                    key_pressed_event event(key, 1);
                    props.on_event(event);
                    break;
                }
            }
        });

        glfwSetMouseButtonCallback(m_window_props.window, [](GLFWwindow* window, i32 button, i32 action, i32 mods)
        {
            window_props& props = *(window_props*)glfwGetWindowUserPointer(window);

            switch (action)
            {
                case GLFW_PRESS:
                {
                    mouse_button_pressed_event event(button);
                    props.on_event(event);
                    break;
                }
                case GLFW_RELEASE:
                {
                    mouse_button_released_event event(button);
                    props.on_event(event);
                    break;
                }
            }
        });

        glfwSetScrollCallback(m_window_props.window, [](GLFWwindow* window, f64 xoffset, f64 yoffset)
        {
            window_props& props = *(window_props*)glfwGetWindowUserPointer(window);

            mouse_scrolled_event event((f32)xoffset, (f32)yoffset);
            props.on_event(event);
        });

        glfwSetCursorPosCallback(m_window_props.window, [](GLFWwindow* window, f64 xpos, f64 ypos)
        {
            window_props& props = *(window_props*)glfwGetWindowUserPointer(window);

            mouse_moved_event event((f32)xpos, (f32)ypos);
            props.on_event(event);
        });
    }

    void window::close()
    {
        glfwSetWindowShouldClose(m_window_props.window, true);
    }

    bool window::should_close()
    {
        return glfwWindowShouldClose(m_window_props.window);
    }

    void window::swap_buffers() const
    {
        glfwSwapBuffers(m_window_props.window);
    }

    void window::poll_events() const
    {
        glfwPollEvents();
    }

    void window::set_vsync(bool state)
    {
        glfwSwapInterval(state);
        m_window_props.vsync = state;
    }

    f64 window::get_time() const
    {
        return glfwGetTime();
    }

    void* window::get_process_address() const
    {
        return glfwGetProcAddress;
    }

    bool window::get_key_pressed(i32 keycode) const
    {
        i32 state = glfwGetKey(m_window_props.window, keycode);
        return state == GLFW_PRESS || state == GLFW_REPEAT;
    }

    bool window::get_key_released(i32 keycode) const
    {
        return glfwGetKey(m_window_props.window, keycode) == GLFW_RELEASE;
    }

    bool window::get_mouse_button_pressed(i32 button) const
    {
        i32 state = glfwGetMouseButton(m_window_props.window, button);
        return state == GLFW_PRESS || state == GLFW_REPEAT;
    }

    bool window::get_mouse_button_released(i32 button) const
    {
        return glfwGetMouseButton(m_window_props.window, button) == GLFW_RELEASE;
    }

    std::pair<f64, f64> window::get_mouse_position() const
    {
        f64 xpos, ypos;
        glfwGetCursorPos(m_window_props.window, &xpos, &ypos);
        return std::make_pair((f64)xpos, (f64)ypos);
    }
    
}