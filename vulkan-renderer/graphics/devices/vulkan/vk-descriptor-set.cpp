//
//  vk-descriptor-set.cpp
//  new-engine
//
//  Created by Kenneth Esdaile on 1/1/24.
//

#include "vk-core.hpp"
#include "shader-program.hpp"

namespace kege{namespace vk{

    void DescriptorSet::bind( kege::CommandBuffer* command_buffer, uint32_t first_set, kege::ShaderProgram* program )const
    {
        VkCommandBuffer vk_command_buffer = command_buffer->vulkan()->getCurrentCommandBuffer();
        const vk::PipelineLayout* pipeline_layout = program->getPipeline()->getPipelineLayout()->vulkan();
        const VkDescriptorSet descriptors[] = { _descriptor_set };
        
        vkCmdBindDescriptorSets
        (
            vk_command_buffer,
            pipeline_layout->pipelineBindPoint(),
            pipeline_layout->handle(),
            first_set, 1, descriptors,
            0, nullptr
        );
    }

    void DescriptorSet::bind( kege::CommandBuffer* command_buffer, uint32_t first_set )const
    {
        if ( _descriptor_pool == nullptr )
        {
            KEGE_ERROR("INVALID_OPERATION: Binding ShaderResource need to update before it is ready for uses.");
            throw std::runtime_error("Binding of uninitialized ShaderResource");
        }
        const std::set< vk::PipelineLayout* >* pipeline_layout_set = _descriptor_pool->allocator()->descriptorSetLayout()->pipelineLayoutSet();
        if ( pipeline_layout_set )
        {
            VkCommandBuffer current_command_buffer = command_buffer->vulkan()->getCurrentCommandBuffer();
            const VkDescriptorSet descriptors[] = { _descriptor_set };
            for (const vk::PipelineLayout* pipeline_layout : *pipeline_layout_set )
            {
                vkCmdBindDescriptorSets
                (
                    current_command_buffer,
                    pipeline_layout->pipelineBindPoint(),
                    pipeline_layout->handle(),
                    first_set, 1, descriptors,
                    0, nullptr
                );
            }
        }
    }

    const VkDescriptorSet DescriptorSet::descriptorSet()const
    {
        return _descriptor_set;
    }

    void DescriptorSet::update()
    {
        std::vector< VkWriteDescriptorSet > write_descriptor_sets( _shader_resource_binding.size() );
        std::vector< VkDescriptorBufferInfo > buffer_infos;
        std::vector< VkDescriptorImageInfo > image_infos;
        std::vector< kege::ivec2 > indices;
        enum{BUFFER_INFO, IMAGE_INFO};

        for ( int i = 0; i < _shader_resource_binding.size(); i++ )
        {
            kege::ShaderResource::Binding& binding = _shader_resource_binding[ i ];

            write_descriptor_sets[ i ] = {};
            write_descriptor_sets[ i ].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
            write_descriptor_sets[ i ].dstBinding = binding.uniform->binding;
            write_descriptor_sets[ i ].descriptorCount = binding.uniform->count;
            write_descriptor_sets[ i ].dstArrayElement = 0; // First element
            write_descriptor_sets[ i ].pTexelBufferView = nullptr;
            write_descriptor_sets[ i ].pImageInfo = nullptr;
            write_descriptor_sets[ i ].pBufferInfo = nullptr;
            write_descriptor_sets[ i ].pNext = nullptr;

            switch ( binding.descriptor_type )
            {
                case kege::DESCRIPTOR_UNIFORM_BUFFER:
                    for (int k=0; k<binding.uniform->count; k++)
                    {
                        indices.push_back({BUFFER_INFO, (int)buffer_infos.size() });
                        buffer_infos.push_back({});
                        binding.uniform->getDescriptorBufferInfo( &buffer_infos[ buffer_infos.size() - 1 ] );
                    }
                    write_descriptor_sets[ i ].descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
                    break;

                case kege::DESCRIPTOR_UNIFORM_TEXEL_BUFFER:
                    for (int k=0; k<binding.uniform->count; k++)
                    {
                        indices.push_back({BUFFER_INFO, (int)buffer_infos.size() });
                        buffer_infos.push_back({});
                        binding.uniform->getDescriptorBufferInfo( &buffer_infos[ buffer_infos.size() - 1 ] );
                    }
                    write_descriptor_sets[ i ].descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_TEXEL_BUFFER;
                    break;

                case kege::DESCRIPTOR_UNIFORM_BUFFER_DYNAMIC:
                    for (int k=0; k<binding.uniform->count; k++)
                    {
                        indices.push_back({BUFFER_INFO, (int)buffer_infos.size() });
                        buffer_infos.push_back({});
                        binding.uniform->getDescriptorBufferInfo( &buffer_infos[ buffer_infos.size() - 1 ] );
                    }
                    write_descriptor_sets[ i ].descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC;
                    break;

                case kege::DESCRIPTOR_STORAGE_BUFFER:
                    for (int k=0; k<binding.uniform->count; k++)
                    {
                        indices.push_back({BUFFER_INFO, (int)buffer_infos.size() });
                        buffer_infos.push_back({});
                        binding.uniform->getDescriptorBufferInfo( &buffer_infos[ buffer_infos.size() - 1 ] );
                    }
                    write_descriptor_sets[ i ].descriptorType = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER;
                    break;

                case kege::DESCRIPTOR_STORAGE_BUFFER_DYNAMIC:
                    for (int k=0; k<binding.uniform->count; k++)
                    {
                        indices.push_back({BUFFER_INFO, (int)buffer_infos.size() });
                        buffer_infos.push_back({});
                        binding.uniform->getDescriptorBufferInfo( &buffer_infos[ buffer_infos.size() - 1 ] );
                    }
                    write_descriptor_sets[ i ].descriptorType = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER_DYNAMIC;
                    break;

                case kege::DESCRIPTOR_STORAGE_TEXEL_BUFFER:
                    for (int k=0; k<binding.uniform->count; k++)
                    {
                        indices.push_back({BUFFER_INFO, (int)buffer_infos.size() });
                        buffer_infos.push_back({});
                        binding.uniform->getDescriptorBufferInfo( &buffer_infos[ buffer_infos.size() - 1 ] );
                    }
                    write_descriptor_sets[ i ].descriptorType = VK_DESCRIPTOR_TYPE_STORAGE_TEXEL_BUFFER;
                    break;

                case kege::DESCRIPTOR_STORAGE_IMAGE:
                    for (int k=0; k<binding.uniform->count; k++)
                    {
                        indices.push_back({IMAGE_INFO, (int)image_infos.size() });
                        image_infos.push_back({});
                        binding.uniform->getDescriptorBufferInfo( &image_infos[ image_infos.size() - 1 ] );
                    }
                    write_descriptor_sets[ i ].descriptorType = VK_DESCRIPTOR_TYPE_STORAGE_IMAGE;
                    break;

                case kege::DESCRIPTOR_COMBINED_IMAGE_SAMPLER:
                    for (int k=0; k<binding.uniform->count; k++)
                    {
                        indices.push_back({IMAGE_INFO, (int)image_infos.size() });
                        image_infos.push_back({});
                        binding.uniform->getDescriptorBufferInfo( &image_infos[ image_infos.size() - 1 ] );
                    }
                    write_descriptor_sets[ i ].descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
                    break;

                case kege::DESCRIPTOR_SAMPLED_IMAGE:
                    for (int k=0; k<binding.uniform->count; k++)
                    {
                        indices.push_back({IMAGE_INFO, (int)image_infos.size() });
                        image_infos.push_back({});
                        binding.uniform->getDescriptorBufferInfo( &image_infos[ image_infos.size() - 1 ] );
                    }
                    write_descriptor_sets[ i ].descriptorType =  VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE;
                    break;

                case kege::DESCRIPTOR_SAMPLER:
                    for (int k=0; k<binding.uniform->count; k++)
                    {
                        indices.push_back({IMAGE_INFO, (int)image_infos.size() });
                        image_infos.push_back({});
                        binding.uniform->getDescriptorBufferInfo( &image_infos[ image_infos.size() - 1 ] );
                    }
                    write_descriptor_sets[ i ].descriptorType = VK_DESCRIPTOR_TYPE_SAMPLER;
                    break;

                default: throw std::runtime_error("DescriptorWriter::integrateUniformLayout() : Unsupported UniformBinding::LayoutType.");
                    break;
            }
        }
        for ( int i = 0; i < write_descriptor_sets.size(); i++ )
        {
            switch ( indices[ i ].x )
            {
                case BUFFER_INFO: write_descriptor_sets[ i ].pBufferInfo = &buffer_infos[ indices[ i ].y ]; break;
                case IMAGE_INFO: write_descriptor_sets[ i ].pImageInfo = &image_infos[ indices[ i ].y ]; break;
                default: break;
            }
        }

        if( !write_descriptor_sets.empty() )
        {
            if ( _descriptor_set == nullptr )
            {
                vk::DescriptorSetLayoutObject descriptor_set_layout_bindings;
                for ( int i = 0; i < write_descriptor_sets.size(); i++ )
                {
                    VkDescriptorSetLayoutBinding dslb = {};
                    dslb.descriptorCount = write_descriptor_sets[ i ].descriptorCount;
                    dslb.descriptorType = write_descriptor_sets[ i ].descriptorType;
                    dslb.binding = write_descriptor_sets[ i ].dstBinding;
                    dslb.stageFlags =
                    {
                        VK_SHADER_STAGE_VERTEX_BIT |
                        VK_SHADER_STAGE_FRAGMENT_BIT |
                        VK_SHADER_STAGE_COMPUTE_BIT
                    };
                    descriptor_set_layout_bindings.names.push_back( _shader_resource_binding[ i ].uniform->name );
                    descriptor_set_layout_bindings.bindings.push_back( dslb );
                }

                vk::DescriptorSetLayout* dsl = _device->getDescriptorSetLayout( descriptor_set_layout_bindings );
                if ( !dsl )
                {
                    dsl = _device->createDescriptorSetLayout( descriptor_set_layout_bindings );
                }
                dsl->allocator()->allocate( write_descriptor_sets, *this );
            }
            else
            {
                _descriptor_pool->allocator()->update( write_descriptor_sets, *this );
            }
        }
    }

    bool DescriptorSet::valid()const
    {
        return _descriptor_set != VK_NULL_HANDLE;
    }

    DescriptorSet::~DescriptorSet()
    {
        if ( _descriptor_pool )
        {
            _descriptor_pool->release( _descriptor_set );
            _descriptor_pool = nullptr;
        }
    }

    DescriptorSet::DescriptorSet( vk::Device* device )
    :   _descriptor_pool( nullptr )
    ,   _descriptor_set( VK_NULL_HANDLE )
    ,   _device( device )
    {}

}}
