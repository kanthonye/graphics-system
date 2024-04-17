//
//  vk-descriptor-set-layout.cpp
//  new-engine
//
//  Created by Kenneth Esdaile on 1/1/24.
//

#include "vk-core.hpp"

namespace kege{namespace vk{

    VkResult DescriptorSetLayout::create
    (  const vk::DescriptorSetLayoutObject& descriptor_set_layout_bindings
    ,  std::set< vk::PipelineLayout* >* pipeline_layout_set
    )
    {
        VkDescriptorSetLayoutCreateInfo info = {};
        info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
        info.bindingCount = static_cast< uint32_t>( descriptor_set_layout_bindings.bindings.size() ); // Number of bindings in the layout
        info.pBindings = descriptor_set_layout_bindings.bindings.data(); // Pointer to array of bindings

        VkResult result = vkCreateDescriptorSetLayout( _device->getLogicalDevice(), &info, nullptr, &_handle );
        if( result == VK_SUCCESS )
        {
            _allocator.init( _device, this );
        }
        _bindings.bindings = std::move( descriptor_set_layout_bindings.bindings );
        _bindings.names = std::move( descriptor_set_layout_bindings.names );
        _pipeline_layouts = pipeline_layout_set;
        return result;
    }

    const vk::DescriptorSetLayoutObject& DescriptorSetLayout::bindings()const
    {
        return _bindings;
    }

    const std::set< vk::PipelineLayout* >* DescriptorSetLayout::pipelineLayoutSet()const
    {
        return _pipeline_layouts;
    }

    std::set< vk::PipelineLayout* >* DescriptorSetLayout::pipelineLayoutSet()
    {
        return _pipeline_layouts;
    }

    const VkDescriptorSetLayout& DescriptorSetLayout::handle()const
    {
        return _handle;
    }

    vk::DescriptorAllocator* DescriptorSetLayout::allocator()
    {
        return &_allocator;
    }

    vk::Device* DescriptorSetLayout::device()
    {
        return _device;
    }
    DescriptorSetLayout::~DescriptorSetLayout()
    {
        _allocator.purge();
        if ( _handle != VK_NULL_HANDLE )
        {
            vkDestroyDescriptorSetLayout( _device->getLogicalDevice(), _handle, nullptr );
            _handle = VK_NULL_HANDLE;
        }
        _bindings.bindings.clear();
        _bindings.names.clear();
    }

    DescriptorSetLayout::DescriptorSetLayout( vk::Device* device )
    :   _device( device )
    ,   _pipeline_layouts( nullptr )
    ,   _handle( VK_NULL_HANDLE )
    ,   _bindings()
    {
    }

}}
