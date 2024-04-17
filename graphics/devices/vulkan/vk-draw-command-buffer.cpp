//
//  vk-draw-command-buffer.cpp
//  new-engine
//
//  Created by Kenneth Esdaile on 3/5/24.
//

#include "vk-core.hpp"

namespace kege{namespace vk{

    void DrawCommandBuffer::drawIndirect( const vk::CommandBuffer* command_buffer, uint64_t offset, uint32_t draw_count )const
    {
        vkCmdDrawIndirect( command_buffer->getCurrentCommandBuffer(), _buffer.handle, offset, draw_count, _stride );
    }

    VkResult DrawCommandBuffer::construct( const kege::DrawCommandBuffer::CreateInfo& info )
    {
        VkResult result;
        switch ( info.memory_usage )
        {
            case kege::STREAM_BUFFER:
            case kege::DYNAMIC_BUFFER:
                result = _buffer.create
                (  _device
                 , VK_SHARING_MODE_EXCLUSIVE
                 , VK_BUFFER_USAGE_INDIRECT_BUFFER_BIT | VK_BUFFER_USAGE_TRANSFER_DST_BIT
                 , VK_MEMORY_PROPERTY_HOST_COHERENT_BIT | VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT
                 , info.size, info.data );
                break;

            case kege::STATIC_BUFFER:
                result = _buffer.create
                (  _device
                 , VK_SHARING_MODE_EXCLUSIVE
                 , VK_BUFFER_USAGE_INDIRECT_BUFFER_BIT | VK_BUFFER_USAGE_TRANSFER_DST_BIT
                 , VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT
                 , info.size, nullptr );
                if( result == VK_SUCCESS )
                {
                    vk::Buffer source;
                    result = source.create
                    (  _device
                     , VK_SHARING_MODE_EXCLUSIVE
                     , VK_BUFFER_USAGE_TRANSFER_SRC_BIT | VK_BUFFER_USAGE_TRANSFER_DST_BIT
                     , VK_MEMORY_PROPERTY_HOST_COHERENT_BIT | VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT
                     , info.size, nullptr );

                    _device->copyBuffer( _buffer, source );
                    source.destroy( _device->getLogicalDevice() );
                }
                break;
        }
        _usage = info.memory_usage;
        _stride = (uint32_t)sizeof( VkDrawIndirectCommand );
        return result;
    }

    void DrawCommandBuffer::setBufferData( uint64_t offset, uint64_t size, const void* data )
    {
        _buffer.setBufferData( _device->getLogicalDevice(), offset, size, data );
    }

    void DrawCommandBuffer::getBufferData( uint64_t offset, uint64_t size, void*& data )
    {
        _buffer.setBufferData( _device->getLogicalDevice(), offset, size, data );
    }

    uint64_t DrawCommandBuffer::sizeInBytes()const
    {
        return _buffer.size;
    }

    const void* DrawCommandBuffer::mapMemory()const
    {
        return _buffer.mapMemory( _device->getLogicalDevice() );
    }

    void DrawCommandBuffer::unmapMemory()
    {
        _buffer.unmapMemory( _device->getLogicalDevice() );
    }

    void* DrawCommandBuffer::mapMemory()
    {
        return _buffer.mapMemory( _device->getLogicalDevice() );
    }

    DrawCommandBuffer::~DrawCommandBuffer()
    {
        _device->waitIdle();
        _buffer.destroy( _device->getLogicalDevice() );
    }

    DrawCommandBuffer::DrawCommandBuffer( vk::Device* device )
    :   _buffer()
    ,   _device( device )
    {}

}}






namespace kege{namespace vk{

    void DrawIndexedCommandBuffer::drawIndirect( const vk::CommandBuffer* command_buffer, uint64_t offset, uint32_t draw_count )const
    {
        vkCmdDrawIndexedIndirect( command_buffer->getCurrentCommandBuffer(), _buffer.handle, offset, draw_count, _stride );
    }

    VkResult DrawIndexedCommandBuffer::construct(  const kege::DrawIndexedCommandBuffer::CreateInfo& info )
    {
        _usage = info.memory_usage;
        _stride = (uint32_t) sizeof( VkDrawIndexedIndirectCommand );
        return _buffer.construct( _device, info.memory_usage, VK_BUFFER_USAGE_INDIRECT_BUFFER_BIT, info.size, info.data );
    }

    void DrawIndexedCommandBuffer::setBufferData( uint64_t offset, uint64_t size, const void* data )
    {
        _buffer.setBufferData( _device->getLogicalDevice(), offset, size, data );
    }

    void DrawIndexedCommandBuffer::getBufferData( uint64_t offset, uint64_t size, void*& data )
    {
        _buffer.setBufferData( _device->getLogicalDevice(), offset, size, data );
    }

    uint64_t DrawIndexedCommandBuffer::sizeInBytes()const
    {
        return _buffer.size;
    }

    const void* DrawIndexedCommandBuffer::mapMemory()const
    {
        return _buffer.mapMemory( _device->getLogicalDevice() );
    }

    void DrawIndexedCommandBuffer::unmapMemory()
    {
        _buffer.unmapMemory( _device->getLogicalDevice() );
    }

    void* DrawIndexedCommandBuffer::mapMemory()
    {
        return _buffer.mapMemory( _device->getLogicalDevice() );
    }

    DrawIndexedCommandBuffer::~DrawIndexedCommandBuffer()
    {
        _device->waitIdle();
        _buffer.destroy( _device->getLogicalDevice() );
    }

    DrawIndexedCommandBuffer::DrawIndexedCommandBuffer( vk::Device* device )
    :   _buffer()
    ,   _device( device )
    {}

}}
