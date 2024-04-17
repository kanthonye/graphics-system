//
//  vk-swapchain.hpp
//  new-engine
//
//  Created by Kenneth Esdaile on 12/30/23.
//

#ifndef kege_graphics_vk_swapchain_hpp
#define kege_graphics_vk_swapchain_hpp

#include "../vulkan/vk-semaphore.hpp"
#include "../vulkan/vk-framebuffer.hpp"

namespace kege{namespace vk{

    /**
     * @brief Represents a Vulkan swapchain object.
     *
     * This class encapsulates a Vulkan swapchain, providing a convenient interface for
     * managing and using swapchains in Vulkan applications.
     */
    class Swapchain : public kege::RefCounter
    {
    public:

        /**
         * @brief Retrieves the framebuffer at the specified index.
         *
         * @param index The index of the framebuffer to retrieve.
         * @return A pointer to the framebuffer.
         */
        const kege::Framebuffer* getFramebuffer( uint32_t index )const;

        /**
         * @brief Retrieves the current framebuffer.
         *
         * @return A pointer to the current framebuffer.
         */
        const kege::Framebuffer* getCurrentFramebuffer()const;

        /**
         * @brief Retrieves the number of framebuffers in the swapchain.
         *
         * @return The number of framebuffers.
         */
        uint32_t getFramebufferCount()const;


        /**
         * @brief Initializes the swapchain.
         *
         * @param device Pointer to the Vulkan device.
         * @return VK_SUCCESS if initialization is successful, otherwise an error code.
         */
        VkResult init( vk::Device* device );

        /**
         * @brief Retrieves the handle of the Vulkan swapchain.
         *
         * @return The Vulkan swapchain handle.
         */
        const VkSwapchainKHR handle()const;

        /**
         * @brief Retrieves the index of the image being rendered.
         *
         * @return The index of the image being rendered.
         */
        uint32_t getImageIndex()const;

        /**
         * @brief Checks if the framebuffer was resized.
         *
         * @return True if the framebuffer was resized, otherwise false.
         */
        bool framebufferResized()const;

        /**
         * @brief Acquires the next image in the swapchain.
         *
         * @return VK_SUCCESS if the image acquisition is successful, otherwise an error code.
         */
        VkResult acquireNextImage( uint32_t current_frame, VkSemaphore _wait_semaphore );

        /**
         * @brief Recreates the swapchain.
         *
         * @return VK_SUCCESS if recreation is successful, otherwise an error code.
         */
        VkResult recreate();

        /**
         * @brief Destructs the Swapchain object and releases associated Vulkan resources.
         */
        void destruct();

        /**
         * @brief Destructs the Swapchain object and releases associated Vulkan resources.
         */
        ~Swapchain();

        /**
         * @brief Constructs a Swapchain object.
         */
        Swapchain();

    private:

        std::vector< kege::Ref< vk::Framebuffer > > _framebuffers;

        VkSwapchainKHR _handle;
        vk::Device* _device;

        /**
         * The index of the image being rendered.
         */
        uint32_t _image_index;

    };

}}
#endif /* kege_graphics_vk_swapchain_hpp */
