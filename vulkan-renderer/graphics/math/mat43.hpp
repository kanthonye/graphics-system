//
//  mat43.hpp
//  kege-rendering-engine
//
//  Created by Kenneth A Esdaile on 2/15/22.
//

#ifndef mat43_hpp
#define mat43_hpp
#include "vec3.hpp"
#include "vec4.hpp"
namespace kege{
    
    template< typename T > class Mat43
    {   
    public:
        
        friend inline Mat43< T > operator +(const Mat43< T >& v, double s)
        {
            return Mat43< T >( v.a[0] + s, v.a[1] + s, v.a[2] + s, v.a[3] + s );
        }
        friend inline Mat43< T > operator -(const Mat43< T >& v, double s)
        {
            return Mat43< T >( v.a[0] - s, v.a[1] - s, v.a[2] - s, v.a[3] - s );
        }
        friend inline Mat43< T > operator *(const Mat43< T >& v, double s)
        {
            return Mat43< T >( v.a[0] * s, v.a[1] * s, v.a[2] * s, v.a[3] * s );
        }
        friend inline Mat43< T > operator /(const Mat43< T >& v, double s)
        {
            return Mat43< T >( v.a[0] / s, v.a[1] / s, v.a[2] / s, v.a[3] / s );
        }
        
        void operator()(const Vec3< T > &x, const Vec3< T > &y, const Vec3< T > &z, const Vec3< T > &w)
        {
            a[ 0 ] = x;
            a[ 1 ] = y;
            a[ 2 ] = z;
            a[ 3 ] = w;
        }
        
        void operator()( T a00, T a01, T a02, T a10, T a11, T a12, T a20, T a21, T a22, T a30, T a31, T a32 )
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
            
            a[ 3 ][ 0 ] = a30;
            a[ 3 ][ 1 ] = a31;
            a[ 3 ][ 2 ] = a32;
        }
        
        void operator () (T val)
        {
            clear();
            a[ 0 ][ 0 ] = 0x1;
            a[ 1 ][ 1 ] = 0x1;
            a[ 2 ][ 2 ] = 0x1;
        }
        
        inline Mat43& operator =(const Mat43& k)
        {
            memcpy( a, k.a, sizeof(Mat43) );
            return *this;
        }
        
        inline Vec4< T > col(int i)const
        {
            return { a[ 0 ].a[ i ] , a[ 1 ].a[ i ] , a[ 2 ].a[ i ] , a[ 3 ].a[ i ] };
        }
        
        void col(int i, const Vec4< T >& v )
        {
            a[ 0 ].a[ i ] = v.a[ 0 ];
            a[ 1 ].a[ i ] = v.a[ 1 ];
            a[ 2 ].a[ i ] = v.a[ 2 ];
            a[ 3 ].a[ i ] = v.a[ 3 ];
        }
        
        inline const Vec3< T >& row(int i)const
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
            return (T*) &a[0][0];
        }
        
        inline T* dptr()
        {
            return (T*) this;
        }
        
        Mat43(const Vec3< T > &a, const Vec3< T > &b, const Vec3< T > &c, const Vec3< T > &d  )
        {
            operator()(a, b, c, d);
        }
        
        Mat43( T a00, T a01, T a02, T a10, T a11, T a12, T a20, T a21, T a22, T a30, T a31, T a32 )
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
            
            a[ 3 ][ 0 ] = a30;
            a[ 3 ][ 1 ] = a31;
            a[ 3 ][ 2 ] = a32;
        }
        
        Mat43 ( const Mat43< T >& m )
        {
            memcpy( a, m.a, sizeof(m) );
        }
        
        Mat43(T val)
        {
            operator()(val);
        }
        
        ~Mat43 (){}
        Mat43 (){}
        
        Vec3< T > a[4];
    };
    
    typedef Mat43< double > mat43d;
    typedef Mat43< float  > mat43f;
    typedef Mat43< int    > mat43i;
    typedef Mat43< double > dmat43;
    typedef Mat43< float  > fmat43;
    typedef Mat43< int    > imat43;
    
    // default 
    typedef Mat43< float > mat43;
}
#endif /* mat43_hpp */
