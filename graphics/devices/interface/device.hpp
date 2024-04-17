//
//  Device.hpp
//  new-engine
//
//  Created by Kenneth Esdaile on 12/30/23.
//

#ifndef kege_graphics_device
#define kege_graphics_device

#include "../../../graphics/devices/interface/buffer.hpp"
#include "../../../graphics/devices/interface/pipeline.hpp"
#include "../../../graphics/devices/interface/image.hpp"
#include "../../../graphics/devices/interface/texture.hpp"
#include "../../../graphics/devices/interface/shader.hpp"
#include "../../../graphics/devices/interface/shader-program.hpp"
#include "../../../graphics/devices/interface/shader-resource.hpp"
#include "../../../graphics/devices/interface/framebuffer.hpp"
#include "../../../graphics/devices/interface/vertex-buffer.hpp"
#include "../../../graphics/devices/interface/index-buffer.hpp"
#include "../../../graphics/devices/interface/uniform-buffer.hpp"
#include "../../../graphics/devices/interface/storage-buffer.hpp"
#include "../../../graphics/devices/interface/command-buffer.hpp"
#include "../../../graphics/devices/interface/draw-command-buffer.hpp"
#include "../../../graphics/devices/interface/renderpass.hpp"
#include "../../../graphics/devices/interface/render-window.hpp"
#include "../../../graphics/devices/interface/render-context.hpp"

namespace kege
{

    class Device: public kege::RefCounter
    {
    public:

        virtual kege::Ref< kege::DrawIndexedCommandBuffer > createDrawIndexedCommandBuffer( const kege::DrawIndexedCommandBuffer::CreateInfo& info ) = 0;
        virtual kege::Ref< kege::DrawCommandBuffer > createDrawCommandBuffer( const kege::DrawCommandBuffer::CreateInfo& info ) = 0;

        virtual kege::Ref< kege::Framebuffer > createFramebuffer( const std::vector< kege::Framebuffer::Attachment >& attachment ) = 0;

        virtual kege::Ref< kege::PipelineLayout > createPipelineLayout( const kege::PipelineLayout::CreateInfo& info ) = 0;
        virtual kege::Ref< kege::CommandBuffer > createCommandBuffer( const kege::CommandBuffer::CreateInfo& info ) = 0;
        virtual kege::Ref< kege::Pipeline > createPipeline( const kege::Pipeline::CreateInfo& info ) = 0;
        virtual kege::Ref< kege::Shader > createShaderModule( const kege::Shader::CreateInfo& info ) = 0;
        virtual kege::Ref< kege::Sampler > createSampler( const kege::Sampler::CreateInfo& info ) = 0;

        /**
         * @brief Creates a vertex-buffer.
         *
         * @param info The creation information for the buffer.
         * @return A reference to the created buffer.
         */
        virtual kege::Ref< kege::VertexBuffer > createVertexBuffer( const kege::CreateBufferInfo& info ) = 0;

        /**
         * @brief Creates a index-buffer.
         *
         * @param info The creation information for the buffer.
         * @return A reference to the created buffer.
         */
        virtual kege::Ref< kege::IndexBuffer > createIndexBuffer( const kege::CreateIndexBufferInfo& info ) = 0;

        /**
         * @brief Creates a storage-buffer.
         *
         * @param info The creation information for the buffer.
         * @return A reference to the created buffer.
         */
        virtual kege::Ref< kege::StorageBuffer > createStorageBuffer( const kege::CreateBufferInfo& info ) = 0;

        /**
         * @brief Creates a uniform-buffer.
         *
         * @param info The creation information for the buffer.
         * @return A reference to the created buffer.
         */
        virtual kege::Ref< kege::UniformBuffer > createUniformBuffer( const kege::CreateBufferInfo& info ) = 0;

        /**
         * @brief Creates a 2d-image.
         *
         * @param info The creation information for the image.
         * @return A reference to the created image.
         */
        virtual kege::Ref< kege::Image2d > createImage2d( const kege::Image2d::CreateInfo& info ) = 0;

        /**
         * @brief Creates a 3d- image.
         *
         * @param info The creation information for the image.
         * @return A reference to the created image.
         */
        virtual kege::Ref< kege::Image3d > createImage3d( const kege::Image3d::CreateInfo& info ) = 0;

        /**
         * @brief Creates a 2d-image-array.
         *
         * @param info The creation information for the image.
         * @return A reference to the created image.
         */
        virtual kege::Ref< kege::Image2dArray > createImage2dArray( const kege::Image2dArray::CreateInfo& info ) = 0;

        /**
         * @brief Creates a 1d-image-array.
         *
         * @param info The creation information for the image.
         * @return A reference to the created image.
         */
        virtual kege::Ref< kege::Image1dArray > createImage1dArray( const kege::Image1dArray::CreateInfo& info ) = 0;

//        /**
//         * @brief Creates a draw-command-buffer.
//         *
//         * @param info The creation information for the buffer.
//         * @return A reference to the created buffer.
//         */
//        virtual kege::Ref< kege::Image > createImage( const kege::Image::CreateInfo& info ) = 0;

        virtual kege::Ref< kege::ShaderResource > createShaderResource() = 0;
        
        //virtual kege::Ref< kege::Sampler > createSampler( const kege::Sampler::CreateInfo& info ) = 0;
        ///virtual kege::Ref< kege::Image > createImage( const kege::Image::CreateInfo& info ) = 0;
        virtual int init( kege::Ref< kege::RenderWindow >& window ) = 0;
        virtual kege::RenderContext& getRenderContext() = 0;

        static Device* create();

    protected:

        Device& operator =( const kege::Device& other );
        Device( const kege::Device& other );
        virtual ~Device();
        Device();

    private:

        friend kege::Ref< kege::Device >;
    };

}

#endif /* kege_graphics_device */
