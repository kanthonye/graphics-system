//
//  vk-render-context.cpp
//  new-engine
//
//  Created by Kenneth Esdaile on 1/7/24.
//

#include "vk-device.hpp"
#include "vk-command-buffer.hpp"
#include "vk-render-context.hpp"

namespace kege{namespace vk{

    const kege::Framebuffer* RenderContext::getFramebuffer( uint32_t index )const
    {
        return _swapchain.getFramebuffer( index );
    }

    bool RenderContext::submit( kege::CommandBuffer* command_buffer )
    {
        vk::CommandBuffer* vk_command_buffer = command_buffer->vulkan();

        bool submit_successful = false;
        switch ( command_buffer->type() )
        {
            case kege::COMPUTE_QUEUE: submit_successful = _compute_queue.submit( vk_command_buffer, &_wait_semaphore, 1, _current_frame );
                break;

            case kege::GRAPHICS_QUEUE: submit_successful = _graphics_queue.submit( vk_command_buffer, &_wait_semaphore, 1, _current_frame );
                break;

            default: break;
        }

        /**
         * Collect the command-buffer fence. We need will reset the all when the frame begins again
         */
        if ( submit_successful )
        {
            _fences[ _current_frame ].push_back( vk_command_buffer->fence() );
            _wait_semaphore = vk_command_buffer->signalSemaphore( _current_frame )->handle();
        }

        return submit_successful;
    }

    const kege::Framebuffer* RenderContext::getFramebuffer()const
    {
        return _swapchain.getCurrentFramebuffer();
    }

    uint32_t RenderContext::getCurrentFrameIndex()const
    {
        return _current_frame;
    }

//    bool RenderContext::beginGraphicsCommand()
//    {
//        if( _graphics_queue.waitForFences( _current_frame ) == VK_SUCCESS )
//        {
//            if( _swapchain.acquireNextImage( _current_frame, _wait_semaphore ) == VK_SUCCESS )
//            {
//                _graphics_queue.resetFences( _current_frame );
//                return true;
//            }
//        }
//        return false;
//    }
//
//    void RenderContext::endGraphicsCommand()
//    {
//        present();
//    }

//    bool RenderContext::beginComputeCommand()
//    {
//        if( _compute_queue.waitForFences( _current_frame ) == VK_SUCCESS )
//        {
//            _compute_queue.resetFences( _current_frame );
//            return true;
//        }
//        return false;
//    }
//
//    void RenderContext::endComputeCommand()
//    {
//    }
//
//    bool RenderContext::present()
//    {
//        return true;
//    }
    
    bool RenderContext::beginRenderProcess()
    {
        if( waitForFences() != VK_SUCCESS ) 
            return false;

        _wait_semaphore = _semaphores[ _current_frame ].handle();
        if( _swapchain.acquireNextImage( _current_frame, _wait_semaphore ) != VK_SUCCESS )
            return false;

        resetFences();
        return true;
    }

    void RenderContext::endRenderProcess()
    {
        VkResult result = _present_queue.present( &_swapchain, &_wait_semaphore, 1 );
        if ( result != VK_SUCCESS )
        {
            if ( result == VK_ERROR_OUT_OF_DATE_KHR || _framebuffer_resized )
            {
                _swapchain.recreate();
            }
            else if ( result != VK_SUBOPTIMAL_KHR )
            {
                KEGE_ERROR( getError( result ) );
                throw std::runtime_error("failed to present swap chain image!");
                //return false;
            }
        }
        _current_frame = (_current_frame + 1) % kege::MAX_FRAMES_IN_FLIGHT;
    }


    VkResult RenderContext::waitForFences()
    {
        if ( !_fences[ _current_frame ].empty() )
        {
            std::vector< VkFence > fence_handles;
            for( vk::Fence* fence : _fences[ _current_frame ] )
            {
                fence_handles.push_back( fence->handle() );
            }

            uint32_t total_fences = static_cast<uint32_t>( fence_handles.size() );
            VkResult result = vkWaitForFences( _device->getLogicalDevice(), total_fences, fence_handles.data(), VK_TRUE, UINT64_MAX );
            if (result != VK_SUCCESS)
            {
                KEGE_ERROR( "vk::DeviceQueue::waitForFences() : %s", vk::getError( result ) );
                return result;
            }
        }
        return VK_SUCCESS;
    }

    void RenderContext::resetFences()
    {
        if ( _fences[ _current_frame ].size() )
        {
            std::vector< VkFence > fence_handles;
            for( vk::Fence* fence : _fences[ _current_frame ] )
            {
                fence_handles.push_back( fence->handle() );
            }
            uint32_t total_fences = static_cast<uint32_t>( fence_handles.size() );
            vkResetFences( _device->getLogicalDevice(), total_fences, fence_handles.data() );
            _fences[ _current_frame ].clear();
        }
    }

    VkResult RenderContext::init( vk::Device* device )
    {
        _device = device;
        _graphics_queue.init( device, kege::GRAPHICS_QUEUE );
        _compute_queue.init( device, kege::COMPUTE_QUEUE );
        _present_queue.init( device, kege::PRESENT_QUEUE );

        _fences.resize( kege::MAX_FRAMES_IN_FLIGHT );
        _semaphores.resize( kege::MAX_FRAMES_IN_FLIGHT );
        for (int i=0; i<kege::MAX_FRAMES_IN_FLIGHT; i++)
        {
            if ( vk::Semaphore::create( _device, _semaphores[ i ] ) != VK_SUCCESS )
            {
                KEGE_ERROR("something when wrong while creating vk::Semaphore!");
                return VK_ERROR_INITIALIZATION_FAILED;
            }
        }

        if ( _swapchain.init( device ) != VK_SUCCESS )
        {
            KEGE_ERROR("something when wrong while initalizing vk::Swapchain.");
            return VK_ERROR_INITIALIZATION_FAILED;
        }

        return VK_SUCCESS;
    }

    void RenderContext::uninit()
    {
        _semaphores.clear();
        _graphics_queue.uninit();
        _compute_queue.uninit();
        _present_queue.uninit();
        _swapchain.destruct();
    }

    RenderContext::RenderContext()
    :   _wait_semaphore( VK_NULL_HANDLE )
    ,   _current_frame( 0 )
    ,   _framebuffer_resized( false )
    ,   _device( nullptr )
    {}
}}
