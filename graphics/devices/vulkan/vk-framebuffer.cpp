//
//  vk-framebuffer.cpp
//  new-engine
//
//  Created by Kenneth Esdaile on 12/30/23.
//

#include "vk-core.hpp"

namespace kege{namespace vk{

    VkResult Framebuffer::construct( const std::vector< kege::Framebuffer::Attachment >& attachments )
    {
        for (const kege::Framebuffer::Attachment& attachment : attachments )
        {
            attach( attachment );
        }

        kege::Ref< vk::Renderpass > renderpass = new vk::Renderpass( _device );
        for (auto& attachment : _color_attachments )
        {
            VkFormat format = attachment->vulkan()->format;
            renderpass->addAttachmentDescription
            (
                format,
                VK_SAMPLE_COUNT_1_BIT,
                VK_IMAGE_LAYOUT_UNDEFINED,
                VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL,
                kege::COLOR_ATTACHMENT
            );
        }

        if ( _depth_attachment )
        {
            VkFormat format = _depth_attachment->vulkan()->format;
            renderpass->addAttachmentDescription
            (
                format,
                VK_SAMPLE_COUNT_1_BIT,
                VK_IMAGE_LAYOUT_UNDEFINED,
                VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL,
                kege::DEPTH_ATTACHMENT
            );
        }

        VkResult result;
        if( (result = renderpass->construct()) != VK_SUCCESS )
        {
            KEGE_ERROR( "%s: Framebuffer creatation failed. Something went wrong with Renderpass creation.", vk::getError( result ) );
            return VK_ERROR_INITIALIZATION_FAILED;
        }

        return construct( renderpass );
    }

    void Framebuffer::attach( const kege::Framebuffer::Attachment& attachment )
    {
        _extent = { attachment.image->width(),  attachment.image->height() };
        if( attachment.attachment == kege::COLOR_ATTACHMENT )
        {
            _color_attachments.push_back( attachment.image );
        }
        else
        {
            _depth_attachment = attachment.image;
        }
    }

    const std::vector< kege::Ref< kege::Image > >& Framebuffer::getColorAttachments()const
    {
        return _color_attachments;
    }

    const kege::Ref< kege::Image >& Framebuffer::getDepthAttachment()const
    {
        return _depth_attachment;
    }

    VkResult Framebuffer::construct( const kege::Ref< vk::Renderpass >& renderpass )
    {
        std::vector< VkImageView > imageviews;
        for (auto& attachment : _color_attachments )
        {
            imageviews.push_back( attachment->vulkan()->view );
        }
        if ( _depth_attachment )
        {
            imageviews.push_back( _depth_attachment->vulkan()->view );
        }

        VkFramebufferCreateInfo info{};
        info.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
        info.attachmentCount = static_cast<uint32_t>( imageviews.size() );
        info.pAttachments = imageviews.data();
        info.renderPass = renderpass->handle();
        info.width  = _extent.width;
        info.height = _extent.height;
        info.layers = 1;

        VkResult result = vkCreateFramebuffer( renderpass->device()->getLogicalDevice(), &info, nullptr, &_framebuffer );
        if ( result != VK_SUCCESS )
        {
            KEGE_ERROR( "$s : Framebuffer creatation failed.", vk::getError( result ) );
            return result;
        }
        _renderpass = renderpass;
        return result;
    }

    const VkClearValue& Framebuffer::cleardepth()const
    {
        return _cleardepth;
    }

    VkClearValue& Framebuffer::cleardepth()
    {
        return _cleardepth;
    }

    const VkClearValue& Framebuffer::clearcolor()const
    {
        return _clearcolor;
    }

    VkClearValue& Framebuffer::clearcolor()
    {
        return _clearcolor;
    }

    const kege::Renderpass* Framebuffer::renderpass()const
    {
        return _renderpass.ref();
    }

    kege::Renderpass* Framebuffer::renderpass()
    {
        return _renderpass.ref();
    }

    const vk::Framebuffer* Framebuffer::vulkan()const
    {
        return this;
    }
    vk::Framebuffer* Framebuffer::vulkan()
    {
        return this;
    }

    const VkFramebuffer Framebuffer::handle()const
    {
        return _framebuffer;
    }

    const VkExtent2D& Framebuffer::extent()const
    {
        return _extent;
    }

    uint32_t Framebuffer::height()const
    {
        return _extent.height;
    }

    uint32_t Framebuffer::width()const
    {
        return _extent.width;
    }

    void Framebuffer::destruct()
    {
        _color_attachments.clear();
        _depth_attachment.clear();
        _renderpass.clear();

        if ( _framebuffer )
        {
            _device->waitIdle();
            vkDestroyFramebuffer( _device->getLogicalDevice(), _framebuffer, nullptr );
            _framebuffer = VK_NULL_HANDLE;
        }
    }

    Framebuffer::~Framebuffer()
    {
        destruct();
    }

    Framebuffer::Framebuffer( vk::Device* device )
    :   _framebuffer( VK_NULL_HANDLE )
    ,   _extent({})
    ,   _device( device )
    {
        _clearcolor = {{{0.1f, 0.1f, 0.1f, 1.0f}}};

        _cleardepth.depthStencil = {1.0f, 0};
        //_clear_values[0].color = {{0.2, 0.2, 0.225, 1.0}};
        //_clear_values[1].depthStencil = {1.0f, 0};
    }
}}
