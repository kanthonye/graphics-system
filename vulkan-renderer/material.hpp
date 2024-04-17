//
//  material.hpp
//  new-engine
//
//  Created by Kenneth Esdaile on 2/9/24.
//

#ifndef kege_graphics_material_hpp
#define kege_graphics_material_hpp

#include "graphics.hpp"

namespace kege{

    class MaterialProperty : public kege::RefCounter
    {
    public:

        virtual ~ MaterialProperty(){}
        kege::Ref< ShaderProgram > _program;
    };

    class Material : public kege::RefCounter
    {
    public:
        Material(const std::vector< kege::Ref< MaterialProperty > >& properties): _properties(properties){}
        virtual ~ Material(){}

        std::vector< kege::Ref< MaterialProperty > > _properties;
    };


}



namespace std {

    template<> struct hash< kege::Ref< kege::Material > >
    {
        std::size_t operator()(const kege::Ref< kege::Material >& material) const {
            return reinterpret_cast< int64_t >( material.ref() );
        }
    };
}
#endif /* kege_graphics_material_hpp */
