//
//  vk-instance.cpp
//  new-engine
//
//  Created by Kenneth Esdaile on 12/30/23.
//

#include "vk-core.hpp"

namespace kege{namespace vk{

    VkResult Instance::init( std::vector< kege::Ref< vk::ValidationLayer > >& validation_layers )
    {
        auto extensions = vk::getRequiredExtensions();
        extensions.emplace_back( VK_KHR_PORTABILITY_ENUMERATION_EXTENSION_NAME );
        //extensions.emplace_back( VK_KHR_SHADER_DRAW_PARAMETERS_EXTENSION_NAME );
        //extensions.emplace_back( VK_KHR_MAINTENANCE_1_EXTENSION_NAME );
        //extensions.emplace_back( VK_EXT_MESH_SHADER_EXTENSION_NAME );

        VkApplicationInfo appInfo{};
        appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        appInfo.pApplicationName = "KEGE";
        appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.pEngineName = "Kenneth Esdaile Game Engine";
        appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.apiVersion = VK_API_VERSION_1_0;

        VkInstanceCreateInfo create_info{};
        create_info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        create_info.pApplicationInfo = &appInfo;
        create_info.enabledExtensionCount = static_cast<uint32_t>( extensions.size() );
        create_info.ppEnabledExtensionNames = extensions.data();
        create_info.enabledExtensionCount = (uint32_t) extensions.size();
        create_info.ppEnabledExtensionNames = extensions.data();
        create_info.flags |= VK_INSTANCE_CREATE_ENUMERATE_PORTABILITY_BIT_KHR;
        create_info.enabledLayerCount = 0;
        create_info.pNext = nullptr;

        if ( !validation_layers.empty() )
        {
            for (int i=0; i<validation_layers.size(); i++)
            {
                _validation_layer_names.push_back( validation_layers[i]->id() );
                if ( strcmp( validation_layers[i]->id(), "VK_LAYER_KHRONOS_validation" ) == 0 )
                {
                    vk::Debugger* debugger = static_cast< vk::Debugger* >( validation_layers[i].ref() );
                    create_info.pNext = &debugger->info();
                }
            }
            create_info.enabledLayerCount = static_cast< uint32_t >( _validation_layer_names.size() );
            create_info.ppEnabledLayerNames = _validation_layer_names.data();
        }

        VkResult result = vkCreateInstance( &create_info, nullptr, &_instance );
        if ( result != VK_SUCCESS )
        {
            return result;
        }

        for (int i=0; i<validation_layers.size(); i++)
        {
            if ( strcmp( validation_layers[i]->id(), "VK_LAYER_KHRONOS_validation" ) == 0 )
            {
                vk::Debugger* debugger = static_cast< vk::Debugger* >( validation_layers[i].ref() );
                debugger->init( this );
            }
        }
        return VK_SUCCESS;
    }

    const std::vector< const char* >& Instance::validationLayerNames()const
    {
        return _validation_layer_names;
    }

    const VkInstance Instance::handle()const
    {
        return _instance;
    }

    void Instance::uninit()
    {
        if ( _instance != VK_NULL_HANDLE )
        {
            vkDestroyInstance( _instance, nullptr );
            _instance = VK_NULL_HANDLE;
        }
    }

    Instance::~Instance()
    {
        uninit();
    }

    Instance::Instance()
    :   _instance( VK_NULL_HANDLE )
    {}

}}
