//
//  vk-device.hpp
//  new-engine
//
//  Created by Kenneth Esdaile on 12/30/23.
//

#ifndef kege_graphics_vk_device_hpp
#define kege_graphics_vk_device_hpp

#include "../vulkan/vk-shader.hpp"
#include "../vulkan/vk-debugger.hpp"
#include "../vulkan/vk-physical-device.hpp"
#include "../vulkan/vk-device-queue.hpp"
#include "../vulkan/vk-command-pool.hpp"
#include "../vulkan/vk-render-context.hpp"
#include "../vulkan/vk-descriptor-writer.hpp"

namespace kege{namespace vk{

    typedef std::vector< kege::Ref< vk::DescriptorSetLayout > > DescriptorSetLayoutGroup;
    typedef std::unordered_map<uint64_t, DescriptorSetLayoutGroup > DescriptorSetLayoutGroupMap;
    
    /**
     * @brief Represents a Vulkan logical device.
     *
     * This class encapsulates a Vulkan logical device, providing a convenient interface for
     * creating, managing, and using Vulkan devices in Vulkan applications.
     */
    class Device: public kege::Device
    {
    public:

        uint64_t getDescriptorSetLayoutBindingsSignature( const vk::DescriptorSetLayoutObject& object );

        vk::DescriptorSetLayout* createDescriptorSetLayout( const vk::DescriptorSetLayoutObject& descriptor_set_layout_bindings );

        /**
         * @brief Retrieves the descriptor set layout corresponding to the specified signature and bindings.
         *
         * @param descriptor_set_layout_bindings The descriptor set layout bindings.
         * @return A pointer to the descriptor set layout.
         */
        vk::DescriptorSetLayout* getDescriptorSetLayout( const vk::DescriptorSetLayoutObject& descriptor_set_layout_bindings );

        /**
         * @brief Creates a draw-command-buffer.
         *
         * @param info The creation information for the buffer.
         * @return A reference to the created buffer.
         */

        kege::Ref< kege::DrawIndexedCommandBuffer > createDrawIndexedCommandBuffer( const kege::DrawIndexedCommandBuffer::CreateInfo& info );

        /**
         * @brief Creates a draw-command-buffer.
         *
         * @param info The creation information for the buffer.
         * @return A reference to the created buffer.
         */
        kege::Ref< kege::DrawCommandBuffer > createDrawCommandBuffer( const kege::DrawCommandBuffer::CreateInfo& info );

        /**
         * @brief Creates a frame-buffer.
         *
         * @param attachments The frame-buffer attachments
         * @return A reference to the created buffer.
         */
        kege::Ref< kege::Framebuffer > createFramebuffer( const std::vector< kege::Framebuffer::Attachment >& attachment );

        /**
         * @brief Creates a pipeline layout.
         *
         * @param info The creation information for the pipeline layout.
         * @return A reference to the created pipeline layout.
         */
        kege::Ref< kege::PipelineLayout > createPipelineLayout( const kege::PipelineLayout::CreateInfo& info );

        /**
         * @brief Creates a command buffer.
         *
         * @param info The creation information for the command buffer.
         * @return A reference to the created command buffer.
         */
        kege::Ref< kege::CommandBuffer > createCommandBuffer( const kege::CommandBuffer::CreateInfo& info );

        /**
         * @brief Creates a render pass.
         *
         * @param info The creation information for the render pass.
         * @return A reference to the created render pass.
         */
        kege::Ref< kege::Renderpass > createRenderpass( const kege::Renderpass::CreateInfo& info );

        /**
         * @brief Creates a shader module.
         *
         * @param info The creation information for the shader module.
         * @return A reference to the created shader module.
         */
        kege::Ref< kege::Shader > createShaderModule( const kege::Shader::CreateInfo& info );

        /**
         * @brief Creates a pipeline.
         *
         * @param info The creation information for the pipeline.
         * @return A reference to the created pipeline.
         */
        kege::Ref< kege::Pipeline > createPipeline( const kege::Pipeline::CreateInfo& info );

        /**
         * @brief Creates a sampler.
         *
         * @param info The creation information for the sampler.
         * @return A reference to the created sampler.
         */
        kege::Ref< kege::Sampler > createSampler( const kege::Sampler::CreateInfo& info );

        /**
         * @brief Creates a vertex-buffer.
         *
         * @param info The creation information for the buffer.
         * @return A reference to the created buffer.
         */
        kege::Ref< kege::VertexBuffer > createVertexBuffer( const kege::CreateBufferInfo& info );

        /**
         * @brief Creates a index-buffer.
         *
         * @param info The creation information for the buffer.
         * @return A reference to the created buffer.
         */
        kege::Ref< kege::IndexBuffer > createIndexBuffer( const kege::CreateIndexBufferInfo& info );

        /**
         * @brief Creates a storage-buffer.
         *
         * @param info The creation information for the buffer.
         * @return A reference to the created buffer.
         */
        kege::Ref< kege::StorageBuffer > createStorageBuffer( const kege::CreateBufferInfo& info );

        /**
         * @brief Creates a uniform-buffer.
         *
         * @param info The creation information for the buffer.
         * @return A reference to the created buffer.
         */
        kege::Ref< kege::UniformBuffer > createUniformBuffer( const kege::CreateBufferInfo& info );

        /**
         * @brief Creates a 2d-image.
         *
         * @param info The creation information for the image.
         * @return A reference to the created image.
         */
        kege::Ref< kege::Image2d > createImage2d( const kege::Image2d::CreateInfo& info );

        /**
         * @brief Creates a 3d- image.
         *
         * @param info The creation information for the image.
         * @return A reference to the created image.
         */
        kege::Ref< kege::Image3d > createImage3d( const kege::Image3d::CreateInfo& info );

        /**
         * @brief Creates a 2d-image-array.
         *
         * @param info The creation information for the image.
         * @return A reference to the created image.
         */
        kege::Ref< kege::Image2dArray > createImage2dArray( const kege::Image2dArray::CreateInfo& info );

        /**
         * @brief Creates a 1d-image-array.
         *
         * @param info The creation information for the image.
         * @return A reference to the created image.
         */
        kege::Ref< kege::Image1dArray > createImage1dArray( const kege::Image1dArray::CreateInfo& info );

        /**
         * @brief Creates a ShaderResource.
         *
         * @return The created shader-resource.
         */
        kege::Ref< kege::ShaderResource > createShaderResource();

        void copyBufferToImage( const vk::Buffer& buffer, vk::Image& image );
        void copyBuffer( vk::Buffer& dst, const vk::Buffer& src );

        /**
         * @brief Initializes the logical device.
         *
         * @param window A reference to the render window.
         * @return 0 if initialization is successful, otherwise an error code.
         */
        int init( kege::Ref< kege::RenderWindow >& window );

        /**
         * @brief Retrieves the command pool corresponding to the specified queue index.
         *
         * @param queue_index The index of the queue.
         * @return The command pool corresponding to the specified queue index.
         */
        vk::CommandPool& getCommandPool( uint32_t queue_index );

        /**
         * @brief Retrieves the render context.
         *
         * @return A reference to the render context.
         */
        kege::RenderContext& getRenderContext();

        /**
         * @brief Retrieves the physical device.
         *
         * @return A reference to the physical device.
         */
        vk::PhysicalDevice& getPhysicalDevice();

        /**
         * @brief Retrieves the logical device handle.
         *
         * @return The logical device handle.
         */
        const VkDevice getLogicalDevice()const;

        /**
         * @brief Retrieves a pointer to the render window.
         *
         * @return A pointer to the render window.
         */
        kege::RenderWindow* window();

        /**
         * @brief Retrieves the surface.
         *
         * @return The surface.
         */
        VkSurfaceKHR getSurface();

        /**
         * @brief Waits for the device to become idle.
         */
        void waitIdle();

        /**
         * @brief Destructs the Device object.
         */
        virtual ~Device();

        /**
         * @brief Constructs a Device object.
         */
        Device();

    private:

        /**
         * @brief Creates the logical device.
         *
         * @param instance The Vulkan instance.
         * @param physical_device The physical device.
         * @return VK_SUCCESS if the logical device creation is successful, otherwise an error code.
         */
        VkResult createLogicalDevice( vk::Instance& instance, vk::PhysicalDevice& physical_device );

        /**
         * @brief Copy assignment operator.
         */
        Device& operator =( const kege::Device& other ) = delete;

        /**
         * @brief Copy constructor.
         */
        Device( const kege::Device& other ) = delete;

    private:

        typedef std::unordered_map< uint64_t, kege::Ref< vk::DescriptorSetLayout > > DescriptorSetLayoutMap;
        typedef std::unordered_map< uint64_t, std::set< vk::PipelineLayout* > > PipelineLayoutSetMap;
        kege::Hashmap< uint32_t > _descriptor_index_map;
        uint32_t _distinct_descriptor_counter;

        DescriptorSetLayoutMap _descriptor_set_layouts;
        PipelineLayoutSetMap _pipeline_layout_sets;
        std::vector< vk::CommandPool > _command_pools;

        std::vector< kege::Ref< vk::ValidationLayer > > _validation_layers;

        kege::Ref< kege::RenderWindow > _window;

        vk::PhysicalDevice _physical_device;

        vk::RenderContext _render_context;

        vk::Instance _instance;

        VkQueue _transfer_queue;
        VkSurfaceKHR _surface;
        VkDevice _device;
    };

}}

#endif /* kege_graphics_vk_device_hpp */
