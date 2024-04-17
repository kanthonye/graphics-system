//
//  storage-buffer.cpp
//  new-engine
//
//  Created by Kenneth Esdaile on 3/5/24.
//

#include "storage-buffer.hpp"
#include "../../../graphics/initializer/graphics.hpp"

namespace kege{

    kege::Ref< kege::StorageBuffer > StorageBuffer::create( const kege::CreateBufferInfo& info )
    {
        return kege::Graphics::device()->createStorageBuffer( info );
    }

}
