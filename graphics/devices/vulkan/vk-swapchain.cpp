//
//  vk-swapchain.cpp
//  new-engine
//
//  Created by Kenneth Esdaile on 12/30/23.
//

#include "vk-core.hpp"

namespace kege{namespace vk{

    VkPresentModeKHR chooseSwapPresentMode
    (
        const std::vector< VkPresentModeKHR >& available_present_modes
    )
    {
        for ( const auto& available_present_mode : available_present_modes )
        {
            if ( available_present_mode == VK_PRESENT_MODE_MAILBOX_KHR )
            {
                return available_present_mode;
            }
        }
        return VK_PRESENT_MODE_FIFO_KHR;
    }

    VkSurfaceFormatKHR chooseSwapSurfaceFormat
    (
        const std::vector< VkSurfaceFormatKHR >& available_formats
    )
    {
        for ( const auto& available_format : available_formats )
        {
            if ( available_format.format == VK_FORMAT_B8G8R8A8_UNORM && available_format.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR )
            {
                return available_format;
            }
        }
        return available_formats[0];
    }

    VkFormat supportedFormat
    (
         VkPhysicalDevice physical_device,
         const std::vector<VkFormat>& candidates,
         VkImageTiling tiling,
         VkFormatFeatureFlags features
    )
    {
        for (VkFormat format : candidates)
        {
            VkFormatProperties props;
            vkGetPhysicalDeviceFormatProperties( physical_device, format, &props );

            if (tiling == VK_IMAGE_TILING_LINEAR && (props.linearTilingFeatures & features) == features) {
                return format;
            } else if (tiling == VK_IMAGE_TILING_OPTIMAL && (props.optimalTilingFeatures & features) == features) {
                return format;
            }
        }

        throw std::runtime_error("failed to find supported format!");
    }

    const kege::Framebuffer* Swapchain::getFramebuffer( uint32_t index )const
    {
        return _framebuffers[ index ].ref();
    }

    uint32_t Swapchain::getFramebufferCount()const
    {
        return uint32_t( _framebuffers.size() );
    }

    struct SwapchainInfo
    {
        vk::SwapChainSupportDetails swapchain_support_details;
        VkSurfaceFormatKHR surface_format;
        VkPresentModeKHR present_mode;
        VkExtent2D extent;
        VkFormat format;
        uint32_t image_count;
        VkFormat depth_format;
    };

    void getSwapchainInfo( vk::Device* device, SwapchainInfo& info )
    {
        querySwapChainSupport( device->getSurface(), device->getPhysicalDevice().handle(), info.swapchain_support_details );
        info.surface_format = chooseSwapSurfaceFormat( info.swapchain_support_details.formats );
        info.present_mode = chooseSwapPresentMode( info.swapchain_support_details.present_modes );
        info.extent = chooseSwapExtent( device->window()->handle(), info.swapchain_support_details.capabilities );
        info.format = info.surface_format.format;

        info.image_count = MAX_FRAMES_IN_FLIGHT;//_device->capabilities().minImageCount;// + 1;
        if ( info.swapchain_support_details.capabilities.maxImageCount > 0 && info.image_count > info.swapchain_support_details.capabilities.maxImageCount )
        {
            info.image_count = info.swapchain_support_details.capabilities.maxImageCount;
        }

        info.depth_format = supportedFormat
        (   device->getPhysicalDevice().handle()
         ,  {VK_FORMAT_D32_SFLOAT, VK_FORMAT_D32_SFLOAT_S8_UINT, VK_FORMAT_D24_UNORM_S8_UINT}
         ,  VK_IMAGE_TILING_OPTIMAL
         ,  VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT
         );
    }


    VkSwapchainKHR createSwapchainhandle( vk::Device* device, SwapchainInfo& swapchain_info, VkResult& result )
    {
        VkSwapchainCreateInfoKHR create_info{};
        create_info.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
        create_info.surface = device->getSurface();
        create_info.minImageCount = swapchain_info.image_count;
        create_info.imageFormat = swapchain_info.surface_format.format;
        create_info.imageColorSpace = swapchain_info.surface_format.colorSpace;
        create_info.imageExtent = swapchain_info.extent;
        create_info.imageArrayLayers = 1;
        create_info.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;

        const vk::DeviceQueueFamily& device_queue_family = device->getPhysicalDevice().deviceQueueFamily();

        uint32_t queue_family_indices[] =
        {
            device_queue_family[ kege::GRAPHICS_QUEUE ].value(),
            device_queue_family[ kege::PRESENT_QUEUE ].value()
        };

        if (device_queue_family[ kege::GRAPHICS_QUEUE ].value() !=
            device_queue_family[ kege::PRESENT_QUEUE ].value() )
        {
            create_info.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
            create_info.queueFamilyIndexCount = 2;
            create_info.pQueueFamilyIndices = queue_family_indices;
        }
        else
        {
            create_info.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
        }

        create_info.preTransform = swapchain_info.swapchain_support_details.capabilities.currentTransform;
        create_info.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
        create_info.presentMode = swapchain_info.present_mode;
        create_info.clipped = VK_TRUE;

        VkSwapchainKHR swapchain_handle;
        result = vkCreateSwapchainKHR( device->getLogicalDevice(), &create_info, nullptr, &swapchain_handle );
        if ( result != VK_SUCCESS )
        {
            KEGE_ERROR("%s : swapchain -> vkCreateSwapchainKHR()", getError( result ));
            return VK_NULL_HANDLE;
        }

        // get swapchain image count. get swapchain images
        vkGetSwapchainImagesKHR( device->getLogicalDevice(), swapchain_handle, &swapchain_info.image_count, nullptr );

        return swapchain_handle;
    }

    std::vector< kege::Ref< vk::Framebuffer > > createSwapchainFramebuffer
    (  vk::Device* device
     , kege::Ref< vk::Image2d > depth_image
     , kege::Ref< vk::Renderpass > renderpass
     , VkSwapchainKHR swapchain
     , SwapchainInfo& swapchain_info
     , VkResult& result
    )
    {
        std::vector< VkImage > color_images;
        color_images.resize( swapchain_info.image_count );
        vkGetSwapchainImagesKHR( device->getLogicalDevice(), swapchain, &swapchain_info.image_count, color_images.data() );

        // create swapchain framebuffers using swapchain images as render-targets
        std::vector< kege::Ref< vk::Framebuffer > > framebuffers( swapchain_info.image_count );
        for (size_t i = 0; i < swapchain_info.image_count; i++)
        {
            VkImageView image_view;
            result = vk::createView
            (  device->getLogicalDevice()
             , swapchain_info.format
             , VK_IMAGE_VIEW_TYPE_2D
             , VK_IMAGE_ASPECT_COLOR_BIT
             , color_images[ i ]
             , image_view
            );

            if ( result != VK_SUCCESS )
            {
                KEGE_ERROR("%s : swapchain -> createImageViewHandle!", getError( result ));
                return {};
            }

            kege::Ref< vk::Image2d > color_image = new vk::Image2d( device );
            color_image->vulkan()->handle = color_images[ i ];
            color_image->vulkan()->view = image_view;
            color_image->vulkan()->format = swapchain_info.format;
            color_image->vulkan()->extend = {swapchain_info.extent.width, swapchain_info.extent.height, 1};
            color_image->vulkan()->memory = nullptr;
            color_image->vulkan()->layers = 1;

            kege::Ref< vk::Framebuffer > framebuffer = new vk::Framebuffer( device );
            framebuffer->attach({ color_image.ref(), kege::Attachment::COLOR_ATTACHMENT });
            framebuffer->attach({ depth_image.ref(), kege::Attachment::DEPTH_ATTACHMENT });
            framebuffer->construct( renderpass );

            framebuffers[ i ] = framebuffer;
        }
        return framebuffers;
    }

    kege::Ref< vk::Renderpass > createSwapchainRenderpass( vk::Device* device, SwapchainInfo& swapchain_info, VkResult& result )
    {
        kege::Ref< vk::Renderpass > renderpass = new vk::Renderpass( device );
        renderpass->addAttachmentDescription
        (
            swapchain_info.format,
            VK_SAMPLE_COUNT_1_BIT,
            VK_IMAGE_LAYOUT_UNDEFINED,
            VK_IMAGE_LAYOUT_PRESENT_SRC_KHR,
            kege::COLOR_ATTACHMENT
        );
        renderpass->addAttachmentDescription
        (
            swapchain_info.depth_format,
            VK_SAMPLE_COUNT_1_BIT,
            VK_IMAGE_LAYOUT_UNDEFINED,
            VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL,
            kege::DEPTH_ATTACHMENT
        );
        result = renderpass->construct();
        return renderpass;
    }

    VkResult Swapchain::recreate()
    {
        destruct();

        VkResult result;
        SwapchainInfo swapchain_info;
        getSwapchainInfo( _device, swapchain_info );

        _handle = createSwapchainhandle( _device, swapchain_info, result );
        if ( result != VK_SUCCESS )
        {
            KEGE_ERROR("%s : swapchain -> renderpass!", getError( result ));
            return result;
        }

        kege::Ref< vk::Renderpass > renderpass = createSwapchainRenderpass( _device, swapchain_info, result );
        if ( result != VK_SUCCESS )
        {
            KEGE_ERROR("%s : swapchain -> renderpass!", getError( result ));
            return result;
        }

        kege::Ref< vk::Image2d > depth_image = new vk::Image2d( _device );
        result = depth_image->construct
        ({
            kege::Format::DEPTH_32_SFLOAT,
            kege::IMAGE_ASPECT_DEPTH,
            swapchain_info.extent.width,
            swapchain_info.extent.height,
            1,
            swapchain_info.extent.width * swapchain_info.extent.height * sizeof(float),
            nullptr
        });
        if ( result != VK_SUCCESS )
        {
            KEGE_ERROR("%s : swapchain -> createDepthImage!", getError( result ));
            return result;
        }

        _framebuffers = vk::createSwapchainFramebuffer( _device, depth_image, renderpass, _handle, swapchain_info, result );
        if ( result != VK_SUCCESS )
        {
            KEGE_ERROR("%s : swapchain -> createSwapchainFramebuffer!", getError( result ));
            return result;
        }

        return result;
    }

    const kege::Framebuffer* Swapchain::getCurrentFramebuffer()const
    {
        return _framebuffers[ _image_index ].ref();
    }

    VkResult Swapchain::init( vk::Device* device )
    {
        _device = device;
        if ( recreate() != VK_SUCCESS )
        {
            return VK_ERROR_INITIALIZATION_FAILED;
        }
        return VK_SUCCESS;
    }

    const VkSwapchainKHR Swapchain::handle()const
    {
        return _handle;
    }

    uint32_t Swapchain::getImageIndex()const
    {
        return _image_index;
    }

    VkResult Swapchain::acquireNextImage( uint32_t current_frame, VkSemaphore semaphore )
    {
        VkResult result = vkAcquireNextImageKHR
        (  _device->getLogicalDevice()
         , _handle
         , UINT64_MAX
         , semaphore
         , VK_NULL_HANDLE
         , &_image_index
        );

        if (result != VK_SUCCESS)
        {
            if (result == VK_ERROR_OUT_OF_DATE_KHR)
            {
                recreate();
                return result;
            }
            else if ( result != VK_SUBOPTIMAL_KHR )
            {
                throw std::runtime_error("failed to acquire swap chain image!");
            }
        }
        return VK_SUCCESS;
    }

    void Swapchain::destruct()
    {
        _framebuffers.clear();
        if ( _handle )
        {
            vkDestroySwapchainKHR( _device->getLogicalDevice(), _handle, nullptr );
            _handle = VK_NULL_HANDLE;
        }
    }

    Swapchain::~Swapchain()
    {
        destruct();
    }
    Swapchain::Swapchain()
    :   _handle( VK_NULL_HANDLE )
    ,   _device( nullptr )
    ,   _framebuffers( false )
    ,   _image_index( 0 )
    {}

}}


