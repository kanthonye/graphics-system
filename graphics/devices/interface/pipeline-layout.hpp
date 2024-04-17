//
//  pipeline-layout.hpp
//  new-engine
//
//  Created by Kenneth Esdaile on 12/30/23.
//

#ifndef kege_graphics_pipeline_layout_hpp
#define kege_graphics_pipeline_layout_hpp

#include "../../../graphics/devices/interface/dependencies.hpp"

namespace kege
{

    typedef struct DescriptorBinding 
    {
        kege::DescriptorType descriptor_type;
        uint32_t binding;
        uint32_t count;
        uint32_t set;
    } DescriptorBinding;

    typedef struct PushConstantRange {
        uint32_t stages;
        uint32_t offset;
        uint32_t size;
    } PushConstantRange;


    class PipelineLayout : public kege::RefCounter
    {
    public:

        struct CreateInfo
        {
            PipelineLayoutType pipeline_layout_type;
            std::vector< kege::string > binding_names;
            std::vector< kege::DescriptorBinding > bindings;
            std::vector< kege::PushConstantRange > constansts;
        };

        static kege::Ref< PipelineLayout > create( const CreateInfo& info );
        virtual const vk::PipelineLayout* vulkan()const = 0;
        virtual vk::PipelineLayout* vulkan() = 0;

        //PipelineLayoutType getPipelineLayoutType()const;

    protected:

        PipelineLayout& operator =( const kege::PipelineLayout& other ) = delete;
        PipelineLayout( const kege::PipelineLayout& other ){}
        virtual ~PipelineLayout(){}
        PipelineLayout(){}

    protected:

        PipelineLayoutType _pipeline_layout_type;
        friend kege::Ref< PipelineLayout >;
    };
}
#endif /* kege_graphics_pipeline_layout_hpp */
