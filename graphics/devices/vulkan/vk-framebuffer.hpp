//
//  vk-framebuffer.hpp
//  new-engine
//
//  Created by Kenneth Esdaile on 12/30/23.
//

#ifndef kege_graphics_vk_framebuffer_hpp
#define kege_graphics_vk_framebuffer_hpp

#include "../vulkan/vk-renderpass.hpp"

namespace kege{namespace vk{

    /**
     * @brief Represents a Vulkan framebuffer object.
     *
     * This class encapsulates a Vulkan framebuffer, providing a convenient interface for
     * creating, managing, and using framebuffer resources in Vulkan applications.
     */
    class Framebuffer : public kege::Framebuffer
    {
    public:

        /**
         * @brief Constructs the framebuffer with the given attachments.
         *
         * @param attachments The to create the framebuffer with.
         *
         * @return VK_SUCCESS if the framebuffer construction is successful, otherwise an error.
         */
        VkResult construct( const std::vector< kege::Framebuffer::Attachment >& attachments );

        /**
         * @brief Constructs the framebuffer using a given render pass.
         *
         * @param renderpass A reference to the render pass object.
         *
         * @return VK_SUCCESS if the framebuffer construction is successful, otherwise an error.
         */
        VkResult construct( const kege::Ref< vk::Renderpass >& renderpass );

        /**
         * @brief atttach an image to be used as an framebuffer attachment.
         *
         * @param attachment The framebuffer attachment to attach.
         */
        void attach( const kege::Framebuffer::Attachment& attachment );

        /**
         * @brief Get the color attachements.
         *
         * @return attachment The color attachments.
         */
        const std::vector< kege::Ref< kege::Image > >& getColorAttachments()const;

        /**
         * @brief Get the depth attachement.
         *
         * @return attachment The depth attachment.
         */
        const kege::Ref< kege::Image >& getDepthAttachment()const;

        /**
         * @brief Retrieves the clear depth value.
         *
         * @return A reference to the clear depth value.
         */
        const VkClearValue& cleardepth()const;
        VkClearValue& cleardepth();

        /**
         * @brief Retrieves the clear color value.
         *
         * @return A reference to the clear color value.
         */
        const VkClearValue& clearcolor()const;
        VkClearValue& clearcolor();

        /**
         * @brief Retrieves the render pass associated with the framebuffer.
         *
         * @return A pointer to the render pass object.
         */
        const kege::Renderpass* renderpass()const;
        kege::Renderpass* renderpass();

        /**
         * @brief Retrieves the Vulkan framebuffer handle.
         *
         * @return The Vulkan framebuffer handle.
         */
        const vk::Framebuffer* vulkan()const;
        vk::Framebuffer* vulkan();

        /**
         * @brief Retrieves the handle of the Vulkan framebuffer.
         *
         * @return The handle of the Vulkan framebuffer.
         */
        const VkFramebuffer handle()const;

        /**
         * @brief Retrieves the extent (width and height) of the framebuffer.
         *
         * @return A reference to the extent of the framebuffer.
         */
        const VkExtent2D& extent()const;

        /**
         * @brief Retrieves the height of the framebuffer.
         *
         * @return The height of the framebuffer.
         */
        uint32_t height()const;

        /**
         * @brief Retrieves the width of the framebuffer.
         *
         * @return The width of the framebuffer.
         */
        uint32_t width()const;

        /**
         * @brief Destructs the Framebuffer object and releases associated Vulkan resources.
         */
        void destruct();

        /**
         * @brief Constructs a Framebuffer object.
         */
        ~Framebuffer();

        /**
         * @brief Constructs a Framebuffer object.
         */
        Framebuffer( vk::Device* device );

    private:

        std::vector< kege::Ref< kege::Image > > _color_attachments;
        kege::Ref< kege::Image > _depth_attachment;

        kege::Ref< vk::Renderpass > _renderpass;

        vk::Device* _device;
        VkFramebuffer _framebuffer;

        VkClearValue _clearcolor;
        VkClearValue _cleardepth;
        VkExtent2D _extent;
    };

}}
#endif /* kege_graphics_vk_framebuffer_hpp */
