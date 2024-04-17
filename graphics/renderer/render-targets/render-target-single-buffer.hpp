//
//  render-target-single-buffer.hpp
//  new-engine
//
//  Created by Kenneth Esdaile on 1/17/24.
//

#ifndef render_target_single_buffer_hpp
#define render_target_single_buffer_hpp

#include "render-target.hpp"

namespace kege{

    class SingleBufferRenderTarget : public kege::RenderTarget
    {
    public:

        SingleBufferRenderTarget( uint16_t width, uint16_t height );
        const kege::ShaderResource* getShaderResource()const;
        const kege::Framebuffer* getFramebuffer()const;

    private:

        kege::Ref< kege::Framebuffer > _framebuffer;
        kege::Ref< kege::ShaderResource > _shader_resource;
    };

}

#endif /* render_target_single_buffer_hpp */
