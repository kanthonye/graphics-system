//
//  vk-storage-buffer.cpp
//  new-engine
//
//  Created by Kenneth Esdaile on 3/5/24.
//


#include "vk-core.hpp"

namespace kege{namespace vk{

    VkResult StorageBuffer::construct( const kege::CreateBufferInfo& info )
    {
        _usage = info.memory_usage;
        return _buffer.construct( _device, info.memory_usage, VK_BUFFER_USAGE_STORAGE_BUFFER_BIT, info.size, info.data );
    }

    void StorageBuffer::setBufferData( uint64_t offset, uint64_t size, const void* data )
    {
        _buffer.setBufferData( _device->getLogicalDevice(), offset, size, data );
    }

    void StorageBuffer::getBufferData( uint64_t offset, uint64_t size, void*& data )
    {
        _buffer.setBufferData( _device->getLogicalDevice(), offset, size, data );
    }

    void StorageBuffer::getDescriptorBufferInfo( void* data )
    {
        VkDescriptorBufferInfo* info = (VkDescriptorBufferInfo*) data;
        info->buffer = _buffer.handle;
        info->range  = _buffer.size;
        info->offset = 0;
    }

    const VkDeviceMemory StorageBuffer::memory()const
    {
        return _buffer.memory;
    }

    const VkBuffer StorageBuffer::handle()const
    {
        return _buffer.handle;
    }

    uint64_t StorageBuffer::sizeInBytes()const
    {
        return _buffer.size;
    }

    const vk::StorageBuffer* StorageBuffer::vulkan()const
    {
        return this;
    }

    vk::StorageBuffer* StorageBuffer::vulkan()
    {
        return this;
    }

    const void* StorageBuffer::mapMemory()const
    {
        return _buffer.mapMemory( _device->getLogicalDevice() );
    }

    void StorageBuffer::unmapMemory()
    {
        _buffer.unmapMemory( _device->getLogicalDevice() );
    }

    void* StorageBuffer::mapMemory()
    {
        return _buffer.mapMemory( _device->getLogicalDevice() );
    }

    StorageBuffer::~StorageBuffer()
    {
        _device->waitIdle();
        _buffer.destroy( _device->getLogicalDevice() );
    }

    StorageBuffer::StorageBuffer( vk::Device* device )
    :   _buffer()
    ,   _device( device )
    {}

}}
