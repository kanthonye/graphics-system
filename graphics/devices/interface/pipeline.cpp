//
//  pipeline.cpp
//  new-engine
//
//  Created by Kenneth Esdaile on 12/30/23.
//

#include "../../../graphics/initializer/graphics.hpp"

namespace kege{

    kege::Ref< Pipeline > Pipeline::create( const CreateInfo& info )
    {
        return kege::Graphics::device()->createPipeline( info );
    }

    const kege::PipelineLayout* Pipeline::getPipelineLayout()const
    {
        return _pipeline_layout.ref();
    }

    kege::PipelineLayout* Pipeline::getPipelineLayout()
    {
        return _pipeline_layout.ref();
    }

    Pipeline::Pipeline()
    {}
}
