//
//  shader.cpp
//  new-engine
//
//  Created by Kenneth Esdaile on 12/31/23.
//

#include "../../../graphics/initializer/graphics.hpp"

namespace kege
{
    kege::Ref< Shader > Shader::create( const CreateInfo& info )
    {
        return kege::Graphics::device()->createShaderModule( info );
    }
}
