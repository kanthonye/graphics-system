//
//  vk-pipeline-layout.hpp
//  new-engine
//
//  Created by Kenneth Esdaile on 12/30/23.
//

#ifndef kege_graphics_vk_pipeline_layout_hpp
#define kege_graphics_vk_pipeline_layout_hpp

#include "../vulkan/vk.hpp"

namespace kege{namespace vk{

    class PipelineLayout : public kege::PipelineLayout
    {
    public:

        static VkResult createHandle
        (  VkDevice device
         , VkPipelineBindPoint pipeline_bind_point
         , std::vector< VkPushConstantRange >& push_constant_ranges
         , std::vector< VkDescriptorSetLayout >& descriptor_set_layout
         , vk::PipelineLayout& pipeline_layout
        );

        static VkResult create
        (  vk::Device* device
         , const kege::PipelineLayout::CreateInfo& info
         , vk::PipelineLayout& pipeline_layout
        );

        //const std::vector< VkVertexInputAttributeDescription >& vertexAttributes()const;
        //const std::vector< VkVertexInputBindingDescription >& vertexBindings()const;

        VkPipelineBindPoint pipelineBindPoint()const;

        const vk::PipelineLayout* vulkan()const;
        vk::PipelineLayout* vulkan();

        const VkPipelineLayout handle()const;
        virtual ~PipelineLayout();
        PipelineLayout();

    private:

        PipelineLayout& operator =( const kege::PipelineLayout& other ) = delete;
        PipelineLayout( const kege::PipelineLayout& other ){}

    protected:

        std::vector< VkPushConstantRange > _push_constant_ranges;

        VkPipelineBindPoint _pipeline_bind_point;
        VkPipelineLayout _handle;
        VkDevice _device;
    };
}}
#endif /* kege_graphics_vk_pipeline_layout_hpp */
