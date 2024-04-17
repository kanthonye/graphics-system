//
//  mat42.hpp
//  kege-rendering-engine
//
//  Created by Kenneth A Esdaile on 7/23/22.
//

#ifndef mat42_hpp
#define mat42_hpp
#include "vec2.hpp"
#include "vec4.hpp"
namespace kege{
    
    template< typename T > class Mat42
    {   
    public:
        
        void operator()(const Vec2< T > &x, const Vec2< T > &y, const Vec2< T > &z, const Vec2< T > &w)
        {
            a[ 0 ] = x;
            a[ 1 ] = y;
            a[ 2 ] = z;
            a[ 3 ] = w;
        }
        
        void operator()( T a00, T a01, T a10, T a11, T a20, T a21, T a30, T a31 )
        {
            a[ 0 ][ 0 ] = a00;
            a[ 0 ][ 1 ] = a01;
            
            a[ 1 ][ 0 ] = a10;
            a[ 1 ][ 1 ] = a11;
            
            a[ 2 ][ 0 ] = a20;
            a[ 2 ][ 1 ] = a21;
            
            a[ 3 ][ 0 ] = a30;
            a[ 3 ][ 1 ] = a31;
        }
        
        void operator () (T val)
        {
            clear();
            a[ 0 ][ 0 ] = 0x1;
            a[ 1 ][ 1 ] = 0x1;
            a[ 2 ][ 2 ] = 0x1;
        }
        
        inline Mat42& operator =(const Mat42& k)
        {
            memcpy( a, k.a, sizeof(Mat42) );
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
        
        Mat42(const Vec2< T > &a, const Vec2< T > &b, const Vec2< T > &c, const Vec2< T > &d  )
        {
            operator()(a, b, c, d);
        }
        
        Mat42( T a00, T a01, T a10, T a11, T a20, T a21, T a30, T a31 )
        {
            a[ 0 ][ 0 ] = a00;
            a[ 0 ][ 1 ] = a01;
            
            a[ 1 ][ 0 ] = a10;
            a[ 1 ][ 1 ] = a11;
            
            a[ 2 ][ 0 ] = a20;
            a[ 2 ][ 1 ] = a21;
            
            a[ 3 ][ 0 ] = a30;
            a[ 3 ][ 1 ] = a31;
        }
        
        Mat42 ( const Mat42< T >& m )
        {
            memcpy( a, m.a, sizeof(m) );
        }
        
        Mat42(T val)
        {
            operator()(val);
        }
        
        ~Mat42 (){}
        Mat42 (){}
        
        Vec2< T > a[4];
    };
    
    typedef Mat42< double > mat42d;
    typedef Mat42< float  > mat42f;
    typedef Mat42< int    > mat42i;
    typedef Mat42< double > dmat42;
    typedef Mat42< float  > fmat42;
    typedef Mat42< int    > imat42;
    
    // default 
    typedef Mat42< float > mat42;
}
#endif /* mat42_hpp */
