//
//  vk-buffer.cpp
//  new-engine
//
//  Created by Kenneth Esdaile on 12/30/23.
//

#include "vk-core.hpp"

namespace kege{namespace vk{

    VkResult Buffer::construct( vk::Device* device, MemoryUsage memory_usage, VkBufferUsageFlags buffer_type, uint64_t size, const void* data )
    {
        VkResult result;
        switch ( memory_usage )
        {
            case kege::STREAM_BUFFER:
            case kege::DYNAMIC_BUFFER:
                result = this->create
                (  device
                 , VK_SHARING_MODE_EXCLUSIVE
                 , buffer_type | VK_BUFFER_USAGE_TRANSFER_DST_BIT
                 , VK_MEMORY_PROPERTY_HOST_COHERENT_BIT | VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT
                 , size, data );
                break;

            case kege::STATIC_BUFFER:
                result = this->create
                (  device
                 , VK_SHARING_MODE_EXCLUSIVE
                 , buffer_type | VK_BUFFER_USAGE_TRANSFER_DST_BIT
                 , VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT
                 , size, nullptr );
                if( result == VK_SUCCESS )
                {
                    vk::Buffer source;
                    result = source.create
                    (  device
                     , VK_SHARING_MODE_EXCLUSIVE
                     , VK_BUFFER_USAGE_TRANSFER_SRC_BIT | VK_BUFFER_USAGE_TRANSFER_DST_BIT
                     , VK_MEMORY_PROPERTY_HOST_COHERENT_BIT | VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT
                     , size, data );

                    device->copyBuffer( *this, source );
                    source.destroy( device->getLogicalDevice() );
                }
                break;
        }
        return result;
    }

    VkResult Buffer::create
    (
        vk::Device* device,
        VkSharingMode sharing_mode,
        VkBufferUsageFlags usage,
        VkMemoryPropertyFlags memory_properties,
        VkDeviceSize size,
        const void* data
    )
    {
        VkDevice logical_device = device->getLogicalDevice();

        VkBufferCreateInfo create_info{};
        create_info.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
        create_info.sharingMode = sharing_mode;
        create_info.usage = usage;
        create_info.size = size;
        VkResult result = vkCreateBuffer( logical_device, &create_info, nullptr, &this->handle );

        if ( result == VK_SUCCESS )
        {
            VkMemoryRequirements memory_requirements;
            vkGetBufferMemoryRequirements( logical_device, this->handle, &memory_requirements );
            uint32_t memory_type_index = device->getPhysicalDevice().getPhysicalDeviceMemoryTypeIndex
            (
                memory_requirements, memory_properties
            );

            VkMemoryAllocateInfo memory_allocate_info =
            {
                VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
                nullptr,
                memory_requirements.size,
                memory_type_index
            };

            VkResult result = vkAllocateMemory( logical_device, &memory_allocate_info, nullptr, &this->memory );
            if( result != VK_SUCCESS )
            {
                KEGE_ERROR( "Could not allocate memory for a buffer." );
                return VK_ERROR_INITIALIZATION_FAILED;
            }

            result = vkBindBufferMemory( logical_device, this->handle, this->memory, 0 );
            if( result != VK_SUCCESS )
            {
                KEGE_ERROR( "Could not bind memory object to an image." );
                return VK_ERROR_INITIALIZATION_FAILED;
            }

            if( data )
            {
                void* mapmem = nullptr;
                vkMapMemory( logical_device, this->memory, 0, memory_requirements.size, 0, &mapmem );
                memcpy( mapmem, data, memory_requirements.size );
                vkUnmapMemory( logical_device, this->memory );
            }

            this->size = size;
            return result;
        }
        KEGE_FATAL("%s: failed to create buffer!", vk::getError(result) );
        return result;
    }

    void Buffer::setBufferData( VkDevice device, uint64_t offset, uint64_t size, const void* data )
    {
        if(size > this->size)
            throw std::runtime_error("buffer size is too small to contain the data");

        void* mapmem = nullptr;
        vkMapMemory( device, this->memory, offset, size, 0, &mapmem );
        memcpy( mapmem, data, size );
        vkUnmapMemory( device, this->memory );
    }

    void Buffer::getBufferData( VkDevice device, uint64_t offset, uint64_t dsize, void*& data )
    {
        void* mapmem = nullptr;
        vkMapMemory( device, this->memory, offset, dsize, 0, &mapmem );
        memcpy( data, mapmem, size );
        vkUnmapMemory( device, this->memory );
    }

    const void* Buffer::mapMemory( VkDevice device )const
    {
        void* mapmem = nullptr;
        vkMapMemory( device, this->memory, 0, this->size, 0, &mapmem );
        return mapmem;
    }

    void Buffer::unmapMemory( VkDevice device  )
    {
        vkUnmapMemory( device, this->memory );
    }

    void* Buffer::mapMemory( VkDevice device )
    {
        void* mapmem = nullptr;
        vkMapMemory( device, this->memory, 0, this->size, 0, &mapmem );
        return mapmem;
    }

    void Buffer::destroy( VkDevice device )
    {
        if ( this->memory != VK_NULL_HANDLE )
        {
            vkFreeMemory( device, this->memory, nullptr );
            this->memory = VK_NULL_HANDLE;
        }

        if ( this->handle != VK_NULL_HANDLE )
        {
            vkDestroyBuffer(device, this->handle, nullptr );
            this->handle = VK_NULL_HANDLE;
        }
    }

    Buffer::~Buffer()
    {
    }

    Buffer::Buffer()
    :   memory( VK_NULL_HANDLE )
    ,   handle( VK_NULL_HANDLE )
    ,   size( 0 )
    {}

}}
