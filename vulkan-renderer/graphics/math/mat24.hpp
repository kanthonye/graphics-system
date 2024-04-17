//
//  mat24.hpp
//  kege-rendering-engine
//
//  Created by Kenneth A Esdaile on 7/23/22.
//

#ifndef mat24_hpp
#define mat24_hpp
#include "vec2.hpp"
#include "vec4.hpp"
namespace kege{
    
    template< typename T > class Mat24
    {   
    public:
        
        void operator()(const Vec4< T > &x, const Vec4< T > &y)
        {
            a[ 0 ] = x;
            a[ 1 ] = y;
        }
        
        void operator()
        (   T a00, T a01, T a02, T a03
         ,  T a10, T a11, T a12, T a13  )
        {
            a[ 0 ][ 0 ] = a00;
            a[ 0 ][ 1 ] = a01;
            a[ 0 ][ 2 ] = a02;
            a[ 0 ][ 3 ] = a03;
            
            a[ 1 ][ 0 ] = a10;
            a[ 1 ][ 1 ] = a11;
            a[ 1 ][ 2 ] = a12;
            a[ 1 ][ 3 ] = a13;
        }
        
        void operator () (T val)
        {
            clear();
            a[ 0 ][ 0 ] = val;
            a[ 1 ][ 1 ] = val;
        }
        
        inline Mat24& operator =(const Mat24& k)
        {
            memcpy( a, k.a, sizeof(Mat24) );
            return *this;
        }
        
        inline Col2< T > col(int i)const
        {
            return Col2< T >( a[ 0 ].a[ i ] , a[ 1 ].a[ i ] );
        }
        
        inline const Vec4< T >& row(int i)const
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
        
        Mat24(const Vec4< T > &a, const Vec4< T > &b)
        {
            operator()(a, b);
        }
        
        Mat24
        (   T a00, T a01, T a02, T a03
         ,  T a10, T a11, T a12, T a13  )
        {
            a[ 0 ][ 0 ] = a00;
            a[ 0 ][ 1 ] = a01;
            a[ 0 ][ 2 ] = a02;
            a[ 0 ][ 3 ] = a03;
            
            a[ 1 ][ 0 ] = a10;
            a[ 1 ][ 1 ] = a11;
            a[ 1 ][ 2 ] = a12;
            a[ 1 ][ 3 ] = a13;
        }
        
        Mat24 ( const Mat24< T >& m )
        {
            memcpy( a, m.a, sizeof(m) );
        }
        
        Mat24(T val)
        {
            operator()(val);
        }
        
        ~Mat24 (){}
        Mat24 (){}
        
        Vec4< T > a[2];
    };
    
    typedef Mat24< double > mat24d;
    typedef Mat24< float  > mat24f;
    typedef Mat24< int    > mat24i;
    typedef Mat24< double > dmat24;
    typedef Mat24< float  > fmat24;
    typedef Mat24< int    > imat24;
    
    // default 
    typedef Mat24< float > mat24;
}
#endif /* mat24_hpp */
