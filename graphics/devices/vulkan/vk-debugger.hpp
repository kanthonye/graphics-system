//
//  vk-debugger.hpp
//  new-engine
//
//  Created by Kenneth Esdaile on 12/30/23.
//

#ifndef kege_graphics_vk_debugger_hpp
#define kege_graphics_vk_debugger_hpp

#include "../vulkan/vk-instance.hpp"
#include "../vulkan/vk-validation-layer.hpp"

namespace kege{namespace vk{

    /**
     * @brief Represents a Vulkan debugger.
     *
     * This class provides functionality for debugging Vulkan applications using validation layers.
     */
    class Debugger : public kege::vk::ValidationLayer
    {
    public:

        /**
         * @brief Retrieves the const reference to the Vulkan debug messenger creation info.
         *
         * @return The const reference to the Vulkan debug messenger creation info.
         */
        const VkDebugUtilsMessengerCreateInfoEXT& info()const;

        /**
         * @brief Retrieves the Vulkan debug messenger handle.
         *
         * @return The Vulkan debug messenger handle.
         */
        const VkDebugUtilsMessengerEXT handle()const;

        /**
         * @brief Initializes the debugger with the specified instance.
         *
         * @param instance Pointer to the Vulkan instance.
         * @return VK_SUCCESS if initialization is successful; otherwise an error code.
         */
        VkResult init( const Instance* instance );

        /**
         * @brief Uninitializes the debugger.
         */
        void uninit();

        /**
         * @brief Destructs the Debugger object.
         */
        ~Debugger();

        /**
         * @brief Constructs a Debugger object.
         */
        Debugger();

    private:

        VkDebugUtilsMessengerCreateInfoEXT _info;
        VkDebugUtilsMessengerEXT _handle;
        const vk::Instance* _instance;
    };

}}
#endif /* kege_graphics_vk_debugger_hpp */
