//
//  vk-device-queue.hpp
//  new-engine
//
//  Created by Kenneth Esdaile on 1/3/24.
//

#ifndef kege_graphics_vk_device_queue_hpp
#define kege_graphics_vk_device_queue_hpp

#include "../vulkan/vk.hpp"
#include "../vulkan/vk-fence.hpp"
#include "../vulkan/vk-semaphore.hpp"

namespace kege{namespace vk{

    /**
     * @brief Represents a Vulkan device queue.
     *
     * This class encapsulates a Vulkan device queue, providing a convenient interface for
     * submitting command buffers and presenting rendered images in Vulkan applications.
     */
    class DeviceQueue : public kege::RefCounter
    {
    public:

        /**
         * @brief Presents the rendered image to the screen.
         *
         * @param swapchain Pointer to the swapchain.
         * @return True if presentation was successful; false otherwise.
         */
        VkResult present( vk::Swapchain* swapchain, VkSemaphore* wait_semaphores, uint32_t count );

        /**
         * @brief Submits a command buffer to the rendering queue.
         *
         * @param command A pointer to the command buffer to be submitted.
         * @return True if the submission was successful; false otherwise.
         */
        virtual bool submit( vk::CommandBuffer* command, VkSemaphore* wait_semaphore, uint32_t count, uint32_t current_frame );

        /**
         * @brief Waits for fences associated with the swapchain.
         *
         * @param current_frame The current_frame index.
         * @return The result of the operation.
         */
        //VkResult waitForFences( uint32_t current_frame );

        /**
         * @brief Resets fences associated with the swapchain.
         *
         * @param current_frame The current_frame index.
         */
        //void resetFences( uint32_t current_frame );

        /**
         * @brief Initializes the device queue.
         *
         * @param device Pointer to the Vulkan device.
         * @return VK_SUCCESS if initialization is successful; otherwise an error code.
         */
        virtual VkResult init( vk::Device* device, kege::DeviceQueueType queue_type );

        /**
         * @brief Uninitializes the device queue.
         */
        virtual void uninit();

        /**
         * @brief Destructs the DeviceQueue object.
         */
        virtual ~DeviceQueue();

        /**
         * @brief Constructs a DeviceQueue object.
         */
        DeviceQueue();

    protected:

        /**
         * fences that were submitted durring a recording frame thats must be reset
         */
        //std::vector< std::vector< vk::Fence* > > _fences;
        VkQueue _handle;

        vk::Device* _device;
        kege::DeviceQueueType _queue_type;
    };

}}

#endif /* kege_graphics_vk_device_queue_hpp */
