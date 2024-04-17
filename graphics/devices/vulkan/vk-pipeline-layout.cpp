//
//  vk-pipeline-layout.cpp
//  new-engine
//
//  Created by Kenneth Esdaile on 12/30/23.
//

#include "vk-core.hpp"


namespace kege{namespace vk{


    VkResult PipelineLayout::create
    (  vk::Device* device
     , const kege::PipelineLayout::CreateInfo& info
     , vk::PipelineLayout& pipeline_layout
    )
    {
        // Select the pipeline-bind-point for that the piepline-layout will bind to. This is necessary for binding shader resource
        VkPipelineBindPoint pipeline_bind_point = VK_PIPELINE_BIND_POINT_MAX_ENUM;
        if ( info.pipeline_layout_type == kege::GRAPHICS_PIPELINE_BIND_POINT )
        {
            pipeline_bind_point = VK_PIPELINE_BIND_POINT_GRAPHICS;
        }
        else if ( info.pipeline_layout_type == kege::COMPUTE_PIPELINE_BIND_POINT )
        {
            pipeline_bind_point = VK_PIPELINE_BIND_POINT_COMPUTE;
        }

        // Organise the push constansts for the current shader
        std::vector< VkPushConstantRange > push_constant_ranges;
        for (const kege::PushConstantRange& constant : info.constansts )
        {
            VkPushConstantRange push_constant = {};
            push_constant.size = constant.size;
            push_constant.offset = constant.offset;
            push_constant.stageFlags = 0;

            if ( (constant.stages & kege::VERTEX_SHADER) == kege::VERTEX_SHADER )
                push_constant.stageFlags |= VK_SHADER_STAGE_VERTEX_BIT;

            if ( (constant.stages & kege::FRAGMENT_SHADER) == kege::FRAGMENT_SHADER )
                push_constant.stageFlags |= VK_SHADER_STAGE_FRAGMENT_BIT;

            if ( (constant.stages & kege::COMPUTE_SHADER) == kege::COMPUTE_SHADER )
                push_constant.stageFlags |= VK_SHADER_STAGE_COMPUTE_BIT;

            if ( (constant.stages & kege::TESS_CONTROL_SHADER) == kege::TESS_CONTROL_SHADER )
                push_constant.stageFlags |= VK_SHADER_STAGE_TESSELLATION_CONTROL_BIT;

            if ( (constant.stages & kege::TESS_EVALUATION_SHADER) == kege::TESS_EVALUATION_SHADER )
                push_constant.stageFlags |= VK_SHADER_STAGE_TESSELLATION_EVALUATION_BIT;

            if ( (constant.stages & kege::GEOMETRY_SHADER) == kege::GEOMETRY_SHADER )
                push_constant.stageFlags |= VK_SHADER_STAGE_GEOMETRY_BIT;

            push_constant_ranges.push_back( push_constant );
        }

        // Organise the descriptor-set-layout-bindings in an increasing ordered fashion
        typedef std::map< uint32_t, vk::DescriptorSetLayoutObject > DescriptorBindingsMap;
        DescriptorBindingsMap descriptor_bindings_map;
        for (int i = 0; i < info.bindings.size(); i++ )
        {
            VkDescriptorSetLayoutBinding descriptor_set_layout_binding = {};
            descriptor_set_layout_binding.descriptorType = toVkDescriptorType( info.bindings[ i ].descriptor_type );
            descriptor_set_layout_binding.descriptorCount = info.bindings[ i ].count;
            descriptor_set_layout_binding.binding = info.bindings[ i ].binding;
            descriptor_set_layout_binding.stageFlags =
            {
                VK_SHADER_STAGE_VERTEX_BIT |
                VK_SHADER_STAGE_FRAGMENT_BIT |
                VK_SHADER_STAGE_COMPUTE_BIT
            };
            descriptor_bindings_map[ info.bindings[ i ].set ].bindings.push_back( descriptor_set_layout_binding );
            descriptor_bindings_map[ info.bindings[ i ].set ].names.push_back( info.binding_names[ i ] );
        }

        /*
          Using the descriptor-set-layout-bindings to create the descriptor-set-layouts,
          or retrieve once that matches the vector of VkDescriptorSetLayoutBindings
         */
        std::vector< vk::DescriptorSetLayout* > descriptor_set_layouts;
        std::vector< VkDescriptorSetLayout > descriptor_handles;
        for ( DescriptorBindingsMap::iterator itr = descriptor_bindings_map.begin(); itr != descriptor_bindings_map.end(); itr++ )
        {
            vk::DescriptorSetLayoutObject& descriptor = itr->second;
            vk::DescriptorSetLayout* descriptor_set_layout = device->getDescriptorSetLayout( descriptor );

            if ( descriptor_set_layout == nullptr )
            {
                descriptor_set_layout = device->createDescriptorSetLayout( descriptor );
            }

            descriptor_set_layouts.push_back( descriptor_set_layout );
            descriptor_handles.push_back( descriptor_set_layout->handle() );
        }

        VkResult result;
        VkPipelineLayoutCreateInfo create_info{};
        create_info.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
        create_info.setLayoutCount = static_cast< uint32_t >( descriptor_handles.size() );
        create_info.pSetLayouts = descriptor_handles.data();
        create_info.pushConstantRangeCount = 0;
        if ( !push_constant_ranges.empty() )
        {
            create_info.pPushConstantRanges = push_constant_ranges.data();
            create_info.pushConstantRangeCount = static_cast< uint32_t >( push_constant_ranges.size() );
        }

        pipeline_layout._device = device->getLogicalDevice();
        pipeline_layout._pipeline_bind_point = pipeline_bind_point;
        result = vkCreatePipelineLayout( device->getLogicalDevice(), &create_info, nullptr, &pipeline_layout._handle );
        if( result != VK_SUCCESS )
        {
            return result;
        }

        /*
         For every new pipeline-layout that match a descriptor-set-layout we will add the pipeline to the
         descriptors pipeline set. This is necessary for globally binding of a shader resources with out
         the presence of a shader-program. Basically what we are going to do is bind the resource to the
         pipeline-layout prior to binding the shader-program, so that when the shader-program is used the
         resource is already ready available. Local binding of shader resource will happen along-side with
         the shader-programs
         */
        for ( vk::DescriptorSetLayout* descriptor_set_layout : descriptor_set_layouts )
        {
            if( descriptor_set_layout )
            {
                descriptor_set_layout->pipelineLayoutSet()->insert( &pipeline_layout );
            }
        }

        return result;
    }
    
    VkPipelineBindPoint PipelineLayout::pipelineBindPoint()const
    {
        return _pipeline_bind_point;
    }

    const vk::PipelineLayout* PipelineLayout::vulkan()const
    {
        return this;
    }
    vk::PipelineLayout* PipelineLayout::vulkan()
    {
        return this;
    }

    const VkPipelineLayout PipelineLayout::handle()const
    {
        return _handle;
    }

    PipelineLayout:: ~PipelineLayout()
    {
        if ( _handle != VK_NULL_HANDLE )
        {
            vkDestroyPipelineLayout( _device, _handle, nullptr );
            _handle = VK_NULL_HANDLE;
        }
    }

    PipelineLayout::PipelineLayout()
    :   _handle( VK_NULL_HANDLE )
    ,   _pipeline_bind_point()
    ,   _device( VK_NULL_HANDLE )
    {}


    VkResult PipelineLayout::createHandle
    (   VkDevice device
     ,  VkPipelineBindPoint pipeline_bind_point
     ,  std::vector< VkPushConstantRange >& push_constant_ranges
     ,  std::vector< VkDescriptorSetLayout >& descriptor_set_layout
     ,  vk::PipelineLayout& pipeline_layout
    )
    {
        VkPipelineLayoutCreateInfo create_info{};
        create_info.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
        create_info.setLayoutCount = static_cast< uint32_t >( descriptor_set_layout.size() );
        create_info.pSetLayouts = descriptor_set_layout.data();
        create_info.pushConstantRangeCount = 0;
        if ( !push_constant_ranges.empty() )
        {
            create_info.pPushConstantRanges = push_constant_ranges.data();
            create_info.pushConstantRangeCount = static_cast< uint32_t >( push_constant_ranges.size() );
        }

        pipeline_layout._device = device;
        pipeline_layout._pipeline_bind_point = pipeline_bind_point;
        return vkCreatePipelineLayout( device, &create_info, nullptr, &pipeline_layout._handle );
    }

}}
