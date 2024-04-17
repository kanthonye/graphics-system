//
//  vk-renderpass.cpp
//  new-engine
//
//  Created by Kenneth Esdaile on 12/30/23.
//

#include "vk-core.hpp"
namespace kege{namespace vk{

    void Renderpass::addAttachmentDescription
    (
        VkFormat format,
        VkSampleCountFlagBits samples,
        VkImageLayout initial_layout,
        VkImageLayout final_layout,
        kege::Attachment attachment
    )
    {
        VkAttachmentDescription attachment_description = {};
        attachment_description.format = format;
        attachment_description.samples = samples;

        /*
         VK_ATTACHMENT_LOAD_OP_LOAD: This option loads the existing contents of the
         attachment. It's useful when you want to preserve the previous content and
         continue rendering on top of it. For example, if you're doing incremental
         rendering and want to accumulate results.

         VK_ATTACHMENT_LOAD_OP_DONT_CARE: This option indicates that the previous
         contents of the attachment are not relevant. Vulkan does not guarantee the
         preservation or clearing of the attachment's contents. This can be useful
         for performance optimization if you don't need the previous contents.

         VK_ATTACHMENT_LOAD_OP_CLEAR: As you mentioned earlier, this option clears
         the attachment's contents at the beginning of the render pass. It's
         typically used when you want a clean slate for rendering.
         */
        attachment_description.loadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;

        attachment_description.storeOp = VK_ATTACHMENT_STORE_OP_STORE;  // Specify the store operation (e.g., store the attachment)
        attachment_description.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;  // Specify the stencil load operation (if applicable)
        attachment_description.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;  // Specify the stencil store operation (if applicable)
        attachment_description.initialLayout = initial_layout;  //VK_IMAGE_LAYOUT_UNDEFINED;  // Specify the initial layout of the attachment
        attachment_description.finalLayout = final_layout; //VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;  // Specify the final layout of the attachment

        if ( attachment == kege::DEPTH_ATTACHMENT )
        {
            _depth_attachment_index = static_cast<uint32_t>( _attachment_descriptions.size() );
        }
        _attachment_descriptions.push_back( attachment_description );
    }

//    void Renderpass::addDepthAttachment
//    (
//        VkFormat format, VkSampleCountFlagBits samples, VkImageLayout initial_layout, VkImageLayout final_layout
//    )
//    {
//        VkAttachmentDescription attachment_description = {};
//        attachment_description.format = format;
//        attachment_description.samples = samples;
//        attachment_description.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
//        attachment_description.storeOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
//        attachment_description.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
//        attachment_description.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
//        attachment_description.initialLayout = initial_layout;//VK_IMAGE_LAYOUT_UNDEFINED;
//        attachment_description.finalLayout = final_layout;//VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;
//
//        _depth_attachment_index = static_cast<uint32_t>( _attachment_descriptions.size() );
//        _attachment_descriptions.push_back( attachment_description );
//    }

    const vk::Renderpass* Renderpass::vulkan()const
    {
        return this;
    }

    vk::Renderpass* Renderpass::vulkan()
    {
        return this;
    }

    VkResult Renderpass::construct()
    {
        // Use subpass dependencies for layout transitions
        std::array<VkSubpassDependency, 2> dependencies;
        dependencies[0].srcSubpass = VK_SUBPASS_EXTERNAL;
        dependencies[0].dstSubpass = 0;
        dependencies[0].srcStageMask = VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT;
        dependencies[0].dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
        dependencies[0].srcAccessMask = VK_ACCESS_SHADER_READ_BIT;
        dependencies[0].dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
        dependencies[0].dependencyFlags = VK_DEPENDENCY_BY_REGION_BIT;

        dependencies[1].srcSubpass = 0;
        dependencies[1].dstSubpass = VK_SUBPASS_EXTERNAL;
        dependencies[1].srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
        dependencies[1].dstStageMask = VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT;
        dependencies[1].srcAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
        dependencies[1].dstAccessMask = VK_ACCESS_SHADER_READ_BIT;
        dependencies[1].dependencyFlags = VK_DEPENDENCY_BY_REGION_BIT;

        std::vector< VkAttachmentReference > color_attachment_references;
        std::vector< VkAttachmentReference > depth_attachment_references;
        for (int attachment = 0; attachment < _attachment_descriptions.size(); attachment++ )
        {
            VkAttachmentReference attachment_reference;
            attachment_reference.attachment = attachment;
            if ( _depth_attachment_index != attachment )
            {
                attachment_reference.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
                color_attachment_references.push_back( attachment_reference );
            }
            else
            {
                attachment_reference.layout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;
                depth_attachment_references.push_back( attachment_reference );
            }
        }

        VkSubpassDescription subpass_description = {};
        subpass_description.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
        subpass_description.pDepthStencilAttachment = depth_attachment_references.data();
        subpass_description.pColorAttachments = color_attachment_references.data();
        subpass_description.colorAttachmentCount = static_cast<uint32_t>( color_attachment_references.size() );

        VkRenderPassCreateInfo info{};
        info.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
        info.attachmentCount = static_cast<uint32_t>( _attachment_descriptions.size() );
        info.pAttachments = _attachment_descriptions.data();
        info.dependencyCount = static_cast< uint32_t >( dependencies.size() );
        info.pDependencies = dependencies.data();
        info.pSubpasses = &subpass_description;
        info.subpassCount = 1;

        return vkCreateRenderPass( _device->getLogicalDevice(), &info, nullptr, &_handle );
    }

    const VkRenderPass Renderpass::handle()const
    {
        return _handle;
    }

    VkRenderPass Renderpass::handle()
    {
        return _handle;
    }

    const vk::Device* Renderpass::device()const
    {
        return _device;
    }
    
    vk::Device* Renderpass::device()
    {
        return _device;
    }

    void Renderpass::destruct()
    {
        _attachment_descriptions.clear();

        if( _handle != VK_NULL_HANDLE )
        {
            _device->waitIdle();
            vkDestroyRenderPass( _device->getLogicalDevice(), _handle, nullptr );
            _handle = VK_NULL_HANDLE;
        }
    }

    Renderpass::~Renderpass()
    {
        destruct();
    }

    Renderpass::Renderpass( vk::Device* device )
    :   _handle( VK_NULL_HANDLE )
    ,   _device( device )
    ,   _depth_attachment_index( -1 )
    {}
}}
