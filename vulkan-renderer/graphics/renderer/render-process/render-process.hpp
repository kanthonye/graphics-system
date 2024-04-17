//
//  graphics-process.hpp
//  new-engine
//
//  Created by Kenneth Esdaile on 4/2/24.
//

#ifndef graphics_process_hpp
#define graphics_process_hpp

#include "hashmap.hpp"
#include "render-phase.hpp"

namespace kege{

    typedef std::pair< kege::string, kege::Ref< kege::RenderPhase > > RenderPhasePair;

    /**
     * @class RenderProcess
     *
     * @brief
     * The RenderProcess refers to the series of procedures taken to generate an image.
     */
    class RenderProcess : public kege::RefCounter
    {
    public:

        void endRenderPhase( kege::RenderPhase* phase );
        kege::RenderPhase* beginRenderPhase();

        const kege::RenderTarget* renderTarget()const;
        kege::RenderTarget* renderTarget();

    private:

        void begin( kege::RenderTarget* render_target, int render_index );
        void end();
        
        ~RenderProcess();
        RenderProcess();

    private:

        std::vector< kege::Ref< kege::CommandBuffer > > _secondary_command_buffers;
        std::vector< kege::Ref< kege::RenderPhase > > _phases;
        kege::Ref< kege::CommandBuffer > _command_buffer;
        kege::Ref< kege::RenderTarget > _render_target;
        int _phase_count;
        int _render_index;

        friend kege::Renderer;
        friend kege::Ref< kege::RenderProcess >;
    };

}
#endif /* graphics_process_hpp */
