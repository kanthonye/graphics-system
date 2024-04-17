//
//  render-target-single-buffer.cpp
//  new-engine
//
//  Created by Kenneth Esdaile on 1/17/24.
//

#include "graphics.hpp"
#include "render-target-single-buffer.hpp"

namespace kege
{

    SingleBufferRenderTarget::SingleBufferRenderTarget( uint16_t width, uint16_t height )
    {
        kege::Ref< kege::Sampler > sampler = kege::Sampler::create
        ({
            kege::LINEAR,
            kege::LINEAR,
            kege::CLAMP_TO_EDGE,
            kege::CLAMP_TO_EDGE,
            kege::CLAMP_TO_EDGE
        });

        kege::Ref< kege::Image > color_image = kege::Image2d::create
        ({
            kege::RGBA8_UNORM,
            kege::IMAGE_ASPECT_COLOR,
            width, height, 1, uint64_t(width * height * 4), nullptr
        });

        kege::Ref< kege::Image > depth_image = kege::Image2d::create
        ({
            kege::DEPTH_32_SFLOAT,
            kege::IMAGE_ASPECT_DEPTH,
            width, height, 1, uint64_t(width * height * 4), nullptr
        });

        _shader_resource = kege::ShaderResource::create();
        _shader_resource->insertCombindedImage( "ColorBuffer", 0, color_image, sampler );
        _shader_resource->insertCombindedImage( "DepthBuffer", 1, depth_image, sampler );

        _framebuffer = kege::Framebuffer::create
        ({
            { color_image, kege::COLOR_ATTACHMENT },
            { depth_image, kege::DEPTH_ATTACHMENT }
        });
    }

    const kege::ShaderResource* SingleBufferRenderTarget::getShaderResource()const
    {
        return _shader_resource.ref();
    }

    const kege::Framebuffer* SingleBufferRenderTarget::getFramebuffer()const
    {
        return _framebuffer.ref();
    }
}


