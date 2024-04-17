//
//  vk-validation-layer.hpp
//  new-engine
//
//  Created by Kenneth Esdaile on 12/30/23.
//

#ifndef kege_graphics_vk_validation_layer_hpp
#define kege_graphics_vk_validation_layer_hpp

#include "../vulkan/vk.hpp"

namespace kege{namespace vk{

    /**
     * @brief Represents a validation layer in a Vulkan application.
     *
     * This class encapsulates a validation layer, providing a convenient interface for
     * managing and using validation layers in Vulkan applications.
     */
    class ValidationLayer : public kege::RefCounter
    {
    public:

        /**
         * @brief Constructs a ValidationLayer object with the specified ID.
         *
         * @param id The ID of the validation layer.
         */
        ValidationLayer( const char* id );

        /**
         * @brief Destroys the ValidationLayer object.
         */
        virtual ~ValidationLayer(){}

        /**
         * @brief Retrieves the ID of the validation layer.
         *
         * @return A pointer to the ID of the validation layer.
         */
        const char* id()const;

    private:

        const char* _id; ///< The ID of the validation layer.
    };

}}

#endif /* kege_graphics_vk_validation_layer_hpp */
