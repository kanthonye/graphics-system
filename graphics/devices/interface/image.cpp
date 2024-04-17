//
//  image.cpp
//  new-engine
//
//  Created by Kenneth Esdaile on 12/30/23.
//

#include "../../../graphics/initializer/graphics.hpp"

namespace kege{

    kege::Ref< kege::Image2d > Image2d::create( const CreateInfo& info )
    {
        return Graphics::device()->createImage2d( info );
    }

    ImageType Image::getType()const
    {
        return _image_type;
    }

}
