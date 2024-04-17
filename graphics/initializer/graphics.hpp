//
//  Graphics.hpp
//  new-engine
//
//  Created by Kenneth Esdaile on 12/30/23.
//

#ifndef KEGE_GRAPHICS
#define KEGE_GRAPHICS

#include "../../graphics/components/geometries/cuboid.hpp"
#include "../../graphics/renderer/renderer.hpp"
#include "../../graphics/devices/interface/device.hpp"

namespace kege
{
    /**
     * @class Graphics
     * @brief The Graphics module responsible for handling rendering operations.
     *
     * This module provides functionality for initializing and managing the graphics subsystem
     * of the game engine, including the creation and management of render windows and devices.
     * It inherits from the Module class.
     */
    class Graphics : public kege::RefCounter
    {
    public:

        //void insert( std::vector< kege::RenderPhasePair > procedures );
        //void submit( kege::Ref< kege::RenderTask > task );
        //void submit( kege::Ref< kege::ComputeTask > task );

        /**
         * @brief Creates an instance of the Graphics module.
         * @return A reference to the created Graphics module.
         */
        static kege::Ref< kege::Graphics > create();
        kege::RenderTarget* getRenderTarget();
        void setTitle( const char* title );
        void setHeight( uint32_t value );
        void setWidth( uint32_t value );
        bool windowIsOpen()const;
        void setInputCallback();
        void poolEvents();


        /**
         * @brief Retrieves the graphics device.
         * @return A pointer to the graphics device.
         */
        static kege::Device* device();

        /**
         * @brief Retrieves the render window.
         * @return A pointer to the render window.
         */
        kege::RenderWindow* window();

        /**
         * @brief Retrieves the render window.
         * @return A pointer to the render window.
         */
        kege::Renderer* renderer();

        /**
         * @brief Uninitializes the Graphics module.
         */
        void uninit();

        /**
         * @brief Initializes the Graphics module.
         * @return True if initialization is successful, false otherwise.
         */
        bool init();

    private:

        Graphics& operator =( const kege::Graphics& other ) = delete;
        Graphics( const kege::Graphics& other ) = delete;
        ~Graphics();
        Graphics();

    private:

        kege::Renderer _renderer;
        kege::Ref< kege::RenderTarget > _render_tagret;
        kege::Ref< kege::RenderWindow > _window;
        static kege::Ref< kege::Device > _device;

        const char* _title;
        uint16_t _width;
        uint16_t _height;
        bool _fullscreen;

        friend kege::Ref< kege::Graphics >;
    };

}

#endif /* KEGE_GRAPHICS */
