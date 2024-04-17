//
//  vk-shader.hpp
//  new-engine
//
//  Created by Kenneth Esdaile on 12/31/23.
//

#ifndef kege_graphics_vk_shader_hpp
#define kege_graphics_vk_shader_hpp

#include "../vulkan/vk.hpp"

namespace kege{namespace vk{

    /**
     * @brief Represents a Vulkan shader object.
     *
     * This class encapsulates a Vulkan shader, providing a convenient interface for
     * managing and using shaders in Vulkan applications.
     */
    class Shader : public kege::Shader
    {
    public:

        /**
         * @brief Compiles shader source code into a Vulkan shader module.
         *
         * @param device The Vulkan device.
         * @param type The type of shader (e.g., vertex, fragment).
         * @param source The source code of the shader.
         *
         * @return The Vulkan shader module.
         */
        static VkShaderModule compileShaderSource( VkDevice device, kege::ShaderStageBit type, const std::vector< char >& source );

        /**
         * @brief Creates a Vulkan shader.
         *
         * @param info Information about the shader to be created.
         *
         * @return VK_SUCCESS if the shader creation is successful, otherwise an error code.
         */
        VkResult construct( const kege::Shader::CreateInfo& info );

        /**
         * @brief Retrieves the handle of the Vulkan shader module.
         *
         * @return The Vulkan shader module handle.
         */
        const VkShaderModule handle()const;

        /**
         * @brief Retrieves the stage of the shader.
         *
         * @return The stage of the shader.
         */
        VkShaderStageFlagBits stage()const;

        /**
         * @brief Retrieves a pointer to the Vulkan shader module.
         *
         * @return A pointer to the Vulkan shader module.
         */
        const vk::Shader* vulkan()const;
        vk::Shader* vulkan();

        /**
         * @brief Destructs the Shader object and releases associated Vulkan resources.
         */
        ~Shader();

        /**
         * @brief Constructs a Shader object.
         */
        Shader( vk::Device* device );

    protected:
        
        VkShaderStageFlagBits _stage;
        VkShaderModule _handle;
        vk::Device* _device;
    };

}}
#endif /* kege_graphics_vk_shader_hpp */
