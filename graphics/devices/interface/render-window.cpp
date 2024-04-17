//
//  render-window.cpp
//  new-engine
//
//  Created by Kenneth Esdaile on 12/30/23.
//

#include "../../../graphics/initializer/graphics.hpp"

#include "GLFW/glfw3.h"

namespace kege{namespace vk{

    class RenderWindow : public kege::RenderWindow
    {
    public:

        RenderWindow( const CreateInfo& info );

        GLFWwindow* handle();

        bool isactive()const;
        void pollEvents();

        ~RenderWindow();

    private:

        GLFWwindow* _window;
    };

    RenderWindow::RenderWindow( const CreateInfo& info )
    {
        if ( !glfwInit() ) // init glfw
        {
            throw std::runtime_error( "failed to initialize GLFW!" );
        }

        /* GLFW was originally designed to create an OpenGL context, we need
         to tell it to not create an OpenGL context with GLFW_NO_API */
        glfwWindowHint( GLFW_CLIENT_API, GLFW_NO_API );

        _window = glfwCreateWindow( info.width, info.height, info.title, nullptr, nullptr);
        //glfwMakeContextCurrent( _window );
    }

    GLFWwindow* RenderWindow::handle()
    {
        return _window;
    }

    bool RenderWindow::isactive()const
    {
        return !glfwWindowShouldClose( _window );
    }

    void RenderWindow::pollEvents()
    {
        glfwPollEvents();
    }


    RenderWindow::~RenderWindow()
    {
        if( _window )
        {
            glfwDestroyWindow( _window );
            _window = nullptr;
        }
        glfwTerminate();
    }
}}


namespace kege
{
    RenderWindow* RenderWindow::create( const CreateInfo& info )
    {
        return new vk::RenderWindow( info );
    }
}


