//
//  draw-command-buffer.cpp
//  new-engine
//
//  Created by Kenneth Esdaile on 3/5/24.
//

#include "../../../graphics/initializer/graphics.hpp"

namespace kege{

    kege::Ref< kege::DrawCommandBuffer > DrawCommandBuffer::create( const kege::DrawCommandBuffer::CreateInfo& info )
    {
        return kege::Graphics::device()->createDrawCommandBuffer( info );
    }


    kege::Ref< kege::DrawIndexedCommandBuffer > DrawIndexedCommandBuffer::create( const kege::DrawIndexedCommandBuffer::CreateInfo& info )
    {
        return kege::Graphics::device()->createDrawIndexedCommandBuffer( info );
    }

}
