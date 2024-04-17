//
//  render-target-double-buffer.hpp
//  new-engine
//
//  Created by Kenneth Esdaile on 1/17/24.
//

#ifndef render_target_double_buffer_hpp
#define render_target_double_buffer_hpp

#include "render-target.hpp"

namespace kege{

    class RenderTargetDoubleBuffer : public kege::RenderTarget
    {
    public:

        RenderTargetDoubleBuffer( uint16_t width, uint16_t height );
        const kege::ShaderResource* getShaderResource()const;
        const kege::Framebuffer* getFramebuffer()const;

    private:

        enum{ MAX_BUFFER_COUNT = 2};
        kege::Ref< kege::Framebuffer > _framebuffers[ MAX_BUFFER_COUNT ];
        kege::Ref< kege::ShaderResource > _shader_resources[ MAX_BUFFER_COUNT ];
    };

}

#endif /* render_target_double_buffer_hpp */
