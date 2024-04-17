//
//  vk-command-pool.cpp
//  new-engine
//
//  Created by Kenneth Esdaile on 1/3/24.
//

#include "vk-core.hpp"

namespace kege{namespace vk{

    VkResult CommandPool::create( vk::Device* device, VkCommandPoolCreateFlags flags, kege::DeviceQueueType queue_index, vk::CommandPool& pool )
    {
        VkCommandPoolCreateInfo pool_info{};
        pool_info.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
        pool_info.queueFamilyIndex = device->getPhysicalDevice().deviceQueueFamily()[ queue_index ].value();
        pool_info.flags = flags;

        VkResult result = vkCreateCommandPool( device->getLogicalDevice(), &pool_info, nullptr, &pool._handle);
        if ( result != VK_SUCCESS )
        {
            return result;
        }

        pool._queue_type = queue_index;
        pool._device = device;
        return VK_SUCCESS;
    }

    VkResult CommandPool::allocateCommandBuffers( VkCommandBufferLevel level, int count, VkCommandBuffer* handle )
    {
        VkCommandBufferAllocateInfo alloc_enfo{};
        alloc_enfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
        alloc_enfo.level = level;
        alloc_enfo.commandPool = _handle;
        alloc_enfo.commandBufferCount = count;

        VkResult result = vkAllocateCommandBuffers( _device->getLogicalDevice(), &alloc_enfo, handle );
        if ( result != VK_SUCCESS )
        {
            KEGE_ERROR( vk::getError( result ) );
            return result;
        }
        return result;
    }

    void CommandPool::freeCommandBuffer( uint32_t count, VkCommandBuffer* command )
    {
        vkFreeCommandBuffers( _device->getLogicalDevice(), _handle, count, command );
    }

    kege::DeviceQueueType CommandPool::getQueueIndex()const
    {
        return _queue_type;
    }

    const VkCommandPool CommandPool::handle()const
    {
        return _handle;
    }

    void CommandPool::destruct()
    {
        if ( _handle != VK_NULL_HANDLE )
        {
            vkDestroyCommandPool( _device->getLogicalDevice(), _handle, nullptr );
            _handle = VK_NULL_HANDLE;
        }
    }

    CommandPool::~CommandPool()
    {
        destruct();
    }

    CommandPool::CommandPool()
    :   _handle( VK_NULL_HANDLE )
    ,   _device( nullptr )
    ,   _queue_type( kege::GRAPHICS_QUEUE )
    {}

}}
