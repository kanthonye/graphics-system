//
//  graphics-procedure.cpp
//  new-engine
//
//  Created by Kenneth Esdaile on 4/2/24.
//

#include "render-phase.hpp"
#include "render-process.hpp"

namespace kege{

    kege::CommandBuffer* RenderPhase::commandBuffer()
    {
        return _command_buffer.ref();
    }

    void RenderPhase::clearBuffers( const kege::vec4& color, float depth )
    {
        _command_buffer->clearColorAttachments({ color.x, color.y, color.z, color.w });
        _command_buffer->clearDepthAttachments({ depth });
    }

    void RenderPhase::clearBuffers()
    {
        _command_buffer->clearColorAttachments({ 0.11, 0.11, 0.14, 1.0 });
        _command_buffer->clearDepthAttachments({ 1.f });
    }

    void RenderPhase::setViewport( const kege::vec4& viewport )
    {
        _command_buffer->setViewport( viewport.x, viewport.y, viewport.z, viewport.w );
    }

    void RenderPhase::setViewport()
    {
        uint32_t height = _parent->renderTarget()->getFramebuffer()->height();
        uint32_t width = _parent->renderTarget()->getFramebuffer()->width();
        _command_buffer->setViewport( 0.f, 0.f, width, height );
    }

    void RenderPhase::setScissor( const kege::ivec4 &scissor )
    {
        _command_buffer->setScissor( scissor.x, scissor.y, scissor.z, scissor.w );
    }

    void RenderPhase::setScissor()
    {
        uint32_t height = _parent->renderTarget()->getFramebuffer()->height();
        uint32_t width = _parent->renderTarget()->getFramebuffer()->width();
        _command_buffer->setScissor( 0, 0, width, height );
    }

    RenderPhase::RenderPhase()
    {
        _command_buffer = kege::CommandBuffer::create({ kege::GRAPHICS_QUEUE, kege::SECONDARY_COMMAND_BUFFER });
    }

    RenderPhase::~RenderPhase()
    {
        _command_buffer.clear();
    }

}
