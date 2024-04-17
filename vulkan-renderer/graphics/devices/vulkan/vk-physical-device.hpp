//
//  vk-physical-device.hpp
//  new-engine
//
//  Created by Kenneth Esdaile on 12/30/23.
//

#ifndef kege_graphics_vk_physical_device_hpp
#define kege_graphics_vk_physical_device_hpp

#include "../vulkan/vk-instance.hpp"

namespace kege{namespace vk{

    /**
     * @brief Represents a Vulkan physical device.
     *
     * This class encapsulates a Vulkan physical device, providing a convenient interface for
     * querying and accessing properties and features of physical devices in Vulkan applications.
     */
    class PhysicalDevice : public kege::RefCounter
    {
    public:

        /**
         * @brief Retrieves the index of a memory type that meets the specified requirements.
         *
         * @param memory_requirements The memory requirements.
         * @param memory_properties The desired memory properties.
         * @return The index of the memory type if found; -1 otherwise.
         */
        int32_t getPhysicalDeviceMemoryTypeIndex( VkMemoryRequirements memory_requirements, VkMemoryPropertyFlags memory_properties );

        /**
         * @brief Selects a physical device for use with a Vulkan instance and surface.
         *
         * @param instance Reference to the Vulkan instance.
         * @param surface The surface to use.
         * @return VK_SUCCESS if a suitable physical device is found and selected; otherwise an error code.
         */
        VkResult selectPhysicalDevice( vk::Instance& instance, VkSurfaceKHR surface );

        /**
         * @brief Retrieves the memory properties of the physical device.
         *
         * @return The memory properties of the physical device.
         */
        const VkPhysicalDeviceMemoryProperties memoryProperties()const;

        /**
         * @brief Retrieves the properties of the physical device.
         *
         * @return The properties of the physical device.
         */
        const VkPhysicalDeviceProperties properties()const;

        /**
         * @brief Retrieves the features supported by the physical device.
         *
         * @return The features supported by the physical device.
         */
        const VkPhysicalDeviceFeatures features()const;

        /**
         * @brief Retrieves the device extensions supported by the physical device.
         *
         * @return The device extensions supported by the physical device.
         */
        const std::vector< const char* >& deviceExtensions()const;

        /**
         * @brief Retrieves information about the device queue family.
         *
         * @return Information about the device queue family.
         */
        const vk::DeviceQueueFamily& deviceQueueFamily()const;

        /**
         * @brief Retrieves the handle of the physical device.
         *
         * @return The handle of the physical device.
         */
        VkPhysicalDevice handle();

        /**
         * @brief Constructs a PhysicalDevice object.
         */
        PhysicalDevice();

    private:

        PhysicalDevice& operator =( const kege::Device& other ) = delete;
        PhysicalDevice( const kege::Device& other ) = delete;

    private:

        // Set the required device extentions we need
        std::vector< const char* > _device_extensions =
        {
            VK_KHR_SWAPCHAIN_EXTENSION_NAME,
            VK_KHR_SHADER_DRAW_PARAMETERS_EXTENSION_NAME,

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
            "VK_KHR_portability_subset",
            //VK_KHR_MAINTENANCE_1_EXTENSION_NAME,
        };

        VkPhysicalDeviceMemoryProperties _memory_properties;
        VkPhysicalDeviceProperties _properties;
        VkPhysicalDeviceFeatures _features;

        vk::DeviceQueueFamily _device_queue_family;
        VkPhysicalDevice _physical_device;
    };

}}

#endif /* kege_graphics_vk_physical_device_hpp */
