//
//  vk-uniform-buffer.cpp
//  new-engine
//
//  Created by Kenneth Esdaile on 3/5/24.
//

#include "vk-core.hpp"

namespace kege{namespace vk{

    VkResult UniformBuffer::construct( const kege::CreateBufferInfo& info )
    {
        _usage = info.memory_usage;
        return _buffer.construct( _device, info.memory_usage, VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, info.size, info.data );
    }

    void UniformBuffer::setBufferData( uint64_t offset, uint64_t size, const void* data )
    {
        _buffer.setBufferData( _device->getLogicalDevice(), offset, size, data );
    }

    void UniformBuffer::getBufferData( uint64_t offset, uint64_t size, void*& data )
    {
        _buffer.setBufferData( _device->getLogicalDevice(), offset, size, data );
    }

    void UniformBuffer::getDescriptorBufferInfo( void* data )
    {
        VkDescriptorBufferInfo* info = (VkDescriptorBufferInfo*) data;
        info->buffer = _buffer.handle;
        info->range  = _buffer.size;
        info->offset = 0;
    }

    const VkDeviceMemory UniformBuffer::memory()const
    {
        return _buffer.memory;
    }

    const VkBuffer UniformBuffer::handle()const
    {
        return _buffer.handle;
    }

    uint64_t UniformBuffer::sizeInBytes()const
    {
        return _buffer.size;
    }

    const vk::UniformBuffer* UniformBuffer::vulkan()const
    {
        return this;
    }

    vk::UniformBuffer* UniformBuffer::vulkan()
    {
        return this;
    }

    const void* UniformBuffer::mapMemory()const
    {
        return _buffer.mapMemory( _device->getLogicalDevice() );
    }

    void UniformBuffer::unmapMemory()
    {
        _buffer.unmapMemory( _device->getLogicalDevice() );
    }

    void* UniformBuffer::mapMemory()
    {
        return _buffer.mapMemory( _device->getLogicalDevice() );
    }

    UniformBuffer::~UniformBuffer()
    {
        _device->waitIdle();
        _buffer.destroy( _device->getLogicalDevice() );
    }

    UniformBuffer::UniformBuffer( vk::Device* device )
    :   _buffer()
    ,   _device( device )
    {}

}}
