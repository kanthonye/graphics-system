//
//  vk-buffer.hpp
//  new-engine
//
//  Created by Kenneth Esdaile on 12/30/23.
//

#ifndef kege_graphics_vk_buffer_hpp
#define kege_graphics_vk_buffer_hpp

#include "../vulkan/vk.hpp"

namespace kege{namespace vk{


    /**
     * @brief Represents a Vulkan buffer object.
     *
     * This class encapsulates a Vulkan buffer, providing a convenient interface for
     * creating, managing, and using buffer resources in Vulkan applications.
     */
    class Buffer
    {
    public:

        VkResult construct( vk::Device* device, MemoryUsage memory_usage, VkBufferUsageFlags buffer_type, uint64_t size, const void* data );

        VkResult create
        (
            vk::Device* device,
            VkSharingMode sharing_mode,
            VkBufferUsageFlags usage,
            VkMemoryPropertyFlags memory_properties,
            VkDeviceSize size,
            const void* data
        );

        /**
         * @brief Sets data into the buffer.
         *
         * @param offset The offset into the buffer.
         * @param size The size of the data to be set.
         * @param data Pointer to the data.
         */
        void setBufferData( VkDevice device, uint64_t offset, uint64_t size, const void* data );

        /**
         * @brief Retrieves data from the buffer.
         *
         * @param offset The offset into the buffer.
         * @param size The size of the data to retrieve.
         * @param data Reference to store the retrieved data.
         */
        void getBufferData( VkDevice device, uint64_t offset, uint64_t size, void*& data );

        /**
         * @brief Maps the memory of the buffer.
         *
         * @return The const pointer to the mapped memory.
         */
        const void* mapMemory( VkDevice device )const;

        /**
         * @brief Unmaps the memory of the buffer.
         */
        void unmapMemory( VkDevice device );

        /**
         * @brief Maps the memory of the buffer.
         *
         * @return The pointer to the mapped memory.
         */
        void* mapMemory( VkDevice device );

        void destroy( VkDevice device );

        /**
         * @brief Destructs the Buffer object.
         */
        ~Buffer();

        /**
         * @brief Constructs a Buffer object.
         */
        Buffer();

    public:

        VkDeviceMemory memory;
        VkDeviceSize size;
        VkBuffer handle;
    };
}}
#endif /* kege_graphics_vk_buffer_hpp */
