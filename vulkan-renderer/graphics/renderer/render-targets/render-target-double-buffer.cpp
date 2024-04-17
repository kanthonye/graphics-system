//
//  render-target-double-buffer.cpp
//  new-engine
//
//  Created by Kenneth Esdaile on 1/17/24.
//

#include "graphics.hpp"
#include "render-target-double-buffer.hpp"

namespace kege
{

    RenderTargetDoubleBuffer::RenderTargetDoubleBuffer( uint16_t width, uint16_t height )
    {
        kege::Ref< kege::Sampler > sampler = kege::Sampler::create
        ({
            kege::LINEAR,
            kege::LINEAR,
            kege::CLAMP_TO_EDGE,
            kege::CLAMP_TO_EDGE,
            kege::CLAMP_TO_EDGE
        });

        for (int i=0; i<MAX_BUFFER_COUNT; i++)
        {
            kege::Ref< kege::Image > color_image = kege::Image2d::create
            ({
                kege::RGBA8_UNORM,
                kege::IMAGE_ASPECT_COLOR,
                width, height, 1, uint64_t(width * height * 4), nullptr,
            });

            kege::Ref< kege::Image > depth_image = kege::Image2d::create
            ({
                kege::DEPTH_32_SFLOAT,
                kege::IMAGE_ASPECT_DEPTH,
                width, height, 1, uint64_t(width * height * 4), nullptr,
            });

            _framebuffers[i] = kege::Framebuffer::create
            ({
                { color_image, kege::COLOR_ATTACHMENT },
                { depth_image, kege::DEPTH_ATTACHMENT }
            });

            _shader_resources[ i ] = kege::ShaderResource::create();
            _shader_resources[ i ]->insertCombindedImage( "ColorBuffer", 0, color_image, sampler );
            _shader_resources[ i ]->insertCombindedImage( "DepthBuffer", 1, depth_image, sampler );
            _shader_resources[ i ]->update();
        }
    }

    const kege::ShaderResource* RenderTargetDoubleBuffer::getShaderResource()const
    {
        uint32_t index = kege::Graphics::device()->getRenderContext().getCurrentFrameIndex() % MAX_BUFFER_COUNT;
        return _shader_resources[ index ].ref();
    }

    const kege::Framebuffer* RenderTargetDoubleBuffer::getFramebuffer()const
    {
        uint32_t index = kege::Graphics::device()->getRenderContext().getCurrentFrameIndex() % MAX_BUFFER_COUNT;
        return _framebuffers[ index ].ref();
    }

}


