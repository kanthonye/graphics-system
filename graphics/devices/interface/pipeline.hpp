//
//  pipeline.hpp
//  new-engine
//
//  Created by Kenneth Esdaile on 12/30/23.
//

#ifndef kege_graphics_pipeline_hpp
#define kege_graphics_pipeline_hpp

#include "../../../graphics/devices/interface/shader.hpp"
#include "../../../graphics/devices/interface/renderpass.hpp"
#include "../../../graphics/devices/interface/pipeline-layout.hpp"

namespace kege
{
    typedef struct VertexInputAttributeDescription {
        kege::Format format;
        uint32_t location;
        uint32_t binding;
        uint32_t offset;
    } VertexInputAttributeDescription;

    typedef struct VertexInputBindingDescription {
        kege::VertexInputRate input_rate;
        uint32_t binding;
        uint32_t stride;
    } VertexInputBindingDescription;

    class Pipeline : public kege::RefCounter
    {
    public:

        struct CreateInfo
        {
            std::vector< kege::VertexInputAttributeDescription > attributes;
            std::vector< kege::VertexInputBindingDescription > bindings;
            std::vector< kege::Ref< kege::Shader > > shaders;
            kege::Ref< kege::PipelineLayout > pipeline_layout;
            const kege::Renderpass* renderpass;
            kege::PrimitiveTopology primitive_topology;
            kege::PolygonMode polygon_mode;
            kege::CullMode cull_mode;
        };

    public:

        static kege::Ref< Pipeline > create( const CreateInfo& info );
        const kege::PipelineLayout* getPipelineLayout()const;
        kege::PipelineLayout* getPipelineLayout();
        
        virtual const kege::Renderpass* renderpass()const = 0;

        virtual const vk::Pipeline* vulkan()const = 0;
        virtual vk::Pipeline* vulkan() = 0;

    protected:

        Pipeline& operator =( const kege::Pipeline& other ) = delete;
        Pipeline( const kege::Pipeline& other ){}
        virtual ~Pipeline(){}
        Pipeline();

    protected:

        kege::Ref< PipelineLayout > _pipeline_layout;
        friend kege::Ref< Pipeline >;
    };

}
#endif /* kege_graphics_pipeline_hpp */
