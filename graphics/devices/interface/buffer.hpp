//
//  buffer.hpp
//  new-engine
//
//  Created by Kenneth Esdaile on 12/30/23.
//

#ifndef kege_graphics_buffer_hpp
#define kege_graphics_buffer_hpp

#include "../../../graphics/devices/interface/dependencies.hpp"

namespace kege{

    class Buffer : public kege::RefCounter
    {
    public:

        virtual void setBufferData( uint64_t offset, uint64_t size, const void* data ) = 0;
        virtual void getBufferData( uint64_t offset, uint64_t size, void*& data ) = 0;

        virtual uint64_t sizeInBytes()const = 0;

        virtual const void* mapMemory()const = 0;
        virtual void unmapMemory() = 0;
        virtual void* mapMemory() = 0;

    protected:

        Buffer& operator =( const kege::Buffer& other ) = delete;
        Buffer( const kege::Buffer& other ){}
        virtual ~Buffer(){}
        Buffer(){}

    protected:

        kege::MemoryUsage _usage;
        friend kege::Ref< kege::Buffer >;
    };

    typedef std::vector< kege::Ref< kege::Buffer > > VertexBindings;
}
#endif /* kege_graphics_buffer_hpp */
