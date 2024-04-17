//
//  vk-semaphore.cpp
//  new-engine
//
//  Created by Kenneth Esdaile on 1/3/24.
//

#include "vk-core.hpp"

namespace kege{namespace vk{

    VkResult Semaphore::create(vk::Device* device, vk::Semaphore& semaphore)
    {
        VkSemaphoreCreateInfo semaphore_info{};
        semaphore_info.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;
        VkResult result = vkCreateSemaphore( device->getLogicalDevice(), &semaphore_info, nullptr, &semaphore._handle );
        if ( result != VK_SUCCESS )
        {
            KEGE_ERROR("%s: failed to create vk::Semaphore!", vk::getError( result ) );
            return result;
        }
        semaphore._device = device;
        return result;
    }

    const VkSemaphore Semaphore::handle()const
    {
        return _handle;
    }

    void Semaphore::destruct()
    {
        if ( _handle != VK_NULL_HANDLE )
        {
            _device->waitIdle();
            vkDestroySemaphore( _device->getLogicalDevice(), _handle, nullptr );
            _handle = VK_NULL_HANDLE;
        }
    }

    Semaphore::~Semaphore()
    {
        destruct();
    }

    Semaphore::Semaphore()
    : _handle( VK_NULL_HANDLE )
    , _device( nullptr )
    {}
}}
