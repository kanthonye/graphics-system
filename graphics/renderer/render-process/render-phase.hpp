//
//  graphics-procedure.hpp
//  new-engine
//
//  Created by Kenneth Esdaile on 4/2/24.
//

#ifndef graphics_procedure_hpp
#define graphics_procedure_hpp

#include "render-target.hpp"

namespace kege{

    class Renderer;
    class RenderProcess;

    /**
     * @class RenderPhase
     *
     * @brief
     * A RenderPhase is a distinct stage within the RenderProcess. Each procedure
     * has a render-target to store the graphical results to. Each render-procedure has one
     * or more graphics-phase that contribute to the overall image.
     *
     * @note
     * Every RenderPhase has a primary command-buffer which the secondary command-buffer
     * of every GraphicsPhase is executed on. Thus, Every GraphicsPhase requires a RenderPhase
     * to executed it.
     *
     * @see RenderProcess, GraphicsPhase
     */
    class RenderPhase : public kege::RefCounter
    {
    public:

        /**
         * @fn commandBuffer
         *
         * @brief
         * Get the command-buffer of this phase
         */
        kege::CommandBuffer* commandBuffer();

        void clearBuffers( const kege::vec4& color, float depth );
        void clearBuffers();

        void setViewport( const kege::vec4& viewport );
        void setViewport();

        void setScissor( const kege::ivec4& viewport );
        void setScissor();
    private:

        /**
         * @fn RenderPhase
         *
         * @brief
         * default constructor
         */
        ~RenderPhase();

        /**
         * @fn init
         *
         * @brief
         * initialize this graphics-procedure
         */
        RenderPhase();

    private:

        kege::Ref< kege::CommandBuffer > _command_buffer;
        kege::RenderProcess* _parent;

        friend kege::RenderProcess;
        friend kege::Ref< kege::RenderPhase >;
    };
    
}

#endif /* graphics_procedure_hpp */
