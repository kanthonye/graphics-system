//
//  renderer.hpp
//  new-engine
//
//  Created by Kenneth Esdaile on 4/2/24.
//

#ifndef kege_graphics_renderer_hpp
#define kege_graphics_renderer_hpp

#include "compute-process.hpp"
#include "render-process.hpp"

namespace kege{

    class RenderContext;

    class Renderer : public kege::RefCounter
    {
    public:

        RenderProcess* beginRenderProcess( kege::RenderTarget* target, int priority );
        void endRenderProcess( RenderProcess* process );

        ComputeProcess* beginComputeProcess( int priority );
        void endComputeProcess( ComputeProcess* process );

        void uninit();
        bool init( kege::RenderContext& render_context );

        bool begin();
        void end();

        ~Renderer();
        Renderer();

    public:

        std::map< int, kege::RenderProcess* > _ordered_render_processes;
        std::vector< kege::Ref< kege::RenderProcess > > _render_processes;

        std::map< int, kege::ComputeProcess* > _ordered_compute_processes;
        std::vector< kege::Ref< kege::ComputeProcess > > _compute_processes;

        std::vector< kege::CommandBuffer* > _execute_commands;

        uint32_t _render_process_count;
        uint32_t _compute_process_count;

        kege::RenderContext* _render_context;
    };

}

#endif /* kege_graphics_renderer_hpp */
