//
//  vk-descriptor-allocator.hpp
//  new-engine
//
//  Created by Kenneth Esdaile on 1/1/24.
//

#ifndef kege_graphics_vk_descriptor_allocator_hpp
#define kege_graphics_vk_descriptor_allocator_hpp

#include "../vulkan/vk.hpp"

namespace kege{namespace vk{

    /**
     * @brief DescriptorAllocator manages the DescriptorPools and the allocation of Vulkan descriptor sets.
     *
     * The DescriptorAllocator class is responsible for the creation and deletion of DescriptorPool. It is
     * responsible for allocating the updating Vulkan descriptor sets.
     *
     * @see vk::DescriptorSetLayout, vk::DescriptorPool,
     */
    class DescriptorAllocator
    {
    public:

        /**
         * @brief Update a UniformAsset.
         *
         * @param writes A vector of VkWriteDescriptorSet structures.
         * @param descriptor Reference to a VkDescriptorSet variable to store the allocated descriptor set.
         */
        void update
        (
            std::vector< VkWriteDescriptorSet >& writes,
            vk::DescriptorSet& descriptor
        );

        /**
         * @brief Allocate a Vulkan descriptor set.
         *
         * @param writes A vector of VkWriteDescriptorSet structures.
         * @param descriptor Reference to a VkDescriptorSet variable to store the allocated descriptor set.
         * @return The true if the descriptor was allocated, false otherwise
         */
        bool allocate
        (   std::vector< VkWriteDescriptorSet >& writes
         ,  vk::DescriptorSet& descriptor
        );

        void init( vk::Device* device, vk::DescriptorSetLayout* descriptor_set_layout );

        /**
         * @brief Get the DescriptorSetLayout associated with this DescriptorAllocator.
         *
         * @return A reference to the DescriptorSetLayout.
         */
        const vk::DescriptorSetLayout* descriptorSetLayout()const;

        vk::Device* device();

        /**
         * @brief Destruct and release resources associated with the DescriptorAllocator.
         */
        void purge();

        ~DescriptorAllocator();
        DescriptorAllocator();

    private:

        std::vector< kege::Ref< vk::DescriptorPool > > _descriptor_pools;
        vk::DescriptorSetLayout* _descriptor_set_layout;
        vk::DescriptorPool* _head;
        vk::DescriptorPool* _tail;
        uint32_t _poolsize;

        vk::Device* _device;
        friend vk::DescriptorPool;
    };

}}

#endif /* kege_graphics_vk_descriptor_allocator_hpp */
