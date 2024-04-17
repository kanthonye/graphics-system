//
//  vk-pipeline.hpp
//  new-engine
//
//  Created by Kenneth Esdaile on 12/30/23.
//

#ifndef kege_graphics_vk_pipeline_hpp
#define kege_graphics_vk_pipeline_hpp

#include "../vulkan/vk.hpp"

namespace kege{namespace vk{

    /**
     * @brief Represents a Vulkan pipeline object.
     *
     * This class encapsulates a Vulkan pipeline, providing a convenient interface for
     * creating, managing, and using pipeline resources in Vulkan applications.
     */
    class Pipeline : public kege::Pipeline
    {
    public:

        /**
         * @brief Creates a graphics pipeline.
         *
         * @param device Pointer to the Vulkan device.
         * @param info Information to create the graphics pipeline.
         * @param pipeline Reference to a VkPipeline object to be filled with the created graphics pipeline.
         *
         * @return VK_SUCCESS if the graphics pipeline creation is successful, otherwise an error code.
         */
        static VkResult createGraphicsPipeline( vk::Device* device, const kege::Pipeline::CreateInfo& info, vk::Pipeline& pipeline );

        /**
         * @brief Creates a compute pipeline.
         *
         * @param device Pointer to the Vulkan device.
         * @param info Information to create the compute pipeline.
         * @param pipeline Reference to a VkPipeline object to be filled with the created compute pipeline.
         *
         * @return VK_SUCCESS if the compute pipeline creation is successful, otherwise an error code.
         */
        static VkResult createComputePipeline( vk::Device* device, const kege::Pipeline::CreateInfo& info, vk::Pipeline& pipeline );

        /**
         * @brief Retrieves a pointer to the render pass associated with the pipeline.
         *
         * @return A pointer to the render pass associated with the pipeline.
         */
        const kege::Renderpass* renderpass()const;

        /**
         * @brief Retrieves a pointer to the Vulkan pipeline.
         *
         * @return A pointer to the Vulkan pipeline.
         */
        const vk::Pipeline* vulkan()const;
        vk::Pipeline* vulkan();

        /**
         * @brief Retrieves the Vulkan pipeline handle.
         *
         * @return The Vulkan pipeline handle.
         */
        const VkPipeline handle()const;

        /**
         * @brief Destructs the Pipeline object.
         */
        ~Pipeline();

        /**
         * @brief Constructs a Pipeline object.
         */
        Pipeline();

    private:

        Pipeline& operator =( const kege::Pipeline& other ) = delete;
        Pipeline( const kege::Pipeline& other ) = delete;

    protected:

        const kege::Renderpass* _renderpass;
        vk::Device* _deivce;
        VkPipeline _handle;
        
        friend kege::Ref< kege::Pipeline >;;
    };

    VkPipeline constructGraphicsPipeline( VkDevice device, const kege::Pipeline::CreateInfo& info );
    VkPipeline constructComputePipeline( VkDevice device, const kege::Pipeline::CreateInfo& info );
}}
#endif /* kege_graphics_vk_pipeline_hpp */
