//
//  vk-vertex-buffer.cpp
//  new-engine
//
//  Created by Kenneth Esdaile on 3/5/24.
//

#include "vk-core.hpp"

namespace kege{namespace vk{

    VkResult VertexBuffer::construct(  const kege::CreateBufferInfo& info )
    {
        _usage = info.memory_usage;
        return _buffer.construct( _device, info.memory_usage, VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, info.size, info.data );
    }

    void VertexBuffer::setBufferData( uint64_t offset, uint64_t size, const void* data )
    {
        _buffer.setBufferData( _device->getLogicalDevice(), offset, size, data );
    }

    void VertexBuffer::getBufferData( uint64_t offset, uint64_t size, void*& data )
    {
        _buffer.setBufferData( _device->getLogicalDevice(), offset, size, data );
    }

    void VertexBuffer::bind( kege::CommandBuffer* command_buffer )const
    {
        const VkDeviceSize offsets[] = {0};
        VkBuffer vertex_bufers[] = { _buffer.handle };
        vkCmdBindVertexBuffers( command_buffer->vulkan()->getCurrentCommandBuffer(), 0, 1, vertex_bufers, offsets );
    }

    const VkDeviceMemory VertexBuffer::memory()const
    {
        return _buffer.memory;
    }

    const VkBuffer VertexBuffer::handle()const
    {
        return _buffer.handle;
    }

    uint64_t VertexBuffer::sizeInBytes()const
    {
        return _buffer.size;
    }

    const vk::VertexBuffer* VertexBuffer::vulkan()const
    {
        return this;
    }

    vk::VertexBuffer* VertexBuffer::vulkan()
    {
        return this;
    }

    const void* VertexBuffer::mapMemory()const
    {
        return _buffer.mapMemory( _device->getLogicalDevice() );
    }

    void VertexBuffer::unmapMemory()
    {
        _buffer.unmapMemory( _device->getLogicalDevice() );
    }

    void* VertexBuffer::mapMemory()
    {
        return _buffer.mapMemory( _device->getLogicalDevice() );
    }

    VertexBuffer::~VertexBuffer()
    {
        _device->waitIdle();
        _buffer.destroy( _device->getLogicalDevice() );
    }

    VertexBuffer::VertexBuffer( vk::Device* device )
    :   _buffer()
    ,   _device( device )
    {}

}}
