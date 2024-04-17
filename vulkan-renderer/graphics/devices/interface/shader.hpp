//
//  shader.hpp
//  new-engine
//
//  Created by Kenneth Esdaile on 12/31/23.
//

#ifndef kege_graphics_shader_hpp
#define kege_graphics_shader_hpp

#include "../../../graphics/devices/interface/dependencies.hpp"

namespace kege
{

    class Shader : public kege::RefCounter
    {
    public:

        struct CreateInfo
        {
            kege::ShaderStageBit type;
            std::vector< char > source;
        };

        static kege::Ref< Shader > create( const CreateInfo& info );
        virtual const vk::Shader* vulkan()const = 0;
        virtual vk::Shader* vulkan() = 0;

    protected:

        Shader& operator =( const kege::Shader& other ) = delete;
        Shader( const kege::Shader& other ){}
        virtual ~Shader(){}
        Shader(){}

    protected:

        friend kege::Ref< Shader >;
    };

}
#endif /* kege_graphics_shader_hpp */
