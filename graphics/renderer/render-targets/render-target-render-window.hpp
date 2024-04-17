//
//  render-target-render-window.hpp
//  new-engine
//
//  Created by Kenneth Esdaile on 1/17/24.
//

#ifndef render_target_render_window_hpp
#define render_target_render_window_hpp

#include "render-target.hpp"
#include "render-context.hpp"

namespace kege{

    class RenderWindowRenderTarget : public kege::RenderTarget
    {
    public:

        RenderWindowRenderTarget( kege::RenderContext& render_context );
        const kege::ShaderResource* getShaderResource()const;
        const kege::Framebuffer* getFramebuffer()const;

    private:

        kege::RenderContext* _context;
        enum{ MAX_BUFFER_COUNT = 2};
        kege::Ref< kege::ShaderResource > _shader_resources[ MAX_BUFFER_COUNT ];
    };

}

#endif /* render_target_render_window_hpp */
