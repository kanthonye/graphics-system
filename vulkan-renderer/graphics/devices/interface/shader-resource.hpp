//
//  descriptor.hpp
//  new-engine
//
//  Created by Kenneth Esdaile on 1/1/24.
//

#ifndef kege_graphics_descriptor_hpp
#define kege_graphics_descriptor_hpp

#include "command-buffer.hpp"
#include "storage-buffer.hpp"
#include "uniform-buffer.hpp"
#include "texture.hpp"

namespace kege{

    struct ShaderProgram;

    class Uniform : public kege::RefCounter
    {
    public:

        enum Type : char { STORAGE_BUFFER, UNIFORM_BUFFER, IMAGE, TEXTURE, SAMPLER, };
        virtual ~Uniform(){}

        virtual void getDescriptorBufferInfo( void* data ){}

        virtual const kege::Buffer* buffer( uint32_t i = 0 )const{ return nullptr; }
        virtual kege::Buffer* buffer( uint32_t i = 0 ){ return nullptr; }

        virtual const kege::Sampler* sampler( uint32_t i = 0 )const{ return nullptr; }
        virtual kege::Sampler* sampler( uint32_t i = 0 ){ return nullptr; }

        virtual const kege::Image* image( uint32_t i = 0 )const{ return nullptr; }
        virtual kege::Image* image( uint32_t i = 0 ){ return nullptr; }

        virtual uint32_t quantity()const{ return 1; }

        kege::string name;
        uint16_t count;
        uint16_t binding;
        Uniform::Type type;
    };

    class ShaderResource : public kege::RefCounter
    {
    public:

        struct Binding
        {
            kege::Ref< kege::Uniform > uniform;
            kege::DescriptorType descriptor_type;
        };

    public:

        static kege::Ref< kege::ShaderResource > create();
        ShaderResource* insertDynamicStorageBuffer( const kege::string& name, uint32_t binding, kege::Ref< kege::StorageBuffer > storage_buffer );
        ShaderResource* insertStorageBuffer( const kege::string& name, uint32_t binding, kege::Ref< kege::StorageBuffer > storage_buffer );

        ShaderResource* insertDynamicUniformBuffer( const kege::string& name, uint32_t binding, kege::Ref< kege::UniformBuffer > uniform_buffer );
        ShaderResource* insertUniformBuffer( const kege::string& name, uint32_t binding, kege::Ref< kege::UniformBuffer > uniform_buffer );

        ShaderResource* insertCombindedImage( const kege::string& name, uint32_t binding, kege::Ref< kege::Image > image, kege::Ref< kege::Sampler > sampler );
        ShaderResource* insertSampledImage( const kege::string& name, uint32_t binding, kege::Ref< kege::Image > image, kege::Ref< kege::Sampler > sampler );
        ShaderResource* insertStorageImage( const kege::string& name, uint32_t binding, kege::Ref< kege::Image > image );

        ShaderResource* insertCombindedImages
        (
            const kege::string& name, uint32_t binding,
            std::vector< kege::Ref< kege::Image > > image,
            std::vector< kege::Ref< kege::Sampler > > sampler
        );

        ShaderResource* insertStorageImages
        (
            const kege::string& name, uint32_t binding,
            std::vector< kege::Ref< kege::Image > > image
        );

        /**
         * Bind shader-resource locally to the given shader-program
         */
        virtual void bind( kege::CommandBuffer* command_buffer, uint32_t first_set, kege::ShaderProgram* program )const = 0;

        /**
         * Bind shader-resource globally
         */
        virtual void bind( kege::CommandBuffer* command_buffer, uint32_t first_set )const = 0;
        virtual bool valid()const = 0;
        virtual void update() = 0;

        void updateBufferData( uint32_t index, uint64_t offset, uint64_t size, const void* data );
        const kege::ShaderResource::Binding& get( int i )const;
        kege::ShaderResource::Binding& get( int i );

    protected:

        ShaderResource& operator =( const kege::ShaderResource& other ) = delete;
        ShaderResource( const kege::ShaderResource& other ){}
        virtual ~ShaderResource();
        ShaderResource(){}

    protected:

        std::vector< kege::ShaderResource::Binding > _shader_resource_binding;
        friend kege::Ref< kege::ShaderResource >;
    };

}

#endif /* kege_graphics_descriptor_hpp */
