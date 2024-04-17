//
//  compute-process.cpp
//  new-engine
//
//  Created by Kenneth Esdaile on 4/2/24.
//

#include "compute-process.hpp"

namespace kege{

    void ComputeProcess::begin( int compute_index )
    {
        _phase_count = 0;
        _compute_index = compute_index;

        _command_buffer->begin();
    }

    void ComputeProcess::end()
    {
        _command_buffer->executeSecondaryCommandBuffers( _secondary_command_buffers );
        //_command_buffer->endRenderpass();
        _command_buffer->end();
        _secondary_command_buffers.clear();
    }

    void ComputeProcess::endComputePhase( kege::ComputePhase* phase )
    {
        if ( phase->_parent == this )
        {
            _secondary_command_buffers.push_back( phase->_command_buffer.ref() );
        }
    }

    kege::ComputePhase* ComputeProcess::beginComputePhase()
    {
        kege::ComputePhase* phase = nullptr;
        if( _phases.size() <= _phase_count )
        {
            phase = new kege::ComputePhase;
            _phases.push_back( phase );
        }
        else
        {
            phase = _phases[ _phase_count ].ref();
        }
        phase->_parent = this;
        phase->_command_buffer->setSecondaryCommandBufferInheritanceInfo( *_command_buffer );
        return phase;
    }


    ComputeProcess::ComputeProcess()
    {
        _command_buffer = kege::CommandBuffer::create({ kege::GRAPHICS_QUEUE, kege::PRIMARY_COMMAND_BUFFER });
    }

    ComputeProcess::~ComputeProcess()
    {
        _phases.clear();
        _secondary_command_buffers.clear();
        _command_buffer.clear();
    }

}
