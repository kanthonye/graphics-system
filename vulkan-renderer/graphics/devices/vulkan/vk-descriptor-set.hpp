//
//  vk-descriptor-set.hpp
//  new-engine
//
//  Created by Kenneth Esdaile on 1/1/24.
//

#ifndef kege_graphics_vk_descriptor_set_hpp
#define kege_graphics_vk_descriptor_set_hpp

#include "../vulkan/vk.hpp"

namespace kege{namespace vk{

    /**
     * @brief Represents a Vulkan descriptor set.
     *
     * This class encapsulates a Vulkan descriptor set, providing methods for binding, updating,
     * and managing descriptor sets in Vulkan applications.
     */
    class DescriptorSet : public kege::ShaderResource
    {
    public:

        /**
         * @brief Binds the descriptor set to a command buffer.
         *
         * @param command_buffer The command buffer to bind to.
         * @param first_set The index of the first descriptor set.
         * @param program The shader-program to use bind the resource to.
         */
        void bind( kege::CommandBuffer* command_buffer, uint32_t first_set, kege::ShaderProgram* program )const;

        /**
         * @brief Binds the descriptor set to a command buffer.
         *
         * @param command_buffer The command buffer to bind to.
         * @param first_set The index of the first descriptor set.
         */
        void bind( kege::CommandBuffer* command_buffer, uint32_t first_set )const;

        /**
         * @brief Sets the descriptor set.
         *
         * @param descriptor The descriptor set to set.
         */
        void setDescriptorSet( VkDescriptorSet descriptor );

        /**
         * @brief Retrieves the descriptor set.
         *
         * @return The descriptor set.
         */
        const VkDescriptorSet descriptorSet()const;

        /**
         * @brief Updates the descriptor set with the specified uniform layout.
         *
         */
        void update();

        /**
         * @brief Retrieves the const handle of the Vulkan descriptor set.
         *
         * @return The const handle of the Vulkan descriptor set.
         */
        bool valid()const;

        /**
         * @brief Destructs the DescriptorSet object.
         */
        void destruct();

        DescriptorSet( vk::Device* device );
        ~DescriptorSet();

    private:

        vk::DescriptorPool* _descriptor_pool;
        VkDescriptorSet _descriptor_set;
        vk::Device* _device;
        
        friend kege::Ref< DescriptorSet >;
        friend vk::DescriptorAllocator;
        friend vk::DescriptorPool;
    };

}}

#endif /* kege_graphics_vk_descriptor_set_hpp */
