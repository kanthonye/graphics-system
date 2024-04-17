//
//  Frustum.hpp
//  kege-rendering-engine
//
//  Created by Kenneth A Esdaile on 11/4/21.
//

#ifndef Frustum_hpp
#define Frustum_hpp

#include "math.h"

namespace kege{
    
    class Frustum
    {
    public:
        
        enum Side{ LEFT, RIGHT, ABOVE, BELOW, FRONT, BACK, TOTAL };
        
        struct Plane
        {
            kege::vec3 _center;
            kege::vec3 _normal;
            double _distance;
            Side _side;
        };
        
    public:
            
        enum Point{ FTR, FBR, FTL, FBL, NTR, NBR, NTL, NBL };
        
        Frustum
        (
            const double near,
            const double far,
            const double fov,
            const double aspect_ratio,
            const kege::vec3& right,
            const kege::vec3& up,
            const kege::vec3& forward,
            const kege::vec3& position
        );
        
        
        void MakePlane
        (
            typename Frustum::Plane& plane,
            const typename Frustum::Side& side,
            const kege::vec3& a,
            const kege::vec3& b,
            const kege::vec3& c,
            const kege::vec3& d
        );
        
        double Distance( const kege::vec3& point, const Frustum::Plane& plane )const;
        int TestRect( const kege::vec3& center, const double w, const double h, const double d )const;
        int TestAABB( const kege::vec3& min, const kege::vec3& max )const;
        int TestSegment( const kege::vec3& a, const kege::vec3& b )const;
        int TestSphere( const kege::vec3& center, const double radius )const;
        int TestPoint( const kege::vec3& point )const;
        
        const kege::vec3& GetForwardVector()const;
        Frustum();
        
    private:
        
        kege::dvec3 _vertices[ 8 ];
        kege::point3d _center;
        kege::point3d _eye;
        kege::vec3 _forward;
        double _radius;
        
        Plane _planes[ 6 ];
    };
}
#endif /* Frustum_hpp */
