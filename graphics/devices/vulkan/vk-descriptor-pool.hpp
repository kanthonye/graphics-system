//
//  vk-descriptor-pool.hpp
//  new-engine
//
//  Created by Kenneth Esdaile on 1/1/24.
//

#ifndef kege_graphics_vk_descriptor_pool_hpp
#define kege_graphics_vk_descriptor_pool_hpp

#include "../vulkan/vk.hpp"

namespace kege{namespace vk{

    /**
     * @brief DescriptorPool is a wrapper class for Vulkan descriptor pools.
     *
     * The DescriptorPool class is responsible for creating the Vulkan descriptor pools.
     * It provides a method for constructing a descriptor pool with specified parameters and exposes methods
     * to access the pool's Vulkan handle and maximum set count.
     *
     * @see DescriptorAllocator, DescriptorSetLayout
     */
    struct DescriptorPool : public kege::RefCounter
    {
    public:

        DescriptorPool
        (
            uint32_t _maxsets,
            const std::vector< VkDescriptorPoolSize >& poolsizes,
            vk::DescriptorAllocator* _allocator
        );

        VkResult allocate
        (
            const vk::DescriptorSetLayout* descriptor_set_layout,
            vk::DescriptorSet& descriptor
        );

        const vk::DescriptorAllocator* allocator()const;
        vk::DescriptorAllocator* allocator();

        void release( VkDescriptorSet& descriptor );

        ~DescriptorPool();

    private:

        std::vector< VkDescriptorPoolSize > _poolsizes;
        VkDescriptorPool _handle;

        vk::DescriptorAllocator* _allocator;
        vk::DescriptorPool* _next;
        vk::DescriptorPool* _prev;

        uint32_t _max_sets;
        uint32_t _count;

        friend vk::DescriptorAllocator;
    };

}}

#endif /* kege_graphics_vk_descriptor_pool_hpp */
