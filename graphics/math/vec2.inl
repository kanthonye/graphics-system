//
//  vec2.cpp
//  KEGE_VECTOR_MATH
//
//  Created by Kenneth A Esdaile on 4/9/20.
//  Copyright © 2020 Kenneth A Esdaile. All rights reserved.
//
namespace kege{
    
    template< typename T > const Vec2< T > Vec2< T >::xaxis(1,0);
    template< typename T > const Vec2< T > Vec2< T >::yaxis(0,1);
    template< typename T > const Vec2< T > Vec2< T >::zero(0,0);
    template< typename T > const Vec2< T > Vec2< T >::one(1,1);
    
    template< typename T > inline Vec2< T > abs2(const Vec2< T >& v)
    {
        return { kege::abs( v.a[ 0 ] ), kege::abs( v.a[ 1 ] ) };
    }

    template< typename T > inline Vec2< T > floor2(const Vec2< T >& v)
    {
        return {  ::floor( v.a[ 0 ] ), ::floor( v.a[ 1 ] ) };
    }

    template< typename T > inline Vec2< T > fract2(const Vec2< T >& v)
    {
        return {  fract( v.a[ 0 ] ), fract( v.a[ 1 ] ) };
    }

    /** inline function. compute the dot product of a vectors. */
    template< typename T > inline double dot(const Vec2< T > &a, const Vec2< T > &b)
    {
        return a & b;
    }
    
    /*! inline function. compute the cross prouduct of two vectors. */
    template< typename T > inline T cross2(const Vec2< T > &a, const Vec2< T > &b)
    {
        return ( a.y || b.z );
    }
    
    /** inline function. compute the distance between two Vec3tors. */
    template< typename T > inline double distsq (const Vec2< T > &a, const Vec2< T > &b)
    {
        return sq( a.a[ 0 ] - b.a[ 0 ] ) + sq( a.a[ 1 ] - b.a[ 1 ] );
    }

    /** inline function. compute the distance between two Vec3tors. */
    template< typename T > inline double distant(const Vec2< T > &a, const Vec2< T > &b)
    {
        return sqrt( distsq( a,b ) );
    }

    /** inline function. compute the math::square magnitude of a Vec3tors. */
    template< typename T > inline double magnsq (const Vec2< T >& v)
    {
        return v & v;
    }

    /** inline function. compute the magnitude of a Vec3tors. */
    template< typename T > inline T magn(const Vec2< T >& v)
    {
        return sqrt( v & v );
    }

    template< typename T > Vec2< T > normalize2(const Vec2< T > &a)
    {
        return a * kege::invrs( magn( a ) );
    }

    /** compute the scalar projection of one Vec3tors onto another */
    template< typename T > inline double scalar_proj(const Vec2< T > &a, const Vec2< T > &b)
    {
        return (a & b) * kege::invrs( magn(b) );
    }

    /** compute the Vec3tor projection of one Vec3tors onto another */
    template< typename T > inline Vec2< T > Vec3_proj2(const Vec2< T > &a, const Vec2< T > &b)
    {
        return a * (a & b) * kege::invrs( magn(b) );
    }

    /** linear interpolate between two Vec3tor resulting the mix between them */
    template<typename T> Vec2<T> mix2(const Vec2<T>& from, const Vec2<T>& to, double t)
    {
        return from * (1.0 - t) + to * t;
    }

    /** compute the center point given a certain number of points */
    template< typename T > Vec2< T > center(const Vec2< T >* a, const int size)
    {
        Vec2< T > sum(0.0f);
        for (int i=0; i<size; i++) sum += a[i];
        return sum * (1.0 / double(size));
    }
    
    /** compute the center point given a certain number of points */
    template< typename T > Vec2< T > center(const Vec2< T >& a, const Vec2< T >& b, const Vec2< T >& c)
    {
        return (a + b + c) / T(0x3);
    }
    
    template< typename T > std::ostream& operator <<( std::ostream& os, const Vec2< T >& v)
    {
        int w = 10;
        int p = 4;
        os << "{ " << std::setw(w) << std::setprecision( p ) << v[ 0 ] << ", " << std::setw(w) << std::setprecision( p ) << v[ 1 ] << " }\n";
        return os;
    }
}
