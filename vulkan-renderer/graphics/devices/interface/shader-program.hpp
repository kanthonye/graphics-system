//
//  shader-program.hpp
//  new-engine
//
//  Created by Kenneth Esdaile on 12/30/23.
//

#ifndef kege_graphics_shader_program_hpp
#define kege_graphics_shader_program_hpp

#include "../../../graphics/devices/interface/shader.hpp"
#include "../../../graphics/devices/interface/pipeline.hpp"
#include "../../../graphics/devices/interface/shader-resource.hpp"

namespace kege{

    class ShaderProgram : public kege::RefCounter
    {
    public:

        struct CreateInfo
        {
            std::vector< kege::VertexInputAttributeDescription > attributes;
            std::vector< kege::VertexInputBindingDescription > bindings;
            std::vector< kege::Ref< kege::Shader > > shaders;
            kege::PipelineLayout::CreateInfo pipeline_layout_create_info;
            const kege::Renderpass* renderpass;
            kege::PrimitiveTopology primitive_topology;
            kege::PolygonMode polygon_mode;
            kege::CullMode cull_mode;
            kege::string name;
        };

        static kege::Ref< ShaderProgram > load( const kege::string& filename, const kege::Framebuffer* framebuffer );
        static kege::Ref< ShaderProgram > create( const CreateInfo& info );

        void bindShaderResource( kege::CommandBuffer* command_buffer, const kege::ShaderResource* resource, uint32_t first_set )const;

        /**
         * @brief Push constant values to the shaders.
         * @param command_buffer The command-buffer this shader was bind to.
         * @param constants The push-constant-data-block load into the shader.
         */
        void pushConstants( kege::CommandBuffer* command_buffer, const kege::PushConstantBlock& constants )const;

        void use( kege::CommandBuffer* command_buffer )const;
        const kege::Pipeline* getPipeline()const;
        void unuse(){}

    protected:

        ShaderProgram& operator =( const kege::ShaderProgram& other ) = delete;
        ShaderProgram( const kege::ShaderProgram& other ){}
        ShaderProgram( kege::Ref< Pipeline > pipeline );
        virtual ~ShaderProgram(){}
        ShaderProgram(){}

    private:

        kege::Ref< Pipeline > _pipeline;
        friend kege::Ref< kege::ShaderProgram >;
    };

}
#endif /* kege_graphics_shader_program_hpp */
