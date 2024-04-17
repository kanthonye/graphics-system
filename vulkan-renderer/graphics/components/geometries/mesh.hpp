//
//  Mesh.hpp
//  new-engine
//
//  Created by Kenneth Esdaile on 2/18/24.
//

#ifndef kege_graphics_mesh_hpp
#define kege_graphics_mesh_hpp

#include "geometry.hpp"

namespace kege{

    class Mesh : public Geometry
    {
    public:
        
        virtual void draw( kege::CommandBuffer* command_buffer, const kege::DrawCommand& params )const;
        virtual void draw( kege::CommandBuffer* command_buffer )const;
        virtual void bind( kege::CommandBuffer* command_buffer )const;

        kege::Ref< kege::VertexBuffer >& getVertexBuffer();
        const kege::DrawCommand& drawparams()const;
        kege::DrawCommand& drawparams();

        Mesh& operator()( const kege::CreateBufferInfo& );
        Mesh( const kege::CreateBufferInfo& );
        virtual ~ Mesh();
        Mesh(){}

    protected:

        kege::Ref< kege::VertexBuffer > _vertex_buffer;
        kege::DrawCommand _drawparams;
    };

}



namespace kege{

    class IndexedMesh : public kege::Mesh
    {
    public:

        struct CreateInfo
        {
            kege::CreateBufferInfo vertex_buffer_create_infos;
            kege::CreateIndexBufferInfo index_buffer_create_info;
            kege::DrawIndexedCommand draw_command;
        };

    public:

        virtual void draw( kege::CommandBuffer* command_buffer, const kege::DrawCommand& params )const;
        virtual void draw( kege::CommandBuffer* command_buffer )const;
        virtual void bind( kege::CommandBuffer* command_buffer )const;

        kege::Ref< kege::IndexBuffer >& getIndexBuffer();
        kege::DrawIndexedCommand& getDrawCommand();
        void clear();

        IndexedMesh& operator()( const IndexedMesh::CreateInfo& );
        IndexedMesh( const IndexedMesh::CreateInfo& );
        virtual ~ IndexedMesh();
        IndexedMesh(){}

    private:

        kege::Ref< kege::IndexBuffer > _index_buffer;
        kege::DrawIndexedCommand _draw_command;
    };

}
#endif /* kege_graphics_mesh_hpp */
