//
//  command-buffer.cpp
//  new-engine
//
//  Created by Kenneth Esdaile on 1/3/24.
//

#include "../../../graphics/initializer/graphics.hpp"

namespace kege{

    kege::Ref< kege::CommandBuffer > CommandBuffer::create( const CreateInfo& info )
    {
        return kege::Graphics::device()->createCommandBuffer( info );
    }


    kege::DeviceQueueType CommandBuffer::type()const
    {
        return _type;
    }
}
