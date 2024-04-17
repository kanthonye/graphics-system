//
//  vk-descriptor-allocator.cpp
//  new-engine
//
//  Created by Kenneth Esdaile on 1/1/24.
//


#include "vk-core.hpp"

namespace kege{namespace vk{

    void DescriptorAllocator::update
    (
        std::vector< VkWriteDescriptorSet >& writes,
        vk::DescriptorSet& descriptor
    )
    {
        for (auto& write :  writes ) write.dstSet = descriptor._descriptor_set;
        vkUpdateDescriptorSets( _device->getLogicalDevice(), (uint32_t) writes.size(), writes.data(), 0, nullptr );
    }

    bool DescriptorAllocator::allocate
    (
        std::vector< VkWriteDescriptorSet >& writes
     ,  vk::DescriptorSet& descriptor
    )
    {
        if( _head )
        {
            /**
             * if( _current_pool->_count < _current_pool->_max_sets ) then their are available descriptor-set
             * that can be allocated.
             */
            if( _head->_count < _head->_max_sets )
            {
                descriptor._descriptor_pool = _head;
                _head->allocate( _descriptor_set_layout, descriptor );
                update( writes, descriptor );

                //std::cout <<"DescriptorSetLayout: " <<this <<" | " << _descriptor_set_layout->bindings()->bindings()[0]._name <<" : " << descriptor;
                //std::cout  <<" | pool: "<<_tail <<" | "<<"pool_size: " << _head->_max_sets << " | count: "<< _head->_count <<"\n";

                /**
                 * if( current-pool->count >= current-pool->max-sets ) then the descriptor-pool ran out
                 * of avaiblable descriptor-set to allocate. in this case get the next descriptor-pool
                 * in the list
                 */
                if( _head->_count >= _head->_max_sets )
                {
                    _head = _head->_next;
                    if( _head )
                    {
                        _head->_prev = nullptr;
                    }
                    /**
                     * else if the head of the list _curr is null then the list is empty, so the tail should  be null also.
                     */
                    else
                    {
                        _tail = nullptr;
                    }
                }
                return true;
            }
        }

        /**
         * if no descriptor-pool with available descriptor-set, we need to allocate a new descriptor-pool
         */
        uint32_t maxsets = pow( 8, _poolsize );
        _poolsize = kege::min( _poolsize + 1, 5 );

        std::vector< VkDescriptorPoolSize > poolsizes;
        for ( auto& binding : _descriptor_set_layout->bindings().bindings )
        {
            poolsizes.push_back({ binding.descriptorType, binding.descriptorCount * maxsets });
        }

        _tail = _head = new vk::DescriptorPool( maxsets, poolsizes, this );
        _descriptor_pools.push_back( _head );
        return allocate( writes, descriptor );
    }


    void DescriptorAllocator::init( vk::Device* device, vk::DescriptorSetLayout* descriptor_set_layout )
    {
        _descriptor_set_layout = descriptor_set_layout;
        _device = device;
        _poolsize = 0;
    }

    const vk::DescriptorSetLayout* DescriptorAllocator::descriptorSetLayout()const
    {
        return _descriptor_set_layout;
    }

    vk::Device* DescriptorAllocator::device()
    {
        return _device;
    }

    void DescriptorAllocator::purge()
    {
        _descriptor_pools.clear();
    }

    DescriptorAllocator::DescriptorAllocator()
    :   _descriptor_set_layout( nullptr )
    ,   _head( nullptr )
    ,   _tail( nullptr )
    ,   _poolsize( 0 )
    ,   _device( nullptr )
    {
    }

    DescriptorAllocator::~DescriptorAllocator()
    {
        purge();
    }
}}
