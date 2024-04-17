//
//  uniform-buffer.hpp
//  new-engine
//
//  Created by Kenneth Esdaile on 3/5/24.
//

#ifndef kege_graphics_uniform_buffer_hpp
#define kege_graphics_uniform_buffer_hpp

#include "buffer.hpp"
#include "command-buffer.hpp"

namespace kege{

    class UniformBuffer : public kege::Buffer
    {
    public:

        static kege::Ref< kege::UniformBuffer > create( const kege::CreateBufferInfo& info );
        virtual void getDescriptorBufferInfo( void* data ) = 0;

    protected:

        UniformBuffer& operator =( const kege::UniformBuffer& other ) = delete;
        UniformBuffer( const kege::UniformBuffer& other ){}
        virtual ~UniformBuffer(){}
        UniformBuffer(){}

    private:

        friend kege::Ref< kege::UniformBuffer >;
    };

}
#endif /* kege_graphics_uniform_buffer_hpp */
