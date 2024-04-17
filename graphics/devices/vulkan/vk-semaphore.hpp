//
//  vk-semaphore.hpp
//  new-engine
//
//  Created by Kenneth Esdaile on 1/3/24.
//

#ifndef kege_graphics_vk_semaphore_hpp
#define kege_graphics_vk_semaphore_hpp

#include "../vulkan/vk.hpp"

namespace kege{namespace vk{

    /**
     * @brief Represents a Vulkan semaphore object.
     *
     * This class encapsulates a Vulkan semaphore, providing a convenient interface for
     * creating, managing, and using semaphore resources in Vulkan applications.
     */
    class Semaphore
    {
    public:

        /**
         * @brief Creates a Vulkan semaphore.
         *
         * @param device Pointer to the Vulkan device.
         * @param semaphore Reference to a VkSemaphore object to be filled with the created semaphore.
         *
         * @return VK_SUCCESS if the semaphore creation is successful, otherwise an error code.
         */
        static VkResult create(vk::Device* device, vk::Semaphore& semaphore);

        /**
         * @brief Retrieves the handle of the Vulkan semaphore.
         *
         * @return The Vulkan semaphore handle.
         */
        const VkSemaphore handle()const;

        /**
         * @brief Destructs the Semaphore object and releases associated Vulkan resources.
         */
        void destruct();

        /**
         * @brief Destructs the Semaphore object and releases associated Vulkan resources.
         */
        ~Semaphore();

        /**
         * @brief Constructs a Semaphore object.
         */
        Semaphore();

    private:

        VkSemaphore _handle;
        vk::Device* _device;
    };

}}

#endif /* kege_graphics_vk_semaphore_hpp */
