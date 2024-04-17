//
//  index-buffer.cpp
//  new-engine
//
//  Created by Kenneth Esdaile on 3/5/24.
//

#include "../../../graphics/initializer/graphics.hpp"

namespace kege{

    kege::Ref< kege::IndexBuffer > IndexBuffer::create( const kege::CreateIndexBufferInfo& info )
    {
        return kege::Graphics::device()->createIndexBuffer( info );
    }

}
