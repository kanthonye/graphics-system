//
//  render-window.hpp
//  new-engine
//
//  Created by Kenneth Esdaile on 12/30/23.
//

#ifndef kege_graphics_render_window_hpp
#define kege_graphics_render_window_hpp

#include "../../../graphics/devices/interface/dependencies.hpp"

struct GLFWwindow;

namespace kege
{

    class RenderWindow : public kege::RefCounter
    {
    public:

        struct Created
        {
            Created(RenderWindow* w):window(w){}
            RenderWindow* window;
        };

        struct CreateInfo
        {
            uint16_t width;
            uint16_t height; 
            bool fullscreen;
            const char* title;
        };

        static RenderWindow* create( const CreateInfo& info );
        virtual GLFWwindow* handle() = 0;
        virtual bool isactive()const = 0;
        virtual void pollEvents() = 0;

    protected:

        RenderWindow& operator =( const kege::RenderWindow& other ) = delete;
        RenderWindow( const kege::RenderWindow& other ){}
        virtual ~RenderWindow(){}
        RenderWindow(){}

    private:

        friend kege::Ref< kege::RenderWindow >;
    };

}


#endif /* kege_graphics_render_window_hpp */
