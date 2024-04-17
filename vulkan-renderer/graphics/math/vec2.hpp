//
//  vec2.hpp
//  KEGE_VECTOR_MATH
//
//  Created by Kenneth A Esdaile on 4/9/20.
//  Copyright © 2020 Kenneth A Esdaile. All rights reserved.
//

#ifndef vec2_hpp
#define vec2_hpp
#include "coremath.hpp"
namespace kege{
    
    template<typename T > class Vec3;
    
    template<typename T > class Vec2 
    {
    public:
        
        template<typename S > friend inline Vec2< T > operator +(const Vec2< T >& a, const Vec2< S >& b)
        {
            return { a.a[0] + b.a[0], a.a[1] + b.a[1] };
        }
        template<typename S > friend inline Vec2< T > operator -(const Vec2< T >& a, const Vec2< S >& b)
        {
            return { a.a[0] - b.a[0], a.a[1] - b.a[1] };
        }
        template<typename S > friend inline Vec2< T > operator *(const Vec2< T >& a, const Vec2< S >& b)
        {
            return Vec2< T >( a.a[0] * b.a[0] , a.a[1] * b.a[1] );
        }
        
        friend inline Vec2< T > operator +(double a, const Vec2< T >& b)
        {
            return Vec2< T >( a + b.a[0], a + b.a[1] );
        }
        friend inline Vec2< T > operator -(double a, const Vec2< T >& b)
        {
            return Vec2< T >( a - b.a[0], a - b.a[1] );
        }
        friend inline Vec2< T > operator *(double a, const Vec2< T >& b)
        {
            return Vec2< T >( a * b.a[0], a * b.a[1] );
        }
        
        friend inline Vec2< T > operator +(const Vec2< T >& v, double s)
        {
            return Vec2< T >( v.a[0] + s, v.a[1] + s );
        }
        friend inline Vec2< T > operator -(const Vec2< T >& v, double s)
        {
            return Vec2< T >( v.a[0] - s, v.a[1] - s );
        }
        friend inline Vec2< T > operator *(const Vec2< T >& v, double s)
        {
            return Vec2< T >( v.a[0] * s, v.a[1] * s );
        }
        friend inline Vec2< T > operator /(const Vec2< T >& v, double s)
        {
            return Vec2< T >( v.a[0] / s, v.a[1] / s );
        }
        
        inline Vec2< T > operator +(const Vec2< T >& b)const
        {
            return { a[0] + b.a[0], a[1] + b.a[1] };
        }
        inline Vec2< T > operator -(const Vec2< T >& b)const
        {
            return { a[0] - b.a[0], a[1] - b.a[1] };
        }
        inline Vec2< T > operator *(const Vec2< T >& b)const
        {
            return { a[0] * b.a[0], a[1] * b.a[1] };
        }
        
        /* cross product operator */
        inline T operator ||(const Vec2< T >& b)const
        {
            return a[0] * b.a[1] - a[1] * b.a[0];
        }
        
        /* dot product operator */
        inline T operator &(const Vec2< T >& b)const
        {
            return a[0] * b.a[0] + a[1] * b.a[1];
        }
        
        inline const Vec2< T >& operator =(const Vec2< T >& b)
        {
            a[0] = b.a[0];
            a[1] = b.a[1];
            return *this;
        }
        
        void operator += (const Vec2< T > &v)
        {
            a[ 0 ] += v.a[ 0 ];
            a[ 1 ] += v.a[ 1 ];
        }
        
        void operator -= (const Vec2< T > &v)
        {
            a[ 0 ] -= v.a[ 0 ];
            a[ 1 ] -= v.a[ 1 ];
        }
        
        void operator *= (const Vec2< T > &v)
        {
            a[ 0 ] *= v.a[ 0 ];
            a[ 1 ] *= v.a[ 1 ];
        }
        
        inline void operator += ( T s )
        {
            a[ 0 ] += s;
            a[ 1 ] += s;
        }
        inline void operator -= ( T s )
        {
            a[ 0 ] -= s;
            a[ 1 ] -= s;
        }
        inline void operator *= ( T s )
        {
            a[ 0 ] *= s;
            a[ 1 ] *= s;
        }
        inline void operator /= ( T s )
        {
            a[ 0 ] /= s;
            a[ 1 ] /= s;
        }
        
        void operator () ( T x, T y )
        {
            a[ 0 ] = x;
            a[ 1 ] = y;
        }
        
        inline void operator ()( T s )
        { 
            a[ 1 ] = a[ 0 ] = s;
        }
        inline Vec2< T > operator -()const
        {
            return { -a[0], -a[1] };
        }
        
        inline const T& operator[](const int n) const { return a[ n ]; }
        inline T& operator[](const int n){ return a[ n ]; }
        
        inline const T* dptr() const { return a; }
        inline T* dptr(){ return a; }
        
        /* conversion operator */
        template<typename S> inline operator Vec2<S>()const
        {
            return { S(a[ 0 ]), S(a[ 1 ]) };
        }
        
        template<typename S> Vec2( const Vec3<S>& v );

        Vec2( T x, T y )
        {
            a[ 0 ] = x;
            a[ 1 ] = y;
        }
        Vec2(T s)
        {
            a[ 1 ] = a[ 0 ] = s;
        }
        Vec2(){}

        static const Vec2 zaxis;
        static const Vec2 xaxis;
        static const Vec2 yaxis;
        static const Vec2 zero;
        static const Vec2 one;

        union
        {
            struct{ T x, y; };
            T a[ 2 ];
        };
    };

    typedef Vec2< double > point2d;
    typedef Vec2< float  > point2f;
    typedef Vec2< int    > point2i;

    typedef Vec2< double > vec2d;
    typedef Vec2< float  > vec2f;
    typedef Vec2< int    > vec2i;

    typedef Vec2< double > dvec2;
    typedef Vec2< float  > fvec2;
    typedef Vec2< int    > ivec2;

    typedef Vec2< float  > point2;
    typedef Vec2< float  > vec2;

}
namespace kege
{    
    template< typename T > struct Col2
    {
        Col2( T& a, T& b )
        :   x( a )
        ,   y( b ) {}
        
        Col2( Vec2< T >& v )
        :   x( v.x )
        ,   y( v.y ) {}
            
        T& x;
        T& y;
    };
    
    typedef Col2< double > col2d;
    typedef Col2< float  > col2f;
    typedef Col2< int    > col2i;
}
#include "vec2.inl"
#endif /* vec2_hpp */
