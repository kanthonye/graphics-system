//
//  vk-draw-command-buffer.hpp
//  new-engine
//
//  Created by Kenneth Esdaile on 3/5/24.
//

#ifndef kege_graphics_vk_draw_command_buffer_hpp
#define kege_graphics_vk_draw_command_buffer_hpp

#include "../vulkan/vk-buffer.hpp"

namespace kege{namespace vk{


    /**
     * @brief Represents a Vulkan buffer object.
     *
     * This class encapsulates a Vulkan buffer, providing a convenient interface for
     * creating, managing, and using buffer resources in Vulkan applications.
     */
    class DrawCommandBuffer : public kege::DrawCommandBuffer
    {
    public:

        void drawIndirect( const vk::CommandBuffer* command_buffer, uint64_t offset, uint32_t draw_count )const;


        /**
         * @brief Creates a Vulkan buffer handle.
         *
         * @param info The buffer info to use to create the buffer.
         * @return VK_SUCCESS if buffer creation is successful; otherwise an error code.
         */
        VkResult construct( const kege::DrawCommandBuffer::CreateInfo& info );

        /**
         * @brief Sets data into the buffer.
         *
         * @param offset The offset into the buffer.
         * @param size The size of the data to be set.
         * @param data Pointer to the data.
         */
        void setBufferData( uint64_t offset, uint64_t size, const void* data );

        /**
         * @brief Retrieves data from the buffer.
         *
         * @param offset The offset into the buffer.
         * @param size The size of the data to retrieve.
         * @param data Reference to store the retrieved data.
         */
        void getBufferData( uint64_t offset, uint64_t size, void*& data );

        /**
         * @brief Retrieves the size of the buffer in bytes.
         *
         * @return The size of the buffer in bytes.
         */
        uint64_t sizeInBytes()const;

        /**
         * @brief Maps the memory of the buffer.
         *
         * @return The const pointer to the mapped memory.
         */
        const void* mapMemory()const;

        /**
         * @brief Unmaps the memory of the buffer.
         */
        void unmapMemory();

        /**
         * @brief Maps the memory of the buffer.
         *
         * @return The pointer to the mapped memory.
         */
        void* mapMemory();

        /**
         * @brief Destructs the Buffer object.
         */
        ~DrawCommandBuffer();

        /**
         * @brief Constructs a Buffer object.
         */
        DrawCommandBuffer( vk::Device* device );

    private:

        vk::Buffer _buffer;
        vk::Device* _device;
        uint32_t _stride;
    };
}}




namespace kege{namespace vk{

    /**
     * @brief Represents a Vulkan buffer object.
     *
     * This class encapsulates a Vulkan buffer, providing a convenient interface for
     * creating, managing, and using buffer resources in Vulkan applications.
     */
    class DrawIndexedCommandBuffer : public kege::DrawIndexedCommandBuffer
    {
    public:

        void drawIndirect( const vk::CommandBuffer* command_buffer, uint64_t offset, uint32_t draw_count )const;

        /**
         * @brief Creates a Vulkan buffer handle.
         *
         * @param info The buffer info to use to create the buffer.
         * @return VK_SUCCESS if buffer creation is successful; otherwise an error code.
         */
        VkResult construct( const kege::DrawIndexedCommandBuffer::CreateInfo& info );

        /**
         * @brief Sets data into the buffer.
         *
         * @param offset The offset into the buffer.
         * @param size The size of the data to be set.
         * @param data Pointer to the data.
         */
        void setBufferData( uint64_t offset, uint64_t size, const void* data );

        /**
         * @brief Retrieves data from the buffer.
         *
         * @param offset The offset into the buffer.
         * @param size The size of the data to retrieve.
         * @param data Reference to store the retrieved data.
         */
        void getBufferData( uint64_t offset, uint64_t size, void*& data );

        /**
         * @brief Retrieves the size of the buffer in bytes.
         *
         * @return The size of the buffer in bytes.
         */
        uint64_t sizeInBytes()const;

        /**
         * @brief Maps the memory of the buffer.
         *
         * @return The const pointer to the mapped memory.
         */
        const void* mapMemory()const;

        /**
         * @brief Unmaps the memory of the buffer.
         */
        void unmapMemory();

        /**
         * @brief Maps the memory of the buffer.
         *
         * @return The pointer to the mapped memory.
         */
        void* mapMemory();

        /**
         * @brief Destructs the Buffer object.
         */
        ~DrawIndexedCommandBuffer();

        /**
         * @brief Constructs a Buffer object.
         */
        DrawIndexedCommandBuffer( vk::Device* device );

    private:

        vk::Buffer _buffer;
        vk::Device* _device;
        uint32_t _stride;
    };
}}

#endif /* kege_graphics_vk_draw_command_buffer_hpp */
