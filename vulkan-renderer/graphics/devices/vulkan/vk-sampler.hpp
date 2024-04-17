//
//  vk-sampler.hpp
//  new-engine
//
//  Created by Kenneth Esdaile on 1/4/24.
//

#ifndef kege_graphics_vk_sampler_hpp
#define kege_graphics_vk_sampler_hpp

#include "../vulkan/vk.hpp"

namespace kege{namespace vk{

    /**
     * @brief Represents a Vulkan sampler object.
     *
     * This class encapsulates a Vulkan sampler, providing a convenient interface for
     * creating, managing, and using sampler resources in Vulkan applications.
     */
    class Sampler : public kege::Sampler
    {
    public:

        /**
         * @brief Creates a Vulkan sampler handle.
         *
         * @param create_info Information to create the sampler.
         *
         * @return VK_SUCCESS if the sampler handle creation is successful, otherwise an error code.
         */
        VkResult construct( kege::Sampler::CreateInfo create_info );

        /**
         * @brief Converts a wrapping mode enum to the corresponding Vulkan address mode.
         *
         * @param wrap The wrapping mode enum value.
         *
         * @return The corresponding Vulkan address mode.
         */
        static VkSamplerAddressMode getAddressMode( kege::Wrapping wrap );
        /**
         * @brief Converts a filter enum to the corresponding Vulkan filter mode.
         *
         * @param filter The filter enum value.
         *
         * @return The corresponding Vulkan filter mode.
         */
        static VkFilter getFilter( kege::Filter filter );


        void getDescriptorBufferInfo( void* data );

        /**
         * @brief Retrieves a pointer to the Vulkan sampler handle.
         *
         * @return A pointer to the Vulkan sampler handle.
         */
        const vk::Sampler* vulkan()const;
        vk::Sampler* vulkan();

        /**
         * @brief Retrieves the Vulkan sampler handle.
         *
         * @return The Vulkan sampler handle.
         */
        const VkSampler handle()const;

        /**
         * @brief Constructs a Sampler object with the given Vulkan sampler handle and device.
         *
         * @param device Pointer to the Vulkan device.
         */
        Sampler( vk::Device* device );

        /**
         * @brief Destructs the Sampler object.
         */
        ~Sampler();

    protected:

        Sampler& operator =( const kege::Sampler& other ) = delete;
        Sampler( const kege::Sampler& other ){}

    private:

        vk::Device* _device;
        VkSampler _handle;
    };

}}
#endif /* kege_graphics_vk_sampler_hpp */
