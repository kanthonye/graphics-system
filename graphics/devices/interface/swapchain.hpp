//
//  swapchain.hpp
//  new-engine
//
//  Created by Kenneth Esdaile on 1/6/24.
//

#ifndef kege_graphics_swapchain_hpp
#define kege_graphics_swapchain_hpp

#include "../../../graphics/devices/interface/framebuffer.hpp"

namespace kege{

    class Swapchain : public kege::RefCounter
    {
    public:

        virtual const kege::Framebuffer* getFramebuffer( uint32_t index )const = 0;
        virtual const kege::Framebuffer* getCurrentFramebuffer()const = 0;
        virtual uint32_t getCurrentFrameIndex()const = 0;
        virtual uint32_t getFramebufferCount()const = 0;
        virtual bool acquireNextImage() = 0;

        ~Swapchain();
        Swapchain();
    };

}

#endif /* kege_graphics_swapchain_hpp */
