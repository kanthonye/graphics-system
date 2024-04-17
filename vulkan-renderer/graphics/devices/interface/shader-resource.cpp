//
//  descriptor.cpp
//  new-engine
//
//  Created by Kenneth Esdaile on 1/1/24.
//

#include "../../../graphics/initializer/graphics.hpp"

namespace kege{

    class UBO : public kege::Uniform
    {
    public:
        const kege::UniformBuffer* buffer( uint32_t i = 0 )const{ return buf.ref(); }
        kege::UniformBuffer* buffer( uint32_t i = 0 ){ return buf.ref(); }
        void getDescriptorBufferInfo( void* data )
        {
            buf->getDescriptorBufferInfo( data );
        }
        kege::Ref< kege::UniformBuffer > buf;
    };

    class SSBO : public kege::Uniform
    {
    public:
        const kege::StorageBuffer* buffer( uint32_t i = 0 )const{ return buf.ref(); }
        kege::StorageBuffer* buffer( uint32_t i = 0 ){ return buf.ref(); }
        void getDescriptorBufferInfo( void* data )
        {
            buf->getDescriptorBufferInfo( data );
        }
        kege::Ref< kege::StorageBuffer > buf;
    };

    class StorageImage : public kege::Uniform
    {
    public:
        const kege::Image* image( uint32_t i = 0 )const{ return img.ref(); }
        kege::Image* image( uint32_t i = 0 ){ return img.ref(); }
        void getDescriptorBufferInfo( void* data )
        {
            img->getDescriptorBufferInfo( data );
        }
        kege::Ref< kege::Image > img;
    };

    class SamplerBinding : public kege::Uniform
    {
    public:
        const kege::Sampler* sampler( uint32_t i = 0 )const{ return samplr.ref(); }
        kege::Sampler* sampler( uint32_t i = 0 ){ return samplr.ref(); }
        void getDescriptorBufferInfo( void* data )
        {
            samplr->getDescriptorBufferInfo( data );
        }
        kege::Ref< kege::Sampler > samplr;
    };

    class CombinedImage : public kege::Uniform
    {
    public:
        const kege::Sampler* sampler( uint32_t i = 0 )const{ return samplr.ref(); }
        const kege::Image* image( uint32_t i = 0 )const{ return img.ref(); }
        kege::Sampler* sampler( uint32_t i = 0 ){ return samplr.ref(); }
        kege::Image* image( uint32_t i = 0 ){ return img.ref(); }
        void getDescriptorBufferInfo( void* data )
        {
            img->getDescriptorBufferInfo( data );
            samplr->getDescriptorBufferInfo( data );
        }
        kege::Ref< kege::Sampler > samplr;
        kege::Ref< kege::Image > img;
    };




    class UniformBufferBindingArray : public kege::Uniform
    {
        const kege::UniformBuffer* buffer( uint32_t i = 0 )const{ return buffers[ i ].ref(); }
        kege::UniformBuffer* buffer( uint32_t i = 0 ){ return buffers[ i ].ref(); }
        uint32_t quantity()const{ return (uint32_t) buffers.size(); }
        void getDescriptorBufferInfo( void* data )
        {
            buffers[ 0 ]->getDescriptorBufferInfo( data );
        }
        std::vector< kege::Ref< kege::UniformBuffer > > buffers;
    };

    class StorageBufferBindingArray : public kege::Uniform
    {
    public:
        const kege::StorageBuffer* buffer( uint32_t i = 0 )const{ return buffers[ i ].ref(); }
        kege::StorageBuffer* buffer( uint32_t i = 0 ){ return buffers[ i ].ref(); }
        uint32_t quantity()const{ return (uint32_t) buffers.size(); }
        void getDescriptorBufferInfo( void* data )
        {
        }
        std::vector< kege::Ref< kege::StorageBuffer > > buffers;
    };

    class ImageBindingArray : public kege::Uniform
    {
    public:
        const kege::Image* image( uint32_t i = 0 )const{ return images[ i ].ref(); }
        kege::Image* image( uint32_t i = 0 ){ return images[ i ].ref(); }
        uint32_t quantity()const{ return (uint32_t) images.size(); }
        void getDescriptorBufferInfo( void* data )
        {
        }
        std::vector< kege::Ref< kege::Image > > images;
    };

    class SamplerBindingArray : public kege::Uniform
    {
    public:
        const kege::Sampler* sampler( uint32_t i = 0 )const{ return samplers[ i ].ref(); }
        kege::Sampler* sampler( uint32_t i = 0 ){ return samplers[ i ].ref(); }
        uint32_t quantity()const{ return (uint32_t) samplers.size(); }
        void getDescriptorBufferInfo( void* data )
        {
        }
        std::vector< kege::Ref< kege::Sampler > > samplers;
    };

    class CombinedImages : public kege::Uniform
    {
    public:
        const kege::Sampler* sampler( uint32_t i = 0 )const{ return samplers[ i ].ref(); }
        kege::Sampler* sampler( uint32_t i = 0 ){ return samplers[ i ].ref(); }
        const kege::Image* image( uint32_t i = 0 )const{ return images[ i ].ref(); }
        kege::Image* image( uint32_t i = 0 ){ return images[ i ].ref(); }
        uint32_t quantity()const{ return (uint32_t) images.size(); }
        void getDescriptorBufferInfo( void* data )
        {
        }

        std::vector< kege::Ref< kege::Sampler > > samplers;
        std::vector< kege::Ref< kege::Image > > images;
    };

    class StorageImages : public kege::Uniform
    {
    public:
        const kege::Image* image( uint32_t i = 0 )const{ return images[ i ].ref(); }
        kege::Image* image( uint32_t i = 0 ){ return images[ i ].ref(); }
        void getDescriptorBufferInfo( void* data )
        {
        }
        std::vector< kege::Ref< kege::Image > > images;
    };



    kege::Ref< kege::ShaderResource > ShaderResource::create()
    {
        return kege::Graphics::device()->createShaderResource();
    }

    ShaderResource* ShaderResource::insertDynamicStorageBuffer
    (
        const kege::string& name,
        uint32_t binding,
        kege::Ref< kege::StorageBuffer > storage_buffer
    )
    {
        SSBO* ssbo = new SSBO;
        ssbo->type = Uniform::STORAGE_BUFFER;
        ssbo->buf = storage_buffer;
        ssbo->binding = binding;
        ssbo->name = name;
        ssbo->count = 1;
        _shader_resource_binding.push_back({ ssbo, kege::DESCRIPTOR_STORAGE_BUFFER_DYNAMIC });
        return this;
    }

    ShaderResource* ShaderResource::insertStorageBuffer( const kege::string& name, uint32_t binding, kege::Ref< kege::StorageBuffer > storage_buffer )
    {
        SSBO* ssbo = new SSBO;
        ssbo->type = Uniform::STORAGE_BUFFER;
        ssbo->buf = storage_buffer;
        ssbo->binding = binding;
        ssbo->name = name;
        ssbo->count = 1;
        _shader_resource_binding.push_back({ ssbo, kege::DESCRIPTOR_STORAGE_BUFFER });
        return this;
    }

    ShaderResource* ShaderResource::insertDynamicUniformBuffer( const kege::string& name, uint32_t binding, kege::Ref< kege::UniformBuffer > buffer )
    {
        UBO* ubo = new UBO;
        ubo->type = Uniform::STORAGE_BUFFER;
        ubo->buf = buffer;
        ubo->binding = binding;
        ubo->name = name;
        ubo->count = 1;
        _shader_resource_binding.push_back({ ubo, kege::DESCRIPTOR_UNIFORM_BUFFER_DYNAMIC });
        return this;
    }

    ShaderResource* ShaderResource::insertUniformBuffer( const kege::string& name, uint32_t binding, kege::Ref< kege::UniformBuffer > buffer )
    {
        UBO* ubo = new UBO;
        ubo->type = Uniform::STORAGE_BUFFER;
        ubo->buf = buffer;
        ubo->binding = binding;
        ubo->name = name;
        ubo->count = 1;
        _shader_resource_binding.push_back({ ubo, kege::DESCRIPTOR_UNIFORM_BUFFER });
        return this;
    }

    ShaderResource* ShaderResource::insertCombindedImage( const kege::string& name, uint32_t binding, kege::Ref< kege::Image > image, kege::Ref< kege::Sampler > sampler )
    {
        CombinedImage* elem = new CombinedImage;
        elem->type = Uniform::STORAGE_BUFFER;
        elem->img = image;
        elem->samplr = sampler;
        elem->binding = binding;
        elem->name = name;
        elem->count = 1;
        _shader_resource_binding.push_back({ elem, kege::DESCRIPTOR_COMBINED_IMAGE_SAMPLER });
        return this;
    }

    ShaderResource* ShaderResource::insertSampledImage( const kege::string& name, uint32_t binding, kege::Ref< kege::Image > image, kege::Ref< kege::Sampler > sampler )
    {
        CombinedImage* elem = new CombinedImage;
        elem->type = Uniform::STORAGE_BUFFER;
        elem->img = image;
        elem->samplr = sampler;
        elem->binding = binding;
        elem->name = name;
        elem->count = 1;
        _shader_resource_binding.push_back({ elem, kege::DESCRIPTOR_SAMPLED_IMAGE });
        return this;
    }

    ShaderResource* ShaderResource::insertStorageImage( const kege::string& name, uint32_t binding, kege::Ref< kege::Image > image )
    {
        StorageImage* elem = new StorageImage;
        elem->type = Uniform::STORAGE_BUFFER;
        elem->img = image;
        elem->binding = binding;
        elem->name = name;
        elem->count = 1;
        _shader_resource_binding.push_back({ elem, kege::DESCRIPTOR_STORAGE_IMAGE });
        return this;
    }

    ShaderResource* ShaderResource::insertCombindedImages
    (
        const kege::string& name, uint32_t binding,
        std::vector< kege::Ref< kege::Image > > images,
        std::vector< kege::Ref< kege::Sampler > > samplers
    )
    {
        CombinedImages* combind_images = new CombinedImages;
        combind_images->type = Uniform::STORAGE_BUFFER;
        combind_images->images = images;
        combind_images->samplers = samplers;
        combind_images->binding = binding;
        combind_images->name = name;
        combind_images->count = (uint32_t) images.size();
        _shader_resource_binding.push_back({ combind_images, kege::DESCRIPTOR_COMBINED_IMAGE_SAMPLER });
        return this;
    }

    ShaderResource* ShaderResource::insertStorageImages
    (
        const kege::string& name, uint32_t binding,
        std::vector< kege::Ref< kege::Image > > images
    )
    {
        StorageImages* storage_images = new StorageImages;
        storage_images->type = Uniform::IMAGE;
        storage_images->images = images;
        storage_images->binding = binding;
        storage_images->name = name;
        storage_images->count = (uint32_t) images.size();
        _shader_resource_binding.push_back({ storage_images, kege::DESCRIPTOR_STORAGE_IMAGE });
        return this;
    }

    void ShaderResource::updateBufferData( uint32_t index, uint64_t offset, uint64_t size, const void* data )
    {
        ShaderResource::Binding& binding = _shader_resource_binding[ index ];
        switch( binding.uniform->type )
        {
            case kege::Uniform::STORAGE_BUFFER:
                binding.uniform->buffer()->setBufferData( offset, size, data );
                break;

            case kege::Uniform::UNIFORM_BUFFER:
                binding.uniform->buffer()->setBufferData( offset, size, data );
                break;
                
            case kege::Uniform::TEXTURE:
            case kege::Uniform::SAMPLER:
            case kege::Uniform::IMAGE:
                KEGE_ERROR( "INVALID_OPERATION: ShaderResource::setBufferData resource at index -> %i is not a buffer", index );
                break;
        }
    }

    const kege::ShaderResource::Binding& ShaderResource::get( int i )const
    {
        return _shader_resource_binding[ i ];
    }

    kege::ShaderResource::Binding& ShaderResource::get( int i )
    {
        return _shader_resource_binding[ i ];
    }

    ShaderResource::~ShaderResource()
    {
        _shader_resource_binding.clear();
    }

}
