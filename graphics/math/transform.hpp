//
//  transform.hpp
//  KEGE
//
//  Created by Kenneth Esdaile on 9/2/23.
//

#ifndef KEGE_TRANSFORM_HPP
#define KEGE_TRANSFORM_HPP
#include "../math/vec3.hpp"
#include "../math/mat33.hpp"
#include "../math/mat44.hpp"
namespace kege
{
    struct transform
    {
        kege::fmat33 rotation = 1.0f;
        kege::fvec3  position = {0.f, 0.f, 0.f};
        kege::fvec3  scale = {1.f, 1.f, 1.f};
        kege::fvec3  up = {0.f, 1.f, 0.f};
    };

    inline kege::transform operator*( const kege::transform& a, const kege::transform& b )
    {
        return
        {
            a.rotation * b.rotation,
            a.position + a.rotation * ( a.scale * b.position ),
            a.scale * b.scale
        };
    }

    inline kege::vec3 operator*( const kege::transform& a, const kege::vec3& v )
    {
        return a.position + a.rotation * ( a.scale * v );
    }


    inline kege::mat44 buildModelMatrix( const kege::transform& t )
    {
        return kege::mat44
        (
            kege::vec4( t.scale[0] * t.rotation[0],  0.0f ),
            kege::vec4( t.scale[1] * t.rotation[1],  0.0f ),
            kege::vec4( t.scale[2] * t.rotation[2],  0.0f ),
            kege::vec4( t.scale    * t.position,     1.0f )
        );
    }
}
#endif /* KEGE_TRANSFORM_HPP */
