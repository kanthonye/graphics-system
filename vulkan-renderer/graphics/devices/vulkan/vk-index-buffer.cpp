//
//  vk-index-buffer.cpp
//  new-engine
//
//  Created by Kenneth Esdaile on 3/5/24.
//

#include "vk-core.hpp"

namespace kege{namespace vk{

    VkResult IndexBuffer::construct(  const kege::CreateIndexBufferInfo& info )
    {
        _usage = info.memory_usage;
        _index_type = ( info.index_type == kege::INDEX_TYPE_U32)
        ? VK_INDEX_TYPE_UINT32 : ( info.index_type == kege::INDEX_TYPE_U16)
        ? VK_INDEX_TYPE_UINT16 : VK_INDEX_TYPE_UINT8_EXT;
        return _buffer.construct( _device, info.memory_usage, VK_BUFFER_USAGE_INDEX_BUFFER_BIT, info.size, info.data );
    }

    void IndexBuffer::setBufferData( uint64_t offset, uint64_t size, const void* data )
    {
        _buffer.setBufferData( _device->getLogicalDevice(), offset, size, data );
    }

    void IndexBuffer::getBufferData( uint64_t offset, uint64_t size, void*& data )
    {
        _buffer.setBufferData( _device->getLogicalDevice(), offset, size, data );
    }

    void IndexBuffer::bind( kege::CommandBuffer* command_buffer )const
    {
        vkCmdBindIndexBuffer( command_buffer->vulkan()->getCurrentCommandBuffer(), _buffer.handle, 0, _index_type );
    }

    const VkDeviceMemory IndexBuffer::memory()const
    {
        return _buffer.memory;
    }

    const VkBuffer IndexBuffer::handle()const
    {
        return _buffer.handle;
    }

    uint64_t IndexBuffer::sizeInBytes()const
    {
        return _buffer.size;
    }

    const vk::IndexBuffer* IndexBuffer::vulkan()const
    {
        return this;
    }

    vk::IndexBuffer* IndexBuffer::vulkan()
    {
        return this;
    }

    const void* IndexBuffer::mapMemory()const
    {
        return _buffer.mapMemory( _device->getLogicalDevice() );
    }

    void IndexBuffer::unmapMemory()
    {
        _buffer.unmapMemory( _device->getLogicalDevice() );
    }

    void* IndexBuffer::mapMemory()
    {
        return _buffer.mapMemory( _device->getLogicalDevice() );
    }

    IndexBuffer::~IndexBuffer()
    {
        _device->waitIdle();
        _buffer.destroy( _device->getLogicalDevice() );
    }

    IndexBuffer::IndexBuffer( vk::Device* device )
    :   _buffer()
    ,   _device( device )
    {}

}}
