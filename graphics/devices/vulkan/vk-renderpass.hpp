//
//  vk-renderpass.hpp
//  new-engine
//
//  Created by Kenneth Esdaile on 12/30/23.
//

#ifndef kege_graphics_vk_renderpass_hpp
#define kege_graphics_vk_renderpass_hpp

#include "../vulkan/vk.hpp"

namespace kege{namespace vk{

    /**
     * @brief Represents a Vulkan render pass object.
     *
     * This class encapsulates a Vulkan render pass, providing a convenient interface for
     * creating, managing, and using render pass resources in Vulkan applications.
     */
    class Renderpass : public kege::Renderpass
    {
    public:

        /**
         * @brief Adds a color attachment to the render pass.
         *
         * @param attachment The attachment type.
         * @param format The format of the color attachment.
         * @param samples The number of samples for the color attachment.
         * @param initial_layout The initial layout of the color attachment.
         * @param final_layout The final layout of the color attachment.
         */
        void addAttachmentDescription
        (
            VkFormat format,
            VkSampleCountFlagBits samples,
            VkImageLayout initial_layout,
            VkImageLayout final_layout,
            kege::Attachment attachment
        );

        /**
         * @brief Retrieves a pointer to the Vulkan render pass handle.
         *
         * @return A pointer to the Vulkan render pass handle.
         */
        const vk::Renderpass* vulkan()const;
        vk::Renderpass* vulkan();

        /**
         * @brief Retrieves the Vulkan render pass handle.
         *
         * @return The Vulkan render pass handle.
         */
        const VkRenderPass handle()const;
        VkRenderPass handle();

        /**
         * @brief Retrieves a pointer to the Vulkan device.
         *
         * @return A pointer to the Vulkan device.
         */
        const vk::Device* device()const;
        vk::Device* device();

        /**
         * @brief Constructs the Vulkan render pass.
         *
         * @return VK_SUCCESS if the render pass construction is successful, otherwise an error code.
         */
        VkResult construct();

        /**
         * @brief Destructs the Renderpass object and releases associated Vulkan resources.
         */
        void destruct();

        /**
         * @brief Destructs the Renderpass object and releases associated Vulkan resources.
         */
        ~Renderpass();

        /**
         * @brief Constructs a Renderpass object.
         *
         * @param device Pointer to the Vulkan device.
         */
        Renderpass( vk::Device* device );

    private:

        std::vector< VkAttachmentDescription > _attachment_descriptions;
        int _depth_attachment_index; 

        VkRenderPass _handle;
        vk::Device* _device;
    };

}}
#endif /* kege_graphics_vk_renderpass_hpp */
