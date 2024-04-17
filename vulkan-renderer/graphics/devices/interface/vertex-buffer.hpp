//
//  vertex-buffer.hpp
//  new-engine
//
//  Created by Kenneth Esdaile on 3/5/24.
//

#ifndef kege_graphics_vertex_buffer_hpp
#define kege_graphics_vertex_buffer_hpp

#include "buffer.hpp"
#include "command-buffer.hpp"

namespace kege{

    class VertexBuffer : public kege::Buffer
    {
    public:

        static kege::Ref< kege::VertexBuffer > create( const kege::CreateBufferInfo& info );
        virtual void bind( kege::CommandBuffer* command_buffer )const = 0;

    protected:

        VertexBuffer& operator =( const kege::VertexBuffer& other ) = delete;
        VertexBuffer( const kege::VertexBuffer& other ){}
        virtual ~VertexBuffer(){}
        VertexBuffer(){}

    private:

        friend kege::Ref< kege::VertexBuffer >;
    };

}
#endif /* vertex_buffer_hpp */
