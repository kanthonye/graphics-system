//
//  draw-command-buffer.hpp
//  new-engine
//
//  Created by Kenneth Esdaile on 3/5/24.
//

#ifndef kege_graphics_draw_command_buffer_hpp
#define kege_graphics_draw_command_buffer_hpp

#include "buffer.hpp"

namespace kege{

    class CommandBuffer;

    class DrawCommandBuffer : public kege::Buffer
    {
    public:

        struct CreateInfo
        {
            uint64_t size;
            const kege::DrawCommand* data;
            MemoryUsage memory_usage;
        };

        static kege::Ref< kege::DrawCommandBuffer > create( const kege::DrawCommandBuffer::CreateInfo& info );
        virtual void drawIndirect( const vk::CommandBuffer* command_buffer, uint64_t offset, uint32_t draw_count )const{}

    protected:

        DrawCommandBuffer& operator =( const kege::DrawCommandBuffer& other ) = delete;
        DrawCommandBuffer( const kege::DrawCommandBuffer& other ){}
        virtual ~DrawCommandBuffer(){}
        DrawCommandBuffer(){}

    private:

        friend kege::Ref< kege::DrawCommandBuffer >;
    };

}

namespace kege{

    class DrawIndexedCommandBuffer : public kege::Buffer
    {
    public:

        struct CreateInfo
        {
            uint64_t size;
            const kege::DrawIndexedCommand* data;
            MemoryUsage memory_usage;
        };

        static kege::Ref< kege::DrawIndexedCommandBuffer > create( const kege::DrawIndexedCommandBuffer::CreateInfo& info );
        virtual void drawIndirect( const vk::CommandBuffer* command_buffer, uint64_t offset, uint32_t draw_count )const{}

    protected:

        DrawIndexedCommandBuffer& operator =( const kege::DrawIndexedCommandBuffer& other ) = delete;
        DrawIndexedCommandBuffer( const kege::DrawIndexedCommandBuffer& other ){}
        virtual ~DrawIndexedCommandBuffer(){}
        DrawIndexedCommandBuffer(){}

    private:

        friend kege::Ref< kege::DrawIndexedCommandBuffer >;
    };

}
#endif /* kege_graphics_draw_command_buffer_hpp */
