//
//  storage-buffer.hpp
//  new-engine
//
//  Created by Kenneth Esdaile on 3/5/24.
//

#ifndef kege_graphics_storage_buffer_hpp
#define kege_graphics_storage_buffer_hpp

#include "buffer.hpp"
#include "command-buffer.hpp"

namespace kege{

    class StorageBuffer : public kege::Buffer
    {
    public:

        static kege::Ref< kege::StorageBuffer > create( const kege::CreateBufferInfo& info );
        virtual void getDescriptorBufferInfo( void* data ) = 0;

    protected:

        StorageBuffer& operator =( const kege::StorageBuffer& other ) = delete;
        StorageBuffer( const kege::StorageBuffer& other ){}
        virtual ~StorageBuffer(){}
        StorageBuffer(){}

    private:

        friend kege::Ref< kege::StorageBuffer >;
    };

}
#endif /* kege_graphics_storage_buffer_hpp */
