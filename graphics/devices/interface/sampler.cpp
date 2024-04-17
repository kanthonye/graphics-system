//
//  sampler.cpp
//  new-engine
//
//  Created by Kenneth Esdaile on 12/30/23.
//

#include "../../../graphics/initializer/graphics.hpp"

namespace kege{

    kege::Ref< kege::Sampler > Sampler::create( const CreateInfo& info )
    {
        return kege::Graphics::device()->createSampler( info );
    }
}
