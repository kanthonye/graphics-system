//
//  vk-instance.hpp
//  new-engine
//
//  Created by Kenneth Esdaile on 12/30/23.
//

#ifndef kege_graphics_vk_instance_hpp
#define kege_graphics_vk_instance_hpp

#include "../vulkan/vk-validation-layer.hpp"

namespace kege{namespace vk{

    /**
     * @brief Represents a Vulkan instance.
     *
     * This class encapsulates a Vulkan instance, providing a convenient interface for
     * creating, managing, and using Vulkan instances in Vulkan applications.
     */
    class Instance
    {
    public:

        /**
         * @brief Initializes the Vulkan instance.
         *
         * @param validation_layers A vector of validation layer references to enable during instance creation.
         * @return VK_SUCCESS if the instance initialization is successful, otherwise an error code.
         */
        VkResult init( std::vector< kege::Ref< vk::ValidationLayer > >& validation_layers );

        /**
         * @brief Retrieves the names of enabled validation layers.
         *
         * @return A vector containing the names of enabled validation layers.
         */
        const std::vector< const char* >& validationLayerNames()const;

        /**
         * @brief Retrieves the handle of the Vulkan instance.
         *
         * @return The handle of the Vulkan instance.
         */
        const VkInstance handle()const;

        /**
         * @brief Uninitializes the Vulkan instance.
         */
        void uninit();

        /**
         * @brief Destructs the Instance object.
         */
        ~Instance();

        /**
         * @brief Constructs an Instance object.
         */
        Instance();

    private:

        std::vector< const char* > _validation_layer_names;
        VkInstance _instance;
    };

}}

#endif /* kege_graphics_vk_instance_hpp */
