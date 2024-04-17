//
//  sampler.hpp
//  new-engine
//
//  Created by Kenneth Esdaile on 12/30/23.
//

#ifndef kege_graphics_sampler_hpp
#define kege_graphics_sampler_hpp

#include "../../../graphics/devices/interface/dependencies.hpp"

namespace kege{

    typedef enum Filter {
        NEAREST,
        LINEAR,
        CUBIC,
    } Filter;

    typedef enum Wrapping {
        REPEAT,
        MIRRORED_REPEAT,
        CLAMP_TO_EDGE,
        CLAMP_TO_BORDER,
        MIRROR_CLAMP_TO_EDGE,
        EDGE_MODE_MAX_ENUM
    } Wrapping;

    typedef enum MipmapFilter {
        MIPMAP_NEAREST,
        MIPMAP_LINEAR,
        MIPMAP_MAX_ENUM
    } MipmapFilter;

    class Sampler : public kege::RefCounter
    {
    public:

        struct CreateInfo
        {
            kege::Filter min;
            kege::Filter mag;
            kege::Wrapping x;
            kege::Wrapping y;
            kege::Wrapping z;
        };

        static kege::Ref< kege::Sampler > create( const CreateInfo& info );
        virtual void getDescriptorBufferInfo( void* data ) = 0;
        virtual const vk::Sampler* vulkan()const{ return nullptr; }
        virtual vk::Sampler* vulkan(){ return nullptr; }

    protected:

        Sampler& operator =( const kege::Sampler& other ) = delete;
        Sampler( const kege::Sampler& other ){}
        virtual ~Sampler(){}
        Sampler(){}

    private:

        friend kege::Ref< kege::Sampler >;
    };

}
#endif /* kege_graphics_sampler_hpp */
