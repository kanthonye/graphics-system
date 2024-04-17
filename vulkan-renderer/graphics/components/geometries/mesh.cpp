//
//  Mesh.cpp
//  new-engine
//
//  Created by Kenneth Esdaile on 2/18/24.
//

#include "mesh.hpp"
namespace kege{

    void Mesh::draw( kege::CommandBuffer* command_buffer, const kege::DrawCommand& params )const
    {
        command_buffer->draw( params );
    }

    void Mesh::draw( kege::CommandBuffer* command_buffer )const
    {
        command_buffer->draw( _drawparams );
    }

    void Mesh::bind( kege::CommandBuffer* command_buffer )const
    {
        _vertex_buffer->bind( command_buffer );
    }

    kege::Ref< kege::VertexBuffer >& Mesh::getVertexBuffer()
    {
        return _vertex_buffer;
    }

    const kege::DrawCommand& Mesh::drawparams()const
    {
        return _drawparams;
    }
    
    kege::DrawCommand& Mesh::drawparams()
    {
        return _drawparams;
    }

    Mesh& Mesh::operator()( const kege::CreateBufferInfo& info )
    {
        _vertex_buffer = kege::VertexBuffer::create( info );
        return *this;
    }

    Mesh::Mesh( const kege::CreateBufferInfo& info )
    {
        operator()( info );
    }
    Mesh:: ~ Mesh()
    {
        _vertex_buffer.clear();
    }

}


namespace kege{

    void IndexedMesh::draw( kege::CommandBuffer* command_buffer, const DrawCommand& params )const
    {
        command_buffer->drawIndexed( _draw_command );
    }

    void IndexedMesh::draw( kege::CommandBuffer* command_buffer )const
    {
        command_buffer->drawIndexed( _draw_command );
    }

    void IndexedMesh::bind( kege::CommandBuffer* command_buffer )const
    {
        _vertex_buffer->bind( command_buffer );
        _index_buffer->bind( command_buffer );
    }

    kege::Ref< kege::IndexBuffer >& IndexedMesh::getIndexBuffer()
    {
        return _index_buffer;
    }
    
    kege::DrawIndexedCommand& IndexedMesh::getDrawCommand()
    {
        return _draw_command;
    }

    void IndexedMesh::clear()
    {
        _index_buffer.clear();
        _vertex_buffer.clear();
    }
    IndexedMesh& IndexedMesh::operator()( const IndexedMesh::CreateInfo& info )
    {
        kege::Mesh::operator()( info.vertex_buffer_create_infos );
        _index_buffer = kege::IndexBuffer::create( info.index_buffer_create_info );
        _draw_command = info.draw_command;
        return *this;
    }

    IndexedMesh::IndexedMesh( const IndexedMesh::CreateInfo& info )
    {
        IndexedMesh::operator()( info );
    }
    
    IndexedMesh:: ~ IndexedMesh()
    {
        _index_buffer.clear();
    }
}
