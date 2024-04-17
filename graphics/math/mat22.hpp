//
//  mat22.hpp
//  vector-math
//
//  Created by Kenneth A Esdaile on 6/6/18.
//  Copyright © 2018 Kenneth A Esdaile. All rights reserved.
//

#ifndef mat22_hpp
#define mat22_hpp
#include "vec2.hpp"
namespace kege{
    
    template< typename T > class Mat22
    {   public:
        
        inline void operator () (T a00, T a01, T a10, T a11)
        {
            v[ 0 ][ 0 ] = a00;
            v[ 0 ][ 1 ] = a01;
            v[ 1 ][ 1 ] = a11;
            v[ 1 ][ 0 ] = a10;
        }
        
        inline void operator () (const Vec2< T > &v0,const Vec2< T > &v1)
        {
            v[ 0 ] = v0;
            v[ 1 ] = v1;
        }
        
        inline void operator () (T val)
        {
            v[ 0 ][ 0 ] = val;
            v[ 0 ][ 1 ] = 0.0;
            v[ 1 ][ 1 ] = val;
            v[ 1 ][ 0 ] = 0.0;
        }
        
        friend Vec2< T >  operator *(const  Vec2< T > &v, const Mat22< T >& m)
        {
            return Vec2< T >( m.v[ 0 ] & v,  m.v[ 1 ] & v);
        }
        
        inline Vec2< T >  operator *(const  Vec2< T > &p)const
        {
            return Vec2< T >( kege::dot(v[ 0 ], p ), kege::dot(v[ 1 ], p ) );
        }
        
        inline Mat22< T > operator +(const Mat22< T > &m)const
        {
            return Mat22< T >( v[ 0 ] - m.v[ 0 ], v[ 1 ] - m.v[ 1 ] );
        }
        
        inline Mat22< T > operator -(const Mat22< T > &m)const
        {
            return Mat22< T >( v[ 0 ] - m.v[ 0 ], v[ 1 ] - m.v[ 1 ] );
        }
        
        inline Mat22< T > operator *(const Mat22< T > &m)const
        {
            return Mat22< T >
            (  v[ 0 ][ 0 ] * m.v[ 0 ][ 0 ] + v[ 0 ][ 1 ] * m.v[ 1 ][ 0 ]
             , v[ 0 ][ 0 ] * m.v[ 0 ][ 1 ] + v[ 0 ][ 1 ] * m.v[ 1 ][ 1 ]  );
        }
        
        inline Mat22< T > operator +(T k)const
        {
            return Mat22< T >( v[ 0 ] + k, v[ 1 ] + k );
        }
        
        inline Mat22< T > operator -(T k)const
        {
            return Mat22< T >( v[ 0 ] - k, v[ 1 ] - k );
        }
        
        inline Mat22< T > operator *(T k)const
        {
            return Mat22< T >( v[ 0 ] * k, v[ 1 ] * k );
        }
        
        inline Mat22< T > operator /(T k)const
        {
            return Mat22< T >( v[ 0 ] / k, v[ 1 ] / k );
        }
        
        inline void operator +=(const Mat22< T > &m)
        {
            v[ 0 ] += m.v[ 0 ];
            v[ 1 ] += m.v[ 1 ];
        }
        
        inline void operator -=(const Mat22< T > &m)
        {
            v[ 0 ] -= m.v[ 0 ];
            v[ 1 ] -= m.v[ 1 ];
        }
        
        inline void operator *=(const Mat22< T > &m)
        {
            *this = (*this) * m;
        }
        
        inline void operator +=(T k)
        {
            v[ 0 ] += k;
            v[ 1 ] += k;
        }
        
        void operator -=(T k)
        {
            v[ 0 ] -= k;
            v[ 1 ] -= k;
        }
        
        void operator *=(T k)
        {
            v[ 0 ] *= k;
            v[ 1 ] *= k;
        }
        
        void operator /=(T k)
        {
            v[ 0 ] /= k;
            v[ 1 ] /= k;
        }
        
        inline const T* dptr()const
        {
            return (T*) this;
        }

        inline const Vec2< T >& operator [](int i)const
        {
            return v[ i ];
        }

        inline Vec2< T >& operator [](int i)
        {
            return v[ i ];
        }

        inline Col2< T > col(int i)const
        {
            return Col2< T >( v[ 0 ].a[ i ] , v[ 1 ].v[ i ] );
        }
        
        inline const Vec2< T >& row(int i)const
        {
            return v[ i ];
        }
        
        Mat22(T a00, T a01, T a10, T a11)
        :   v{a00, a01, a10, a11}
        {
        }
        
        Mat22(const Vec2< T > &v0, const Vec2< T > &v1)
        {
            v[ 0 ] = v0;
            v[ 1 ] = v1;
        }
        
        Mat22(T val)
        :   v{}
        {
            v[ 0 ][ 0 ] = val;
            v[ 0 ][ 1 ] = 0.0;
            v[ 1 ][ 1 ] = val;
            v[ 1 ][ 0 ] = 0.0;
        }
        
        Mat22( const Mat22< T >& m )
        {
            v[ 0 ] = m.v[ 0 ];
            v[ 1 ] = m.v[ 1 ];
        }
        
        ~Mat22(void){}
        Mat22(void){}
        
        Vec2< T > v[2];
    };
    
    typedef Mat22< double > mat22d;
    typedef Mat22< float > mat22f;
    typedef Mat22< int > mat22i;
    
    typedef Mat22< double > dmat22;
    typedef Mat22< float > fmat22;
    typedef Mat22< int > imat22;
    // default 
    typedef Mat22< float > mat22;
}
#include "mat22.inl"
#endif /* mat22_hpp */
