//
//  render-engine.cpp
//  new-engine
//
//  Created by Kenneth Esdaile on 4/2/24.
//

#include "renderer.hpp"
#include "graphics.hpp"

namespace kege{

    RenderProcess* Renderer::beginRenderProcess( kege::RenderTarget* render_target, int render_index )
    {
        kege::RenderProcess* render_process = nullptr;
        if( _render_processes.size() <= _render_process_count )
        {
            render_process = new kege::RenderProcess();
            _render_processes.push_back( render_process );
        }
        else
        {
            render_process = _render_processes[ _render_process_count ].ref();
        }

        _ordered_render_processes[ render_index ] = render_process;
        render_process->begin( render_target, render_index );
        
        return render_process;

    }

    void Renderer::endRenderProcess( RenderProcess* process )
    {
        auto itr = _ordered_render_processes.find( process->_render_index );
        if ( itr != _ordered_render_processes.end() )
        {
            process->end();
            _execute_commands.push_back( process->_command_buffer.ref() );
            _ordered_render_processes.erase( itr );
        }
        else
        {
            KEGE_ERROR("Renderer::endRenderProcess() : unknown render-process");
        }
    }

    ComputeProcess* Renderer::beginComputeProcess( int compute_index )
    {
        kege::ComputeProcess* process = nullptr;
        if( _compute_processes.size() <= _compute_process_count )
        {
            process = new kege::ComputeProcess();
            _compute_processes.push_back( process );
        }
        else
        {
            process = _compute_processes[ _render_process_count ].ref();
        }

        _ordered_compute_processes[ compute_index ] = process;
        process->begin( compute_index );

        return process;

    }

    void Renderer::endComputeProcess( ComputeProcess* process )
    {
        auto itr = _ordered_compute_processes.find( process->_compute_index );
        if ( itr != _ordered_compute_processes.end() )
        {
            process->end();
            _execute_commands.push_back( process->_command_buffer.ref() );
            _ordered_compute_processes.erase( itr );
        }
        else
        {
            KEGE_ERROR("Renderer::endRenderProcess() : unknown render-process");
        }
    }

    void Renderer::uninit()
    {
        _ordered_render_processes.clear();
        _execute_commands.clear();
        _render_processes.clear();

        _ordered_compute_processes.clear();
        _compute_processes.clear();
    }

    bool Renderer::init( kege::RenderContext& render_context )
    {
        _render_context = &render_context;
        return true;
    }

    bool Renderer::begin()
    {
        _render_process_count = 0;
        _compute_process_count = 0;
        return _render_context->beginRenderProcess();
    }

    void Renderer::end()
    {
        // submit all command buffers for processing
        for ( kege::CommandBuffer* command_buffer : _execute_commands )
        {
            command_buffer->submit();
        }
        _execute_commands.clear();

        _render_context->endRenderProcess();
    }

    Renderer::~Renderer()
    {
        uninit();
    }
    Renderer::Renderer()
    :   _render_process_count( 0 )
    ,   _compute_process_count( 0 )
    {}
}
