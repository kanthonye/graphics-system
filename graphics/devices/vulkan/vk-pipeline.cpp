//
//  vk-pipeline.cpp
//  new-engine
//
//  Created by Kenneth Esdaile on 12/30/23.
//

#include "vk-core.hpp"

namespace kege{ namespace vk{

    void initPipelineRasterizationStateCreateInfo
    (   const kege::Pipeline::CreateInfo& info
     ,  VkPipelineRasterizationStateCreateInfo& rasterization
     ,  VkGraphicsPipelineCreateInfo& create_info
    )
    {
        rasterization.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
        rasterization.depthClampEnable = VK_FALSE;
        rasterization.rasterizerDiscardEnable = VK_FALSE;
        rasterization.lineWidth = 1.0f;
        rasterization.depthBiasEnable = VK_FALSE;
        switch ( info.polygon_mode )
        {
            default:
            case kege::FILL: rasterization.polygonMode = VK_POLYGON_MODE_FILL; break;
            case kege::LINE: rasterization.polygonMode = VK_POLYGON_MODE_LINE; break;
            case kege::POINT: rasterization.polygonMode = VK_POLYGON_MODE_POINT; break;
        }
        if ( info.cull_mode == kege::CullMode::CULL_CW )
        {
            rasterization.cullMode = VK_CULL_MODE_BACK_BIT;
            rasterization.frontFace = VK_FRONT_FACE_CLOCKWISE;
        }
        else if ( info.cull_mode == kege::CullMode::CULL_CCW )
        {
            rasterization.cullMode = VK_CULL_MODE_BACK_BIT;
            rasterization.frontFace = VK_FRONT_FACE_COUNTER_CLOCKWISE;
        }
        else if ( info.cull_mode == kege::CullMode::CULL_NONE )
        {
            rasterization.cullMode = VK_CULL_MODE_NONE;
            rasterization.frontFace = VK_FRONT_FACE_CLOCKWISE;
        }

        create_info.pRasterizationState = &rasterization;
    }

    void initPipelineShaderStageCreateInfo
    (   const kege::Pipeline::CreateInfo& info
     ,  std::vector< VkPipelineShaderStageCreateInfo >& stages
     ,  VkGraphicsPipelineCreateInfo& create_info
    )
    {
        for (const kege::Ref< kege::Shader >& m : info.shaders )
        {
            VkPipelineShaderStageCreateInfo stage{};
            stage.sType  = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
            stage.module = m->vulkan()->handle();
            stage.stage  = m->vulkan()->stage();
            stage.pName  = "main";
            stages.push_back( stage );
        }
        create_info.stageCount = (uint32_t) stages.size();
        create_info.pStages = stages.data();
    }

    void initPipelineVertexInputStateCreateInfo
    (   const kege::Pipeline::CreateInfo& info
     ,  std::vector< VkVertexInputAttributeDescription >& vertex_attributes
     ,  std::vector< VkVertexInputBindingDescription >& vertex_bindings
     ,  VkPipelineVertexInputStateCreateInfo& input_state
     ,  VkGraphicsPipelineCreateInfo& create_info
    )
    {
        for (const kege::VertexInputBindingDescription& r : info.bindings )
        {
            vertex_bindings.push_back
            ({
                r.binding, r.stride,
                ((r.input_rate == kege::VERTEX_INPUT_PER_VERTEX)
                 ? VK_VERTEX_INPUT_RATE_VERTEX : VK_VERTEX_INPUT_RATE_INSTANCE)
            });
        }

        for (const kege::VertexInputAttributeDescription& r : info.attributes )
        {
            vertex_attributes.push_back
            ({
                r.location,
                r.binding,
                vk::getFormat( r.format ),
                r.offset
            });
        }
        input_state.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
        input_state.pVertexBindingDescriptions = vertex_bindings.data();
        input_state.pVertexAttributeDescriptions = vertex_attributes.data();
        input_state.vertexBindingDescriptionCount = static_cast< uint32_t >( vertex_bindings.size() );
        input_state.vertexAttributeDescriptionCount = static_cast< uint32_t >( vertex_attributes.size() );

        create_info.pVertexInputState = &input_state;
    }

    void initPipelineColorBlendStateCreateInfo
    (   VkPipelineColorBlendAttachmentState& color_blend_attachment
     ,  VkPipelineColorBlendStateCreateInfo& blend_state
     ,  VkGraphicsPipelineCreateInfo& create_info
    )
    {
        color_blend_attachment.blendEnable = VK_TRUE;
        color_blend_attachment.colorBlendOp = VK_BLEND_OP_ADD;
        color_blend_attachment.srcColorBlendFactor = VK_BLEND_FACTOR_SRC_ALPHA;
        color_blend_attachment.dstColorBlendFactor = VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA;
        color_blend_attachment.alphaBlendOp = VK_BLEND_OP_ADD;
        color_blend_attachment.srcAlphaBlendFactor = VK_BLEND_FACTOR_SRC_ALPHA;
        color_blend_attachment.dstAlphaBlendFactor = VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA;
        color_blend_attachment.colorWriteMask =
        {
            VK_COLOR_COMPONENT_R_BIT |
            VK_COLOR_COMPONENT_G_BIT |
            VK_COLOR_COMPONENT_B_BIT |
            VK_COLOR_COMPONENT_A_BIT
        };

        blend_state.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
        blend_state.logicOpEnable = VK_FALSE;
        blend_state.logicOp = VK_LOGIC_OP_COPY;
        blend_state.attachmentCount = 1;
        blend_state.pAttachments = &color_blend_attachment;
        blend_state.blendConstants[0] = 0.0f;
        blend_state.blendConstants[1] = 0.0f;
        blend_state.blendConstants[2] = 0.0f;
        blend_state.blendConstants[3] = 0.0f;

        create_info.pColorBlendState = &blend_state;
    }

    void initPipelineDepthStencilStateCreateInfo
    (   VkPipelineDepthStencilStateCreateInfo& depth_stencil
     ,  VkGraphicsPipelineCreateInfo& create_info )
    {
        depth_stencil.sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO;
        depth_stencil.depthTestEnable = VK_TRUE;
        depth_stencil.depthWriteEnable = VK_TRUE;
        depth_stencil.depthCompareOp = VK_COMPARE_OP_LESS_OR_EQUAL;
        depth_stencil.depthBoundsTestEnable = VK_FALSE;
        depth_stencil.minDepthBounds = 0.0f; // Optional
        depth_stencil.maxDepthBounds = 1.0f; // Optional
        depth_stencil.stencilTestEnable = VK_FALSE;
        depth_stencil.front = {}; // Optional
        depth_stencil.back = {}; // Optional

        create_info.pDepthStencilState = &depth_stencil;
    }

    void initPipelineDynamicStateCreateInfo
    (   VkPipelineDynamicStateCreateInfo& dynamic_state
     ,  std::vector< VkDynamicState >& dynamic_states
     ,  VkGraphicsPipelineCreateInfo& create_info )
    {
        dynamic_states = std::vector< VkDynamicState >
        {
            VK_DYNAMIC_STATE_VIEWPORT,
            VK_DYNAMIC_STATE_SCISSOR,
            VK_DYNAMIC_STATE_LINE_WIDTH
        };

        dynamic_state.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
        dynamic_state.dynamicStateCount = static_cast< uint32_t >( dynamic_states.size() );
        dynamic_state.pDynamicStates = dynamic_states.data();

        create_info.pDynamicState = &dynamic_state;
    }

    void setupPipelineMultisampleStateCreateInfo
    (   VkPipelineMultisampleStateCreateInfo& multisampling
     ,  VkGraphicsPipelineCreateInfo& create_info
    )
    {
        multisampling.sType = {VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO};
        multisampling.sampleShadingEnable = VK_FALSE;
        multisampling.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;
        multisampling.minSampleShading = 1.0f;
        multisampling.pSampleMask = 0;
        multisampling.alphaToCoverageEnable = VK_FALSE;
        multisampling.alphaToOneEnable = VK_FALSE;
        multisampling.flags = 0;

        create_info.pMultisampleState = &multisampling;
    }

    void setupPipelineInputAssemblyStateCreateInfo
    (   const kege::Pipeline::CreateInfo& info
     ,  VkPipelineInputAssemblyStateCreateInfo& input_assembly
     ,  VkGraphicsPipelineCreateInfo& create_info   )
    {
        input_assembly.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
        input_assembly.topology = getPrimitiveTopology( info.primitive_topology );
        input_assembly.primitiveRestartEnable = VK_FALSE;
        create_info.pInputAssemblyState = &input_assembly;
    }

    void setupPipelineViewportStateCreateInfo
    (   VkPipelineViewportStateCreateInfo& viewport_state
     ,  VkGraphicsPipelineCreateInfo& create_info   )
    {
        viewport_state.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
        viewport_state.viewportCount = 1;
        viewport_state.scissorCount = 1;
        create_info.pViewportState = &viewport_state;
    }

    VkResult Pipeline::createGraphicsPipeline( vk::Device* device, const kege::Pipeline::CreateInfo& info, vk::Pipeline& pipeline )
    {
        VkGraphicsPipelineCreateInfo create_info{};
        create_info.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
        create_info.subpass = 0;
        create_info.basePipelineHandle = VK_NULL_HANDLE;
        create_info.layout = info.pipeline_layout->vulkan()->handle();
        if ( !info.renderpass )
        {
            create_info.renderPass = device->getRenderContext().getFramebuffer()->renderpass()->vulkan()->handle();
        }
        else create_info.renderPass = info.renderpass->vulkan()->handle();

        std::vector< VkPipelineShaderStageCreateInfo > shader_stage_create_infos;
        initPipelineShaderStageCreateInfo( info, shader_stage_create_infos, create_info );

        VkPipelineVertexInputStateCreateInfo vertex_input_info = {};
        std::vector< VkVertexInputBindingDescription > vertex_bindings;
        std::vector< VkVertexInputAttributeDescription > vertex_attributes;
        initPipelineVertexInputStateCreateInfo( info, vertex_attributes, vertex_bindings, vertex_input_info, create_info );

        VkPipelineRasterizationStateCreateInfo rasterizer{};
        initPipelineRasterizationStateCreateInfo( info, rasterizer, create_info );

        VkPipelineColorBlendStateCreateInfo color_blending{};
        VkPipelineColorBlendAttachmentState color_blend_attachment{};
        initPipelineColorBlendStateCreateInfo( color_blend_attachment, color_blending, create_info );

        VkPipelineDepthStencilStateCreateInfo depth_stencil{};
        initPipelineDepthStencilStateCreateInfo( depth_stencil, create_info );

        std::vector< VkDynamicState > dynamic_states;
        VkPipelineDynamicStateCreateInfo dynamic_state{};
        initPipelineDynamicStateCreateInfo( dynamic_state, dynamic_states, create_info );

        VkPipelineInputAssemblyStateCreateInfo input_assembly{};
        setupPipelineInputAssemblyStateCreateInfo( info, input_assembly, create_info );

        VkPipelineViewportStateCreateInfo viewport_state{};
        setupPipelineViewportStateCreateInfo( viewport_state, create_info );

        VkPipelineMultisampleStateCreateInfo multisampling = {};
        setupPipelineMultisampleStateCreateInfo( multisampling, create_info );

        // CREATE THE VULKAN GRAPHICS PIPELINE
        VkResult result = vkCreateGraphicsPipelines( device->getLogicalDevice(), VK_NULL_HANDLE, 1, &create_info, nullptr, &pipeline._handle );
        if ( result != VK_SUCCESS )
        {
            return VK_ERROR_INITIALIZATION_FAILED;
        }
        pipeline._pipeline_layout = info.pipeline_layout;
        pipeline._renderpass = info.renderpass;
        pipeline._deivce = device;
        return VK_SUCCESS;
    }

    VkResult Pipeline::createComputePipeline( vk::Device* device, const kege::Pipeline::CreateInfo& info, vk::Pipeline& pipeline )
    {
        VkPipelineShaderStageCreateInfo compute_shader_stage_info{};
        compute_shader_stage_info.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
        compute_shader_stage_info.stage = VK_SHADER_STAGE_COMPUTE_BIT;
        compute_shader_stage_info.module = info.shaders[0]->vulkan()->handle();
        compute_shader_stage_info.pName = "main";

        VkComputePipelineCreateInfo create_info{};
        create_info.sType = VK_STRUCTURE_TYPE_COMPUTE_PIPELINE_CREATE_INFO;
        create_info.layout = info.pipeline_layout->vulkan()->handle();
        create_info.stage = compute_shader_stage_info;

        VkResult result = vkCreateComputePipelines
        (  device->getLogicalDevice()
         , VK_NULL_HANDLE
         , 1, &create_info
         , nullptr
         , &pipeline._handle
        );

        if ( result != VK_SUCCESS )
        {
            return VK_ERROR_INITIALIZATION_FAILED;
        }
        pipeline._pipeline_layout = info.pipeline_layout;
        pipeline._renderpass = info.renderpass;
        pipeline._deivce = device;
        return VK_SUCCESS;
    }

    const kege::Renderpass* Pipeline::renderpass()const
    {
        return _renderpass;
    }

    const vk::Pipeline* Pipeline::vulkan()const
    {
        return this;
    }
    vk::Pipeline* Pipeline::vulkan()
    {
        return this;
    }

    const VkPipeline Pipeline::handle()const
    {
        return _handle;
    }

    Pipeline:: ~Pipeline()
    {
        if ( _handle != VK_NULL_HANDLE )
        {
            vkDestroyPipeline( _deivce->getLogicalDevice(), _handle, VK_NULL_HANDLE );
            _handle = nullptr;
        }
    }

    Pipeline::Pipeline()
    :   _deivce( nullptr )
    ,   _renderpass( nullptr )
    ,   _handle( VK_NULL_HANDLE )
    {}

}}
