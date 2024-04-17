//
//  framebuffer.hpp
//  new-engine
//
//  Created by Kenneth Esdaile on 12/30/23.
//

#ifndef kege_graphics_framebuffer_hpp
#define kege_graphics_framebuffer_hpp

#include "../../../graphics/devices/interface/image.hpp"
#include "../../../graphics/devices/interface/renderpass.hpp"

namespace kege{

    class Framebuffer : public kege::RefCounter
    {
    public:

        struct Attachment
        {
            kege::Ref< kege::Image > image;
            kege::Attachment attachment;
        };

        static kege::Ref< kege::Framebuffer > create( const std::vector< kege::Framebuffer::Attachment >& info );

        /**
         * @brief atttach an image to be used as an framebuffer attachment.
         *
         * @param attachment The framebuffer attachment.
         */
        virtual void attach( const kege::Framebuffer::Attachment& attachment ) = 0;

        /**
         * @brief Get the color attachements.
         *
         * @return attachment The color attachments.
         */
        virtual const std::vector< kege::Ref< kege::Image > >& getColorAttachments()const = 0;

        /**
         * @brief Get the depth attachement.
         *
         * @return attachment The depth attachment.
         */
        virtual const kege::Ref< kege::Image >& getDepthAttachment()const = 0;

        virtual const vk::Framebuffer* vulkan()const{ return nullptr; }
        virtual vk::Framebuffer* vulkan(){ return nullptr; }

        /**
         * @brief Retrieves the render pass associated with the framebuffer.
         *
         * @return A pointer to the render pass object.
         */
        virtual const kege::Renderpass* renderpass()const{ return nullptr; }

        /**
         * @brief Retrieves the render pass associated with the framebuffer.
         *
         * @return A pointer to the render pass object.
         */
        virtual kege::Renderpass* renderpass(){ return nullptr; }

        /**
         * @brief Retrieves the height of the framebuffer.
         *
         * @return The height of the framebuffer.
         */
        virtual uint32_t height()const = 0;

        /**
         * @brief Retrieves the width of the framebuffer.
         *
         * @return The width of the framebuffer.
         */
        virtual uint32_t width()const = 0;

    protected:

        Framebuffer& operator =( const kege::Framebuffer& other ) = delete;
        Framebuffer( const kege::Framebuffer& other ) = delete;
        virtual ~Framebuffer(){}
        Framebuffer(){}

    private:

        friend kege::Ref< kege::Framebuffer >;
    };;

}
#endif /* kege_graphics_framebuffer_hpp */
