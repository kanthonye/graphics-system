//
//  vec3.inl
//  GeoMipMapTerrain
//
//  Created by Kenneth A Esdaile on 4/6/20.
//  Copyright © 2020 Kenneth A Esdaile. All rights reserved.
//

#ifndef vec3_inl
#define vec3_inl
namespace kege{
    
    template< typename T > const Vec3< T > Vec3< T >::zaxis(0,0,1);
    template< typename T > const Vec3< T > Vec3< T >::xaxis(1,0,0);
    template< typename T > const Vec3< T > Vec3< T >::yaxis(0,1,0);
    template< typename T > const Vec3< T > Vec3< T >::zero(0,0,0);
    template< typename T > const Vec3< T > Vec3< T >::one(1,1,1);
    
    template< typename T > inline Vec3< T > abs3(const Vec3< T >& v)
    {
        return { kege::abs( v.a[ 0 ] ), kege::abs( v.a[ 1 ] ), kege::abs( v.a[ 2 ] ) };
    }

    template< typename T > inline Vec3< T > floor3(const Vec3< T >& v)
    {
        return {  ::floor( v.a[ 0 ] ), ::floor( v.a[ 1 ] ), ::floor( v.a[ 2 ] ) };
    }

    template< typename T > inline Vec3< T > fract3(const Vec3< T >& v)
    {
        return {  fract( v.a[ 0 ] ), fract( v.a[ 1 ] ), fract( v.a[ 2 ] ) };
    }

    /** inline function. compute the dot product of a vectors. */
    template< typename T > inline T dot(const Vec3< T > &a, const Vec3< T > &b)
    {
        return a & b;
    }
    
    /*! inline function. compute the cross prouduct of two vectors. */
    template< typename T > inline Vec3< T > cross(const Vec3< T > &a, const Vec3< T > &b)
    {
        return ( a || b );
    }
    
    /** inline function. compute the distance between two Vec3tors. */
    template< typename T > inline double distsq (const Vec3< T > &a, const Vec3< T > &b)
    {
        return sq( a.a[ 0 ] - b.a[ 0 ] ) + sq( a.a[ 1 ] - b.a[ 1 ] ) + sq( a.a[ 2 ] - b.a[ 2 ] );
    }

    /** inline function. compute the distance between two Vec3tors. */
    template< typename T > inline double distant(const Vec3< T > &a, const Vec3< T > &b)
    {
        return sqrt( distsq( a,b ) );
    }

    /** inline function. compute the math::square magnitude of a Vec3tors. */
    template< typename T > inline double magnsq (const Vec3< T >& v)
    {
        return v & v;
    }

    /** inline function. compute the magnitude of a Vec3tors. */
    template< typename T > inline T magn(const Vec3< T >& v)
    {
        return sqrt( v & v );
    }

    template< typename T > Vec3< T > normalize(const Vec3< T > &a)
    {
        return a * kege::invrs( magn( a ) );
    }

    /** compute the scalar projection of one Vec3tors onto another */
    template< typename T > inline double scalar_proj(const Vec3< T > &a, const Vec3< T > &b)
    {
        return (a & b) * kege::invrs( magn(b) );
    }

    /** compute the Vec3tor projection of one Vec3tors onto another */
    template< typename T > inline Vec3< T > Vec3_proj3(const Vec3< T > &a, const Vec3< T > &b)
    {
        return a * (a & b) * kege::invrs( magn(b) );
    }

    /** linear interpolate between two Vec3tor resulting the mix between them */
    template<typename T> Vec3<T> mix4(const Vec3<T>& from, const Vec3<T>& to, double t)
    {
        return from * (1.0 - t) + to * t;
    }

    /** compute the normalize cross prouduct of two Vec3tors. */
    template< typename T > inline Vec3< T > orthonormal(Vec3< T > const& B, Vec3< T > const& C)
    {
        return normalize( (B || C) );
    }

    /*! compute the face normal of triangle a,b,c. */
    template< typename T > inline Vec3< T > facenormal(const Vec3< T > &a, const Vec3< T > &b, const Vec3< T > &c)
    {
        return orthonormal(b - a, c - a);
    }

    /** compute the center point given a certain number of points */
    template< typename T > Vec3< T > center(const Vec3< T >* a, const int size)
    {
        Vec3< T > sum(0.0f);
        for (int i=0; i<size; i++) sum += a[i];
        return sum * (1.0 / double(size));
    }
    
    /** compute the center point given a certain number of points */
    template< typename T > Vec3< T > center(const Vec3< T >& a, const Vec3< T >& b, const Vec3< T >& c)
    {
        return (a + b + c) / T(0x3);
    }
    
    /** compute float Vec3tor color from integer inputs */
    inline vec3f rgb(unsigned red, unsigned green, unsigned blue)
    {
        return vec3f(double(red) * _1_DIV_255, double(green) * _1_DIV_255, double(blue) * _1_DIV_255);
    }

    /** convert hex to Vec3tor color */
    inline vec3f hex_rgb(unsigned int n)
    {
        return vec3f
        (  ((n >> 16) & 0xFF) * _1_DIV_255
         , ((n >>  8) & 0xFF) * _1_DIV_255
         , ((n >>  0) & 0xFF) * _1_DIV_255  );
    }

    /** convert Vec3tor to hex color */
    template< typename T > inline unsigned int rgb_hex(Vec3< T > const& v)
    {
        return ((int(v.y*255) & 0xff) << 16) + ((int(v.z*255) & 0xff) << 8) + ((int(v.x*255) & 0xff) << 0);
    }
    
    template< typename T > std::ostream& operator <<( std::ostream& os, const Vec3< T >& v)
    {
        int w = 10;
        int p = 4;
        os << "{ " << std::setw(w) << std::setprecision( p ) << v[ 0 ] << ", " << std::setw(w) << std::setprecision( p ) << v[ 1 ]; 
        os << ", " << std::setw(w) << std::setprecision( p ) << v[ 2 ] << " }\n";
        return os;
    }
//    template< typename T > inline Vec3< T > abs3(const Vec3< T >& a)
//    {
//        return Vec3< T >(abs(a.x), abs(a.y), abs(a.z));
//    }
//    
//    template< typename T > inline Vec3< T > floor3(const Vec3< T >& v)
//    {
//        return Vec3< T >(::floor(v.x), ::floor(v.y), ::floor(v.z));
//    }
//    
//    template< typename T > inline Vec3< T > fract3(const Vec3< T >& v)
//    {
//        return Vec3< T >(fract(v.x), fract(v.y), fract(v.z));
//    }
//    
//    
//    /** inline function. compute the math::square magnitude of a vectors. */
//    template< typename T > inline double magnsq (const Vec3< T >& v)
//    {
//        return dot(v,v);
//    }
//    
//    /** inline function. compute the magnitude of a vectors. */
//    template< typename T > inline double magn(const Vec3< T >& v)
//    {
//        return sqrt(dot(v,v));
//    }
//    
//    template< typename T > inline Vec3< T > normalize(const Vec3< T > &a)
//    {
//        return a * invrs( magn(a) );
//    }
//    
    
//    
//    /*! inline function. compute the cross prouduct of two vectors. */
//    template< typename T > inline double triple_product (const Vec3< T > &a, const Vec3< T > &b, const Vec3< T > &c)
//    {
//        return dot( a, cross ( b,c ) );
//    }
//    
//    /** inline function. compute the cross prouduct of two vectors. */
//    template< typename T > inline Vec3< T > cross(const Vec3< T > &v, real x, real y, real z)
//    {
//        return cross(v, Vec3< T >(x,y,z));
//    }
//    
//    /** inline function. compute the cross prouduct of two vectors. */
//    template< typename T > inline Vec3< T > cross(real x, real y, real z, const Vec3< T > &v)
//    {
//        return cross( Vec3< T >(x,y,z), v);
//    }
//    
//    /** inline function. compute the distance between two vectors. */
//    template< typename T > inline double distant_sq (const Vec3< T > &a, const Vec3< T > &b)
//    {
//        return sq(a.x-b.x) + sq(a.y-b.y) + sq(a.z-b.z);
//    }
//    
//    /** inline function. compute the distance between two vectors. */
//    template< typename T > inline double distant (const Vec3< T > &a, const Vec3< T > &b)
//    {
//        return sqrt( distant_sq(a, b) );
//    }
//    
//    /** inline function. compute the projection of one vectors onto another, return it magnitude. */
//    template< typename T > inline double scalar_proj(const Vec3< T > &a, const Vec3< T > &b)
//    {
//        return dot(a,b) * invrs( magn(b) );
//    }
//    
//    template< typename T > inline Vec3< T > vec_proj(const Vec3< T > &a, const Vec3< T > &b)
//    {
//        return a * dot(a,b) * invrs( magn(b) );
//    }
//    
//    /*! compute the cross prouduct of two vectors, then normalize it. */
//    template< typename T > inline Vec3< T > orthonormal(Vec3< T > const&B, Vec3< T > const&C)
//    {
//        return normalize( cross(B, C) );
//    }
//    
//    /*! compute the face normal of triangle a,b,c. */
//    template< typename T > inline Vec3< T > face_normal(const Vec3< T > &a, const Vec3< T > &b, const Vec3< T > &c)
//    {
//        return cross(b - a, c - a);
//    }
//    
//    template< typename T > inline Vec3< T > face_orthonormal(const Vec3< T > &a, const Vec3< T > &b, const Vec3< T > &c)
//    {
//        return orthonormal(b - a, c - a);
//    }
//    
//    /*! calculate the radian between two vector, and return the angle in radian. */
//    template< typename T > inline real radian(const Vec3< T > &a, const Vec3< T > &b)
//    {
//        return acos(dot(a,b) * invrs(magn(a) * magn(b)));
//    }
//    
//    /*! calculate the angle between two vector, and return the angle in angle. */
//    template< typename T > inline real angle(const Vec3< T > &a, const Vec3< T > &b)
//    {
//        return rad2deg( radian(a,b) );
//    }
//    
//    /*! compute the angle between a vectors and the zx-plane. */
//    template< typename T > inline float radian(const Vec3< T > &a)
//    {
//        return radian(a, Vec3< T >(a.x, 0.0f, a.z));
//    }
//    
//    /*! compute the angle between a vectors and the zx-plane. */
//    template< typename T > inline float angle(const Vec3< T > &a)
//    {
//        return rad2deg( radian(a) );
//    }
//    
//    /*! compute the false length of a vector : but very fast */
//    template< typename T > inline double psuedo_length(const Vec3< T > &a)
//    {
//        return abs(a.x) + abs(a.y) + abs(a.z);
//    }
//    
//    inline Vec3< float > rgb(unsigned red, unsigned green, unsigned blue)
//    {
//        return Vec3< float >(real(red) * _1_DIV_255, real(green) * _1_DIV_255, real(blue) * _1_DIV_255);
//    }
//    
//    inline Vec3< float > hex2rgb(unsigned int n)
//    {
//        return Vec3< float >(((n >> 16) & 0xFF)*_1_DIV_255, ((n >> 8) & 0xFF)*_1_DIV_255, ((n >>  0) & 0xFF)*_1_DIV_255);
//    }
//    
//    template< typename T > inline unsigned int rgb2hex(Vec3< T > const& v)
//    {
//        return ((int(v.x*255) & 0xff) << 24) + ((int(v.y*255) & 0xff) << 16) + ((int(v.z*255) & 0xff) << 8);
//    }
//    
//    inline Vec3< float > color(short r,short g,short b)
//    {
//        return Vec3< float >(float(r*_1_DIV_255), float(g*_1_DIV_255), float(b*_1_DIV_255));
//    }
//    
//    template< typename T > Vec3< T > center(const Vec3< T > *a, const int size)
//    {
//        Vec3< T > res(0.0f);
//        for (int i=0; i<size; i++) res += a[i];
//        return res * invrs(size);
//    }
//    
//    template< typename T > void calc_dir_vecs(Vec3< T >& forward, Vec3< T >& right, Vec3< T >& up, const float x, const float y)
//    {
//        float cosPitch = cos(deg2rad(x));
//        float sinPitch = sin(deg2rad(x));
//        float cosYaw = cos(deg2rad(y));
//        float sinYaw = sin(deg2rad(y));
//        
//        forward( sinYaw * cosPitch, -sinPitch, cosPitch * cosYaw );
//        up( sinYaw * sinPitch, cosPitch, cosYaw * sinPitch );
//        right( cosYaw, 0, -sinYaw );
//    }
//    
//    
//    template< typename T > std::ostream& operator <<( std::ostream& os, const Vec3< T >& q)
//    {
//        return (os <<"{ " << q.x <<", " << q.y <<", " << q.z << " }");
//    }
//    
//    template<typename T> Vec3<T> mix(const Vec3<T>& from, const Vec3<T>& to, float t)
//    {
//        return from * (1.0f - t) + to * t;
//    }
    
}
#endif /* vec3_inl */
