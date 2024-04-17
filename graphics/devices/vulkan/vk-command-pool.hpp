//
//  vk-command-pool.hpp
//  new-engine
//
//  Created by Kenneth Esdaile on 1/3/24.
//

#ifndef kege_graphics_vk_command_pool_hpp
#define kege_graphics_vk_command_pool_hpp

#include "../vulkan/vk-fence.hpp"

namespace kege{namespace vk{
    /**
     * @brief Represents a Vulkan command pool.
     *
     * This class encapsulates a Vulkan command pool, providing a convenient interface for
     * managing command buffers and their allocation.
     */
    class CommandPool : public kege::RefCounter
    {
    public:

        static VkResult create( vk::Device* device, VkCommandPoolCreateFlags flags, kege::DeviceQueueType queue_index, vk::CommandPool& pool );

        VkResult allocateCommandBuffers( VkCommandBufferLevel level, int count, VkCommandBuffer* handle );
        void freeCommandBuffer( uint32_t count, VkCommandBuffer* command );
        kege::DeviceQueueType getQueueIndex()const;
        const VkCommandPool handle()const;
        void destruct();

        ~CommandPool();
        CommandPool();

    private:

        kege::DeviceQueueType _queue_type;
        VkCommandPool _handle;
        vk::Device* _device;
    };

}}
#endif /* kege_graphics_vk_command_pool_hpp */
