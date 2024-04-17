//
//  Graphics.cpp
//  new-engine
//
//  Created by Kenneth Esdaile on 12/30/23.
//

#include "../../graphics/initializer/graphics.hpp"
#include "../../graphics/renderer/render-targets/render-target-render-window.hpp"

namespace kege
{

    kege::Ref< kege::Graphics > Graphics::create()
    {
        return new kege::Graphics();
    }

    kege::RenderTarget* Graphics::getRenderTarget()
    {
        return _render_tagret.ref();
    }

    void Graphics::setTitle( const char* title )
    {
        _title = title;
    }

    void Graphics::setHeight( uint32_t value )
    {
        _height = value;
    }

    void Graphics::setWidth( uint32_t value )
    {
        _width = value;
    }

    bool Graphics::windowIsOpen()const
    {
        return _window->isactive();
    }

    void Graphics::setInputCallback()
    {
    }

    void Graphics::poolEvents()
    {
        _window->pollEvents();
    }

    kege::Device* Graphics::device()
    {
        return _device.ref();
    }

    bool Graphics::init()
    {
        assert( !_window  && "error : INVALID_OPERATION : calling Graphics::init() more than once is not allowed." );
        try
        {
            RenderWindow::CreateInfo info;
            info.fullscreen = _fullscreen;
            info.height = _height;
            info.width = _width;
            info.title = _title;

            _window = kege::RenderWindow::create( info );
            _device = kege::Device::create();
            if ( !_device->init( _window ) )
            {
                return false;
            }

            _render_tagret = new kege::RenderWindowRenderTarget( _device->getRenderContext() );
            _renderer.init( _device->getRenderContext() );
            //kege::Channel::broadcast< const RenderWindow::Created&, const RenderWindow::Created& >( _window.ref() );
        }
        catch ( const std::runtime_error& err )
        {
            std::cout << err.what() <<"\n";
            return false;
        }
        return true;
    }

    kege::RenderWindow* Graphics::window()
    {
        return _window.ref();
    }

    kege::Renderer* Graphics::renderer()
    {
        return &_renderer;
    }

    void Graphics::uninit()
    {
        _render_tagret.clear();
        _renderer.uninit();
        _device.clear();
        _window.clear();
    }

    Graphics::~Graphics()
    {
        uninit();
    }

    Graphics::Graphics()
    {
        _width = 800;
        _height = 500;
        _fullscreen = false;
        _title = "KEGE";
    }

    kege::Ref< kege::Device > Graphics::_device;
}
