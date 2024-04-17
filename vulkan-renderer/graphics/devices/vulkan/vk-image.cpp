//
//  vk-image.cpp
//  new-engine
//
//  Created by Kenneth Esdaile on 1/3/24.
//

#include "vk-core.hpp"
namespace kege{namespace vk{

    /**
     * @brief Creates a Vulkan image view.
     *
     * @param device_handle The Vulkan device associated with the image view.
     * @param image_format The format of the image.
     * @param view_type The type of image view (e.g., 2D, 3D, cube map).
     * @param aspect_flags Flags specifying which aspects of the image are included in the view.
     * @param image The handle of the Vulkan image.
     * @param handle Reference to a VkImageView object to be filled with the created image view.
     *
     * @return VK_SUCCESS if the image view creation is successful, otherwise an error code.
     */
    VkResult createView
    (  VkDevice device_handle
     , VkFormat image_format
     , VkImageViewType view_type
     , VkImageAspectFlags aspect_flags
     , VkImage image
     , VkImageView& handle
    )
    {
        VkImageViewCreateInfo info{};
        info.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
        info.image = image;
        info.format = image_format;
        info.viewType = view_type;
        info.subresourceRange.aspectMask = aspect_flags;
        info.subresourceRange.baseMipLevel = 0;
        info.subresourceRange.levelCount = 1;
        info.subresourceRange.baseArrayLayer = 0;
        info.subresourceRange.layerCount = 1;
        info.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
        info.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
        info.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
        info.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;

        VkResult result = vkCreateImageView( device_handle, &info, nullptr, &handle );
        if ( result != VK_SUCCESS )
        {
            KEGE_ERROR( "Could not bind memory object to an image." );
            return result;
        }
        return result;
    }
    
    /**
     * @brief Creates memory for a Vulkan image.
     *
     * @param device Pointer to the Vulkan device associated with the image.
     * @param memory_properties Memory properties for the image memory.
     * @param bind_image_memory Whether to bind the image memory to the image.
     * @param image The handle of the Vulkan image.
     * @param handle Reference to a VkDeviceMemory object to be filled with the created image memory.
     *
     * @return VK_SUCCESS if the image memory creation is successful, otherwise an error code.
     */
    VkResult createMemory
    (  vk::Device* device
     , VkMemoryPropertyFlags memory_properties
     , bool bind_image_memory
     , VkImage image
     , VkDeviceMemory& handle
    )
    {
        VkMemoryRequirements memory_requirements;
        vkGetImageMemoryRequirements( device->getLogicalDevice(), image, &memory_requirements );
        uint32_t memory_type_index = device->getPhysicalDevice().getPhysicalDeviceMemoryTypeIndex
        (
            memory_requirements, memory_properties
        );

        if( memory_type_index < 0 )
        {
            KEGE_ERROR( "Could not allocate memory for an image." );
            return VK_ERROR_INITIALIZATION_FAILED;
        }

        VkMemoryAllocateInfo image_memory_allocate_info =
        {
            VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
            nullptr,
            memory_requirements.size,
            memory_type_index
        };

        VkResult result = vkAllocateMemory( device->getLogicalDevice(), &image_memory_allocate_info, nullptr, &handle );
        if( result != VK_SUCCESS )
        {
            KEGE_ERROR( "Could not allocate memory for an image." );
            return result;
        }

        if ( bind_image_memory )
        {
            result = vkBindImageMemory( device->getLogicalDevice(), image, handle, 0 );
            if( result != VK_SUCCESS )
            {
                KEGE_ERROR( "Could not bind memory object to an image." );
                return result;
            }
        }

        return VK_SUCCESS;
    }

    /**
     * @brief Creates a Vulkan image.
     *
     * @return VK_SUCCESS if the image creation is successful, otherwise an error code.
     */
    VkResult createImage
    (
        vk::Device* device,
        VkImageType image_type,
        VkFormat format,
        VkExtent3D extent,
        uint32_t mip_levels,
        uint32_t array_layers,
        VkImageViewType view_type,
        VkImageAspectFlagBits aspect_type,
        VkImageUsageFlags usage,
        vk::Image& image,
        uint64_t size,
        const void* data
    )
    {
        VkImageCreateInfo info{};
        info.sType         = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
        info.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
        info.sharingMode   = VK_SHARING_MODE_EXCLUSIVE;
        info.samples       = VK_SAMPLE_COUNT_1_BIT;
        info.extent        = extent;
        info.mipLevels     = mip_levels;
        info.arrayLayers   = array_layers;
        info.format        = format;
        info.imageType     = VK_IMAGE_TYPE_2D;
        info.tiling        = VK_IMAGE_TILING_OPTIMAL;
        info.flags         = 0; // Optional
        info.usage         = usage;

        image.layers = info.arrayLayers;
        image.format = info.format;
        image.extend = info.extent;

        VkResult result = vkCreateImage( device->getLogicalDevice(), &info, nullptr, &image.handle );
        if ( result != VK_SUCCESS )
        {
            KEGE_ERROR( "Could not bind memory object to an image." );
            return result;
        }

        result = vk::createMemory( device, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, true, image.handle, image.memory );
        if ( result != VK_SUCCESS )
        {
            return result;
        }

        result = vk::createView( device->getLogicalDevice(), info.format, view_type, aspect_type, image.handle, image.view );
        if ( result != VK_SUCCESS )
        {
            return result;
        }

        if ( data != nullptr )
        {
            vk::Buffer source;
            VkResult result = source.create
            (  device, VK_SHARING_MODE_EXCLUSIVE
             , VK_BUFFER_USAGE_TRANSFER_SRC_BIT | VK_BUFFER_USAGE_TRANSFER_DST_BIT
             , VK_MEMORY_PROPERTY_HOST_COHERENT_BIT | VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT
             , size, data );

            if ( result != VK_SUCCESS )
            {
                return result;
            }
            device->copyBufferToImage( source, image );
            source.destroy( device->getLogicalDevice() );
        }
        return VK_SUCCESS;
    }


    VkImageAspectFlagBits getAspectType( kege::ImageAspect image_aspect )
    {
        switch ( image_aspect )
        {
            case kege::IMAGE_ASPECT_COLOR: return VK_IMAGE_ASPECT_COLOR_BIT;
            case kege::IMAGE_ASPECT_DEPTH: return VK_IMAGE_ASPECT_DEPTH_BIT;
            case kege::IMAGE_ASPECT_STENCIL: return VK_IMAGE_ASPECT_STENCIL_BIT;
        }
    }

    VkImageUsageFlags getImageUsage( ImageAspect image_aspect )
    {
        if ( image_aspect == kege::IMAGE_ASPECT_COLOR )
        {
            return
            (
                VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT |
                VK_IMAGE_USAGE_TRANSFER_SRC_BIT |
                VK_IMAGE_USAGE_TRANSFER_DST_BIT |
                VK_IMAGE_USAGE_SAMPLED_BIT
            );
        }
        else
        {
            return VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT;
        }
    }

    void destroyImage( VkDevice device, vk::Image& image )
    {
        if ( image.view != VK_NULL_HANDLE )
        {
            vkDestroyImageView( device, image.view, nullptr );
            image.view = VK_NULL_HANDLE;
        }
        if ( image.memory != VK_NULL_HANDLE )
        {
            vkFreeMemory( device, image.memory, nullptr );
            vkDestroyImage( device, image.handle, nullptr );
            image.memory = VK_NULL_HANDLE;
        }
        image.handle = VK_NULL_HANDLE;
    }
//    VkImageType image_type;
//    VkImageViewType view_type;
//    switch ( info.image_type )
//    {
//        case IMAGE_1D:
//            image_type = VK_IMAGE_TYPE_1D;
//            view_type = VK_IMAGE_VIEW_TYPE_1D;
//            break;
//        case IMAGE_2D:
//            image_type = VK_IMAGE_TYPE_2D;
//            view_type = VK_IMAGE_VIEW_TYPE_2D;
//            break;
//        case IMAGE_3D:
//            image_type = VK_IMAGE_TYPE_3D;
//            view_type = VK_IMAGE_VIEW_TYPE_3D;
//            break;
//        case IMAGE_1D_ARRAY:
//            image_type = VK_IMAGE_TYPE_1D;
//            view_type = VK_IMAGE_VIEW_TYPE_1D_ARRAY;
//            break;
//        case IMAGE_2D_ARRAY:
//            image_type = VK_IMAGE_TYPE_2D;
//            view_type = VK_IMAGE_VIEW_TYPE_2D_ARRAY;
//            break;
//        case IMAGE_CUBE:
//            image_type = VK_IMAGE_TYPE_2D;
//            view_type = VK_IMAGE_VIEW_TYPE_CUBE;
//            break;
//        case IMAGE_CUBE_ARRAY:
//            image_type = VK_IMAGE_TYPE_2D;
//            view_type = VK_IMAGE_VIEW_TYPE_CUBE_ARRAY;
//            break;
//    }
//    VkImageCreateInfo image_info{};
//    image_info.sType         = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
//    image_info.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
//    image_info.sharingMode   = VK_SHARING_MODE_EXCLUSIVE;
//    image_info.samples       = VK_SAMPLE_COUNT_1_BIT;
//    image_info.extent.width  = info.dimentions.width;
//    image_info.extent.height = info.dimentions.height;
//    image_info.mipLevels     = info.mip_levels;
//    image_info.arrayLayers   = info.layers;
//    image_info.extent.depth  = 1;
//    image_info.format        = vk::getFormat( info.format );
//    image_info.imageType     = VK_IMAGE_TYPE_2D;
//    image_info.tiling        = VK_IMAGE_TILING_OPTIMAL;
//    image_info.flags         = 0; // Optional
//    if ( info.image_aspect == kege::IMAGE_ASPECT_COLOR )
//    {
//        image_info.usage =
//        {
//            VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT |
//            VK_IMAGE_USAGE_TRANSFER_SRC_BIT |
//            VK_IMAGE_USAGE_TRANSFER_DST_BIT |
//            VK_IMAGE_USAGE_SAMPLED_BIT
//        };
//    }
//    else
//    {
//        image_info.usage = VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT;
//    }
}}






namespace kege{namespace vk{

    VkResult Image2d::construct( const kege::Image2d::CreateInfo& info )
    {
        VkResult result = vk::createImage
        (
            _device,
            VK_IMAGE_TYPE_2D,
            vk::getFormat( info.format ),
            { info.width, info.height, 1 },
            info.mip_levels,
            1 /*array_layers*/,
            VK_IMAGE_VIEW_TYPE_2D,
            getAspectType( info.image_aspect ),
            getImageUsage( info.image_aspect ),
            _params, info.data_size, info.data
        );

        if ( result != VK_SUCCESS )
        {
            destroyImage( _device->getLogicalDevice(), _params );
            return result;
        }

        return VK_SUCCESS;
    }

    void Image2d::getDescriptorBufferInfo( void* data )
    {
        VkDescriptorImageInfo* info = (VkDescriptorImageInfo*) data;
        info->imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
        info->imageView = _params.view;
    }

    const vk::Image* Image2d::vulkan()const
    {
        return &_params;
    }

    vk::Image* Image2d::vulkan()
    {
        return &_params;
    }

    vk::Device* Image2d::device()
    {
        return _device;
    }

    uint32_t Image2d::layers()const
    {
        return 1;
    }

    uint32_t Image2d::height()const
    {
        return _params.extend.height;
    }
    
    uint32_t Image2d::width()const
    {
        return _params.extend.width;
    }

    uint32_t Image2d::depth()const
    {
        return 1;
    }
    
    Image2d::Image2d
    (   vk::Device* device
    ,   const vk::Image& image
    )
    :   _device( device )
    ,   _params( image )
    {
    }

    Image2d::~Image2d()
    {
        destroyImage( _device->getLogicalDevice(), _params );
    }
    
    Image2d::Image2d( vk::Device* device )
    :   _device( device )
    ,   _params({ VK_NULL_HANDLE, VK_NULL_HANDLE, VK_NULL_HANDLE, {}, {}, 1 })
    {}

}}






namespace kege{namespace vk{

    VkResult Image2dArray::construct( const kege::Image2dArray::CreateInfo& info )
    {
        VkResult result = vk::createImage
        (
            _device,
            VK_IMAGE_TYPE_2D,
            vk::getFormat( info.format ),
            { info.width, info.height, 1 },
            info.mip_levels,
            info.layers,
            VK_IMAGE_VIEW_TYPE_2D_ARRAY,
            getAspectType( info.image_aspect ),
            getImageUsage( info.image_aspect ),
            _params, info.data_size, info.data
        );

        if ( result != VK_SUCCESS )
        {
            destroyImage( _device->getLogicalDevice(), _params );
            return result;
        }

        return VK_SUCCESS;
    }

    void Image2dArray::getDescriptorBufferInfo( void* data )
    {
        VkDescriptorImageInfo* info = (VkDescriptorImageInfo*) data;
        info->imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
        info->imageView = _params.view;
    }

    const vk::Image* Image2dArray::vulkan()const
    { 
        return &_params;
    }

    vk::Image* Image2dArray::vulkan()
    { 
        return &_params;
    }

    vk::Device* Image2dArray::device()
    {
        return _device;
    }

    uint32_t Image2dArray::layers()const
    {
        return 1;
    }

    uint32_t Image2dArray::height()const
    {
        return _params.extend.height;
    }

    uint32_t Image2dArray::width()const
    {
        return _params.extend.width;
    }

    uint32_t Image2dArray::depth()const
    {
        return 1;
    }

    Image2dArray::~Image2dArray()
    {
        destroyImage( _device->getLogicalDevice(), _params );
    }

    Image2dArray::Image2dArray( vk::Device* device )
    :   _device( device )
    ,   _params({ VK_NULL_HANDLE, VK_NULL_HANDLE, VK_NULL_HANDLE, {}, {}, 1 })
    {}

}}





namespace kege{namespace vk{

    VkResult Image3d::construct( const kege::Image3d::CreateInfo& info )
    {
        VkResult result = vk::createImage
        (
            _device,
            VK_IMAGE_TYPE_3D,
            vk::getFormat( info.format ),
            { info.width, info.height, info.depth },
            info.mip_levels,
            1 /* array-layers */,
            VK_IMAGE_VIEW_TYPE_3D,
            getAspectType( info.image_aspect ),
            getImageUsage( info.image_aspect ),
            _params, info.data_size, info.data
        );

        if ( result != VK_SUCCESS )
        {
            destroyImage( _device->getLogicalDevice(), _params );
            return result;
        }

        return VK_SUCCESS;
    }

    void Image3d::getDescriptorBufferInfo( void* data )
    {
        VkDescriptorImageInfo* info = (VkDescriptorImageInfo*) data;
        info->imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
        info->imageView = _params.view;
    }

    const vk::Image* Image3d::vulkan()const
    {
        return &_params;
    }

    vk::Image* Image3d::vulkan()
    {
        return &_params;
    }

    vk::Device* Image3d::device()
    {
        return _device;
    }

    uint32_t Image3d::layers()const
    {
        return _params.layers;
    }

    uint32_t Image3d::height()const
    {
        return _params.extend.height;
    }

    uint32_t Image3d::width()const
    {
        return _params.extend.width;
    }

    uint32_t Image3d::depth()const
    {
        return _params.extend.depth;
    }

    Image3d::~Image3d()
    {
        destroyImage( _device->getLogicalDevice(), _params );
    }

    Image3d::Image3d( vk::Device* device )
    :   _device( device )
    ,   _params({ VK_NULL_HANDLE, VK_NULL_HANDLE, VK_NULL_HANDLE, {}, {}, 1 })
    {}

}}







namespace kege{namespace vk{

    VkResult Image1dArray::construct( const kege::Image1dArray::CreateInfo& info )
    {
        VkResult result = vk::createImage
        (
            _device,
            VK_IMAGE_TYPE_1D,
            vk::getFormat( info.format ),
            { info.width, 1, 1 },
            info.mip_levels,
            1 /* array-layers */,
            VK_IMAGE_VIEW_TYPE_1D_ARRAY,
            getAspectType( info.image_aspect ),
            getImageUsage( info.image_aspect ),
            _params, info.data_size, info.data
        );

        if ( result != VK_SUCCESS )
        {
            destroyImage( _device->getLogicalDevice(), _params );
            return result;
        }
        return VK_SUCCESS;
    }

    void Image1dArray::getDescriptorBufferInfo( void* data )
    {
        VkDescriptorImageInfo* info = (VkDescriptorImageInfo*) data;
        info->imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
        info->imageView = _params.view;
    }

    const vk::Image* Image1dArray::vulkan()const
    {
        return &_params;
    }

    vk::Image* Image1dArray::vulkan()
    {
        return &_params;
    }

    vk::Device* Image1dArray::device()
    {
        return _device;
    }

    uint32_t Image1dArray::layers()const
    {
        return _params.layers;
    }

    uint32_t Image1dArray::height()const
    {
        return _params.extend.height;
    }

    uint32_t Image1dArray::width()const
    {
        return _params.extend.width;
    }

    uint32_t Image1dArray::depth()const
    {
        return 1;
    }

    Image1dArray::~Image1dArray()
    {
        destroyImage( _device->getLogicalDevice(), _params );
    }

    Image1dArray::Image1dArray( vk::Device* device )
    :   _device( device )
    ,   _params({ VK_NULL_HANDLE, VK_NULL_HANDLE, VK_NULL_HANDLE, {}, {}, 1 })
    {}

}}
