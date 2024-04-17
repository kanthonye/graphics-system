//
//  index-buffer.hpp
//  new-engine
//
//  Created by Kenneth Esdaile on 3/5/24.
//

#ifndef kege_graphics_index_buffer_hpp
#define kege_graphics_index_buffer_hpp

#include "buffer.hpp"
#include "command-buffer.hpp"

namespace kege{

    class IndexBuffer : public kege::Buffer
    {
    public:

        static kege::Ref< kege::IndexBuffer > create( const kege::CreateIndexBufferInfo& info );

        /**
         * @brief Bind this index-buffer to the given command buffer.
         *
         * @param command_buffer The command-buffer to bind to.
         */
        virtual void bind( kege::CommandBuffer* command_buffer )const = 0;

    protected:

        IndexBuffer& operator =( const kege::IndexBuffer& other ) = delete;
        IndexBuffer( const kege::IndexBuffer& other ){}
        virtual ~IndexBuffer(){}
        IndexBuffer(){}

    private:

        friend kege::Ref< kege::IndexBuffer >;
    };

}
#endif /* kege_graphics_index_buffer_hpp */
