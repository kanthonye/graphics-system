//
//  vk.cpp
//  new-engine
//
//  Created by Kenneth Esdaile on 12/30/23.
//

#include "vk.hpp"

namespace kege{namespace vk{

    std::vector< const char*> getRequiredExtensions()
    {
        uint32_t glfwExtensionCount = 0;
        const char** glfwExtensions;
        glfwExtensions = glfwGetRequiredInstanceExtensions( &glfwExtensionCount );

        std::vector<const char*> extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);

        if ( KEGE_VULKAN_VALIDATION_LAYER_ENABLES )
        {
            extensions.push_back( VK_EXT_DEBUG_UTILS_EXTENSION_NAME );

            /*
             I have been getting validation error everytime i ran vulkan project.

             Validation Error: [ VUID-VkDeviceCreateInfo-pProperties-04451 ]
             vkCreateDevice: VK_KHR_portability_subset must be enabled because
             physical device VkPhysicalDevice 0x600000245880[] supports it The
             Vulkan spec states: If the VK_KHR_portability_subset extension is
             included in pProperties of vkEnumerateDeviceExtensionProperties,
             ppEnabledExtensionNames must include "VK_KHR_portability_subset".

             To fix I added VK_KHR_get_physical_device_properties2 to instance
             extension and added VK_KHR_portability_subset to device extension */
            extensions.push_back("VK_KHR_get_physical_device_properties2");
        }

        return extensions;
    }

    void querySwapChainSupport
    (
        VkSurfaceKHR surface,
        VkPhysicalDevice physical_device,
         SwapChainSupportDetails& details
    )
    {
        vkGetPhysicalDeviceSurfaceCapabilitiesKHR( physical_device, surface, &details.capabilities );

        uint32_t format_count;
        vkGetPhysicalDeviceSurfaceFormatsKHR( physical_device, surface, &format_count, nullptr );

        if (format_count != 0)
        {
            details.formats.resize( format_count );
            vkGetPhysicalDeviceSurfaceFormatsKHR( physical_device, surface, &format_count, details.formats.data() );
        }

        uint32_t present_mode_count;
        vkGetPhysicalDeviceSurfacePresentModesKHR( physical_device, surface, &present_mode_count, nullptr);

        if ( present_mode_count != 0 )
        {
            details.present_modes.resize( present_mode_count );
            vkGetPhysicalDeviceSurfacePresentModesKHR( physical_device, surface, &present_mode_count, details.present_modes.data() );
        }
    }

    bool checkDeviceExtensionSupport
    (
        VkPhysicalDevice physical_device,
        const std::vector< const char* >& device_extensions
    )
    {
        uint32_t extensionCount;
        vkEnumerateDeviceExtensionProperties( physical_device, nullptr, &extensionCount, nullptr );

        std::vector<VkExtensionProperties> availableExtensions(extensionCount);
        vkEnumerateDeviceExtensionProperties( physical_device, nullptr, &extensionCount, availableExtensions.data() );

        std::set<std::string> required_extensions( device_extensions.begin(), device_extensions.end() );

        for (const auto& extension : availableExtensions)
        {
            required_extensions.erase( extension.extensionName );
        }

        return required_extensions.empty();
    }
    
    VkShaderStageFlagBits toShaderStageFlagBit( kege::ShaderStageBit stage )
    {
        switch( stage )
        {
            case kege::VERTEX_SHADER: return VK_SHADER_STAGE_VERTEX_BIT;
            case kege::TESS_CONTROL_SHADER: return VK_SHADER_STAGE_TESSELLATION_CONTROL_BIT;
            case kege::TESS_EVALUATION_SHADER: return VK_SHADER_STAGE_TESSELLATION_EVALUATION_BIT;
            case kege::GEOMETRY_SHADER: return VK_SHADER_STAGE_GEOMETRY_BIT;
            case kege::FRAGMENT_SHADER: return VK_SHADER_STAGE_FRAGMENT_BIT;
            case kege::COMPUTE_SHADER: return VK_SHADER_STAGE_COMPUTE_BIT;
        }
    }

    VkDescriptorType toVkDescriptorType( kege::DescriptorType descriptor_type )
    {
        VkDescriptorType type;
        switch ( descriptor_type )
        {
            case kege::DESCRIPTOR_COMBINED_IMAGE_SAMPLER:
                type = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
                break;

            case DESCRIPTOR_UNIFORM_BUFFER:
                type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
                break;

            case DESCRIPTOR_STORAGE_IMAGE:
                type = VK_DESCRIPTOR_TYPE_STORAGE_IMAGE;
                break;

            case DESCRIPTOR_SAMPLER:
                type = VK_DESCRIPTOR_TYPE_SAMPLER;
                break;

            case DESCRIPTOR_SAMPLED_IMAGE:
                type = VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE;
                break;

            case DESCRIPTOR_UNIFORM_TEXEL_BUFFER:
                type = VK_DESCRIPTOR_TYPE_UNIFORM_TEXEL_BUFFER;
                break;

            case DESCRIPTOR_STORAGE_TEXEL_BUFFER:
                type = VK_DESCRIPTOR_TYPE_STORAGE_TEXEL_BUFFER;
                break;

            case DESCRIPTOR_STORAGE_BUFFER:
                type = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER;
                break;

            case DESCRIPTOR_UNIFORM_BUFFER_DYNAMIC:
                type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC;
                break;

            case DESCRIPTOR_STORAGE_BUFFER_DYNAMIC:
                type = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER_DYNAMIC;
                break;

            default: throw std::runtime_error("UNKNOW SpvReflectDescriptorType");
                break;
        }
        return type;
    }


    const char* getError( VkResult result )
    {
        switch ( result )
        {
        default: return "";

        case VK_ERROR_OUT_OF_POOL_MEMORY:
            return "VK_ERROR_OUT_OF_POOL_MEMORY";
        case VK_NOT_READY:
            return "VK_NOT_READY";
        case VK_TIMEOUT:
            return "VK_TIMEOUT";
        case VK_EVENT_SET:
            return "VK_EVENT_SET";
        case VK_EVENT_RESET:
            return "VK_EVENT_RESET";
        case VK_INCOMPLETE:
            return "VK_INCOMPLETE";
        case VK_PIPELINE_COMPILE_REQUIRED:
            return "VK_PIPELINE_COMPILE_REQUIRED";
        case VK_THREAD_IDLE_KHR:
            return "VK_THREAD_IDLE_KHR";
        case VK_THREAD_DONE_KHR:
            return "VK_THREAD_DONE_KHR";
        case VK_OPERATION_DEFERRED_KHR:
            return "VK_OPERATION_DEFERRED_KHR";
        case VK_OPERATION_NOT_DEFERRED_KHR:
            return "VK_OPERATION_NOT_DEFERRED_KHR";
        case VK_ERROR_INITIALIZATION_FAILED:
            return "VK_ERROR_INITIALIZATION_FAILED";
        case VK_ERROR_DEVICE_LOST:
            return "VK_ERROR_DEVICE_LOST";
        case VK_ERROR_MEMORY_MAP_FAILED:
            return "VK_ERROR_MEMORY_MAP_FAILED";
        case VK_ERROR_LAYER_NOT_PRESENT:
            return "VK_ERROR_LAYER_NOT_PRESENT";
        case VK_ERROR_EXTENSION_NOT_PRESENT:
            return "VK_ERROR_EXTENSION_NOT_PRESENT";
        case VK_ERROR_FEATURE_NOT_PRESENT:
            return "VK_ERROR_FEATURE_NOT_PRESENT";
        case VK_ERROR_INCOMPATIBLE_DRIVER:
            return "VK_ERROR_INCOMPATIBLE_DRIVER";
        case VK_ERROR_TOO_MANY_OBJECTS:
            return "VK_ERROR_TOO_MANY_OBJECTS";
        case VK_ERROR_FORMAT_NOT_SUPPORTED:
            return "VK_ERROR_FORMAT_NOT_SUPPORTED";
        case VK_ERROR_UNKNOWN:
            return "VK_ERROR_UNKNOWN";
        case VK_ERROR_INVALID_EXTERNAL_HANDLE:
            return "VK_ERROR_INVALID_EXTERNAL_HANDLE";
        case VK_ERROR_FRAGMENTATION:
            return "VK_ERROR_FRAGMENTATION";
        case VK_ERROR_INVALID_OPAQUE_CAPTURE_ADDRESS:
            return "VK_ERROR_INVALID_OPAQUE_CAPTURE_ADDRESS";
        case VK_ERROR_SURFACE_LOST_KHR:
            return "VK_ERROR_SURFACE_LOST_KHR";
        case VK_ERROR_NATIVE_WINDOW_IN_USE_KHR:
            return "VK_ERROR_NATIVE_WINDOW_IN_USE_KHR";
        case VK_SUBOPTIMAL_KHR:
            return "VK_SUBOPTIMAL_KHR";
        case VK_ERROR_OUT_OF_DATE_KHR:
            return "VK_ERROR_OUT_OF_DATE_KHR";
        case VK_ERROR_INCOMPATIBLE_DISPLAY_KHR:
            return "VK_ERROR_INCOMPATIBLE_DISPLAY_KHR";
        case VK_ERROR_VALIDATION_FAILED_EXT:
            return "VK_ERROR_VALIDATION_FAILED_EXT";
        case VK_ERROR_INVALID_SHADER_NV:
            return "VK_ERROR_INVALID_SHADER_NV";
        case VK_ERROR_INVALID_DRM_FORMAT_MODIFIER_PLANE_LAYOUT_EXT:
            return "VK_ERROR_INVALID_DRM_FORMAT_MODIFIER_PLANE_LAYOUT_EXT";
        case VK_ERROR_NOT_PERMITTED_KHR:
            return "VK_ERROR_NOT_PERMITTED_KHR";
        case VK_ERROR_FULL_SCREEN_EXCLUSIVE_MODE_LOST_EXT:
            return "VK_ERROR_FULL_SCREEN_EXCLUSIVE_MODE_LOST_EXT";
        case VK_ERROR_COMPRESSION_EXHAUSTED_EXT:
            return "VK_ERROR_COMPRESSION_EXHAUSTED_EXT";
        }
    }


    VkExtent2D chooseSwapExtent
    (
        GLFWwindow* window,
        const VkSurfaceCapabilitiesKHR& capabilities
    )
    {
        if (capabilities.currentExtent.width == std::numeric_limits<uint32_t>::max())
        {
            return capabilities.currentExtent;
        }
        else
        {
            int width, height;
            glfwGetFramebufferSize( window, &width, &height );

            VkExtent2D actualExtent =
            {
                static_cast<uint32_t>(width),
                static_cast<uint32_t>(height)
            };

            actualExtent.width = std::clamp
            (
                 actualExtent.width,
                 capabilities.minImageExtent.width,
                 capabilities.maxImageExtent.width
            );

            actualExtent.height = std::clamp
            (
                 actualExtent.height,
                 capabilities.minImageExtent.height,
                 capabilities.maxImageExtent.height
            );

            return actualExtent;
        }
    }

    VkShaderStageFlagBits getShaderStateFlagBit( kege::ShaderStageBit stage )
    {
        switch ( stage )
        {
            case kege::VERTEX_SHADER: return VK_SHADER_STAGE_VERTEX_BIT; break;
            case kege::COMPUTE_SHADER: return VK_SHADER_STAGE_COMPUTE_BIT; break;
            case kege::FRAGMENT_SHADER: return VK_SHADER_STAGE_FRAGMENT_BIT; break;
            case kege::GEOMETRY_SHADER: return VK_SHADER_STAGE_GEOMETRY_BIT; break;
            case kege::TESS_EVALUATION_SHADER: return VK_SHADER_STAGE_TESSELLATION_EVALUATION_BIT; break;
            case kege::TESS_CONTROL_SHADER: return VK_SHADER_STAGE_TESSELLATION_CONTROL_BIT; break;
            default: throw std::runtime_error("INVALID_ENUM being passed to vk::getShaderStateFlagBit( kege::ShaderStageBit )");
        }
    }


    VkFormat getFormat( kege::Format format )
    {
        switch ( format )
        {
            default:                return VK_FORMAT_UNDEFINED;

            case kege::DEPTH_16_UNORM:          return VK_FORMAT_D16_UNORM;
            case kege::DEPTH_24_UNORM_S8_UINT:  return VK_FORMAT_D24_UNORM_S8_UINT;
            case kege::DEPTH_32_SFLOAT:         return VK_FORMAT_D32_SFLOAT;
            case kege::DEPTH_16_UNORM_S8_UINT:  return VK_FORMAT_D16_UNORM_S8_UINT;
            case kege::DEPTH_24_UNORM_PACK32:   return VK_FORMAT_X8_D24_UNORM_PACK32;
            case kege::DEPTH_32_SFLOAT_S8_UINT: return VK_FORMAT_D32_SFLOAT_S8_UINT;

            case kege::R8_SRGB:     return VK_FORMAT_R8_SRGB;
            case kege::RG8_SRGB:    return VK_FORMAT_R8G8_SRGB;
            case kege::RGB8_SRGB:   return VK_FORMAT_R8G8B8_SRGB;
            case kege::RGBA8_SRGB:  return VK_FORMAT_R8G8B8A8_SRGB;

            case kege::BGR8_SRGB:   return VK_FORMAT_B8G8R8_SRGB;
            case kege::BGRA8_SRGB:  return VK_FORMAT_B8G8R8A8_SRGB;

            case kege::R8_UNORM:    return VK_FORMAT_R8_UNORM;
            case kege::RG8_UNORM:   return VK_FORMAT_R8G8_UNORM;
            case kege::RGB8_UNORM:  return VK_FORMAT_R8G8B8_UNORM;
            case kege::RGBA8_UNORM: return VK_FORMAT_R8G8B8A8_UNORM;

            case kege::R8_UINT:     return VK_FORMAT_R8_UINT;
            case kege::RG8_UINT:    return VK_FORMAT_R8G8_UINT;
            case kege::RGB8_UINT:   return VK_FORMAT_R8G8B8_UINT;
            case kege::RGBA8_UINT:  return VK_FORMAT_R8G8B8A8_UINT;

            case kege::R16_UINT:    return VK_FORMAT_R16_UINT;
            case kege::RG16_UINT:   return VK_FORMAT_R16G16_UINT;
            case kege::RGB16_UINT:  return VK_FORMAT_R16G16B16_UINT;
            case kege::RGBA16_UINT: return VK_FORMAT_R16G16B16A16_UINT;

            case kege::R32_UINT:    return VK_FORMAT_R32_UINT;
            case kege::RG32_UINT:   return VK_FORMAT_R32G32_UINT;
            case kege::RGB32_UINT:  return VK_FORMAT_R32G32B32_UINT;
            case kege::RGBA32_UINT: return VK_FORMAT_R32G32B32A32_UINT;

            case kege::R64_UINT:    return VK_FORMAT_R64_UINT;
            case kege::RG64_UINT:   return VK_FORMAT_R64G64_UINT;
            case kege::RGB64_UINT:  return VK_FORMAT_R64G64B64_UINT;
            case kege::RGBA64_UINT: return VK_FORMAT_R64G64B64A64_UINT;

            case kege::R8_SINT:     return VK_FORMAT_R8_SINT;
            case kege::RG8_SINT:    return VK_FORMAT_R8G8_SINT;
            case kege::RGB8_SINT:   return VK_FORMAT_R8G8B8_SINT;
            case kege::RGBA8_SINT:  return VK_FORMAT_R8G8B8A8_SINT;

            case kege::R16_SINT:    return VK_FORMAT_R16_SINT;
            case kege::RG16_SINT:   return VK_FORMAT_R16G16_SINT;
            case kege::RGB16_SINT:  return VK_FORMAT_R16G16B16_SINT;
            case kege::RGBA16_SINT: return VK_FORMAT_R16G16B16A16_SINT;

            case kege::R32_SINT:    return VK_FORMAT_R32_SINT;
            case kege::RG32_SINT:   return VK_FORMAT_R32G32_SINT;
            case kege::RGB32_SINT:  return VK_FORMAT_R32G32B32_SINT;
            case kege::RGBA32_SINT: return VK_FORMAT_R32G32B32A32_SINT;

            case kege::R64_SINT:    return VK_FORMAT_R64_SINT;
            case kege::RG64_SINT:   return VK_FORMAT_R64G64_SINT;
            case kege::RGB64_SINT:  return VK_FORMAT_R64G64B64_SINT;
            case kege::RGBA64_SINT: return VK_FORMAT_R64G64B64A64_SINT;

            case kege::R32_FLOAT:    return VK_FORMAT_R32_SFLOAT;
            case kege::RG32_FLOAT:   return VK_FORMAT_R32G32_SFLOAT;
            case kege::RGB32_FLOAT:  return VK_FORMAT_R32G32B32_SFLOAT;
            case kege::RGBA32_FLOAT: return VK_FORMAT_R32G32B32A32_SFLOAT;

            case kege::R64_FLOAT:    return VK_FORMAT_R64_SFLOAT;
            case kege::RG64_FLOAT:   return VK_FORMAT_R64G64_SFLOAT;
            case kege::RGB64_FLOAT:  return VK_FORMAT_R64G64B64_SFLOAT;
            case kege::RGBA64_FLOAT: return VK_FORMAT_R64G64B64A64_SFLOAT;
        }
    }

    VkPrimitiveTopology getPrimitiveTopology( kege::PrimitiveTopology topology )
    {
        switch ( topology )
        {
            default:
            case kege::TRIANGLE_LIST: return VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST; break;
            case kege::TRIANGLE_FAN: return VK_PRIMITIVE_TOPOLOGY_TRIANGLE_FAN; break;
            case kege::TRIANGLE_STRIP: return VK_PRIMITIVE_TOPOLOGY_TRIANGLE_STRIP; break;
            case kege::TRIANGLE_LIST_WITH_ADJACENCY: return VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST_WITH_ADJACENCY; break;
            case kege::TRIANGLE_STRIP_WITH_ADJACENCY: return VK_PRIMITIVE_TOPOLOGY_TRIANGLE_STRIP_WITH_ADJACENCY; break;
            case kege::LINE_LIST: return VK_PRIMITIVE_TOPOLOGY_LINE_LIST; break;
            case kege::LINE_STRIP: return VK_PRIMITIVE_TOPOLOGY_LINE_STRIP; break;
            case kege::LINE_LIST_WITH_ADJACENCY: return VK_PRIMITIVE_TOPOLOGY_LINE_LIST_WITH_ADJACENCY; break;
            case kege::LINE_STRIP_WITH_ADJACENCY:  return VK_PRIMITIVE_TOPOLOGY_LINE_STRIP_WITH_ADJACENCY; break;
            case kege::POINT_LIST: return VK_PRIMITIVE_TOPOLOGY_POINT_LIST; break;
            case kege::PATCH_LIST: return VK_PRIMITIVE_TOPOLOGY_PATCH_LIST; break;
        }
    }

}}
