//
//  mat32.hpp
//  kege-rendering-engine
//
//  Created by Kenneth A Esdaile on 7/23/22.
//

#ifndef mat32_hpp
#define mat32_hpp
#include "vec2.hpp"
#include "vec3.hpp"
namespace kege
{
    
    template< typename T > class Mat32
    {   
    public:
        
        void operator()(const Vec2< T > &x, const Vec2< T > &y, const Vec2< T > &z)
        {
            a[ 0 ] = x;
            a[ 1 ] = y;
            a[ 2 ] = z;
        }
        
        void operator()( T a00, T a01, T a10, T a11, T a20, T a21 )
        {
            a[ 0 ][ 0 ] = a00;
            a[ 0 ][ 1 ] = a01;
            
            a[ 1 ][ 0 ] = a10;
            a[ 1 ][ 1 ] = a11;
            
            a[ 2 ][ 0 ] = a20;
            a[ 2 ][ 1 ] = a21;
        }
        
        void operator () (T val)
        {
            clear();
            a[ 0 ][ 0 ] = 0x1;
            a[ 1 ][ 1 ] = 0x1;
        }
        
        inline Mat32& operator =(const Mat32& k)
        {
            memcpy( a, k.a, sizeof(Mat32) );
            return *this;
        }
        
        inline Col3< const T > col(int i)const
        {
            return Col3< T >( a[ 0 ].a[ i ] , a[ 1 ].a[ i ] , a[ 2 ].a[ i ] );
        }
        
        inline Col3< T > col(int i)
        {
            return Col3< T >( a[ 0 ].a[ i ] , a[ 1 ].a[ i ] , a[ 2 ].a[ i ] );
        }
        
        inline const Vec2< T >& row(int i)const
        {
            return a[ i ];
        }
        
        inline void clear()
        {
            memset(a, 0x0, 9 * sizeof(T));
        }
        
        inline const Vec2< T >& operator [](int i)const
        {
            return a[i];
        }
        
        inline Vec2< T >& operator [](int i)
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
        
        Mat32(const Vec2< T > &a, const Vec2< T > &b, const Vec2< T > &c )
        {
            operator()(a, b, c);
        }
        
        Mat32( T a00, T a01, T a10, T a11, T a20, T a21 )
        {
            a[ 0 ][ 0 ] = a00;
            a[ 0 ][ 1 ] = a01;
            
            a[ 1 ][ 0 ] = a10;
            a[ 1 ][ 1 ] = a11;
            
            a[ 2 ][ 0 ] = a20;
            a[ 2 ][ 1 ] = a21;
        }
        
        Mat32 ( const Mat32< T >& m )
        {
            memcpy( a, m.a, sizeof(m) );
        }
        
        Mat32(T val)
        {
            operator()(val);
        }
        
        ~Mat32 (){}
        Mat32 (){}
        
        Vec2< T > a[3];
    };
    
    typedef Mat32< double > mat32d;
    typedef Mat32< float  > mat31f;
    typedef Mat32< int    > mat31i;
    typedef Mat32< double > dmat32;
    typedef Mat32< float  > fmat32;
    typedef Mat32< int    > imat32;
    
    // default 
    typedef Mat32< float > mat32;
}
#endif /* mat32_hpp */
