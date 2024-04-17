//
//  vk-debugger.cpp
//  new-engine
//
//  Created by Kenneth Esdaile on 12/30/23.
//

#include "vk-core.hpp"

namespace kege{namespace vk{

    VKAPI_ATTR VkBool32 VKAPI_CALL debugUtilsMessengerCallback
    (
        VkDebugUtilsMessageSeverityFlagBitsEXT message_severity,
        VkDebugUtilsMessageTypeFlagsEXT message_type,
        const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
        void* pUserData
    )
    {
        switch ( message_severity )
        {
            case VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT:{
                /* Indicates messages with the lowest severity level. These
                 messages provide detailed information for debugging but
                 are not typically relevant for most development scenarios. */
                //if ( message_type == VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT )
                {
                    KEGE_TRACE("vulkan: %s", pCallbackData->pMessage );
                }
                break;
            }

            case VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT:{
                /*  Indicates informational messages that can help you understand
                 the behavior of the Vulkan API and your application. */
                KEGE_INFO("vulkan: %s", pCallbackData->pMessage );
                break;
            }

            case VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT:{
                /* Indicates warning messages that point out potential issues that
                 could lead to unexpected behavior or suboptimal performance. */
                KEGE_WARN("vulkan: %s", pCallbackData->pMessage );
                break;
            }

            case VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT:{
                /* Indicates error messages that signal problems in your code
                 that need to be addressed. These messages often indicate
                 incorrect API usage or other issues that might cause your
                 application to misbehave or crash. */
                if ( message_type == VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT )
                {
                    KEGE_ERROR("vulkan: %s", pCallbackData->pMessage );
                }
                else if ( message_type == VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT )
                {
                    KEGE_ERROR("vulkan: %s", pCallbackData->pMessage );
                }
                else if ( message_type == VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT )
                {
                    KEGE_FATAL("vulkan: %s", pCallbackData->pMessage );
                }
                break;
            }

            default:
                break;
        }
        return VK_FALSE;
    }

    VkResult debugUtilsMessengerEXT
    (
        VkInstance instance,
        const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo,
        const VkAllocationCallbacks* pAllocator,
        VkDebugUtilsMessengerEXT* pDebugMessenger
    )
    {
        auto func = (PFN_vkCreateDebugUtilsMessengerEXT) vkGetInstanceProcAddr( instance, "vkCreateDebugUtilsMessengerEXT" );
        if (func != nullptr)
        {
            return func( instance, pCreateInfo, pAllocator, pDebugMessenger );
        }
        else
        {
            return VK_ERROR_EXTENSION_NOT_PRESENT;
        }
    }

    const VkDebugUtilsMessengerCreateInfoEXT& Debugger::info()const
    {
        return _info;
    }

    VkResult Debugger::init( const Instance* instance )
    {
        _instance = instance;
        return vk::debugUtilsMessengerEXT( instance->handle(), &_info, nullptr, &_handle );
    }

    const VkDebugUtilsMessengerEXT Debugger::handle()const
    {
        return _handle;
    }

    void Debugger::uninit()
    {
        auto destroyDebugUtilsMessenger = (PFN_vkDestroyDebugUtilsMessengerEXT) vkGetInstanceProcAddr( _instance->handle(), "vkDestroyDebugUtilsMessengerEXT" );
        if (destroyDebugUtilsMessenger != nullptr)
        {
            destroyDebugUtilsMessenger( _instance->handle(), _handle, nullptr );
            _handle = nullptr;
        }
    }

//    const kege::string& DebugUtilsMessenger::sid()const
//    {
//        return _sid;
//    }

    Debugger::~Debugger()
    {
        uninit();
    }

    Debugger::Debugger()
    :   vk::ValidationLayer( "VK_LAYER_KHRONOS_validation" )
    ,   _handle( VK_NULL_HANDLE )
    {
        _info = {};
        _info.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;

        _info.messageSeverity =
            VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT |
            VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT |
            VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT   |
            VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT
        ;

        _info.messageType =
            VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT |
            VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT |
            VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT
        ;
        _info.pfnUserCallback = debugUtilsMessengerCallback;
    }


}}
