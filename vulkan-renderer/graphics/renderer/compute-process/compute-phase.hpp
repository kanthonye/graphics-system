//
//  compute-phase.hpp
//  new-engine
//
//  Created by Kenneth Esdaile on 4/2/24.
//

#ifndef kege_compute_phase_hpp
#define kege_compute_phase_hpp

#include "render-target.hpp"

namespace kege{

    class Renderer;
    class ComputeProcess;

    /**
     * @class ComputePhase
     *
     * @brief
     * A ComputePhase is a distinct stage within the ComputeProcess.
     *
     * @see RenderProcess, ComputePhase
     */
    class ComputePhase : public kege::RefCounter
    {
    public:

        /**
         * @fn commandBuffer
         *
         * @brief
         * Get the command-buffer of this phase
         */
        kege::CommandBuffer* commandBuffer();

    private:

        /**
         * @fn RenderPhase
         *
         * @brief
         * default constructor
         */
        ~ComputePhase();

        /**
         * @fn init
         *
         * @brief
         * initialize this graphics-procedure
         */
        ComputePhase();

    private:

        kege::Ref< kege::CommandBuffer > _command_buffer;
        kege::ComputeProcess* _parent;

        friend kege::ComputeProcess;
        friend kege::Ref< kege::ComputePhase >;
    };
    
}

#endif /* kege_compute_phase_hpp */
