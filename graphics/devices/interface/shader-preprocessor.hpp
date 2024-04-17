//
//  shader-preprocessor.hpp
//  new-engine
//
//  Created by Kenneth Esdaile on 4/5/24.
//

#ifndef kege_graphics_shader_preprocessor_hpp
#define kege_graphics_shader_preprocessor_hpp

#include "../../../graphics/devices/interface/dependencies.hpp"

namespace kege{

    struct ShaderReflection
    {
        struct Variable
        {
            kege::string type;
            kege::string name;
        };

        struct Struct
        {
            kege::string name;
            std::vector< Variable > members;
        };

        struct Layout
        {
            uint32_t set;
            uint32_t binding;
            uint32_t location;
            kege::string type;
            kege::string name;
            kege::string instance_name;
            kege::DescriptorType descriptor_type;
            std::vector< Variable > members;
            kege::ShaderStageBit shader_stage;
        };

        ~ShaderReflection();

        std::vector< Struct* > structs;
        std::vector< kege::ShaderReflection::Layout* > inputs;
        std::vector< kege::ShaderReflection::Layout* > outputs;
        std::vector< kege::ShaderReflection::Layout* > attributes;
        std::vector< kege::ShaderReflection::Layout* > descriptors;
        std::vector< kege::ShaderReflection::Layout* > push_constants;
        std::vector< kege::ShaderReflection::Layout* > layouts;
    };

    void parse( ShaderReflection* preprocessor, kege::ShaderStageBit shader_stage, const char* source );
}
#endif /* kege_graphics_shader_preprocessor_hpp */
