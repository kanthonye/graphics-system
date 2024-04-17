//
//  compute-process.hpp
//  new-engine
//
//  Created by Kenneth Esdaile on 4/2/24.
//

#ifndef compute_process_hpp
#define compute_process_hpp

#include "compute-phase.hpp"

namespace kege{

    class ComputeProcess : public kege::RefCounter
    {
    public:

        void endComputePhase( kege::ComputePhase* phase );
        kege::ComputePhase* beginComputePhase();

    private:

        void begin( int compute_index );
        void end();

        ~ComputeProcess();
        ComputeProcess();

    private:

        std::vector< kege::Ref< kege::CommandBuffer > > _secondary_command_buffers;
        std::vector< kege::Ref< kege::ComputePhase > > _phases;
        kege::Ref< kege::CommandBuffer > _command_buffer;
        int _compute_index;
        int _phase_count;

        friend kege::Renderer;
        friend kege::Ref< kege::ComputeProcess >;
    };

};
#endif /* compute_process_hpp */
