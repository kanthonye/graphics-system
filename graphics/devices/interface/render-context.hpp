//
//  render-context.hpp
//  new-engine
//
//  Created by Kenneth Esdaile on 1/6/24.
//

#ifndef kege_graphics_render_context_hpp
#define kege_graphics_render_context_hpp

#include <stdio.h>

#include "framebuffer.hpp"
#include "command-buffer.hpp"
#include "shader-program.hpp"

namespace kege{

    class RenderContext : public kege::RefCounter
    {
    public:


       virtual const kege::Framebuffer* getFramebuffer( uint32_t index )const = 0;

        /**
         * @brief Get the current framebuffer.
         * @return Pointer to the current framebuffer
         */
        virtual const kege::Framebuffer* getFramebuffer()const = 0;

        /**
         * @brief Submit a command buffer to a rendering queue.
         * @param command A pointer to the command buffer to be submitted.
         * @return true if the submission was successful; false otherwise.
         */
        virtual bool submit(  kege::CommandBuffer* command ) = 0;

        /**
         * @brief Get the current frame-index.
         * @return Integer index
         */
        virtual uint32_t getCurrentFrameIndex()const = 0;

        /**
         * @brief TODO: need documentation
         */
        virtual bool beginRenderProcess() = 0;
        virtual void endRenderProcess() = 0;


    protected:

        RenderContext& operator =( const kege::RenderContext& other ) = delete;
        RenderContext( const kege::RenderContext& other ){}
        virtual ~RenderContext(){}
        RenderContext(){}

        friend kege::Ref< kege::RenderContext >;
    };

}
#endif /* kege_graphics_render_context_hpp */
