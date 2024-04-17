//
//  vk-command-buffer.cpp
//  new-engine
//
//  Created by Kenneth Esdaile on 12/30/23.
//

#include "vk-core.hpp"

namespace kege{namespace vk{

    void CommandBuffer::drawIndexed( const kege::Ref< kege::DrawIndexedCommandBuffer >& drawbuffer, uint64_t offset, uint32_t draw_count )const
    {
        drawbuffer->drawIndirect( this, offset, draw_count );
    }

    void CommandBuffer::draw( const kege::Ref< kege::DrawCommandBuffer >& drawbuffer, uint64_t offset, uint32_t draw_count )const
    {
        drawbuffer->drawIndirect( this, offset, draw_count );
    }

    void CommandBuffer::drawIndexed( const kege::DrawIndexedCommand& params )const
    {
        //vkCmdDrawIndexedIndirectCount(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, VkBuffer countBuffer, VkDeviceSize countBufferOffset, uint32_t maxDrawCount, uint32_t stride)
        vkCmdDrawIndexed( getCurrentCommandBuffer(), params.index_count, params.instance_count, params.first_index, params.vertex_offset, params.first_instance );
    }

    void CommandBuffer::draw( const kege::DrawCommand& params )const
    {
        vkCmdDraw( getCurrentCommandBuffer(), params.vertex_count, params.instance_count, params.first_vertex, params.first_instance );
    }

    void CommandBuffer::dispatch( uint32_t num_groups_x, uint32_t num_groups_y, uint32_t num_groups_z )const
    {
        try
        {
            vkCmdDispatch( getCurrentCommandBuffer(), num_groups_x, num_groups_y, num_groups_z );
        }
        catch ( const std::runtime_error& err )
        {
            throw err;
        }
        catch ( ... )
        {
            throw std::runtime_error("unknown error CommandBuffer::dispatch");
        }
    }

    void CommandBuffer::beginRenderpass( const kege::Framebuffer* framebuffer, kege::SubpassContents contents )
    {
        VkClearValue clear_values[2]
        {
            {0.0f, 0.0f, 0.0f, 1.0f},
            {1.0f, 0}
        };

        _framebuffer = framebuffer->vulkan();
        _render_area.extent = {_framebuffer->width(), _framebuffer->height()};
        _render_area.offset = {0, 0};

        VkRenderPassBeginInfo render_pass_info{};
        render_pass_info.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
        render_pass_info.renderArea = _render_area;
        render_pass_info.framebuffer = _framebuffer->handle();
        render_pass_info.renderPass = _framebuffer->renderpass()->vulkan()->handle();
        render_pass_info.pClearValues = clear_values;
        render_pass_info.clearValueCount = 2;

        VkSubpassContents subpass_contents =
        {
            (contents == kege::SUBPASS_CONTENTS_PRIMARY_COMMAND_BUFFERS) ?
            VK_SUBPASS_CONTENTS_INLINE :
            VK_SUBPASS_CONTENTS_SECONDARY_COMMAND_BUFFERS
        };

        vkCmdBeginRenderPass( getCurrentCommandBuffer(), &render_pass_info, subpass_contents );

//        VkViewport viewport{};
//        viewport.x = _render_area.offset.x;
//        viewport.y = _render_area.offset.y;
//        viewport.width = _render_area.extent.width;
//        viewport.height = _render_area.extent.height;
//        viewport.minDepth = 0.0f;
//        viewport.maxDepth = 1.0f;
//        vkCmdSetViewport( getCurrentCommandBuffer(), 0, 1, &viewport);
        
//        // vkCmdSetScissor() cannot be called in a subpass using secondary command buffers.
//        VkRect2D scissor{};
//        scissor.offset = _render_area.offset;
//        scissor.extent = _render_area.extent;
//        vkCmdSetScissor( getCurrentCommandBuffer(), 0, 1, &scissor );
    }

    void CommandBuffer::executeSecondaryCommandBuffers( std::vector< kege::Ref< kege::CommandBuffer > >& command_buffers )
    {
        VkCommandBuffer commands[ command_buffers.size() ];
        for (int i=0; i<command_buffers.size(); i++ )
        {
            commands[i] = command_buffers[ i ].ref()->vulkan()->getCurrentCommandBuffer();
        }

        vkCmdExecuteCommands( getCurrentCommandBuffer(), static_cast<uint32_t>( command_buffers.size() ), commands );
    }

    void CommandBuffer::setSecondaryCommandBufferInheritanceInfo( kege::CommandBuffer& command_buffer )
    {
       vk::CommandBuffer* comdbufr = command_buffer.vulkan();

        _inheritance_info = {};
        _inheritance_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_INHERITANCE_INFO;
        _inheritance_info.occlusionQueryEnable = VK_FALSE;
        _inheritance_info.framebuffer = comdbufr->_framebuffer->handle();
        _inheritance_info.renderPass = comdbufr->_framebuffer->renderpass()->vulkan()->handle();
        _render_area = comdbufr->_render_area;
    }

    void CommandBuffer::pushConstants( const kege::PipelineLayout* pipeline_layout, const kege::PushConstantBlock& constants )
    {
        VkShaderStageFlags stage_flags = 0;
        if ( (constants.shader_stages & kege::VERTEX_SHADER) == kege::VERTEX_SHADER )
        {
            stage_flags |= VK_SHADER_STAGE_VERTEX_BIT;
        }
        if ( (constants.shader_stages & kege::FRAGMENT_SHADER) == kege::FRAGMENT_SHADER )
        {
            stage_flags |= VK_SHADER_STAGE_FRAGMENT_BIT;
        }
        if ( (constants.shader_stages & kege::GEOMETRY_SHADER) == kege::GEOMETRY_SHADER )
        {
            stage_flags |= VK_SHADER_STAGE_GEOMETRY_BIT;
        }
        if ( (constants.shader_stages & kege::TESS_CONTROL_SHADER) == kege::TESS_CONTROL_SHADER )
        {
            stage_flags |= VK_SHADER_STAGE_TESSELLATION_CONTROL_BIT;
        }
        if ( (constants.shader_stages & kege::TESS_EVALUATION_SHADER) == kege::TESS_EVALUATION_SHADER )
        {
            stage_flags |= VK_SHADER_STAGE_TESSELLATION_EVALUATION_BIT;
        }
        if ( (constants.shader_stages & kege::COMPUTE_SHADER) == kege::COMPUTE_SHADER )
        {
            stage_flags |= VK_SHADER_STAGE_COMPUTE_BIT;
        }
        vkCmdPushConstants( getCurrentCommandBuffer(), pipeline_layout->vulkan()->handle(), stage_flags, constants.offset, constants.size, constants.data );
    }

    void CommandBuffer::bindPipeline( const kege::Ref< kege::Pipeline >& pipeline )const
    {
        const vk::Pipeline* p = pipeline->vulkan();
        const vk::PipelineLayout* l = p->getPipelineLayout()->vulkan();
        vkCmdBindPipeline( getCurrentCommandBuffer(), l->pipelineBindPoint(), p->handle() );
    }

    void CommandBuffer::setScissor( uint32_t x, uint32_t y, uint32_t width, uint32_t height )
    {
        VkRect2D scissor{};
        scissor.offset.x = x;
        scissor.offset.y = y;
        scissor.extent.width = width;
        scissor.extent.height = height;

        vkCmdSetScissor( getCurrentCommandBuffer(), 0, 1, &scissor );
    }

    void CommandBuffer::setViewport( float x, float y, float width, float height )
    {
        _render_area.offset.x = x;
        _render_area.offset.y = y;
        _render_area.extent.width = width;
        _render_area.extent.height = height;

        VkViewport viewport{};
        viewport.x = x;
        viewport.y = y;
        viewport.width = width;
        viewport.height = height;
        viewport.minDepth = 0.0f;
        viewport.maxDepth = 1.0f;
        
        vkCmdSetViewport( getCurrentCommandBuffer(), 0, 1, &viewport );
    }

    void CommandBuffer::clearColorAttachments( const kege::ClearColorState& state )
    {
        VkClearRect clear_rect = {};
        clear_rect.baseArrayLayer = 0;
        clear_rect.layerCount = 1;
        clear_rect.rect = _render_area;

        VkClearAttachment clear_attachment_color = {};
        clear_attachment_color.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
        clear_attachment_color.colorAttachment = 0; // Color attachment index
        clear_attachment_color.clearValue = {state.color[0], state.color[1], state.color[2], state.color[3]};//fb->clearcolor();
        vkCmdClearAttachments( getCurrentCommandBuffer(), 1, &clear_attachment_color, 1, &clear_rect); // Clear color attachment
    }

    void CommandBuffer::clearDepthAttachments( const kege::ClearDepthState& state )
    {
        VkClearRect clear_rect = {};
        clear_rect.baseArrayLayer = 0;
        clear_rect.rect = _render_area;
        clear_rect.layerCount = 1;

        VkClearAttachment clear_attachment_depth = {};
        clear_attachment_depth.aspectMask = VK_IMAGE_ASPECT_DEPTH_BIT;
        clear_attachment_depth.colorAttachment = VK_ATTACHMENT_UNUSED; // Not a color attachment
        clear_attachment_depth.clearValue = { state.value };
        vkCmdClearAttachments( getCurrentCommandBuffer(), 1, &clear_attachment_depth, 1, &clear_rect); // Clear depth-stencil attachment
    }

    const vk::Framebuffer* CommandBuffer::framebuffer()const
    {
        return _framebuffer;
    }
    
    void CommandBuffer::endRenderpass()
    {
        vkCmdEndRenderPass( getCurrentCommandBuffer() );
    }

    const VkCommandBuffer CommandBuffer::getCurrentCommandBuffer()const
    {
        uint32_t current_frame_index = _device->getRenderContext().getCurrentFrameIndex();
        return _handles[ current_frame_index ];
    }

    VkCommandBuffer CommandBuffer::getCurrentCommandBuffer()
    {
        uint32_t current_frame_index = _device->getRenderContext().getCurrentFrameIndex();
        return _handles[ current_frame_index ];
    }

    const vk::CommandBuffer* CommandBuffer::vulkan()const
    {
        return this;
    }

    vk::CommandBuffer* CommandBuffer::vulkan()
    {
        return this;
    }

    vk::Semaphore* CommandBuffer::signalSemaphore( uint32_t current_frame_index )
    {
        return &_synchronization[ current_frame_index ].semaphore;
    }

    vk::Fence* CommandBuffer::fence()
    {
        uint32_t current_frame_index = _device->getRenderContext().getCurrentFrameIndex();
        return &_synchronization[ current_frame_index ].fence;
    }

    uint32_t CommandBuffer::getQueueIndex()const
    {
        return _command_pool->getQueueIndex();
    }

    bool CommandBuffer::submit()
    {
       if( _command_buffer_level == VK_COMMAND_BUFFER_LEVEL_PRIMARY )
       {
           return _device->getRenderContext().submit( this );
       }
        return false;
    }
    
    bool CommandBuffer::begin()
    {
        VkCommandBuffer command_buffer = getCurrentCommandBuffer();
        vkResetCommandBuffer( command_buffer, 0 );

        VkCommandBufferBeginInfo info{};
        info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;

        if ( _command_buffer_level == VK_COMMAND_BUFFER_LEVEL_SECONDARY )
        {
            info.flags = VK_COMMAND_BUFFER_USAGE_RENDER_PASS_CONTINUE_BIT;
            info.pInheritanceInfo = &_inheritance_info;
        }

        VkResult result = vkBeginCommandBuffer( command_buffer, &info );
        if ( result != VK_SUCCESS )
        {
            KEGE_ERROR( vk::getError( result ) );
            return false;
        }
        
        _is_recording = true;
        return true;
    }

    bool CommandBuffer::end()
    {
        VkResult result = vkEndCommandBuffer( getCurrentCommandBuffer() );
        if ( result != VK_SUCCESS )
        {
            KEGE_ERROR( vk::getError( result ) );
            return false;
        }
        _is_recording = false;
        return true;
    }

    VkResult CommandBuffer::construct( kege::CommandBuffer::CreateInfo info )
    {
        _command_buffer_level = (info.command_buffer_type == kege::PRIMARY_COMMAND_BUFFER)
        ? VK_COMMAND_BUFFER_LEVEL_PRIMARY
        : VK_COMMAND_BUFFER_LEVEL_SECONDARY;

        _command_pool = &_device->getCommandPool( info.queue_index );
        _handles.resize( kege::MAX_FRAMES_IN_FLIGHT );

        VkResult result = _command_pool->allocateCommandBuffers
        (  _command_buffer_level
         , kege::MAX_FRAMES_IN_FLIGHT
         , _handles.data()
        );

        if ( result != VK_SUCCESS )
        {
            KEGE_ERROR("vk::CommandBuffer::create : Something went wrong wile creating a VkCommandBuffer handle");
            return result;
        };

        _synchronization.resize( kege::MAX_FRAMES_IN_FLIGHT );
        for (CommandBuffer::Synchronization& synchronization : _synchronization )
        {
            if( vk::Fence::create( _device, synchronization.fence ) != VK_SUCCESS )
            {
                KEGE_ERROR("vk::CommandBuffer::create : Something went wrong wile creating a vk::Fence");
                return VK_ERROR_INITIALIZATION_FAILED;
            }

            if( vk::Semaphore::create( _device, synchronization.semaphore ) != VK_SUCCESS )
            {
                KEGE_ERROR("vk::CommandBuffer::create : Something went wrong wile creating a vk::Semaphore");
                return VK_ERROR_INITIALIZATION_FAILED;
            }
        }
        _type = info.queue_index;
        return result;
    }

    CommandBuffer::CommandBuffer( vk::Device* device )
    :   _device( device )
    {}

    CommandBuffer::~CommandBuffer()
    {
        _synchronization.clear();

        if ( _command_pool )
        {
            _command_pool->freeCommandBuffer( uint32_t(_handles.size()), _handles.data() );
            _command_pool = nullptr;
        }
    }
}}
