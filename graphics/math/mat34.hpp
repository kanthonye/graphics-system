//
//  mat34.hpp
//  kege-rendering-engine
//
//  Created by Kenneth A Esdaile on 7/23/22.
//

#ifndef mat34_hpp
#define mat34_hpp
#include "vec3.hpp"
#include "vec4.hpp"
namespace kege{
    
    template< typename T > class Mat34
    {   
    public:
        
        void operator()(const Vec4< T > &x, const Vec4< T > &y, const Vec4< T > &z)
        {
            a[ 0 ] = x;
            a[ 1 ] = y;
            a[ 2 ] = z;
        }
        
        void operator()
        (   T a00, T a01, T a02, T a03
         ,  T a10, T a11, T a12, T a13
         ,  T a20, T a21, T a22, T a23  )
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
        
        inline Mat34& operator =(const Mat34& k)
        {
            memcpy( a, k.a, sizeof(Mat34) );
            return *this;
        }
        
        inline Col4< T > col(int i)const
        {
            return Col4< T >( a[ 0 ].a[ i ] , a[ 1 ].a[ i ] , a[ 2 ].a[ i ] , a[ 3 ].a[ i ] );
        }
        
        inline const Vec3< T >& row(int i)const
        {
            return a[ i ];
        }
        
        inline void clear()
        {
            memset(a, 0x0, 9 * sizeof(T));
        }
        
        inline const Vec4< T >& operator [](int i)const
        {
            return a[i];
        }
        
        inline Vec4< T >& operator [](int i)
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
        
        Mat34(const Vec4< T > &a, const Vec4< T > &b, const Vec4< T > &c  )
        {
            operator()(a, b, c);
        }
        
        Mat34
        (   T a00, T a01, T a02, T a03
         ,  T a10, T a11, T a12, T a13
         ,  T a20, T a21, T a22, T a23  )
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
        
        Mat34 ( const Mat34< T >& m )
        {
            memcpy( a, m.a, sizeof(m) );
        }
        
        Mat34(T val)
        {
            operator()(val);
        }
        
        ~Mat34 (){}
        Mat34 (){}
        
        Vec4< T > a[3];
    };
    
    typedef Mat34< double > mat34d;
    typedef Mat34< float  > mat34f;
    typedef Mat34< int    > mat34i;
    typedef Mat34< double > dmat34;
    typedef Mat34< float  > fmat34;
    typedef Mat34< int    > imat34;
    
    // default 
    typedef Mat34< float > mat34;
}
#endif /* mat34_hpp */
