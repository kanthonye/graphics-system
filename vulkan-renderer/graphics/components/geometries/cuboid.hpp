//
//  cuboid.hpp
//  new-engine
//
//  Created by Kenneth Esdaile on 2/18/24.
//

#ifndef kege_graphics_cuboid_hpp
#define kege_graphics_cuboid_hpp

#include "mesh.hpp"

namespace kege
{
    class Cuboid : public kege::IndexedMesh
    {
        public: Cuboid( const kege::vec3& center, const kege::vec3& lengths );
    };

}

#endif /* kege_graphics_cuboid_hpp */
