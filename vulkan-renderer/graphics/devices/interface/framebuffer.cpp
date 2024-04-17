//
//  framebuffer.cpp
//  new-engine
//
//  Created by Kenneth Esdaile on 12/30/23.
//

#include "../../../graphics/initializer/graphics.hpp"

namespace kege{

    kege::Ref< kege::Framebuffer > Framebuffer::create( const std::vector< kege::Framebuffer::Attachment >& info )
    {
        return kege::Graphics::device()->createFramebuffer( info );
    }

}
