//
//  geometry.hpp
//  new-engine
//
//  Created by Kenneth Esdaile on 2/9/24.
//

#ifndef kege_graphics_geometry_hpp
#define kege_graphics_geometry_hpp

#include "../../../graphics/devices/interface/device.hpp"

namespace kege{

    class Geometry : public kege::RefCounter
    {
    public:
        virtual void draw( kege::ShaderProgram* program, kege::CommandBuffer* command_buffer, const kege::Ref< kege::DrawIndexedCommandBuffer >& drawbuffer )const{}
        virtual void draw( kege::ShaderProgram* program, kege::CommandBuffer* command_buffer, const kege::Ref< kege::DrawCommandBuffer >& drawbuffer )const{}
        virtual void draw( kege::ShaderProgram* program, kege::CommandBuffer* command_buffer, kege::DrawIndexedCommand& command )const{}
        virtual void draw( kege::ShaderProgram* program, kege::CommandBuffer* command_buffer, kege::DrawCommand& command )const{}
        virtual void draw( kege::ShaderProgram* program, kege::CommandBuffer* command_buffer )const{}
        virtual void bind( kege::ShaderProgram* program, kege::CommandBuffer* command_buffer )const{}
        virtual ~ Geometry(){}
    };

}

#endif /* kege_graphics_geometry_hpp */
