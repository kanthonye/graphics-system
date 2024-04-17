//
//  vec4.hpp
//
//  Created by Kenneth A Esdaile on 7/12/18.
//  Copyright © 2018 Kenneth A Esdaile. All rights reserved.
//

#ifndef VEC4_hpp
#define VEC4_hpp
#include "vec3.hpp"
namespace kege
{    
    template<typename T > class Vec4 
    {
    public:

        template<typename S > friend inline Vec4< T > operator +(const Vec4< T >& a, const Vec4< S >& b)
        {
            return Vec4< T >( a.a[0] + b.a[0], a.a[1] + b.a[1], a.a[2] + b.a[2], a.a[3] + b.a[3] );
        }
        template<typename S > friend inline Vec4< T > operator -(const Vec4< T >& a, const Vec4< S >& b)
        {
            return Vec4< T >( a.a[0] - b.a[0], a.a[1] - b.a[1], a.a[2] - b.a[2], a.a[3] - b.a[3] );
        }
        template<typename S > friend inline Vec4< T > operator *(const Vec4< T >& a, const Vec4< S >& b)
        {
            return Vec4< T >( a.a[0] * b.a[0] , a.a[1] * b.a[1] , a.a[2] * b.a[2] , a.a[3] * b.a[3] );
        }
        
        friend inline Vec4< T > operator +(double a, const Vec4< T >& b)
        {
            return { a + b.a[0], a + b.a[1], a + b.a[2], a + b.a[3] };
        }
        friend inline Vec4< T > operator -(double a, const Vec4< T >& b)
        {
            return Vec4< T >( a - b.a[0], a - b.a[1], a - b.a[2], a - b.a[3] );
        }
        friend inline Vec4< T > operator *(double a, const Vec4< T >& b)
        {
            return Vec4< T >( a * b.a[0], a * b.a[1], a * b.a[2], a * b.a[3] );
        }
        
        friend inline Vec4< T > operator +(const Vec4< T >& v, double s)
        {
            return Vec4< T >( v.a[0] + s, v.a[1] + s, v.a[2] + s, v.a[3] + s );
        }
        friend inline Vec4< T > operator -(const Vec4< T >& v, double s)
        {
            return Vec4< T >( v.a[0] - s, v.a[1] - s, v.a[2] - s, v.a[3] - s );
        }
        friend inline Vec4< T > operator *(const Vec4< T >& v, double s)
        {
            return Vec4< T >( v.a[0] * s, v.a[1] * s, v.a[2] * s, v.a[3] * s );
        }
        friend inline Vec4< T > operator /(const Vec4< T >& v, double s)
        {
            return Vec4< T >( v.a[0] / s, v.a[1] / s, v.a[2] / s, v.a[3] / s );
        }
        
        inline Vec4< T > operator +(const Vec4< T >& b)const
        {
            return Vec4< T >( a[0] + b.a[0], a[1] + b.a[1], a[2] + b.a[2], a[3] + b.a[3] );
        }
        inline Vec4< T > operator -(const Vec4< T >& b)const
        {
            return Vec4< T >( a[0] - b.a[0], a[1] - b.a[1], a[2] - b.a[2], a[3] - b.a[3] );
        }
        inline Vec4< T > operator *(const Vec4< T >& b)const
        {
            return Vec4< T >( a[0] * b.a[0], a[1] * b.a[1], a[2] * b.a[2], a[3] * b.a[3] );
        }
        
        /* cross product operator */
        inline Vec4< T > operator ||(const Vec4< T >& b)const
        {
            return 
            {
                a[1] * b.a[2] - a[2] * b.a[1], 
                a[2] * b.a[0] - a[0] * b.a[2], 
                a[0] * b.a[1] - a[1] * b.a[0],
                0.0
            };
        }
        
        /* dot product operator */
        inline T operator &(const Vec4< T >& b)const
        {
            return a[0] * b.a[0] + a[1] * b.a[1] + a[2] * b.a[2] + a[3] * b.a[3];
        }
        
        inline const Vec4< T >& operator =(const Vec4< T >& b)
        {
            a[0] = b.a[0];
            a[1] = b.a[1];
            a[2] = b.a[2];
            a[3] = b.a[3];
            return *this;
        }
        
        void operator += (const Vec4< T > &v)
        {
            a[ 0 ] += v.a[ 0 ];
            a[ 1 ] += v.a[ 1 ];
            a[ 2 ] += v.a[ 2 ];
            a[ 3 ] += v.a[ 3 ];
        }
        
        void operator -= (const Vec4< T > &v)
        {
            a[ 0 ] -= v.a[ 0 ];
            a[ 1 ] -= v.a[ 1 ];
            a[ 2 ] -= v.a[ 2 ];
            a[ 3 ] -= v.a[ 3 ];
        }
        
        void operator *= (const Vec4< T > &v)
        {
            a[ 0 ] *= v.a[ 0 ];
            a[ 1 ] *= v.a[ 1 ];
            a[ 2 ] *= v.a[ 2 ];
            a[ 3 ] *= v.a[ 3 ];
        }
        
        inline void operator += ( T s )
        {
            a[ 0 ] += s;
            a[ 1 ] += s;
            a[ 2 ] += s;
            a[ 3 ] += s;
        }
        inline void operator -= ( T s )
        {
            a[ 0 ] -= s;
            a[ 1 ] -= s;
            a[ 2 ] -= s;
            a[ 3 ] -= s;
        }
        inline void operator *= ( T s )
        {
            a[ 0 ] *= s;
            a[ 1 ] *= s;
            a[ 2 ] *= s;
            a[ 3 ] *= s;
        }
        inline void operator /= ( T s )
        {
            a[ 0 ] /= s;
            a[ 1 ] /= s;
            a[ 2 ] /= s;
            a[ 3 ] /= s;
        }
        
        void operator () ( const Vec3< T >& v, T w )
        {
            a[ 0 ] = v.x;
            a[ 1 ] = v.y;
            a[ 2 ] = v.z;
            a[ 3 ] = w;
        }
        
        void operator () ( T x, T y, T z, T w )
        {
            a[ 0 ] = x;
            a[ 1 ] = y;
            a[ 2 ] = z;
            a[ 3 ] = w;
        }
        
        inline void operator ()( T val )
        {
            a[ 0 ] = a[ 1 ] = a[ 2 ] = a[ 3 ] = val;
        }
        inline Vec4< T > operator -()const
        {
            return { -a[0], -a[1], -a[2], -a[3] };
        }
        
        inline const T& operator[](const int n) const
        {
            return a[ n ];
        }
        inline T& operator[](const int n)
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
        template<typename S> inline operator Vec4<S>()const
        {
            return Vec4< S >( a[ 0 ], a[ 1 ], a[ 2 ], a[ 3 ] );
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
            return { a[0], a[1], a[2] };
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



        inline Vec4< T > wxyz()const
        {
            return { a[3], a[0], a[2], a[1] };
        }
        inline Vec4< T > xwyz()const
        {
            return { a[0], a[3], a[2], a[1] };
        }
        inline Vec4< T > xywz()const
        {
            return { a[0], a[2], a[3], a[1] };
        }

        inline Vec4< T > yxzw()const
        {
            return { a[2], a[0], a[3], a[1] };
        }
        inline Vec4< T > yzxw()const
        {
            return { a[2], a[3], a[0], a[1] };
        }
        inline Vec4< T > yzwx()const
        {
            return { a[2], a[3], a[1], a[0] };
        }


        inline Vec4< T > zxyw()const
        {
            return { a[2], a[0], a[1], a[3] };
        }
        inline Vec4< T > xzyw()const
        {
            return { a[0], a[2], a[1], a[3] };
        }

        inline Vec4< T > yxwz()const
        {
            return { a[1], a[0], a[3], a[2] };
        }
        inline Vec4< T > ywxz()const
        {
            return { a[1], a[3], a[0], a[2] };
        }
        inline Vec4< T > ywzx()const
        {
            return { a[1], a[3], a[2], a[0] };
        }
        inline Vec4< T > xzwy()const
        {
            return { a[0], a[2], a[3], a[1] };
        }
        inline Vec4< T > wzyx()const
        {
            return { a[3], a[2], a[1], a[0] };
        }

        Vec4( const Vec3< T >& v, T w )
        {
            a[ 0 ] = v.x;
            a[ 1 ] = v.y;
            a[ 2 ] = v.z;
            a[ 3 ] = w;
        }
        Vec4( const Vec3< T >& v )
        {
            a[ 0 ] = v.x;
            a[ 1 ] = v.y;
            a[ 2 ] = v.z;
        }
        Vec4( T x, T y, T z, T w )
        {
            a[ 0 ] = x;
            a[ 1 ] = y;
            a[ 2 ] = z;
            a[ 3 ] = w;
        }
        Vec4(T v)
        {
            a[ 3 ] = a[ 2 ] = a[ 1 ] = a[ 0 ] = v;
        }
        Vec4(){}

        union
        {
            struct{ T x,y,z,w; };
            T a[ 4 ];
        };
    };

    typedef Vec4< double > point4d;
    typedef Vec4< float  > point4f;
    typedef Vec4< int    > point4i;

    typedef Vec4< double > vec4d;
    typedef Vec4< float  > vec4f;
    typedef Vec4< int    > vec4i;

    typedef Vec4< double > dvec4;
    typedef Vec4< float  > fvec4;
    typedef Vec4< int    > ivec4;

    typedef Vec4< float  > point4;
    typedef Vec4< float  > vec4;
    
    
    typedef Vec4< unsigned int > uint4;
}

namespace kege
{    
    template< typename T > struct Col4
    {
        inline Col4& operator =(const Vec4< T >& v)
        {
            x = v.x;
            y = v.y;
            z = v.z;
            w = v.w;
            return *this;
        }
        
        inline Col4& operator =(const T& k)
        {
            x = k;
            y = k;
            z = k;
            w = k;
            return *this;
        }
            
        Col4( T& a, T& b, T& c, T& d )
        :   x( a )
        ,   y( b )
        ,   z( c )
        ,   w( d ) {}
        
        Col4( Vec4< T >& v )
        :   x( v.x )
        ,   y( v.y )
        ,   z( v.z )
        ,   w( v.w ) {}
            
        T& x;
        T& y;
        T& z;
        T& w;
    };
    
    typedef Col4< double > col4d;
    typedef Col4< float  > col4f;
    typedef Col4< int    > col4i;
}
#include "vec4.inl"
#endif /* Vec44_hpp */
