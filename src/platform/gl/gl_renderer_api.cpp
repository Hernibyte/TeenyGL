#include "platform/gl/gl_renderer_api.h"

extern "C" 
{
    #include "glad/gl.h"
}
#include "platform/assert.h"
#include "platform/log.h"

namespace TGL::GL
{
    void gl_renderer_api::init(void* process_address_ptr) const
    {
        int status = gladLoadGL((GLADloadfunc)process_address_ptr);
        TGL_CORE_ASSERT_LOG(status, "Failed to initialize Glad!");
        
        TGL_INFO("Glad initialized successfully!");
    }

    void gl_renderer_api::draw_indexed(buffer_id vertex_array_id, i32 index_count) const
    {
        glBindVertexArray(vertex_array_id);
        glDrawElements(GL_TRIANGLES, index_count, GL_UNSIGNED_INT, nullptr);
    }

    void gl_renderer_api::clear_color(const f32 red, const f32 green, const f32 blue, const f32 alpha) const
    {
        glClearColor(red, green, blue, alpha);
    }

    void gl_renderer_api::clear(const i32 mask) const
    {
        glClear(mask);
    }
    
}
