//
//  mat33.cpp
//  vector-math
//
//  Created by Kenneth A Esdaile on 6/6/18.
//  Copyright © 2018 Kenneth A Esdaile. All rights reserved.
//

#include "mat33.hpp"
namespace kege{
    
    template< typename T >  T trace (const Mat33< T >& m)
    {
        return ( m[ 0 ][ 0 ] + m[ 1 ][ 1 ] + m[ 2 ][ 2 ] );
    }
    
    template< typename T >  Mat33< T > transpose (const Mat33< T > &m)
    {
        return Mat33< T >
        (  m[ 0 ].x, m[ 1 ].x, m[ 2 ].x
         , m[ 0 ].y, m[ 1 ].y, m[ 2 ].y
         , m[ 0 ].z, m[ 1 ].z, m[ 2 ].z );
    }
    
    template< typename T >  Mat33< T > translate(T x, T y)
    {
        return Mat33< T >
        (  1.0f, 0.0f, x
         , 0.0f, 1.0f, y
         , x   , y   , 1.0f  );
    }
    
    template< typename T >  Mat33< T > translate (const Vec2< T >& v)
    {
        return translate< T >( v.x, v.y );
    }
    
    template< typename T >  Mat33< T > diagonal(const T& x, const T& y, const T& z)
    {
        return Mat33< T >
        (  x   , 0.0f, 0.0f
         , 0.0f, y   , 0.0f
         , 0.0f, 0.0f, z);
    }
    
    template< typename T >  Mat33< T > scale (T x, T y)
    {
        return Mat33< T >
        (  x   , 0.0f, 0.0f
         , 0.0f, y   , 0.0f
         , 0.0f, 0.0f, 1.0f);
    }
    
    template< typename T >  Mat33< T > scale (const Vec2< T >& v)
    {
        return Mat33< T >
        (  v.x , 0.0f, 0.0f
         , 0.0f, v.y , 0.0f
         , 0.0f, 0.0f, 1.0f);
    }
    
    template< typename T >  Mat33< T > reflectY (T x, T y)
    {
        return Mat33< T >
        ( -1.0f, 0.0f, 0.0
         , 0.0f, 1.0f, 0.0
         , x   , y   , 1.0f);
    }
    
    template< typename T >  Mat33< T > reflectY (const Vec2< T > v)
    {
        return reflectY< T >( v.x, v.y );
    }
    
    template< typename T >  Mat33< T > reflectX (T x, T y)
    {
        return Mat33< T >
        ( -1.0f, 0.0f, 0.0
         , 0.0f, 1.0f, 0.0
         , x   , y   , 1.0f);
    }
    
    template< typename T >  Mat33< T > reflectX (const Vec2< T >& v)
    {
        return Mat33< T >
        ( -1.0f, 0.0f, 0.0
         , 0.0f, 1.0f, 0.0
         , v.x , v.y , 1.0f);
    }
    
    template< typename T >  Mat33< T > rotm33X (T DEG)
    {
        float s = sin( deg2rad(DEG) );
        float c = cos( deg2rad(DEG) );
        return Mat33< T >
        (  1.0f, 0.0f, 0.0f
         , 0.0f,  c  ,-s
         , 0.0f,  s  , c  );
    }
    
    template< typename T >  Mat33< T > rotm33Y (T DEG)
    {
        float s = sin( deg2rad(DEG) );
        float c = cos( deg2rad(DEG) );
        return Mat33< T >
        (  c    , 0.0f , s
         , 0.0f , 1.0f , 0.0f
         ,-s    , 0.0f , c  );
    }
    
    /*
     0x 0y 0z
     1x 1y 1z
     2x 2y 2z
     */
    template< typename T >  Mat33< T > rotm33Z (T DEG)
    {
        float s = sin( deg2rad(DEG) );
        float c = cos( deg2rad(DEG) );
        return Mat33< T >
        (   c  , -s  , 0.0f
         ,  s  ,  c  , 0.0f
         , 0.0f, 0.0f, 1.0f);
    }
    
    /*! @brief Determinant of 3x3 matrix */
    template< typename T >  double det (const Mat33< T >& m)
    {
        return (m[ 0 ][ 2 ] * (m[ 1 ][ 0 ] * m[ 2 ][ 1 ] - m[ 1 ][ 1 ] * m[ 2 ][ 0 ]) -
                m[ 1 ][ 2 ] * (m[ 0 ][ 0 ] * m[ 2 ][ 1 ] - m[ 0 ][ 1 ] * m[ 2 ][ 0 ]) +
                m[ 2 ][ 2 ] * (m[ 0 ][ 0 ] * m[ 1 ][ 1 ] - m[ 0 ][ 1 ] * m[ 1 ][ 0 ]));
    }
    
    template< typename T >  Mat33< T > adj (const Mat33< T >& m)
    {
        return Mat33< T >
        (  (m[ 1 ][ 1 ] * m[ 2 ][ 2 ] - m[ 1 ][ 2 ] * m[ 2 ][ 1 ])
         ,-(m[ 1 ][ 0 ] * m[ 2 ][ 2 ] - m[ 1 ][ 2 ] * m[ 2 ][ 0 ])
         , (m[ 1 ][ 0 ] * m[ 2 ][ 1 ] - m[ 1 ][ 1 ] * m[ 2 ][ 0 ])
         
         ,-(m[ 0 ][ 1 ] * m[ 2 ][ 2 ] - m[ 0 ][ 2 ] * m[ 2 ][ 1 ])
         , (m[ 0 ][ 0 ] * m[ 2 ][ 2 ] - m[ 0 ][ 2 ] * m[ 2 ][ 0 ])
         ,-(m[ 0 ][ 0 ] * m[ 2 ][ 1 ] - m[ 0 ][ 1 ] * m[ 2 ][ 0 ])
         
         , (m[ 0 ][ 1 ] * m[ 1 ][ 2 ] - m[ 0 ][ 2 ] * m[ 1 ][ 1 ])
         ,-(m[ 0 ][ 0 ] * m[ 1 ][ 2 ] - m[ 0 ][ 2 ] * m[ 1 ][ 0 ])
         , (m[ 0 ][ 0 ] * m[ 1 ][ 1 ] - m[ 0 ][ 1 ] * m[ 1 ][ 0 ])  );
    }
    
    template< typename T >  Mat33< T > inverse(const Mat33< T >& m)
    {
        return adj(m) * invrs( det(m) );
    }
    
    
    template< typename T >  Mat33< T > m33LookAt(const Vec3< T >& from, const Vec3< T >& to, const Vec3< T >& up) 
    { 
        Vec3< T > f = normalize( from - to ); 
        Vec3< T > r = cross( normalize(up), f); 
        Vec3< T > u = cross( f, r ); 
        return Mat33< T >( r, u, f );
    } 
}
