//
//  vk-validation-layer.cpp
//  new-engine
//
//  Created by Kenneth Esdaile on 12/30/23.
//

#include "vk-core.hpp"

namespace kege{namespace vk{

    ValidationLayer::ValidationLayer( const char* id )
    : _id( id )
    {}

    const char* ValidationLayer::id()const
    {
        return _id;
    }

}}
