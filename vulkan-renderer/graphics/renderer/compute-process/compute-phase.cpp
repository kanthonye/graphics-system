//
//  graphics-procedure.cpp
//  new-engine
//
//  Created by Kenneth Esdaile on 4/2/24.
//

#include "compute-phase.hpp"

namespace kege{

    kege::CommandBuffer* ComputePhase::commandBuffer()
    {
        return _command_buffer.ref();
    }

    ComputePhase::ComputePhase()
    {
        _command_buffer = kege::CommandBuffer::create({ kege::GRAPHICS_QUEUE, kege::SECONDARY_COMMAND_BUFFER });
    }

    ComputePhase::~ComputePhase()
    {
        _command_buffer.clear();
    }

}
