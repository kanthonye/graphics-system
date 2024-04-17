//
//  vk.hpp
//  new-engine
//
//  Created by Kenneth Esdaile on 12/30/23.
//

#ifndef kege_graphics_vk_hpp
#define kege_graphics_vk_hpp

#include <set>
#include <map>
#include <vector>
#include <optional>

#define _DEBUG 
#ifdef _DEBUG
    static const bool KEGE_VULKAN_VALIDATION_LAYER_ENABLES = true;
#else
    static const bool KEGE_VULKAN_VALIDATION_LAYER_ENABLES = false;
#endif

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <vulkan/vulkan.h>
#include "../../../graphics/devices/interface/device.hpp"

namespace kege{namespace vk{

    std::vector< const char*> getRequiredExtensions();

    struct PhysicalDeviceRequirements
    {
        bool _graphics;
        bool _present;
        bool _compute;
        bool _transfer;
        bool _descrete_gpu;
        bool _sampler_anisotropy;
        std::vector< std::string > _device_extension_names;
    };

    struct DeviceQueueFamily
    {
        const std::optional< uint32_t >& operator[]( kege::DeviceQueueType i )const
        {
            return _indices[ i ];
        }

        std::optional< uint32_t >& operator[]( kege::DeviceQueueType i )
        {
            return _indices[ i ];
        }

        bool isComplete()
        {
            return
            (
             _indices[ kege::GRAPHICS_QUEUE ].has_value() &&
             _indices[ kege::PRESENT_QUEUE  ].has_value()
            );
        }

        std::optional< uint32_t > _indices[ kege::MAX_QUEUE_COUNT ];
    };

    struct SwapChainSupportDetails
    {
        VkSurfaceCapabilitiesKHR capabilities;
        std::vector<VkSurfaceFormatKHR> formats;
        std::vector<VkPresentModeKHR> present_modes;
    };

    void querySwapChainSupport
    (
        VkSurfaceKHR surface,
        VkPhysicalDevice physical_device,
        SwapChainSupportDetails& details
    );

    bool checkDeviceExtensionSupport
    (
        VkPhysicalDevice physical_device,
        const std::vector< const char* >& device_extensions
    );

    struct DescriptorSetLayoutObject
    {
        std::vector< kege::string > names;
        std::vector< VkDescriptorSetLayoutBinding > bindings;
    };


    VkShaderStageFlagBits toShaderStageFlagBit( kege::ShaderStageBit stage );
    VkDescriptorType toVkDescriptorType( kege::DescriptorType descriptor_type );

    const char* getError( VkResult result );

    VkExtent2D chooseSwapExtent( GLFWwindow* window, const VkSurfaceCapabilitiesKHR& capabilities );

    VkShaderStageFlagBits getShaderStateFlagBit( kege::ShaderStageBit stage );

    VkFormat getFormat( kege::Format format );

    VkPrimitiveTopology getPrimitiveTopology( kege::PrimitiveTopology topology );
}}

#endif /* kege_graphics_vk_hpp */
