//
//  vk-command-buffer.hpp
//  new-engine
//
//  Created by Kenneth Esdaile on 12/30/23.
//

#ifndef kege_graphics_vk_command_buffer_hpp
#define kege_graphics_vk_command_buffer_hpp

#include "../vulkan/vk-fence.hpp"
#include "../vulkan/vk-semaphore.hpp"

namespace kege{namespace vk{

    /**
     * @brief CommandBuffer is a concrete implementation of the core::CommandBuffer interface
     * for Vulkan-based command buffer management.
     *
     * Before a GPU can execute any rendering or compute tasks, a sequence of commands needs to be
     * recorded into a command buffer. These commands typically include operations such as drawing
     * geometry, setting render states, and dispatching compute shaders. A CommandBuffer represents
     * a list of commands that the GPU (Graphics Processing Unit) needs to execute in order to render
     * a frame or perform other graphical operations.
     * 
     * @code
     * ...
     * command_buffer->begin();
     * command_buffer->beginRenderpass( framebuffer, kege::PRIMARY_COMMAND_BUFFER );
     * ... record to command buffer
     * command_buffer->endRenderpass();
     * command_buffer->end();
     * @endcode
     *
     * @see core::CommandBuffer, core::UniformAsset, vk::Shader
     */
    class CommandBuffer : public kege::CommandBuffer
    {
    public:

        void drawIndexed( const kege::Ref< kege::DrawIndexedCommandBuffer >& drawbuffer, uint64_t offset, uint32_t draw_count )const;
        void draw( const kege::Ref< kege::DrawCommandBuffer >& drawbuffer, uint64_t offset, uint32_t draw_count )const;
        void drawIndexed( const kege::DrawIndexedCommand& command )const;
        void draw( const kege::DrawCommand& command )const;

        void dispatch( uint32_t num_groups_x, uint32_t num_groups_y, uint32_t num_groups_z )const;

        /**
         * @brief Execute secondary-command buffer associated with this parent command-buffer
         * @param command_buffers A vector of command-buffers to execute
         */
        void executeSecondaryCommandBuffers( std::vector< kege::Ref< kege::CommandBuffer > >& command_buffers );

        /**
         * @brief Begin a render pass with the given framebuffer.
         * @param framebuffer A pointer to the framebuffer to use in the render pass.
         * @param contents Specifies how the commands within the subpass will be provided.
         */
        void beginRenderpass( const kege::Framebuffer* framebuffer, kege::SubpassContents contents );

        /**
         * @brief Set the secondary command-buffer inheritance info.
         * @param command_buffer The primary command-buffer to inherit the info from.
         */
        void setSecondaryCommandBufferInheritanceInfo( kege::CommandBuffer& command_buffer );

        /**
         * @brief Push constant values to the shaders.
         * @param pipeline_layout The pipeline-layout of the current bound pipeline
         * @param push_constants The data-structure contain the data and info to push to the shader
         */
        void pushConstants( const kege::PipelineLayout* pipeline_layout, const PushConstantBlock& push_constants );

        /**
         * @brief Bind a graphics or compute pipeline
         * @param pipeline A pointer to the pipeline to bind.
         */
        void bindPipeline( const kege::Ref< kege::Pipeline >& pipeline )const;

        /**
         * @brief Set the scissor rectangle for rendering.
         * @param x The x-coordinate of the scissor rectangle.
         * @param y The y-coordinate of the scissor rectangle.
         * @param width The width of the scissor rectangle.
         * @param height The height of the scissor rectangle.
         */
        void setScissor( uint32_t x, uint32_t y, uint32_t width, uint32_t height );

        /**
         * @brief Set the viewport parameters for rendering.
         * @param x The x-coordinate of the viewport.
         * @param y The y-coordinate of the viewport.
         * @param width The width of the viewport.
         * @param height The height of the viewport.
         */
        void setViewport( float x, float y, float width, float height );
        
        /**
         * @brief Clear specified color attachments within the active render pass.
         */
        void clearColorAttachments( const kege::ClearColorState& state );

        /**
         * @brief Clear specified depth attachments within the active render pass.
         */
        void clearDepthAttachments( const kege::ClearDepthState& state );

        /**
         * @brief Get the render target for this command-buffer.
         */
        const vk::Framebuffer* framebuffer()const;

        /**
         * @brief End the current render pass.
         */
        void endRenderpass();

        /**
         * @brief Get the current VkCommandBuffer.
         */
        const VkCommandBuffer getCurrentCommandBuffer()const;
        VkCommandBuffer getCurrentCommandBuffer();

        /**
         * @brief Get self pointer. This function is used for converting from base class to derived class
         */
        const vk::CommandBuffer* vulkan()const;
        vk::CommandBuffer* vulkan();

        /**
         * @brief Get the queue family index. The queue family index indicate 
         * which device queue this command-buffer is associated with
         */
        uint32_t getQueueIndex()const;

        /**
         * @brief Get the signal semaphore associated with the command buffer.
         * @return The Vulkan semaphore used for signaling.
         */
        vk::Semaphore* signalSemaphore( uint32_t current_frame_index );

        /**
         * @brief Get the fence associated with the command buffer.
         * @return The Vulkan fence used for synchronization.
         */
        vk::Fence* fence();

        /**
         * @brief Submit cimmand-buffer to device-queue to execute its commands
         *
         * @return True if submission was successful, false otherwise
         */
        bool submit();

        /**
         * @brief Start recording to command buffer.
         * @return true if recording was successfully started; false otherwise.
         */
        bool begin();

        /**
         * @brief End recording to command buffer.
         * @return true if recording was successfully ended; false otherwise.
         */
        bool end();


        VkResult construct( kege::CommandBuffer::CreateInfo info );

        CommandBuffer( vk::Device* device );
        ~CommandBuffer();

    private:

        struct Synchronization
        {

            /**
             * The signal semaphore for synchronization on the GPU.
             */
            vk::Semaphore semaphore;

            /**
             * The fence for synchronization on the CPU.
             */
            vk::Fence fence;
        };

        VkRect2D _render_area;

        /**
         * The semaphore for synchronization on the GPU.
         */
        std::vector< vk::CommandBuffer::Synchronization > _synchronization;

        /**
         * The command-buffer handles for each frame in flight
         */
        std::vector< VkCommandBuffer > _handles;

        /**
         * Specifies the secondary command-buffer inheritance info
         */
        VkCommandBufferInheritanceInfo _inheritance_info;

        /**
         * Specifies if the allocated command-buffers are primary or secondary command-buffers
         */
        VkCommandBufferLevel _command_buffer_level;

        /**
         * The command-pool that allocated this command-buffer.
         */
        vk::CommandPool* _command_pool;

        /**
         * The _framebuffer hold the renderpass
         */
        const vk::Framebuffer* _framebuffer;

        /**
         * The core graphics device that manages the whole operation
         */
        vk::Device* _device;

        bool _is_recording;
    };
}}

#endif /* kege_graphics_vk_command_buffer_hpp */
