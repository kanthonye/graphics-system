//
//  vk-storage-buffer.hpp
//  new-engine
//
//  Created by Kenneth Esdaile on 3/5/24.
//

#ifndef kege_graphics_vk_storage_buffer_hpp
#define kege_graphics_vk_storage_buffer_hpp

#include "../vulkan/vk-buffer.hpp"

namespace kege{namespace vk{


    /**
     * @brief Represents a Vulkan buffer object.
     *
     * This class encapsulates a Vulkan buffer, providing a convenient interface for
     * creating, managing, and using buffer resources in Vulkan applications.
     */
    class StorageBuffer : public kege::StorageBuffer
    {
    public:

        /**
         * @brief Creates a Vulkan buffer handle.
         *
         * @param info The buffer info to use to create the buffer.
         * @return VK_SUCCESS if buffer creation is successful; otherwise an error code.
         */
        VkResult construct( const kege::CreateBufferInfo& info );

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

        void getDescriptorBufferInfo( void* data );

        /**
         * @brief Retrieves the const handle of the memory associated with the buffer.
         *
         * @return The const handle of the memory associated with the buffer.
         */
        const VkDeviceMemory memory()const;

        /**
         * @brief Retrieves the const handle of the buffer.
         *
         * @return The const handle of the buffer.
         */
        const VkBuffer handle()const;

        /**
         * @brief Retrieves the size of the buffer in bytes.
         *
         * @return The size of the buffer in bytes.
         */
        uint64_t sizeInBytes()const;

        /**
         * @brief Retrieves the const pointer to the Vulkan buffer.
         *
         * @return The const pointer to the Vulkan buffer.
         */
        const vk::StorageBuffer* vulkan()const;

        /**
         * @brief Retrieves the const pointer to the Vulkan buffer.
         *
         * @return The const pointer to the Vulkan buffer.
         */
        vk::StorageBuffer* vulkan();

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
        ~StorageBuffer();

        /**
         * @brief Constructs a Buffer object.
         */
        StorageBuffer( vk::Device* device );

    private:

        vk::Buffer _buffer;
        vk::Device* _device;
    };
}}

#endif /* kege_graphics_vk_storage_buffer_hpp */
