//
//  vk-descriptor-pool.cpp
//  new-engine
//
//  Created by Kenneth Esdaile on 1/1/24.
//

#include "vk-core.hpp"

namespace kege{namespace vk{

    DescriptorPool::DescriptorPool
    (
        uint32_t maxsets,
        const std::vector< VkDescriptorPoolSize >& poolsizes,
        vk::DescriptorAllocator* allocator
    )
    :   _poolsizes( poolsizes )
    ,   _allocator( allocator )
    ,   _max_sets( maxsets )
    ,   _next( nullptr )
    ,   _prev( nullptr )
    ,   _count( 0 )
    {
        VkDescriptorPoolCreateInfo info = {};
        info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
        info.flags = VK_DESCRIPTOR_POOL_CREATE_FREE_DESCRIPTOR_SET_BIT;
        info.poolSizeCount = static_cast< uint32_t>( poolsizes.size() );
        info.pPoolSizes = poolsizes.data();
        info.maxSets = maxsets;

        VkResult result = vkCreateDescriptorPool( allocator->device()->getLogicalDevice(), &info, nullptr, &_handle);
        if ( result != VK_SUCCESS )
        {
            //KEGE_ERROR( "%s: Failed to create descriptor pool", vk::getError( result ) );
            return;
        }
    }

    VkResult DescriptorPool::allocate
    (
        const vk::DescriptorSetLayout* descriptor_set_layout,
        vk::DescriptorSet& descriptor
    )
    {
        VkDescriptorSetAllocateInfo alloc_info{};
        alloc_info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
        alloc_info.pSetLayouts = &descriptor_set_layout->handle();
        alloc_info.descriptorPool = _handle;
        alloc_info.descriptorSetCount = 1;
        VkResult result = vkAllocateDescriptorSets( _allocator->device()->getLogicalDevice(), &alloc_info, &descriptor._descriptor_set );
        if ( result != VK_SUCCESS )
        {
            //KEGE_ERROR( vk::getError( result ) );
            return result;
        }
        _count++;
        return result;
    }

    const vk::DescriptorAllocator* DescriptorPool::allocator()const
    {
        return _allocator;
    }

    vk::DescriptorAllocator* DescriptorPool::allocator()
    {
        return _allocator;
    }

    void DescriptorPool::release( VkDescriptorSet& descriptor )
    {
        if ( descriptor != VK_NULL_HANDLE )
        {
            _allocator->device()->waitIdle();
            vkFreeDescriptorSets( _allocator->device()->getLogicalDevice(), _handle, 1, &descriptor );
            descriptor = VK_NULL_HANDLE;
            _count--;
        }

        /**
         * if ( !this->_prev ) then this descriptor-pool is not in the available
         * descriptor list. In this case we need to append it to the back of the list.
         */
        if ( !this->_prev && _allocator->_tail != this )
        {
            if ( _allocator->_tail == nullptr )
            {
                _allocator->_tail = _allocator->_head = this;
            }
            else
            {
                _allocator->_tail->_next = this;
                this->_prev = _allocator->_tail;
                _allocator->_tail = this;
            }
        }
    }

    DescriptorPool::~DescriptorPool()
    {
        if ( _handle != VK_NULL_HANDLE )
        {
            vkDestroyDescriptorPool( _allocator->device()->getLogicalDevice(), _handle, nullptr );
            _handle = VK_NULL_HANDLE;
        }
        _poolsizes.clear();
    }

}}
