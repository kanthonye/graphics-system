//
//  Frustum.cpp
//  kege-rendering-engine
//
//  Created by Kenneth A Esdaile on 11/4/21.
//

#include "../math/math.hpp"


namespace kege
{
   void Frustum::MakePlane( typename Frustum::Plane& plane, const typename Frustum::Side& side, const kege::vec3& a, const kege::vec3& b, const kege::vec3& c, const kege::vec3& d )
    {
        plane._normal = normalize( cross( b - a, c - a ) );
        plane._center = (a + b + c + d) * 0.25;
        plane._distance = plane._normal.x*plane._center.x + plane._normal.y*plane._center.y + plane._normal.z*plane._center.z;
        plane._side = side;
    }

   Frustum::Frustum( const double near, const double far, const double fov, const double aspect_ratio, const kege::vec3& right, const kege::vec3& up, const kege::vec3& forward, const kege::vec3& position )
    {
        double angle = tanf( deg2rad( fov * 0.5 ) );
        double near_height = near * angle;
        double far_height  = far  * angle;
        double near_width  = near_height * aspect_ratio;
        double far_width   = far_height  * aspect_ratio;

        dvec3 near_centr = position - forward * near;
        dvec3 far_centr = position - forward * far;

        far_height = abs(far_height);
        far_width = abs(far_width);

        _vertices[ FTR ] = far_centr + right * far_width + up * far_height;
        _vertices[ FBR ] = far_centr + right * far_width - up * far_height;
        _vertices[ FTL ] = far_centr - right * far_width + up * far_height;
        _vertices[ FBL ] = far_centr - right * far_width - up * far_height;

        _vertices[ NTR ] = near_centr + right * near_width + up * near_height;
        _vertices[ NBR ] = near_centr + right * near_width - up * near_height;
        _vertices[ NTL ] = near_centr - right * near_width + up * near_height;
        _vertices[ NBL ] = near_centr - right * near_width - up * near_height;

        _eye = position;
        _forward = forward;
        _center = (far_centr + near_centr) * 0.5;
        _radius = kege::distant( _center, _vertices[ FTR ] );

        MakePlane( _planes[ Frustum::LEFT  ], Frustum::LEFT , _vertices[ FTL ], _vertices[ NTL ], _vertices[ FBL ], _vertices[ NBL ] );
        MakePlane( _planes[ Frustum::RIGHT ], Frustum::RIGHT, _vertices[ FTR ], _vertices[ FBR ], _vertices[ NTR ], _vertices[ NBR ] );
        MakePlane( _planes[ Frustum::BELOW ], Frustum::BELOW, _vertices[ FBL ], _vertices[ NBL ], _vertices[ FBR ], _vertices[ NBR ] );
        MakePlane( _planes[ Frustum::ABOVE ], Frustum::ABOVE, _vertices[ FTL ], _vertices[ FTR ], _vertices[ NTL ], _vertices[ NTR ] );
        MakePlane( _planes[ Frustum::FRONT ], Frustum::FRONT, _vertices[ FBL ], _vertices[ FTL ], _vertices[ FTR ], _vertices[ FBR ] );
        MakePlane( _planes[ Frustum::BACK  ], Frustum::BACK , _vertices[ NBL ], _vertices[ NBR ], _vertices[ NTR ],_vertices[ NTL ] );
    }

   double Frustum::Distance( const kege::vec3& point, const typename Frustum::Plane& plane )const
    {
        return kege::dot( plane._normal, point - plane._center );
    }
   int Frustum::TestSphere( const kege::vec3& center, const double radius )const
    {
        for ( int i=0; i<4; i++ )
        {
            if ( this->Distance( center, _planes[i] ) < -radius )
            {
                return 0;
            }
        }
        return 1;
    }

   int Frustum::TestRect( const kege::vec3& center, const double w, const double h, const double d )const
    {
        if( TestPoint( kege::point3( center.x-w, center.y-h, center.z-d ) ) ) return true;
        if( TestPoint( kege::point3( center.x-w, center.y-h, center.z+d ) ) ) return true;
        if( TestPoint( kege::point3( center.x-w, center.y+h, center.z-d ) ) ) return true;
        if( TestPoint( kege::point3( center.x-w, center.y+h, center.z+d ) ) ) return true;
        if( TestPoint( kege::point3( center.x+w, center.y-h, center.z-d ) ) ) return true;
        if( TestPoint( kege::point3( center.x+w, center.y-h, center.z+d ) ) ) return true;
        if( TestPoint( kege::point3( center.x+w, center.y+h, center.z-d ) ) ) return true;
        if( TestPoint( kege::point3( center.x+w, center.y+h, center.z+d ) ) ) return true;
        return false;
    }

   int Frustum::TestAABB( const kege::vec3& min, const kege::vec3& max )const
    {
        if( TestPoint( kege::point3( min.x, min.y, min.z ) ) ) return true;
        if( TestPoint( kege::point3( max.x, min.y, min.z ) ) ) return true;
        if( TestPoint( kege::point3( min.x, max.y, min.z ) ) ) return true;
        if( TestPoint( kege::point3( max.x, max.y, min.z ) ) ) return true;
        if( TestPoint( kege::point3( min.x, min.y, max.z ) ) ) return true;
        if( TestPoint( kege::point3( max.x, min.y, max.z ) ) ) return true;
        if( TestPoint( kege::point3( min.x, max.y, max.z ) ) ) return true;
        if( TestPoint( kege::point3( max.x, max.y, max.z ) ) ) return true;
        return false;
    }

   int Frustum::TestPoint( const kege::vec3& point )const
    {
        if( kege::dot( _planes[ 0 ]._normal, point ) - _planes[ 0 ]._distance < 0 ) return 0;
        if( kege::dot( _planes[ 1 ]._normal, point ) - _planes[ 1 ]._distance < 0 ) return 0;
        if( kege::dot( _planes[ 2 ]._normal, point ) - _planes[ 2 ]._distance < 0 ) return 0;
        if( kege::dot( _planes[ 3 ]._normal, point ) - _planes[ 3 ]._distance < 0 ) return 0;
        if( kege::dot( _planes[ 4 ]._normal, point ) - _planes[ 4 ]._distance < 0 ) return 0;
        if( kege::dot( _planes[ 5 ]._normal, point ) - _planes[ 5 ]._distance < 0 ) return 0;
        return 1;
    }

   const kege::vec3& Frustum::GetForwardVector()const
    {
        return _forward;
    }

   Frustum::Frustum()
    {}
}
