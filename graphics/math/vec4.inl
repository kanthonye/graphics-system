//
//  vec4.cpp
//  column-major
//
//  Created by Kenneth A Esdaile on 7/12/18.
//  Copyright © 2018 Kenneth A Esdaile. All rights reserved.
//
namespace kege{
    
    template<typename T > inline Vec4< T > max4(const Vec4< T >& a, T b)
    {
        return Vec4< T >( kege::max( a.a[0], b ), kege::max( a.a[1], b ), kege::max( a.a[2], b ), kege::max( a.a[3], b ) );
    }
    
    template<typename T > inline T dot(const Vec4< T >& a, const Vec4< T >& b)
    {
        return ( a.a[0] * b.a[0] + a.a[1] * b.a[1] + a.a[2] * b.a[2] + a.a[3] * b.a[3] );
    }
    
    template< typename T > inline Vec4< T > abs4(const Vec4< T >& v)
    {
        return { kege::abs( v.a[ 0 ] ), kege::abs( v.a[ 1 ] ), kege::abs( v.a[ 2 ] ), kege::abs( v.a[ 3 ] ) };
    }

    template< typename T > inline Vec4< T > floor4(const Vec4< T >& v)
    {
        return {  ::floor( v.a[ 0 ] ), ::floor( v.a[ 1 ] ), ::floor( v.a[ 2 ] ), ::floor( v.a[ 3 ] ) };
    }

    template< typename T > inline Vec4< T > fract4(const Vec4< T >& v)
    {
        return {  fract( v.a[ 0 ] ), fract( v.a[ 1 ] ), fract( v.a[ 2 ] ), fract( v.a[ 3 ] ) };
    }

    /** inline function. compute the distance between two Vec4tors. */
    template< typename T > inline double distsq (const Vec4< T > &a, const Vec4< T > &b)
    {
        return sq( a.a[ 0 ] - b.a[ 0 ] ) + sq( a.a[ 1 ] - b.a[ 1 ] ) + sq( a.a[ 2 ] - b.a[ 2 ] ) + sq( a.a[ 3 ] - b.a[ 3 ] );
    }

    /** inline function. compute the distance between two Vec4tors. */
    template< typename T > inline double distant(const Vec4< T > &a, const Vec4< T > &b)
    {
        return sqrt( distsq( a,b ) );
    }

    /** inline function. compute the math::square magnitude of a Vec4tors. */
    template< typename T > inline double magnsq(const Vec4< T >& v)
    {
        return v & v;
    }

    /** inline function. compute the magnitude of a Vec4tors. */
    template< typename T > inline T magn(const Vec4< T >& v)
    {
        return sqrt( v & v );
    }

    template< typename T > Vec4< T > normalize4(const Vec4< T > &a)
    {
        return a * kege::invrs( magn( a ) );
    }

    /** compute the scalar projection of one Vec4tors onto another */
    template< typename T > inline double scalar_proj(const Vec4< T > &a, const Vec4< T > &b)
    {
        return (a & b) * kege::invrs( magn(b) );
    }

    /** compute the Vec4tor projection of one Vec4tors onto another */
    template< typename T > inline Vec4< T > Vec4_proj4(const Vec4< T > &a, const Vec4< T > &b)
    {
        return a * (a & b) * kege::invrs( magn(b) );
    }

    /** linear interpolate between two Vec4tor resulting the mix between them */
    template<typename T> Vec4<T> mix4(const Vec4<T>& from, const Vec4<T>& to, double t)
    {
        return from * (1.0 - t) + to * t;
    }

    /** compute the normalize cross prouduct of two Vec4tors. */
    template< typename T > inline Vec4< T > orthonormal4(Vec4< T > const&B, Vec4< T > const&C)
    {
        return normalize( (B || C) );
    }

    /*! compute the face normal of triangle a,b,c. */
    template< typename T > inline Vec4< T > facenormal4(const Vec4< T > &a, const Vec4< T > &b, const Vec4< T > &c)
    {
        return orthonormal(b - a, c - a);
    }

    /** compute the center point given a certain number of points */
    template< typename T > Vec4< T > center4(const Vec4< T >* a, const int size)
    {
        Vec4< T > sum(0.0f);
        for (int i=0; i<size; i++) sum += a[i];
        return sum * (1.0 / double(size));
    }

    /** compute float Vec4tor color from integer inputs */
    template< typename T > inline Vec4< T > rgba(T red, T green, T blue, T alpha)
    {
        return Vec4< T >(double(red) * _1_DIV_255, double(green) * _1_DIV_255, double(blue) * _1_DIV_255, double(alpha) * _1_DIV_255);
    }

    /** convert hex to Vec4tor color */
    template< typename T > inline Vec4< T > hex_rgba(unsigned long n)
    {
        return Vec4< T >
        (  ((n >> 24) & 0xFF) * _1_DIV_255
         , ((n >> 16) & 0xFF) * _1_DIV_255
         , ((n >>  8) & 0xFF) * _1_DIV_255
         , ((n >>  0) & 0xFF) * _1_DIV_255  );
    }

    /** convert Vec4tor to hex color */
    template< typename T > inline unsigned long rgba_hex(Vec4< T > const& v)
    {
        return ((int(v.x*255) & 0xff) << 24) + ((int(v.y*255) & 0xff) << 16) + ((int(v.z*255) & 0xff) << 8) + ((int(v.x*255) & 0xff) << 0);
    }
    
    template< typename T > std::ostream& operator <<( std::ostream& os, const Vec4< T >& v)
    {
        int w = 10;
        int p = 4;
        os << "{ " << std::setw(w) << std::setprecision( p ) << v[ 0 ] << ", " << std::setw(w) << std::setprecision( p ) << v[ 1 ]; 
        os << ", " << std::setw(w) << std::setprecision( p ) << v[ 3 ] << ", " << std::setw(w) << std::setprecision( p ) << v[ 3 ] << " }\n";
        return os;
    }
}
