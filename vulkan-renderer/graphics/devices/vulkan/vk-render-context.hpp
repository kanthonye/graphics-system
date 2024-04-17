//
//  vk-render-context.hpp
//  new-engine
//
//  Created by Kenneth Esdaile on 1/7/24.
//

#ifndef kege_graphics_vk_render_context_hpp
#define kege_graphics_vk_render_context_hpp

#include "../vulkan/vk-swapchain.hpp"
#include "../vulkan/vk-device-queue.hpp"

namespace kege{namespace vk{
    
    /**
     * @brief Represents a Vulkan render context.
     *
     * This class encapsulates a Vulkan render context, providing a convenient interface for
     * managing and using render contexts in Vulkan applications.
     */
    class RenderContext : public kege::RenderContext
    {
    public:

        const kege::Framebuffer* getFramebuffer( uint32_t index )const;

        /**
         * @brief Submit a command buffer to a rendering queue.
         * @param command A pointer to the command buffer to be submitted.
         * @return true if the submission was successful; false otherwise.
         */
        bool submit( kege::CommandBuffer* command );

        const kege::Framebuffer* getFramebuffer()const;
        
        /**
         * @fn Initalize this render-context
         * @return A the results of the initalization
         */
        VkResult init( vk::Device* device );

        /**
         * @fn Get the current frame-index.
         * @return Integer index
         */
        uint32_t getCurrentFrameIndex()const;

//        /**
//         * @brief Begin submition of graphics command-buffer
//         * @note This function should be called before any graphics command-buffer submission.
//         */
//        bool beginGraphicsCommand();
//
//        /**
//         * @brief End graphics command-buffer submission
//         */
//        void endGraphicsCommand();
//
//        /**
//         * @brief Begin submition of compute command-buffer
//         * @note This function should be called before any compute command-buffer submission.
//         */
//        bool beginComputeCommand();
//
//        /**
//         * @brief End compute command-buffer submission
//         */
//        void endComputeCommand();

        bool beginRenderProcess();
        void endRenderProcess();

        /**
         * @brief Present the rendered graphics
         */
        bool present();

        /**
         * @fn Clear the framebuffer.
         * @note This function should only be called if the rendering content is contained in th primary command-buffers
         */
        void clearFramebuffer();

        void uninit();
        
        RenderContext();

    protected:

        vk::RenderContext& operator =( const vk::RenderContext& other ) = delete;
        RenderContext( const vk::RenderContext& other ){}
        VkResult initDeviceQueues( vk::Device* device );
        VkResult waitForFences();
        void resetFences();

    protected:


       std::vector< std::vector< vk::Fence* > > _fences;
        std::vector< vk::Semaphore > _semaphores;

        vk::DeviceQueue _graphics_queue;
        vk::DeviceQueue _compute_queue;
        vk::DeviceQueue _present_queue;

        vk::Swapchain _swapchain;
        vk::Device* _device;

        VkSemaphore _wait_semaphore;

        /**
         * Flag indicating whether the framebuffer was resized.
         */
        bool _framebuffer_resized;

        /**
         * The index of the current frame.
         */
        int32_t _current_frame;
    };

}}
#endif /* kege_graphics_vk_render_context_hpp */
