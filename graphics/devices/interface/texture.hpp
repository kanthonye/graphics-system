//
//  texture.hpp
//  new-engine
//
//  Created by Kenneth Esdaile on 12/30/23.
//

#ifndef kege_graphics_texture_hpp
#define kege_graphics_texture_hpp

#include "../../../graphics/devices/interface/image.hpp"
#include "../../../graphics/devices/interface/sampler.hpp"

namespace kege{

    class Texture : public kege::RefCounter
    {
    public:

        Texture( kege::Ref< kege::Image > image, kege::Ref< kege::Sampler > sampler );
        virtual void getDescriptorBufferInfo( void* data );
        const kege::Sampler* sampler()const;
        const kege::Image* image()const;
        kege::Sampler* sampler();
        kege::Image* image();

    protected:

        Texture& operator =( const kege::Texture& other ) = delete;
        Texture( const kege::Texture& other ){}
        virtual ~Texture(){}
        Texture(){}

    private:

        kege::Ref< kege::Sampler > _sampler;
        kege::Ref< kege::Image > _image;
        friend kege::Ref< kege::Texture >;
    };;

}
#endif /* kege_graphics_texture_hpp */
