//
//  pipeline-layout.cpp
//  new-engine
//
//  Created by Kenneth Esdaile on 12/30/23.
//

#include "../../../graphics/initializer/graphics.hpp"

namespace kege{

    kege::Ref< PipelineLayout > PipelineLayout::create( const CreateInfo& info )
    {
        return kege::Graphics::device()->createPipelineLayout( info );
    }

}
