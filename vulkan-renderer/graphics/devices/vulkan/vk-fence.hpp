//
//  vk-fence.hpp
//  new-engine
//
//  Created by Kenneth Esdaile on 1/3/24.
//

#ifndef kege_graphics_vk_fence_hpp
#define kege_graphics_vk_fence_hpp

#include "../vulkan/vk.hpp"

namespace kege{namespace vk{

    /**
     * @brief Represents a Vulkan fence object.
     *
     * This class encapsulates a Vulkan fence, providing a convenient interface for
     * creating, managing, and using fence resources in Vulkan applications.
     */
    class Fence
    {
    public:

        /**
         * @brief Creates a Vulkan fence.
         *
         * @param device Pointer to the Vulkan device.
         * @param fence Reference to a VkFence object to be filled with the created fence.
         *
         * @return VK_SUCCESS if the fence creation is successful, otherwise an error code.
         */
        static VkResult create(vk::Device* device, vk::Fence& fence);

        /**
         * @brief Retrieves the handle of the Vulkan fence.
         *
         * @return The Vulkan fence handle.
         */
        const VkFence handle()const;

        /**
         * @brief Destructs the Fence object and releases associated Vulkan resources.
         */
        void destruct();

        /**
         * @brief Destructs the Fence object and releases associated Vulkan resources.
         */
        ~Fence();

        /**
         * @brief Constructs a Fence object.
         */
        Fence();

    private:

        VkFence _handle;
        vk::Device* _device;
    };

}}

#endif /* kege_graphics_vk_fence_hpp */
