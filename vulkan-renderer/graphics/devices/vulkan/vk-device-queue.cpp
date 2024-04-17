//
//  vk-device-queue.cpp
//  new-engine
//
//  Created by Kenneth Esdaile on 1/3/24.
//

#include "vk-core.hpp"

namespace kege{namespace vk{

    bool DeviceQueue::submit( vk::CommandBuffer* command_buffer, VkSemaphore* wait_semaphores, uint32_t count, uint32_t current_frame )
    {
        VkCommandBuffer command_buffers[] = { command_buffer->getCurrentCommandBuffer() };
        VkSemaphore signal_semaphores[] = { command_buffer->signalSemaphore( current_frame )->handle() };

        VkSubmitInfo submit_info{};
        submit_info.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
        submit_info.pCommandBuffers = command_buffers;
        submit_info.commandBufferCount = 1;
        submit_info.pSignalSemaphores = signal_semaphores;
        submit_info.signalSemaphoreCount = 1;
        submit_info.pWaitSemaphores = wait_semaphores;
        submit_info.waitSemaphoreCount = count;

        /**
         * submit the command-buffer to device queue
         */
        VkResult result;
        if ( command_buffer->type() == kege::GRAPHICS_QUEUE )
        {
            VkPipelineStageFlags wait_stages[] = { VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT };
            submit_info.pWaitDstStageMask = wait_stages;
            result = vkQueueSubmit( _handle, 1, &submit_info, command_buffer->fence()->handle() );
        }
        else
        {
            VkPipelineStageFlags wait_stages[] = { VK_PIPELINE_STAGE_COMPUTE_SHADER_BIT };
            submit_info.pWaitDstStageMask = wait_stages;
            result = vkQueueSubmit( _handle, 1, &submit_info, command_buffer->fence()->handle() );
        }

        if ( result != VK_SUCCESS )
        {
            KEGE_ERROR( "%s: failed to submit command buffer!", getError( result ) );
            return false;
        }
        return true;
    }

    VkResult DeviceQueue::present( vk::Swapchain* swapchain, VkSemaphore* wait_semaphores, uint32_t count )
    {
        uint32_t image_indices[] = { swapchain->getImageIndex() };
        VkSwapchainKHR swapchains[] = { swapchain->handle() };

        VkPresentInfoKHR present_info{};
        present_info.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
        present_info.pImageIndices = image_indices;
        present_info.waitSemaphoreCount = 1;
        present_info.pWaitSemaphores = wait_semaphores;
        present_info.swapchainCount = count;
        present_info.pSwapchains = swapchains;
        return vkQueuePresentKHR( _handle, &present_info );
    }

//    VkResult DeviceQueue::waitForFences( uint32_t current_frame )
//    {
//        if ( !_fences[ current_frame ].empty() )
//        {
//            std::vector< VkFence > fence_handles;
//            for( vk::Fence* fence : _fences[ current_frame ] )
//            {
//                fence_handles.push_back( fence->handle() );
//            }
//
//            uint32_t total_fences = static_cast<uint32_t>( fence_handles.size() );
//            VkResult result = vkWaitForFences( _device->getLogicalDevice(), total_fences, fence_handles.data(), VK_TRUE, UINT64_MAX );
//            if (result != VK_SUCCESS)
//            {
//                KEGE_ERROR( "vk::DeviceQueue::waitForFences() : %s", vk::getError( result ) );
//                return result;
//            }
//        }
//        return VK_SUCCESS;
//    }
//
//    void DeviceQueue::resetFences( uint32_t current_frame )
//    {
//        if ( _fences[ current_frame ].size() )
//        {
//            std::vector< VkFence > fence_handles;
//            for( vk::Fence* fence : _fences[ current_frame ] )
//            {
//                fence_handles.push_back( fence->handle() );
//            }
//            uint32_t total_fences = static_cast<uint32_t>( fence_handles.size() );
//            vkResetFences( _device->getLogicalDevice(), total_fences, fence_handles.data() );
//            _fences[ current_frame ].clear();
//        }
//    }

    VkResult DeviceQueue::init( vk::Device* device, kege::DeviceQueueType queue_type )
    {
        _device = device;
        _queue_type = queue_type;
        //_fences.resize( kege::MAX_FRAMES_IN_FLIGHT );
        const vk::DeviceQueueFamily& device_queue_family = device->getPhysicalDevice().deviceQueueFamily();
        vkGetDeviceQueue( device->getLogicalDevice(), device_queue_family[ queue_type ].value(), 0, &_handle );
        return VK_SUCCESS;
    }

    void DeviceQueue::uninit()
    {
        //_fences.clear();
    }

    DeviceQueue::~DeviceQueue()
    {
        uninit();
    }

    DeviceQueue::DeviceQueue()
    :   _device( nullptr )
    ,   _queue_type()
    {
    }
}}
