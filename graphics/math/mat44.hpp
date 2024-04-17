//
//  mat44.hpp
//  column-major
//
//  Created by Kenneth A Esdaile on 7/12/18.
//  Copyright © 2018 Kenneth A Esdaile. All rights reserved.
//

#ifndef mat44_hpp
#define mat44_hpp
#include "vec3.hpp"
#include "vec4.hpp"
#include "mat33.hpp"
#include "mat43.hpp"
namespace kege{
    
    template< typename T > class Mat44
    {   
    public:
        
        inline Mat44<T>& operator =( const Mat44<T>& m )
        {
            memcpy( v, m.v, 16 * sizeof(T) );
            return *this;
        }
        
        inline void operator()
        (  T a00, T a01, T a02, T a03
         , T a10, T a11, T a12, T a13
         , T a20, T a21, T a22, T a23
         , T a30, T a31, T a32, T a33  )
        {
            v[ 0 ] = {a00, a01, a02, a03};
            v[ 1 ] = {a10, a11, a12, a13};
            v[ 2 ] = {a20, a21, a22, a23};
            v[ 3 ] = {a30, a31, a32, a33};
        }
        
        inline void operator () (T val)
        {
            zero();
            v[ 0 ][ 0 ] = v[ 1 ][ 1 ] = v[ 2 ][ 2 ] = 0x0;
            v[ 3 ][ 3 ] = 0x1;
        }
        
        inline Mat44 operator +(const Mat44 &m)const
        {
            return Mat44
            (  v[ 0 ] + m.v[ 0 ]
             , v[ 1 ] + m.v[ 1 ]
             , v[ 2 ] + m.v[ 2 ]
             , v[ 3 ] + m.v[ 3 ]  );
        }
        
        inline Mat44 operator -(const Mat44 &m)const
        {
            return Mat44
            (  v[ 0 ] - m.v[ 0 ]
             , v[ 1 ] - m.v[ 1 ]
             , v[ 2 ] - m.v[ 2 ]
             , v[ 3 ] - m.v[ 3 ]  );
        }
        
        inline Mat44 operator *(const Mat44 &m)const
        {
            return Mat44
            (  v[ 0 ] & m.col( 0 )
             , v[ 0 ] & m.col( 1 )
             , v[ 0 ] & m.col( 2 )
             , v[ 0 ] & m.col( 3 )
             
             , v[ 1 ] & m.col( 0 )
             , v[ 1 ] & m.col( 1 )
             , v[ 1 ] & m.col( 2 )
             , v[ 1 ] & m.col( 3 )
             
             , v[ 2 ] & m.col( 0 )
             , v[ 2 ] & m.col( 1 )
             , v[ 2 ] & m.col( 2 )
             , v[ 2 ] & m.col( 3 )
             
             , v[ 3 ] & m.col( 0 )
             , v[ 3 ] & m.col( 1 )
             , v[ 3 ] & m.col( 2 )
             , v[ 3 ] & m.col( 3 ) );
        }
        
        friend inline Vec4< T > operator *(const Vec4< T > &v, const Mat44 &m)
        {
            return Vec4< T >
            (  (m.m00*v.x) + (m.m10*v.y) + (m.m20*v.z) + (m.m30*v.w)
             , (m.m01*v.x) + (m.m11*v.y) + (m.m21*v.z) + (m.m31*v.w)
             , (m.m02*v.x) + (m.m12*v.y) + (m.m22*v.z) + (m.m32*v.w)
             , (m.m03*v.x) + (m.m13*v.y) + (m.m23*v.z) + (m.m33*v.w) );
        }
        
        inline Vec4< T > operator *(const Vec4< T > &k)const
        {
            return Vec4< T >
            (  (v[ 0 ].x*k.x) + (v[ 0 ].y*k.y) + (v[ 0 ].z*k.z) + (v[ 0 ].w*k.w)
             , (v[ 1 ].x*k.x) + (v[ 1 ].y*k.y) + (v[ 1 ].z*k.z) + (v[ 1 ].w*k.w)
             , (v[ 2 ].x*k.x) + (v[ 2 ].y*k.y) + (v[ 2 ].z*k.z) + (v[ 2 ].w*k.w)
             , (v[ 3 ].x*k.x) + (v[ 3 ].y*k.y) + (v[ 3 ].z*k.z) + (v[ 3 ].w*k.w) );
        }
        
        inline Mat44 operator +(T k)const
        {
            return Mat44( v[ 0 ] + k, v[ 1 ] + k, v[ 2 ] + k, v[ 3 ] + k );
        }
        
        inline Mat44 operator -(T k)const
        {
            return Mat44( v[ 0 ] - k, v[ 1 ] - k, v[ 2 ] - k, v[ 3 ] - k );
        }
        
        inline Mat44 operator *(T k)const
        {
            return Mat44( v[ 0 ] * k, v[ 1 ] * k, v[ 2 ] * k, v[ 3 ] * k );
        }
        
        inline Mat44 operator /(T k)const
        {
             return Mat44( v[ 0 ] / k, v[ 1 ] / k, v[ 2 ] / k, v[ 3 ] / k  );
        }
        
        inline void operator +=(const Mat44 &m)
        {
            operator=(*this + m);
        }
        inline void operator -=(const Mat44 &m)
        {
            operator=(*this - m);
        }
        inline void operator *=(const Mat44 &m)
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
        
        inline Vec4< T > col(int i)const
        {
            return { v[ 0 ].a[ i ] , v[ 1 ].a[ i ] , v[ 2 ].a[ i ] , v[ 3 ].a[ i ] };
        }
        
        void col(int i, const Vec4< T >& a )
        {
            v[ 0 ].a[ i ] = a.a[ 0 ];
            v[ 1 ].a[ i ] = a.a[ 1 ];
            v[ 2 ].a[ i ] = a.a[ 2 ];
            v[ 3 ].a[ i ] = a.a[ 3 ];
        }
        
        inline const Vec4< T >& row(int i)const
        {
            return v[ i ];
        }
        
        inline Mat44& zero()
        {
            memset(v, 0x0, 16 * sizeof(T));
            return *this;
        }
        
        inline const Vec4< T >& operator [](int i)const
        {
            return v[i];
        }
        
        inline Vec4< T >& operator [](int i)
        {
            return v[i];
        }
        
        inline const T* dptr()const
        {
            return (T*) v;
        }
        
        inline T* dptr()
        {
            return (T*) v;
        }

        template< typename K > operator Mat44< K >()const
        {
            return Mat44< K >
            (
             v[0][0], v[0][1], v[0][2], v[0][3],
             v[1][0], v[1][1], v[1][2], v[1][3],
             v[2][0], v[2][1], v[2][2], v[2][3],
             v[3][0], v[3][1], v[3][2], v[3][3]
            );
        }

        Mat44(const Vec3< T > &a, const Vec3< T > &b, const Vec3< T > &c  )
        {
            operator()(a, b, c);
        }

        Mat44
        (  T a00, T a01, T a02, T a03
         , T a10, T a11, T a12, T a13
         , T a20, T a21, T a22, T a23
         , T a30, T a31, T a32, T a33 )
        {
            v[ 0 ] = {a00, a01, a02, a03};
            v[ 1 ] = {a10, a11, a12, a13};
            v[ 2 ] = {a20, a21, a22, a23};
            v[ 3 ] = {a30, a31, a32, a33};
        }
        
        Mat44
        (  const Vec3< T > &r, T a03
         , const Vec3< T > &u, T a13
         , const Vec3< T > &f, T a23)
        {
            v[ 0 ] = {r.a[0], r.a[1], r.a[2], a03};
            v[ 1 ] = {u.a[0], u.a[1], u.a[2], a13};
            v[ 2 ] = {f.a[0], f.a[1], f.a[2], a23};
            v[ 3 ] = {0.0, 0.0, 0.0, 1.0};
        }
        
        
        Mat44( const Vec4< T > &a, const Vec4< T > &b, const Vec4< T > &c, const Vec4< T > &d )
        {
            v[ 0 ] = a;
            v[ 1 ] = b;
            v[ 2 ] = c;
            v[ 3 ] = d;
        }
        
        Mat44 (T val)
        {
            zero();
            v[ 0 ][ 0 ] = v[ 1 ][ 1 ] = v[ 2 ][ 2 ] = val;
            v[ 3 ][ 3 ] = 0x1;
        }

        Mat44 ( const Mat33< T >& m )
        {
            v[ 0 ] = {m.a[0], T(0x0) };
            v[ 1 ] = {m.a[1], T(0x0) };
            v[ 2 ] = {m.a[2], T(0x0) };
            v[ 3 ] = {0.0, 0.0, 0.0, 1.0};
        }

        Mat44 ( const Mat44< T >& m )
        {
            memcpy(v, m.v, 16 * sizeof(T));
        }

        Mat44 ( const Mat43< T >& m )
        {
            v[0] = vec4( m.a[0] );
            v[1] = vec4( m.a[1] );
            v[2] = vec4( m.a[2] );
            v[3] = vec4( m.a[3] );
        }
        
        ~Mat44< T >(){}
        Mat44(){}

        Vec4< T > v[4];
    };
    
    typedef Mat44< double > mat44d;
    typedef Mat44< float > mat44f;
    typedef Mat44< int > mat44i;
    typedef Mat44< double > dmat44;
    typedef Mat44< float > fmat44;
    typedef Mat44< int > imat44;
    
    // default 
    typedef Mat44< float > mat44;
}
#include "mat44.inl"
#endif /* mat44_hpp */
