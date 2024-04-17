//
//  renderpass.hpp
//  new-engine
//
//  Created by Kenneth Esdaile on 12/31/23.
//

#ifndef kege_graphics_renderpass_hpp
#define kege_graphics_renderpass_hpp

#include "../../../graphics/devices/interface/dependencies.hpp"

namespace kege
{

    class Renderpass : public kege::RefCounter
    {
    public:

        struct CreateInfo
        {
        };

        static kege::Ref< Renderpass > create( const CreateInfo& info );
        virtual const vk::Renderpass* vulkan()const{return nullptr;}
        virtual vk::Renderpass* vulkan(){return nullptr;}

    protected:

        Renderpass& operator =( const kege::Renderpass& other ) = delete;
        Renderpass( const kege::Renderpass& other ){}
        virtual ~Renderpass(){}
        Renderpass(){}

    protected:

        friend kege::Ref< Renderpass >;
    };

}
#endif /* kege_graphics_renderpass_hpp */
