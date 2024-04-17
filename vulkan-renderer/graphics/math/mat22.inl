//
//  mat22.cpp
//  vector-math
//
//  Created by Kenneth A Esdaile on 6/6/18.
//  Copyright © 2018 Kenneth A Esdaile. All rights reserved.
//
namespace kege{
    
    template< typename T >  Mat22< T > operator +(T k, const Mat22< T > &m)
    {
        return Mat22< T >( k + m.v[0], k + m.v[1] );
    }
    
    template< typename T >  Mat22< T > operator -(T k, const Mat22< T > &m)
    {
        return Mat22< T >( k - m.v[0], k - m.v[1] );
    }
    
    template< typename T >  Mat22< T > operator *(T k, const Mat22< T > &m)
    {
        return Mat22< T >( k * m.v[0], k * m.v[1] );
    }
    
    template< typename T >  Mat22< T > transpose (const Mat22< T > &m)
    {
        return Mat22< T >( m[ 0 ][ 0 ], m[ 1 ][ 0 ], m[ 0 ][ 1 ], m[ 1 ][ 1 ] );
    }
    
    template< typename T >  Mat22< T > reflect (T DEG)
    {
        float s = sin( deg2rad(DEG) );
        float c = cos( deg2rad(DEG) );
        return Mat22< T >(c, -s, s, c);
    }
    
    template< typename T >  Mat22< T > rotm22 (T DEG)
    {
        float s = sin( deg2rad(DEG) );
        float c = cos( deg2rad(DEG) );
        return Mat22< T >(c, s, -s, c);
    }
    
    /*! @brief Trace of 2x2 matrix */
    template< typename T >  float trace (const Mat22< T >& m)
    {
        return m.v[ 0 ][ 0 ] + m.v[ 1 ][ 1 ];
    }
    
    /*! @brief Determinant of 2x2 matrix */
    template< typename T >  float det (const Mat22< T >& m)
    {
        return m.v[ 0 ][ 0 ] * m[ 1 ][ 1 ]  -  m[ 0 ][ 1 ] * m[ 1 ][ 0 ];
    }
    
    template< typename T >  Mat22< T > adj (const Mat22< T >& m)
    {
        return Mat22< T >(m[ 1 ][ 1 ], -m[ 0 ][ 1 ], -m[ 1 ][ 0 ], m[ 0 ][ 0 ]);
    }
    
    template< typename T >  Mat22< T > inverse(const Mat22< T >& m)
    {
        return  adj(m) * invrs( det(m) );
    }
}
