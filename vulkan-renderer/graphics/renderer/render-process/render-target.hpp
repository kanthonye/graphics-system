//
//  render-target.hpp
//  new-engine
//
//  Created by Kenneth Esdaile on 1/11/24.
//

#ifndef render_target_hpp
#define render_target_hpp

#include "framebuffer.hpp"
#include "shader-resource.hpp"

namespace kege{

    class RenderTarget : public kege::RefCounter
    {
    public:

        virtual const kege::ShaderResource* getShaderResource()const = 0;
        virtual const kege::Framebuffer* getFramebuffer()const = 0;
        virtual ~RenderTarget(){}
    };

}

#endif /* render_target_hpp */
