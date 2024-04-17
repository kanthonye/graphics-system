//
//  mat33.hpp
//  vector-math
//
//  Created by Kenneth A Esdaile on 6/6/18.
//  Copyright © 2018 Kenneth A Esdaile. All rights reserved.
//

#ifndef mat33_hpp
#define mat33_hpp
#include "vec3.hpp"
#include "mat22.hpp"
namespace kege{
    template< typename T > class Mat44;
    
    template< typename T > class Mat33
    {   
    public:
        
        friend Mat33< T > operator +(T k, const Mat33< T > &m)
        {
            return Mat33< T >
            (  k + m.a[ 0 ]
             , k + m.a[ 1 ]
             , k + m.a[ 2 ] );
        }
        
        friend Mat33< T > operator -(T k, const Mat33< T > &m)
        {
            return Mat33< T >
            (  k - m.a[ 0 ]
             , k - m.a[ 1 ]
             , k - m.a[ 2 ] );
        }
        
        friend Mat33< T > operator *(T k, const Mat33< T > &m)
        {
            return Mat33< T >
            (  m.a[ 0 ] * k
             , m.a[ 1 ] * k
             , m.a[ 2 ] * k );
        }
        
        friend Mat33< T > operator /(T k, const Mat33< T > &m)
        {
            return Mat33< T >
            (  k/assert_zero(m.m00), k/assert_zero(m.m10), k/assert_zero(m.m20)
             , k/assert_zero(m.m01), k/assert_zero(m.m11), k/assert_zero(m.m21)
             , k/assert_zero(m.m02), k/assert_zero(m.m12), k/assert_zero(m.m22)  );
        }
        
        friend Vec3< T > operator *(const Vec3< T > &v, const Mat33< T > &m)
        {
            return Vec3< T >
            (  v.x * m.a[0][0] + v.y * m.a[1][0] + v.z * m.a[2][0]
             , v.x * m.a[0][1] + v.y * m.a[1][1] + v.z * m.a[2][1]
             , v.x * m.a[0][2] + v.y * m.a[1][2] + v.z * m.a[2][2]  );
        }
        
        void operator()(const Vec3< T > &x, const Vec3< T > &y, const Vec3< T > &z)
        {
            a[ 0 ] = x;
            a[ 1 ] = y;
            a[ 2 ] = z;
        }
        
        void operator()( T a00, T a01, T a02, T a10, T a11, T a12, T a20, T a21, T a22 )
        {
            a[ 0 ][ 0 ] = a00;
            a[ 0 ][ 1 ] = a01;
            a[ 0 ][ 2 ] = a02;
            
            a[ 1 ][ 0 ] = a10;
            a[ 1 ][ 1 ] = a11;
            a[ 1 ][ 2 ] = a12;
            
            a[ 2 ][ 0 ] = a20;
            a[ 2 ][ 1 ] = a21;
            a[ 2 ][ 2 ] = a22;
        }
        
        void operator () (T val)
        {
            clear();
            a[ 0 ][ 0 ] = val;
            a[ 1 ][ 1 ] = val;
            a[ 2 ][ 2 ] = val;
        }
        
        Mat33< T > operator +(const Mat33< T > &m)const
        {
            return Mat33< T >
            (  a[ 0 ] + m.a[ 0 ]
             , a[ 1 ] + m.a[ 1 ]
             , a[ 2 ] + m.a[ 2 ] );
        }
        
        Mat33< T > operator -(const Mat33< T > &m)const
        {
            return Mat33< T >
            (  a[ 0 ] - m.a[ 0 ]
             , a[ 1 ] - m.a[ 1 ]
             , a[ 2 ] - m.a[ 2 ] );
        }
        
        Mat33< T > operator *(const Mat33< T > &m)const
        {
            return Mat33< T >
            (  ( a[ 0 ][ 0 ] * m.a[ 0 ][ 0 ] ) + ( a[ 0 ][ 1 ] * m.a[ 0 ][ 0 ] ) + ( a[ 0 ][ 2 ] * m.a[ 0 ][ 0 ] )
             , ( a[ 1 ][ 0 ] * m.a[ 0 ][ 1 ] ) + ( a[ 1 ][ 1 ] * m.a[ 0 ][ 1 ] ) + ( a[ 1 ][ 2 ] * m.a[ 0 ][ 1 ] )
             , ( a[ 2 ][ 0 ] * m.a[ 0 ][ 2 ] ) + ( a[ 2 ][ 1 ] * m.a[ 0 ][ 2 ] ) + ( a[ 2 ][ 2 ] * m.a[ 0 ][ 2 ] )
             
             , ( a[ 0 ][ 0 ] * m.a[ 1 ][ 0 ] ) + ( a[ 0 ][ 1 ] * m.a[ 1 ][ 0 ] ) + ( a[ 0 ][ 2 ] * m.a[ 1 ][ 0 ] )
             , ( a[ 1 ][ 0 ] * m.a[ 1 ][ 1 ] ) + ( a[ 1 ][ 1 ] * m.a[ 1 ][ 1 ] ) + ( a[ 1 ][ 2 ] * m.a[ 1 ][ 1 ] )
             , ( a[ 2 ][ 0 ] * m.a[ 1 ][ 2 ] ) + ( a[ 2 ][ 1 ] * m.a[ 1 ][ 2 ] ) + ( a[ 2 ][ 2 ] * m.a[ 1 ][ 2 ] )
             
             , ( a[ 0 ][ 0 ] * m.a[ 2 ][ 0 ] ) + ( a[ 0 ][ 1 ] * m.a[ 2 ][ 0 ] ) + ( a[ 0 ][ 2 ] * m.a[ 2 ][ 0 ] )
             , ( a[ 1 ][ 0 ] * m.a[ 2 ][ 1 ] ) + ( a[ 1 ][ 1 ] * m.a[ 2 ][ 1 ] ) + ( a[ 1 ][ 2 ] * m.a[ 2 ][ 1 ] )
             , ( a[ 2 ][ 0 ] * m.a[ 2 ][ 2 ] ) + ( a[ 2 ][ 1 ] * m.a[ 2 ][ 2 ] ) + ( a[ 2 ][ 2 ] * m.a[ 2 ][ 2 ] ) );
        }
        
        Vec3< T > operator *(const Vec3< T >& v)const
        {
            return Vec3< T >( a[ 0 ] & v, a[ 1 ] & v, a[ 2 ] & v );
        }
        
        Mat33< T > operator +(T k)const
        {
            return Mat33< T >
            (  a[ 0 ] + k
             , a[ 1 ] + k
             , a[ 2 ] + k );
        }
        
        Mat33< T > operator -(T k)const
        {
            return Mat33< T >
            (  a[ 0 ] - k
             , a[ 1 ] - k
             , a[ 2 ] - k  );
        }
        
        Mat33< T > operator *(T k)const
        {
            return Mat33< T >
            (  a[ 0 ] * k
             , a[ 1 ] * k
             , a[ 2 ] * k  );
        }
        
        Mat33< T > operator /(T k)const
        {
            return Mat33< T >
            (  a[ 0 ] / k
             , a[ 1 ] / k
             , a[ 2 ] / k  );
        }
        
        void operator +=(const Mat33< T > &m)
        {
            operator=(*this + m);
        }
        
        void operator -=(const Mat33< T > &m)
        {
            operator=(*this - m);
        }
        
        void operator *=(const Mat33< T > &m)
        {
            operator=(*this * m);
        }
        
        inline void operator +=(T k)
        {
            operator=(*this + k);
        }
        
        inline void operator -=(T k)
        {
            operator=(*this - k);
        }
        
        inline void operator *=(T k)
        {
            operator=(*this * k);
        }
        
        inline void operator /=(T k)
        {
            operator=(*this / k);
        }
        
        inline Mat33& operator =(const Mat33& k)
        {
            memcpy( a, k.a, sizeof(Mat33) );
            return *this;
        }
        
        /* conversion operator */
        template<typename S> inline operator Mat33<S>()const
        {
            return Mat33< S >( a[ 0 ], a[ 1 ], a[ 2 ] );
        }
        
        inline Col3< const T > col(int i)const
        {
            return Col3< T >( a[ 0 ].a[ i ] , a[ 1 ].a[ i ] , a[ 2 ].a[ i ] );
        }
        
        inline Col3< T > col(int i)
        {
            return Col3< T >( a[ 0 ].a[ i ] , a[ 1 ].a[ i ] , a[ 2 ].a[ i ] );
        }
        
        inline const Vec3< T >& row(int i)const
        {
            return a[ i ];
        }
        
        inline Vec3< T >& row(int i)
        {
            return a[ i ];
        }
        
        inline void clear()
        {
            memset(a, 0x0, 9 * sizeof(T));
        }
        
        inline const Vec3< T >& operator [](int i)const
        {
            return a[i];
        }
        
        inline Vec3< T >& operator [](int i)
        {
            return a[i];
        }
        
        inline const T* dptr()const
        {
            return (T*) this;
        }
        
        inline T* dptr()
        {
            return (T*) this;
        }
        
        Mat33(const Vec3< T > &a, const Vec3< T > &b, const Vec3< T > &c  )
        {
            operator()(a, b, c);
        }
        
        Mat33( T a00, T a01, T a02, T a10, T a11, T a12, T a20, T a21, T a22 )
        {
            a[ 0 ][ 0 ] = a00;
            a[ 0 ][ 1 ] = a01;
            a[ 0 ][ 2 ] = a02;
            
            a[ 1 ][ 0 ] = a10;
            a[ 1 ][ 1 ] = a11;
            a[ 1 ][ 2 ] = a12;
            
            a[ 2 ][ 0 ] = a20;
            a[ 2 ][ 1 ] = a21;
            a[ 2 ][ 2 ] = a22;
        }
        
        Mat33 ( const Mat33< T >& m )
        {
            memcpy( a, m.a, 9 * sizeof(T) );
        }
        
        Mat33(T val)
        {
            operator()(val);
        }
        
        ~Mat33 (){}
        Mat33 (){}
        
        Vec3< T > a[3];
    };
    
    typedef Mat33< double > mat33d;
    typedef Mat33< float > mat33f;
    typedef Mat33< int > mat33i;
    typedef Mat33< double > dmat33;
    typedef Mat33< float > fmat33;
    typedef Mat33< int > imat33;
    
    // default 
    typedef Mat33< float > mat33;
}
#include "mat33.inl"
#endif /* mat33_hpp */
