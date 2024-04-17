//
//  Mat23.hpp
//  kege-rendering-engine
//
//  Created by Kenneth A Esdaile on 2/22/22.
//

#ifndef Mat23_hpp
#define Mat23_hpp
#include "vec2.hpp"
#include "vec3.hpp"
namespace kege
{
    
    template< typename T > class Mat23
    {   
    public:
        
        void operator()(const Vec3< T > &x, const Vec3< T > &y)
        {
            a[ 0 ] = x;
            a[ 1 ] = y;
        }
        
        void operator()( T a00, T a01, T a02, T a10, T a11, T a12 )
        {
            a[ 0 ][ 0 ] = a00;
            a[ 0 ][ 1 ] = a01;
            a[ 0 ][ 2 ] = a02;
            
            a[ 1 ][ 0 ] = a10;
            a[ 1 ][ 1 ] = a11;
            a[ 1 ][ 2 ] = a12;
        }
        
        void operator () (T val)
        {
            clear();
            a[ 0 ][ 0 ] = 0x1;
            a[ 1 ][ 1 ] = 0x1;
        }
        
        inline Mat23& operator =(const Mat23& k)
        {
            memcpy( a, k.a, sizeof(Mat23) );
            return *this;
        }
        
        inline Vec3< T > col(int i)const
        {
            return { a[ 0 ].a[ i ] , a[ 1 ].a[ i ] , a[ 2 ].a[ i ] };
        }
        
        void col(int i, const Vec2< T >& v )
        {
            a[ 0 ].a[ i ] = v.a[ 0 ];
            a[ 1 ].a[ i ] = v.a[ 1 ];
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
        
        Mat23(const Vec3< T > &a, const Vec3< T > &b )
        {
            operator()(a, b);
        }
        
        Mat23( T a00, T a01, T a02, T a10, T a11, T a12 )
        {
            a[ 0 ][ 0 ] = a00;
            a[ 0 ][ 1 ] = a01;
            a[ 0 ][ 2 ] = a02;
            
            a[ 1 ][ 0 ] = a10;
            a[ 1 ][ 1 ] = a11;
            a[ 1 ][ 2 ] = a12;
        }
        
        Mat23 ( const Mat23< T >& m )
        {
            memcpy( a, m.a, sizeof(m) );
        }
        
        Mat23(T val)
        {
            operator()(val);
        }
        
        ~Mat23 (){}
        Mat23 (){}
        
        Vec3< T > a[2];
    };
    
    typedef Mat23< double > mat23d;
    typedef Mat23< float  > mat23f;
    typedef Mat23< int    > mat23i;
    typedef Mat23< double > dmat23;
    typedef Mat23< float  > fmat23;
    typedef Mat23< int    > imat23;
    
    // default 
    typedef Mat23< float > mat23;
}
#endif /* Mat23_hpp */
