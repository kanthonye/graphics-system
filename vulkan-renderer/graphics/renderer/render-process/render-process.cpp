//
//  graphics-process.cpp
//  new-engine
//
//  Created by Kenneth Esdaile on 4/2/24.
//

#include "render-process.hpp"
namespace kege{

    void RenderProcess::begin( kege::RenderTarget* render_target, int render_index )
    {
        _phase_count = 0;
        _render_index = render_index;
        _render_target = render_target;

        _command_buffer->begin();
        _command_buffer->beginRenderpass( render_target->getFramebuffer(), kege::SUBPASS_CONTENTS_SECONDARY_COMMAND_BUFFERS );
    }

    void RenderProcess::endRenderPhase( kege::RenderPhase* phase )
    {
        if ( phase->_parent == this )
        {
            phase->_command_buffer->end();
            _secondary_command_buffers.push_back( phase->_command_buffer.ref() );
        }
    }
    
    const kege::RenderTarget* RenderProcess::renderTarget()const
    {
        return _render_target.ref();
    }

    kege::RenderTarget* RenderProcess::renderTarget()
    {
        return _render_target.ref();
    }

    kege::RenderPhase* RenderProcess::beginRenderPhase()
    {
        kege::RenderPhase* phase = nullptr;
        if( _phases.size() <= _phase_count )
        {
            phase = new kege::RenderPhase;
            _phases.push_back( phase );
        }
        else
        {
            phase = _phases[ _phase_count ].ref();
        }
        _phase_count++;
        phase->_parent = this;
        phase->_command_buffer->setSecondaryCommandBufferInheritanceInfo( *_command_buffer );
        phase->_command_buffer->begin();
        return phase;
    }


    RenderProcess::RenderProcess()
    {
        _command_buffer = kege::CommandBuffer::create({ kege::GRAPHICS_QUEUE, kege::PRIMARY_COMMAND_BUFFER });
    }

    RenderProcess::~RenderProcess()
    {
        _render_target.clear();
        _phases.clear();
        _secondary_command_buffers.clear();
        _command_buffer.clear();
    }

    void RenderProcess::end()
    {
        _command_buffer->executeSecondaryCommandBuffers( _secondary_command_buffers );
        _command_buffer->endRenderpass();
        _command_buffer->end();
        _secondary_command_buffers.clear();
    }
}
