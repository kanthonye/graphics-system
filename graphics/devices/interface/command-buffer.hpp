//
//  command-buffer.hpp
//  new-engine
//
//  Created by Kenneth Esdaile on 1/3/24.
//

#ifndef kege_graphics_command_buffer_hpp
#define kege_graphics_command_buffer_hpp

#include "../../../graphics/devices/interface/framebuffer.hpp"
#include "../../../graphics/devices/interface/pipeline.hpp"
#include "../../../graphics/devices/interface/draw-command-buffer.hpp"

namespace kege{

   class VertexBuffer;

    /**
     * Before a GPU can execute any rendering or compute tasks, a sequence of commands needs to be
     * recorded into a command buffer. These commands typically include operations such as drawing
     * geometry, setting render states, and dispatching compute shaders. A CommandBuffer represents
     * a list of commands that the GPU (Graphics Processing Unit) needs to execute in order to render
     * a frame or perform other graphical operations.
     * @code
     * ...
     * command_buffer->begin();
     * command_buffer->beginRenderpass( framebuffer, kege::PRIMARY_COMMAND_BUFFER );
     * ... record to command buffer
     * command_buffer->endRenderpass();
     * command_buffer->end();
     * @endcode
     */
    class CommandBuffer : public kege::RefCounter
    {
    public:

        virtual void drawIndexed( const kege::Ref< kege::DrawIndexedCommandBuffer >& drawbuffer, uint64_t offset, uint32_t draw_count )const = 0;
        virtual void draw( const kege::Ref< kege::DrawCommandBuffer >& drawbuffer, uint64_t offset, uint32_t draw_count )const = 0;
        virtual void drawIndexed( const kege::DrawIndexedCommand& command )const = 0;
        virtual void draw( const kege::DrawCommand& command )const = 0;

        virtual void dispatch( uint32_t num_groups_x, uint32_t num_groups_y, uint32_t num_groups_z )const = 0;

        /**
         * @brief Execute secondary command buffer associated with this parent command buffer
         * @param command_buffers A vector of command buffers to execute
         */
        virtual void executeSecondaryCommandBuffers( std::vector< kege::Ref< kege::CommandBuffer > >& command_buffers ) = 0;

        /**
         * @brief Set the secondary command-buffer inheritance info.
         * @param command_buffer The primary command-buffer to inherit the info from.
         */
        virtual void setSecondaryCommandBufferInheritanceInfo( kege::CommandBuffer& command_buffer ) = 0;

        /**
         * @brief Begin a render pass with the given framebuffer.
         * @param framebuffer A pointer to the framebuffer to use in the render pass.
         * @param contents Specifies how the commands within the subpass will be provided.
         */
        virtual void beginRenderpass( const kege::Framebuffer* framebuffer, kege::SubpassContents contents ) = 0;

        /**
         * @brief Set the scissor rectangle for rendering.
         * @param x The x-coordinate of the scissor rectangle.
         * @param y The y-coordinate of the scissor rectangle.
         * @param width The width of the scissor rectangle.
         * @param height The height of the scissor rectangle.
         */
        virtual void setScissor( uint32_t x, uint32_t y, uint32_t width, uint32_t height ) = 0;

        /**
         * @brief Set the viewport parameters for rendering.
         * @param x The x-coordinate of the viewport.
         * @param y The y-coordinate of the viewport.
         * @param width The width of the viewport.
         * @param height The height of the viewport.
         */
        virtual void setViewport( float x, float y, float width, float height ) = 0;

        /**
         * @brief Clear specified color attachments within the active render pass.
         */
        virtual void clearColorAttachments( const kege::ClearColorState& state ) = 0;

        /**
         * @brief Clear specified depth attachments within the active render pass.
         */
        virtual void clearDepthAttachments( const kege::ClearDepthState& state ) = 0;

        /**
         * @brief Push constant values to the shaders.
         * @param pipeline_layout The pipeline-layout to bind the data to.
         * @param constants The push-constant-data-block load into the shader.
         */
        virtual void pushConstants( const kege::PipelineLayout* pipeline_layout, const kege::PushConstantBlock& constants ) = 0;

        /**
         * @brief Bind vertex buffers to the command buffer.
         * @param buffers A list of vertex-buffers to bind.
         */
        //virtual void bindVertexBuffer( const std::vector< kege::Ref< kege::VertexBuffer > >& buffers )const = 0;

        /**
         * @brief Bind a graphics or compute pipeline
         * @param pipeline A pointer to the pipeline to bind.
         */
        virtual void bindPipeline( const kege::Ref< kege::Pipeline >& pipeline )const = 0;

        /**
         * @brief End the current render pass.
         */
        virtual void endRenderpass() = 0;

        /**
         * @brief Get self pointer. This function is used for converting from base class to derived class
         */
        virtual const vk::CommandBuffer* vulkan()const{ return nullptr; }
        virtual vk::CommandBuffer* vulkan(){ return nullptr; }

        kege::DeviceQueueType type()const;

        /**
         * @brief Submit cimmand-buffer to device-queue to execute its commands
         *
         * @return True if submission was successful, false otherwise.
         */
        virtual bool submit() = 0;

        /**
         * @brief Start recording to command buffer.
         * @return true if recording was successfully started; false otherwise.
         */
        virtual bool begin() = 0;

        /**
         * @brief End recording to command buffer.
         * @return true if recording was successfully ended; false otherwise.
         */
        virtual bool end() = 0;

        struct CreateInfo
        {
            kege::DeviceQueueType queue_index;
            kege::CommandBufferType command_buffer_type;
        };
        static kege::Ref< kege::CommandBuffer > create( const CreateInfo& info );

    protected:

        CommandBuffer& operator =( const kege::CommandBuffer& other ) = delete;
        CommandBuffer( const kege::CommandBuffer& other ){}
        virtual ~CommandBuffer(){}
        CommandBuffer(){}

    protected:

        friend kege::Ref< kege::CommandBuffer >;
        kege::DeviceQueueType _type;
    };


    typedef std::vector< kege::Ref< kege::CommandBuffer > > CommandBufferCollection;
}

#endif /* kege_graphics_command_buffer_hpp */
