//
//  vk-fence.cpp
//  new-engine
//
//  Created by Kenneth Esdaile on 1/3/24.
//

#include "vk-core.hpp"

namespace kege{namespace vk{

    VkResult Fence::create(vk::Device* device, vk::Fence& fence)
    {
        VkFenceCreateInfo fence_info{};
        fence_info.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
        fence_info.flags = VK_FENCE_CREATE_SIGNALED_BIT;
        VkResult result = vkCreateFence( device->getLogicalDevice(), &fence_info, nullptr, &fence._handle );
        if ( result != VK_SUCCESS )
        {
            KEGE_ERROR("%s: failed to create vk::Fence!", vk::getError( result ) );
            return result;
        }
        fence._device = device;
        vkResetFences( device->getLogicalDevice(), 1, &fence._handle );
        return result;
    }

    const VkFence Fence::handle()const
    {
        return _handle;
    }

    void Fence::destruct()
    {
        if ( _handle != VK_NULL_HANDLE )
        {
            _device->waitIdle();
            vkDestroyFence( _device->getLogicalDevice(), _handle, nullptr );
            _handle = VK_NULL_HANDLE;
        }
    }

    Fence::~Fence()
    {
        destruct();
    }

    Fence::Fence()
    : _handle( VK_NULL_HANDLE )
    , _device( nullptr )
    {
    }
}}
