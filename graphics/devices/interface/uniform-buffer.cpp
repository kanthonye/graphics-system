//
//  uniform-buffer.cpp
//  new-engine
//
//  Created by Kenneth Esdaile on 3/5/24.
//

#include "../../../graphics/initializer/graphics.hpp"

namespace kege{

    kege::Ref< kege::UniformBuffer > UniformBuffer::create( const kege::CreateBufferInfo& info )
    {
        return kege::Graphics::device()->createUniformBuffer( info );
    }

}
