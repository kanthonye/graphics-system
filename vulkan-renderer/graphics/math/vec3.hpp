//
//  vec3.hpp
//  vector-math
//
//  Created by Kenneth A Esdaile on 6/6/18.
//  Copyright © 2018 Kenneth A Esdaile. All rights reserved.
//

#ifndef vec3_hpp
#define vec3_hpp
#include "vec2.hpp"
#include "coremath.hpp"
namespace kege{
    template <typename var> var divsafe(var val){ return (val == 0)? 1.0: val; }
    
    template<typename T > class Vec3 
    {
    public:
        
        template<typename S > friend inline Vec3< T > operator +(const Vec3< T >& a, const Vec3< S >& b)
        {
            return { T(a.a[0] + b.a[0]), T(a.a[1] + b.a[1]), T(a.a[2] + b.a[2]) };
        }
        template<typename S > friend inline Vec3< T > operator -(const Vec3< T >& a, const Vec3< S >& b)
        {
            return { T(a.a[0] - b.a[0]), T(a.a[1] - b.a[1]), T(a.a[2] - b.a[2]) };
        }
        template<typename S > friend inline Vec3< T > operator *(const Vec3< T >& a, const Vec3< S >& b)
        {
            return Vec3< T >( T(a.a[0] * b.a[0]) , T(a.a[1] * b.a[1]) , T(a.a[2] * b.a[2]) );
        }
        
        friend inline Vec3< T > operator +(double a, const Vec3< T >& b)
        {
            return Vec3< T >( a + b.a[0], a + b.a[1], a + b.a[2] );
        }
        friend inline Vec3< T > operator -(double a, const Vec3< T >& b)
        {
            return Vec3< T >( a - b.a[0], a - b.a[1], a - b.a[2] );
        }
        friend inline Vec3< T > operator *(double a, const Vec3< T >& b)
        {
            return Vec3< T >( a * b.a[0], a * b.a[1], a * b.a[2] );
        }
        
        friend inline Vec3< T > operator +(const Vec3< T >& v, double s)
        {
            return Vec3< T >( v.a[0] + s, v.a[1] + s, v.a[2] + s );
        }
        friend inline Vec3< T > operator -(const Vec3< T >& v, double s)
        {
            return Vec3< T >( v.a[0] - s, v.a[1] - s, v.a[2] - s );
        }
        friend inline Vec3< T > operator *(const Vec3< T >& v, double s)
        {
            return Vec3< T >( v.a[0] * s, v.a[1] * s, v.a[2] * s );
        }
        friend inline Vec3< T > operator /(const Vec3< T >& v, double s)
        {
            return Vec3< T >( v.a[0] / s, v.a[1] / s, v.a[2] / s );
        }
        
        inline Vec3< T > operator +(const Vec3< T >& b)const
        {
            return { a[0] + b.a[0], a[1] + b.a[1], a[2] + b.a[2] };
        }
        inline Vec3< T > operator -(const Vec3< T >& b)const
        {
            return { a[0] - b.a[0], a[1] - b.a[1], a[2] - b.a[2] };
        }
        inline Vec3< T > operator *(const Vec3< T >& b)const
        {
            return { a[0] * b.a[0], a[1] * b.a[1], a[2] * b.a[2] };
        }
        
        inline Vec3< T > operator / (const Vec3< T >& v)const
        {
            return Vec3< T >( a[0] / kege::divsafe(v.x), a[1] / kege::divsafe(v.y), a[2] / kege::divsafe(v.z));
        }
        
        /* cross product operator */
        inline Vec3< T > operator ||(const Vec3< T >& b)const
        {
            return 
            {
                a[1] * b.a[2] - a[2] * b.a[1], 
                a[2] * b.a[0] - a[0] * b.a[2], 
                a[0] * b.a[1] - a[1] * b.a[0]
            };
        }
        
        /* dot product operator */
        inline T operator &(const Vec3< T >& b)const
        {
            return a[0] * b.a[0] + a[1] * b.a[1] + a[2] * b.a[2];
        }
        
        inline const Vec3< T >& operator =(const Vec3< T >& b)
        {
            a[0] = b.a[0];
            a[1] = b.a[1];
            a[2] = b.a[2];
            return *this;
        }
        
        void operator += (const Vec3< T > &v)
        {
            a[ 0 ] += v.a[ 0 ];
            a[ 1 ] += v.a[ 1 ];
            a[ 2 ] += v.a[ 2 ];
        }
        
        void operator -= (const Vec3< T > &v)
        {
            a[ 0 ] -= v.a[ 0 ];
            a[ 1 ] -= v.a[ 1 ];
            a[ 2 ] -= v.a[ 2 ];
        }
        
        void operator *= (const Vec3< T > &v)
        {
            a[ 0 ] *= v.a[ 0 ];
            a[ 1 ] *= v.a[ 1 ];
            a[ 2 ] *= v.a[ 2 ];
        }
        
        inline void operator += ( T s )
        {
            a[ 0 ] += s;
            a[ 1 ] += s;
            a[ 2 ] += s;
        }
        inline void operator -= ( T s )
        {
            a[ 0 ] -= s;
            a[ 1 ] -= s;
            a[ 2 ] -= s;
        }
        inline void operator *= ( T s )
        {
            a[ 0 ] *= s;
            a[ 1 ] *= s;
            a[ 2 ] *= s;
        }
        inline void operator /= ( T s )
        {
            a[ 0 ] /= s;
            a[ 1 ] /= s;
            a[ 2 ] /= s;
        }
        
        void operator () ( T x, T y, T z, T w )
        {
            a[ 0 ] = x;
            a[ 1 ] = y;
            a[ 2 ] = z;
        }
        
        inline void operator ()( T s )
        { 
            a[ 2 ] = a[ 1 ] = a[ 0 ] = s;
        }

        inline const T& operator[](int n) const
        {
            return a[ n ];
        }

        inline T& operator[](int n)
        {
            return a[ n ];
        }

        inline const T* dptr() const
        {
            return a;
        }

        inline T* dptr()
        {
            return a;
        }

        /* conversion operator */
        template<typename S> inline operator Vec3<S>()const
        {
            return Vec3< S >( a[0], a[1], a[2] );
        }

        inline Vec3< T > operator -()const
        {
            return { -a[0], -a[1], -a[2] };
        }

        inline Vec2< T > xy()const
        {
            return { a[0], a[1] };
        }
        
        inline Vec2< T > yx()const
        {
            return { a[1], a[0] };
        }
        
        inline Vec3< T > xyz()const
        {
            return *this;
        }
        
        inline Vec3< T > xzy()const
        {
            return { a[0], a[2], a[1] };
        }
        
        inline Vec3< T > zyx()const
        {
            return { a[2], a[1], a[0] };
        }
        
        inline Vec3< T > yzx()const
        {
            return { a[1], a[2], a[0] };
        }
        
        inline Vec3< T > yxz()const
        {
            return { a[1], a[0], a[2] };
        }
        
        inline Vec3< T > zxy()const
        {
            return { a[2], a[0], a[1] };
        }

        Vec3( const Vec2< T >& v, T z )
        {
            a[ 0 ] = v.a[ 0 ];
            a[ 1 ] = v.a[ 1 ];
            a[ 2 ] = z;
        }
        Vec3( T x, T y, T z )
        {
            a[ 0 ] = x;
            a[ 1 ] = y;
            a[ 2 ] = z;
        }
        Vec3(T s)
        {
            a[ 2 ] = a[ 1 ] = a[ 0 ] = s;
        }
        Vec3(){}
        
        static const Vec3 zaxis;
        static const Vec3 xaxis;
        static const Vec3 yaxis;
        static const Vec3 zero;
        static const Vec3 one;

        union
        {
            struct{ T x,y,z; };
            T a[ 3 ];
        };
    };

    typedef Vec3< double > point3d;
    typedef Vec3< float  > point3f;
    typedef Vec3< int    > point3i;

    typedef Vec3< double > vec3d;
    typedef Vec3< float  > vec3f;
    typedef Vec3< int    > vec3i;

    typedef Vec3< double > dvec3;
    typedef Vec3< float  > fvec3;
    typedef Vec3< int    > ivec3;

    typedef Vec3< float  > point3;
    typedef Vec3< float  > vec3;

    template<typename T > template<typename S> Vec2< T >::Vec2( const Vec3<S>& v )
    {
        a[ 0 ] = v.x;
        a[ 1 ] = v.y;
    }
}

namespace kege
{    
    template< typename T > struct Col3
    {
        inline Col3& operator =(const T& k)
        {
            x = k;
            y = k;
            z = k;
            return *this;
        }
            
        Col3( T& a, T& b, T& c )
        :   x( a )
        ,   y( b )
        ,   z( c ) {}
        
        Col3( Vec3< T >& v )
        :   x( v.x )
        ,   y( v.y )
        ,   z( v.z ) {}
            
        T& x;
        T& y;
        T& z;
    };
    
    typedef Col3< double > col3d;
    typedef Col3< float  > col3f;
    typedef Col3< int    > col3i;
}
#include "vec3.inl"
#endif /* vec3_hpp */
