//
//  vk-descriptor-set-layout.hpp
//  new-engine
//
//  Created by Kenneth Esdaile on 1/1/24.
//

#ifndef kege_graphics_vk_descriptor_set_layout_hpp
#define kege_graphics_vk_descriptor_set_layout_hpp

#include "../vulkan/vk-descriptor-allocator.hpp"

namespace kege{namespace vk{

    /**
     * @brief Represents a Vulkan descriptor set layout.
     *
     * This class provides a convenient interface for creating Vulkan descriptor set layouts.
     */
    class DescriptorSetLayout : public kege::RefCounter
    {
    public:

        /**
         * @brief Creates a Vulkan descriptor set layout handle.
         *
         * @param descriptor_set_layout_bindings The vector of descriptor set layout bindings.
         * @param pipeline_layout_set The pipeline-layouts to bind to.
         * @return The handle to the created Vulkan descriptor set layout.
         */
        VkResult create
        (   const vk::DescriptorSetLayoutObject& descriptor_set_layout_bindings
         ,  std::set< vk::PipelineLayout* >* pipeline_layout_set
        );

        /**
         * @brief Get the pipeline-layout-set associated with this DescriptorSetLayout
         *
         * @return A reference to the PipelineLayout.
         */
        const std::set< vk::PipelineLayout* >* pipelineLayoutSet()const;
        std::set< vk::PipelineLayout* >* pipelineLayoutSet();

        /**
         * @brief Get the bindings associated with the descriptor set layout.
         *
         * @return A reference to a vector of VkDescriptorSetLayoutBinding structures.
         */
        const vk::DescriptorSetLayoutObject& bindings()const;

        /**
         * @brief Get the Vulkan handle of the descriptor set layout.
         *
         * @return A reference to the Vulkan handle of the descriptor set layout.
         */
        const VkDescriptorSetLayout& handle()const;

        /**
         * @brief Get the DescriptorAllocator of this DescriptorSetLayout.
         *
         * @return A reference to the DescriptorAllocator of this object.
         */
        DescriptorAllocator* allocator();


        vk::Device* device();
        /**
         * @brief The DescriptorSetLayout destructor.
         */
        ~DescriptorSetLayout();

        /**
         * @brief The DescriptorSetLayout constructor.
         */
        DescriptorSetLayout( vk::Device* device );

    private:

        std::set< vk::PipelineLayout* >* _pipeline_layouts;
        vk::DescriptorSetLayoutObject _bindings;
        vk::DescriptorAllocator _allocator;
        vk::Device* _device;

        VkDescriptorSetLayout _handle;
    };

}}

#endif /* kege_graphics_vk_descriptor_set_layout_hpp */
