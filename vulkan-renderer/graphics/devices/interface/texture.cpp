//
//  texture.cpp
//  new-engine
//
//  Created by Kenneth Esdaile on 12/30/23.
//

#include "../../../graphics/initializer/graphics.hpp"

namespace kege{

    Texture::Texture( kege::Ref< kege::Image > image, kege::Ref< kege::Sampler > sampler )
    :   _image( image )
    ,   _sampler( sampler )
    {}
    
    void Texture::getDescriptorBufferInfo( void* data )
    {
        _image->getDescriptorBufferInfo( data );
        _sampler->getDescriptorBufferInfo( data );
    }
    const kege::Sampler* Texture::sampler()const
    {
        return _sampler.ref();
    }
    const kege::Image* Texture::image()const
    {
        return _image.ref();
    }
    kege::Sampler* Texture::sampler()
    {
        return _sampler.ref();
    }
    kege::Image* Texture::image()
    {
        return _image.ref();
    }
}
