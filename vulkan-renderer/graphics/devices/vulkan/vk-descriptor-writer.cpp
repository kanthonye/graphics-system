//
//  vk-descriptor-writer.cpp
//  new-engine
//
//  Created by Kenneth Esdaile on 1/1/24.
//

#include "vk-core.hpp"

//namespace kege{namespace vk{
//
//    const std::vector< VkWriteDescriptorSet >& DescriptorWriter::getWriteDescriptorSets()const
//    {
//        return _write_descriptor_sets;
//    }
//
//    std::vector< VkWriteDescriptorSet >& DescriptorWriter::getWriteDescriptorSets()
//    {
//        return _write_descriptor_sets;
//    }
//
//    void DescriptorWriter::writeDescriptorSetBuffer
//    (
//        const kege::UniformBinding* binding
//    )
//    {
////        VkWriteDescriptorSet* write = newDescriptorWriteSet();
////        VkDescriptorBufferInfo* info = newDescriptorBufferInfo( binding->getCount() );
////
////        switch ( binding->getDescriptorType() )
////        {
////            case kege::DESCRIPTOR_UNIFORM_BUFFER: write->descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER; 
////                break;
////            case kege::DESCRIPTOR_STORAGE_BUFFER: write->descriptorType = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER;
////                break;
////            case kege::DESCRIPTOR_UNIFORM_BUFFER_DYNAMIC: write->descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC;
////                break;
////            case kege::DESCRIPTOR_STORAGE_BUFFER_DYNAMIC: write->descriptorType = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER_DYNAMIC;
////                break;
////            case kege::DESCRIPTOR_STORAGE_TEXEL_BUFFER: write->descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_TEXEL_BUFFER;
////                break;
////            case kege::DESCRIPTOR_UNIFORM_TEXEL_BUFFER: write->descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_TEXEL_BUFFER;
////                break;
////            default: break;
////        }
////
////        std::cout <<"\n";
////        for ( int i = 0; i < binding->getCount(); i++ )
////        {
////            const vk::Buffer* buffer = binding->getBuffer( i )->vulkan();
////
////            info[i] = {};
////            info[i].buffer = buffer->handle();
////            info[i].range  = buffer->sizeInBytes();
////            info[i].offset = 0;
////            //std::cout << binding->name() <<" -> " <<info[i].buffer <<": [range: " <<info[i].range  <<"] : [offset: " <<info[i].offset;
////        }
////
////        write->pImageInfo = nullptr; // Optional
////        write->pTexelBufferView = nullptr; // Optional
////        write->dstBinding = binding->binding();
////        write->descriptorCount = binding->getCount(); // Number of descriptors to update
////        write->dstArrayElement = 0; // Start from element 0
////        write->pBufferInfo = info;
////
////        std::cout <<"] : [descriptorCount: " <<write->descriptorCount <<"] : [pBufferInfo: " <<write->pBufferInfo <<"]\n";
//    }
//
//    void DescriptorWriter::writeDescriptorSetImage
//    (
//        const kege::UniformBinding* binding
//    )
//    {
//        VkWriteDescriptorSet* write = newDescriptorWriteSet();
//        VkDescriptorImageInfo* info = newDescriptorImageInfo( binding->getCount() );
//
//        for ( int i = 0; i < binding->getCount(); i++ )
//        {
//            const vk::Image* image = binding->getImage( i )->vulkan();
//            info[i] = {};
//
//            switch ( binding->getDescriptorType() )
//            {
//                case kege::DESCRIPTOR_STORAGE_IMAGE: 
//                    write->descriptorType = VK_DESCRIPTOR_TYPE_STORAGE_IMAGE;
//                    info[i].imageLayout = VK_IMAGE_LAYOUT_GENERAL;
//                    info[i].imageView = image->view();
//                    break;
//
//                case kege::DESCRIPTOR_COMBINED_IMAGE_SAMPLER:
//                    write->descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
//                    info[i].imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
//                    info[i].sampler = binding->getSampler()->vulkan()->handle();
//                    info[i].imageView = image->view();
//                    break;
//
//                case kege::DESCRIPTOR_SAMPLED_IMAGE:
//                    write->descriptorType = VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE;
//                    info[i].imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
//                    info[i].sampler = binding->getSampler()->vulkan()->handle();
//                    info[i].imageView = image->view();
//                    break;
//
//                case kege::DESCRIPTOR_SAMPLER:
//                    write->descriptorType = VK_DESCRIPTOR_TYPE_SAMPLER;
//                    info[i].sampler = binding->getSampler()->vulkan()->handle();
//                    break;
//                default: break;
//            }
//        }
//
//        write->pBufferInfo = nullptr; // Optional
//        write->pTexelBufferView = nullptr; // Optional
//        write->dstBinding = binding->binding();
//        write->descriptorCount = binding->getCount(); // Number of descriptors to update
//        write->dstArrayElement = 0; // Start from element 0
//        write->pImageInfo = info;
//    }
//
//    void DescriptorWriter::integrateUniformLayout( const kege::UniformLayout *layout )
//    {
//        for (int i = 0; i < layout->get().size(); i++ )
//        {
//            const kege::UniformBinding* binding = layout->get()[ i ].ref();
//            switch ( binding->getDescriptorType() )
//            {
//                case kege::DESCRIPTOR_UNIFORM_BUFFER:
//                case kege::DESCRIPTOR_STORAGE_BUFFER:
//                case kege::DESCRIPTOR_UNIFORM_BUFFER_DYNAMIC:
//                case kege::DESCRIPTOR_STORAGE_BUFFER_DYNAMIC:
//                case kege::DESCRIPTOR_STORAGE_TEXEL_BUFFER:
//                case kege::DESCRIPTOR_UNIFORM_TEXEL_BUFFER:
//                    writeDescriptorSetBuffer ( binding );
//                    break;
//
//                case kege::DESCRIPTOR_SAMPLER:
//                case kege::DESCRIPTOR_STORAGE_IMAGE:
//                case kege::DESCRIPTOR_COMBINED_IMAGE_SAMPLER:
//                case kege::DESCRIPTOR_SAMPLED_IMAGE:
//                    writeDescriptorSetImage ( binding );
//                    break;
//
//                default: throw std::runtime_error("DescriptorWriter::integrateUniformLayout() : Unsupported UniformBinding::LayoutType.");
//                    break;
//            }
//        }
//    }
//
//    VkDescriptorBufferInfo* DescriptorWriter::newDescriptorBufferInfo( uint32_t n )
//    {
//        VkDescriptorBufferInfo* info = &_descriptor_buffer_infos[ _buffer_info_count + n ];
//        _buffer_info_count += n;
//        return info;
//    }
//
//    VkDescriptorImageInfo* DescriptorWriter::newDescriptorImageInfo( uint32_t n )
//    {
//        VkDescriptorImageInfo* info = &_descriptor_image_infos[ _image_info_count + n ];
//        _image_info_count += n;
//        return info;
//    }
//
//    VkWriteDescriptorSet* DescriptorWriter::newDescriptorWriteSet()
//    {
//        _write_descriptor_sets.push_back({});
//        _write_descriptor_sets[ _write_descriptor_sets.size() - 1 ].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
//        return &_write_descriptor_sets[ _write_descriptor_sets.size() - 1 ];
//    }
//
//    DescriptorWriter::DescriptorWriter( const kege::UniformLayout* layout )
//    :   _buffer_info_count( 0 )
//    ,   _image_info_count( 0 )
//    {
//        integrateUniformLayout( layout );
//    }
//
//    DescriptorWriter::operator bool()const
//    {
//        return !_write_descriptor_sets.empty();
//    }
//
//}}
