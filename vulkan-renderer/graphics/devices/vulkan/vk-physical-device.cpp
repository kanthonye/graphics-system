//
//  vk-physical-device.cpp
//  new-engine
//
//  Created by Kenneth Esdaile on 12/30/23.
//

#include "vk-core.hpp"

namespace kege{namespace vk{

    bool isPhysicalDeviceSuitable
    (
        VkSurfaceKHR surface,
        VkPhysicalDevice physical_device,
        VkPhysicalDeviceFeatures supported_features,
        const std::vector< const char* >& device_extensions
    )
    {
        bool extensions_supported = checkDeviceExtensionSupport( physical_device, device_extensions );

        bool swapchain_adequate = false;
        if ( extensions_supported )
        {
            SwapChainSupportDetails details;
            querySwapChainSupport( surface, physical_device, details );
            swapchain_adequate = ( !details.formats.empty() && !details.present_modes.empty() );
        }

        return extensions_supported && swapchain_adequate && supported_features.samplerAnisotropy;
    }

    bool physicalMeetDeviceRequirements
    (
        VkSurfaceKHR surface,
        VkPhysicalDevice physical_device,
        VkPhysicalDeviceProperties* properties,
        VkPhysicalDeviceFeatures* features,
        VkPhysicalDeviceMemoryProperties* memory,
        PhysicalDeviceRequirements* requirements,
        DeviceQueueFamily& queue_family
    )
    {
        if ( !requirements->_descrete_gpu )
        {
            if( properties->deviceType != VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU ) {
                KEGE_INFO( "device is not a descrete GPU, a descrete GPU is required, so this one is skipped." );
                return false;
            }
        }

        uint32_t queue_family_count = 0;
        vkGetPhysicalDeviceQueueFamilyProperties( physical_device, &queue_family_count, nullptr );
        VkQueueFamilyProperties queue_family_properties[ queue_family_count ];
        vkGetPhysicalDeviceQueueFamilyProperties( physical_device, &queue_family_count, queue_family_properties );

        KEGE_INFO( "Graphics | Present | Compute | Transfer | Name" );

        for(int i=0; i<queue_family_count; i++)
        {
            int index_taken = 0;
            if( !queue_family[ kege::GRAPHICS_QUEUE ].has_value() && queue_family_properties[i].queueFlags & VK_QUEUE_GRAPHICS_BIT )
            {
                queue_family[ kege::GRAPHICS_QUEUE ] = i;
                index_taken = 'G';
            }
            if( !queue_family[ kege::COMPUTE_QUEUE ].has_value() && queue_family_properties[i].queueFlags & VK_QUEUE_COMPUTE_BIT )
            {
                if ( i >= 1 )
                {
                    queue_family[ kege::COMPUTE_QUEUE ] = i;
                    index_taken = 'C';
                }
            }
            if( !queue_family[ kege::TRANSFER_QUEUE ].has_value() && queue_family_properties[i].queueFlags & VK_QUEUE_TRANSFER_BIT )
            {
                if ( index_taken == 0 )
                {
                    queue_family[ kege::TRANSFER_QUEUE ] = i;
                    index_taken = 'T';
                }
            }

            VkBool32 support_present = VK_FALSE;
            vkGetPhysicalDeviceSurfaceSupportKHR( physical_device, i, surface, &support_present );
            if ( !queue_family[ kege::PRESENT_QUEUE ].has_value() && support_present == VK_TRUE )
            {
                if ( index_taken == 0 )
                {
                    queue_family[ kege::PRESENT_QUEUE ] = i;
                    index_taken = 'P';
                }
            }
        }

        KEGE_INFO( " %7d | %7d | %7d | %8d | %s",
            queue_family[ kege::GRAPHICS_QUEUE ],
            queue_family[ kege::COMPUTE_QUEUE  ],
            queue_family[ kege::PRESENT_QUEUE  ],
            queue_family[ kege::TRANSFER_QUEUE ],
            properties->deviceName
        );

        if
        (
            (!requirements->_graphics || (requirements->_graphics && queue_family[ kege::GRAPHICS_QUEUE ].has_value())) &&
            (!requirements->_compute  || (requirements->_compute  && queue_family[ kege::COMPUTE_QUEUE ].has_value()) ) &&
            (!requirements->_transfer || (requirements->_transfer && queue_family[ kege::PRESENT_QUEUE ].has_value()) ) &&
            (!requirements->_present  || (requirements->_present  && queue_family[ kege::TRANSFER_QUEUE ].has_value()) )
        )
        {
            KEGE_INFO( "Device %s meets queue requirements", properties->deviceName );
            KEGE_TRACE( "Graphics Queue family index %i", queue_family[ kege::GRAPHICS_QUEUE ] );
            KEGE_TRACE( "Present  Queue family index %i", queue_family[ kege::PRESENT_QUEUE  ] );
            KEGE_TRACE( "Transfer Queue family index %i", queue_family[ kege::TRANSFER_QUEUE ] );
            KEGE_TRACE( "Compute  Queue family index %i", queue_family[ kege::COMPUTE_QUEUE  ] );

            SwapChainSupportDetails details;
            querySwapChainSupport( surface, physical_device, details );

            if ( details.formats.empty() || details.present_modes.empty() )
            {
                KEGE_INFO( "Required swapchain support not available for the device %s. Skipping device.", properties->deviceName );
                return false;
            }

            if ( requirements->_device_extension_names.size() )
            {
                uint32_t available_extenstion_count = 0;
                vkEnumerateDeviceExtensionProperties( physical_device, nullptr, &available_extenstion_count, nullptr );
                if ( available_extenstion_count )
                {
                    std::vector< VkExtensionProperties > extension_properties;
                    extension_properties.resize( available_extenstion_count );
                    vkEnumerateDeviceExtensionProperties( physical_device, nullptr, &available_extenstion_count, extension_properties.data() );

                    for (int i=0; i<requirements->_device_extension_names.size(); i++)
                    {
                        bool found = false;
                        for (int j=0; j<extension_properties.size(); j++)
                        {
                            if ( requirements->_device_extension_names[i] == extension_properties[j].extensionName )
                            {
                                found = true;
                                break;
                            }
                        }

                        if ( !found )
                        {
                            KEGE_INFO( "Required extension not available for the device %s, skipping device.", properties->deviceName );
                            return false;
                        }
                    }
                }
            }

            if ( requirements->_sampler_anisotropy && !features->samplerAnisotropy )
            {
                KEGE_INFO( "Device does not support not sampler-anisotropy, skipping device.", properties->deviceName );
                return false;
            }
            return true;
        }

        return false;
    }

    int32_t PhysicalDevice::getPhysicalDeviceMemoryTypeIndex( VkMemoryRequirements memory_requirements, VkMemoryPropertyFlags memory_properties )
    {
        for( uint32_t type = 0; type < _memory_properties.memoryTypeCount; ++type )
        {
            if( (memory_requirements.memoryTypeBits & (1 << type)) && ((_memory_properties.memoryTypes[ type ].propertyFlags & memory_properties) == memory_properties) )
            {
                return type;
            }
        }
        return -1;
    }
    
    VkResult PhysicalDevice::selectPhysicalDevice( vk::Instance& instance, VkSurfaceKHR surface )
    {
        uint32_t device_count = 0;
        vkEnumeratePhysicalDevices( instance.handle(), &device_count, nullptr );

        if (device_count == 0)
        {
            KEGE_FATAL("failed to find GPUs with Vulkan support!");
            return VK_ERROR_INITIALIZATION_FAILED;
        }

        //VkPhysicalDevice physical_device = VK_NULL_HANDLE;
        VkPhysicalDevice physical_devices[ device_count ];
        vkEnumeratePhysicalDevices( instance.handle(), &device_count, physical_devices );

        for (int i=0; i<device_count; i++)
        {
            vkGetPhysicalDeviceFeatures( physical_devices[i], &_features );

            if (_features.shaderFloat64 == VK_TRUE) {
                KEGE_DEBUG( "shaderFloat64 is supported." );
            } else {
                KEGE_DEBUG( "shaderFloat64 is NOT supported." );
            }
        }

        for (int i=0; i<device_count; i++)
        {
            vkGetPhysicalDeviceMemoryProperties( physical_devices[i], &_memory_properties );
            vkGetPhysicalDeviceProperties( physical_devices[i], &_properties );
            vkGetPhysicalDeviceFeatures( physical_devices[i], &_features );

            PhysicalDeviceRequirements requirements = {};
            requirements._graphics = true;
            requirements._present = true;
            requirements._compute = true;
            requirements._transfer = true;
            requirements._descrete_gpu = true;
            requirements._sampler_anisotropy = true;
            requirements._device_extension_names = { VK_KHR_SWAPCHAIN_EXTENSION_NAME };

            DeviceQueueFamily device_queue_family;

            bool device_is_sutable = physicalMeetDeviceRequirements
            (
                surface,
                physical_devices[i],
                &_properties,
                &_features,
                &_memory_properties,
                &requirements,
                _device_queue_family
            );

            if ( device_is_sutable )
            {
                _physical_device = physical_devices[i];

                KEGE_INFO
                (
                    "GPU Drive Version: %i.%i.%i",
                    VK_VERSION_MAJOR( _properties.driverVersion),
                    VK_VERSION_MINOR( _properties.driverVersion),
                    VK_VERSION_PATCH( _properties.driverVersion)
                );

                KEGE_INFO
                (
                    "Vulkan API Version: %i.%i.%i",
                    VK_VERSION_MAJOR( _properties.apiVersion),
                    VK_VERSION_MINOR( _properties.apiVersion),
                    VK_VERSION_PATCH( _properties.apiVersion)
                );

                for (int i=0; i<_memory_properties.memoryHeapCount; i++)
                {
                    double memsize = double( _memory_properties.memoryHeaps[i].size ) / ( 1024.0 * 1024.0 * 1024.0 );

                    if ( _memory_properties.memoryHeaps[i].flags & VK_MEMORY_HEAP_DEVICE_LOCAL_BIT )
                    {
                        KEGE_INFO( "Local GPU Memory: %.2f GiB", memsize );
                    }
                    else
                    {
                        KEGE_INFO( "Shared System Memory: %.2f GiB", memsize );
                    }
                }

                break;
            }

            if ( device_queue_family.isComplete() && isPhysicalDeviceSuitable( surface, physical_devices[i], _features, _device_extensions ) )
            {
                _physical_device = physical_devices[i];
                break;
            }
        }

        if ( _physical_device == VK_NULL_HANDLE )
        {
            KEGE_FATAL("failed to find a suitable GPU!");
            return VK_ERROR_INITIALIZATION_FAILED;
        }
        
        std::cout <<"\n\n";
        std::cout <<"max-storage-buffer-size: "<< _properties.limits.maxStorageBufferRange <<"\n";
        std::cout <<"max-uniform-buffer-size: "<< _properties.limits.maxUniformBufferRange <<"\n";
        std::cout <<"max-push-constants-size: "<< _properties.limits.maxPushConstantsSize <<"\n";
        std::cout <<"max-image-array-layers: "<< _properties.limits.maxImageArrayLayers <<"\n";
        std::cout <<"max-framebuffer-width: "<< _properties.limits.maxFramebufferWidth <<"\n";
        std::cout <<"max-framebuffer-height: "<< _properties.limits.maxFramebufferHeight <<"\n";
        std::cout <<"max-framebuffer-layers: "<< _properties.limits.maxFramebufferLayers <<"\n";
        std::cout <<"max-clip-distances: "<< _properties.limits.maxClipDistances <<"\n";
        std::cout <<"max-cull-distances: "<< _properties.limits.maxCullDistances <<"\n";
        std::cout <<"\n\n";

        return VK_SUCCESS;
    }

    const VkPhysicalDeviceMemoryProperties PhysicalDevice::memoryProperties()const
    {
        return _memory_properties;
    }
    const VkPhysicalDeviceProperties PhysicalDevice::properties()const
    {
        return _properties;
    }
    const VkPhysicalDeviceFeatures PhysicalDevice::features()const
    {
        return _features;
    }

    const std::vector< const char* >& PhysicalDevice::deviceExtensions()const
    {
        return _device_extensions;
    }

    const vk::DeviceQueueFamily& PhysicalDevice::deviceQueueFamily()const
    {
        return _device_queue_family;
    }

    VkPhysicalDevice PhysicalDevice::handle()
    {
        return _physical_device;
    }

    PhysicalDevice::PhysicalDevice()
    :   _physical_device( VK_NULL_HANDLE )
    {}

}}
