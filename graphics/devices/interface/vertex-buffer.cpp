//
//  vertex-buffer.cpp
//  new-engine
//
//  Created by Kenneth Esdaile on 3/5/24.
//

#include "../../../graphics/initializer/graphics.hpp"

namespace kege{

    kege::Ref< kege::VertexBuffer > VertexBuffer::create( const kege::CreateBufferInfo& info )
    {
        return kege::Graphics::device()->createVertexBuffer( info );
    }

}
