//
//  render-target-render-window.cpp
//  new-engine
//
//  Created by Kenneth Esdaile on 1/17/24.
//

#include "render-target-render-window.hpp"

namespace kege
{

    RenderWindowRenderTarget::RenderWindowRenderTarget( kege::RenderContext& render_context )
    {
        _context = &render_context;
    }
    
    const kege::ShaderResource* RenderWindowRenderTarget::getShaderResource()const
    {
        uint32_t index = _context->getCurrentFrameIndex() % MAX_BUFFER_COUNT;
        return _shader_resources[ index ].ref();
    }

    const kege::Framebuffer* RenderWindowRenderTarget::getFramebuffer()const
    {
        return _context->getFramebuffer();
    }
    
}

