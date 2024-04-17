//
//  image.hpp
//  new-engine
//
//  Created by Kenneth Esdaile on 12/30/23.
//

#ifndef kege_graphics_image_hpp
#define kege_graphics_image_hpp

#include "../../../graphics/devices/interface/buffer.hpp"

namespace kege{

    typedef enum ImageType
    {
        IMAGE_1D,
        IMAGE_2D,
        IMAGE_3D,
        IMAGE_CUBE,
        IMAGE_1D_ARRAY,
        IMAGE_2D_ARRAY,
        IMAGE_CUBE_ARRAY,
    } ImageType;

    typedef enum ImageAspect 
    {
        IMAGE_ASPECT_COLOR,
        IMAGE_ASPECT_DEPTH,
        IMAGE_ASPECT_STENCIL,
    } ImageAspect;

    class Image : public kege::RefCounter
    {
    public:

        virtual const vk::Image* vulkan()const{ return nullptr; }
        virtual vk::Image* vulkan(){ return nullptr; }
        virtual void getDescriptorBufferInfo( void* data ) = 0;
        virtual uint32_t layers()const = 0;
        virtual uint32_t height()const = 0;
        virtual uint32_t width()const = 0;
        virtual uint32_t depth()const = 0;
        ImageType getType()const;

    protected:

        Image& operator =( const kege::Image& other ) = delete;
        Image( const kege::Image& other ){}
        virtual ~Image(){}
        Image(){}

    private:

        kege::ImageType _image_type;
        friend kege::Ref< kege::Image >;
    };;

}



namespace kege{

    class Image2d : public kege::Image
    {
    public:

        struct CreateInfo
        {
            Format format;
            ImageAspect image_aspect;
            uint32_t width;
            uint32_t height;
            uint32_t mip_levels;
            uint64_t data_size;
            const void* data;
        };

    public:

        static kege::Ref< kege::Image2d > create( const CreateInfo& info );
        virtual void getDescriptorBufferInfo( void* data ) = 0;
        virtual const vk::Image* vulkan()const{ return nullptr; }
        virtual vk::Image* vulkan(){ return nullptr; }
        virtual uint32_t height()const = 0;
        virtual uint32_t width()const = 0;

    protected:

        Image2d& operator =( const kege::Image2d& other ) = delete;
        Image2d( const kege::Image2d& other ){}
        virtual ~Image2d(){}
        Image2d(){}

    private:

        friend kege::Ref< kege::Image2d >;
    };

}


namespace kege{

    class Image3d : public kege::Image
    {
    public:

        struct CreateInfo
        {
            Format format;
            ImageAspect image_aspect;
            uint32_t width;
            uint32_t height;
            uint32_t depth;
            uint32_t mip_levels;
            uint64_t data_size;
            const void* data;
        };

    public:

        static kege::Ref< kege::Image3d > create( const CreateInfo& info );
        virtual void getDescriptorBufferInfo( void* data ) = 0;
        virtual const vk::Image* vulkan()const{ return nullptr; }
        virtual vk::Image* vulkan(){ return nullptr; }
        virtual uint32_t height()const = 0;
        virtual uint32_t width()const = 0;

    protected:

        Image3d& operator =( const kege::Image3d& other ) = delete;
        Image3d( const kege::Image3d& other ){}
        virtual ~Image3d(){}
        Image3d(){}

    private:

        friend kege::Ref< kege::Image3d >;
    };

}


namespace kege{

    class Image2dArray : public kege::Image
    {
    public:

        struct CreateInfo
        {
            Format format;
            ImageAspect image_aspect;
            uint32_t width;
            uint32_t height;
            uint32_t mip_levels;
            uint32_t layers;
            uint64_t data_size;
            const void* data;
        };

    public:

        static kege::Ref< kege::Image2dArray > create( const CreateInfo& info );
        virtual void getDescriptorBufferInfo( void* data ) = 0;
        virtual const vk::Image* vulkan()const{ return nullptr; }
        virtual vk::Image* vulkan(){ return nullptr; }
        virtual uint32_t height()const = 0;
        virtual uint32_t width()const = 0;

    protected:

        Image2dArray& operator =( const kege::Image2dArray& other ) = delete;
        Image2dArray( const kege::Image2dArray& other ){}
        virtual ~Image2dArray(){}
        Image2dArray(){}

    private:

        friend kege::Ref< kege::Image2dArray >;
    };

}




namespace kege{

    class Image1dArray : public kege::Image
    {
    public:

        struct CreateInfo
        {
            Format format;
            ImageAspect image_aspect;
            uint32_t width;
            uint32_t mip_levels;
            uint32_t layers;
            uint64_t data_size;
            const void* data;
        };

    public:

        static kege::Ref< kege::Image1dArray > create( const CreateInfo& info );
        virtual void getDescriptorBufferInfo( void* data ) = 0;
        virtual const vk::Image* vulkan()const{ return nullptr; }
        virtual vk::Image* vulkan(){ return nullptr; }
        virtual uint32_t height()const = 0;
        virtual uint32_t width()const = 0;

    protected:

        Image1dArray& operator =( const kege::Image1dArray& other ) = delete;
        Image1dArray( const kege::Image1dArray& other ){}
        virtual ~Image1dArray(){}
        Image1dArray(){}

    private:

        friend kege::Ref< kege::Image1dArray >;
    };

}
#endif /* kege_graphics_image_hpp */
