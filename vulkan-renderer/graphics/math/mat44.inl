//
//  mat44.cpp
//  column-major
//
//  Created by Kenneth A Esdaile on 7/12/18.
//  Copyright © 2018 Kenneth A Esdaile. All rights reserved.
//
namespace kege{
    
    template< typename T > inline Mat44< T > operator +(T k, const Mat44< T > &m)
    {
        return Mat44< T >( k + m[ 0 ], k + m[ 1 ], k + m[ 2 ], k + m[ 3 ] );
    }
    
    template< typename T > inline Mat44< T > operator -(T k, const Mat44< T > &m)
    {
        return Mat44< T >( k - m[ 0 ], k - m[ 1 ], k - m[ 2 ], k - m[ 3 ] );
    }
    
    template< typename T > inline Mat44< T > operator *(T k, const Mat44< T > &m)
    {
        return Mat44< T >( k * m[ 0 ], k * m[ 1 ], k * m[ 2 ], k * m[ 3 ] );
    }
    
    template< typename T > inline Mat44< T > operator /(T k, const Mat44< T > &m)
    {
        return Mat44< T >( k / m[ 0 ], k / m[ 1 ], k / m[ 2 ], k / m[ 3 ] );
    }
    
    template< typename T > inline T trace (const Mat44< T >& m)
    {
        return ( m[ 0 ][ 0 ] + m[ 1 ][ 1 ] + m[ 2 ][ 2 ] + m[ 3 ][ 3 ] );
    }
    
    template< typename T > inline Mat44< T > transpose (const Mat44< T >& m)
    {
        return Mat44< T >( m.col(0), m.col(1), m.col(2), m.col(3) );
    }
    
    template< typename T > inline Mat44< T > translate(T x, T y, T z)
    {
        return Mat44< T >
        (  1.0f, 0.0f, 0.0f, 0.0f
         , 0.0f, 1.0f, 0.0f, 0.0f
         , 0.0f, 0.0f, 1.0f, 0.0f
         , x   , y   , z   , 1.0f);
    }
    
    template< typename T > inline Mat44< T > translate(const Vec3< T >& p)
    {
        return translate(p.a[0], p.a[1], p.a[2]);
    }
    
    template< typename T > inline Mat44< T > scale (T x, T y, T z)
    {
        return Mat44< T >
        (  x   , 0.0f, 0.0f, 0.0f
         , 0.0f, y   , 0.0f, 0.0f
         , 0.0f, 0.0f, z   , 0.0f
         , 0.0f, 0.0f, 0.0f, 1.0f);
    }
    
    template< typename T > inline Mat44< T > scale (const Vec3< T > v)
    {
        return scale(v.x, v.y, v.z);
    }
    
    template< typename T > inline Mat44< T > rotm44X (T DEG)
    {
        double s = sin( deg2rad(DEG) );
        double c = cos( deg2rad(DEG) );
        return Mat44< T >
        (  1.0f, 0.0f, 0.0f, 0.0f
         , 0.0f,  c  ,  s  , 0.0f
         , 0.0f, -s  ,  c  , 0.0f
         , 0.0f, 0.0f, 0.0f, 1.0f);
    }
    
    template< typename T > inline Mat44< T > rotm44Y (T DEG)
    {
        double s = sin( deg2rad(DEG) );
        double c = cos( deg2rad(DEG) );
//        c = clamp_close_to_zero( c );
//        s = clamp_close_to_zero( s );
        return Mat44< T >
        (    c, 0.0,  -s, 0.0
         , 0.0, 1.0, 0.0, 0.0
         ,   s, 0.0,   c, 0.0
         , 0.0, 0.0, 0.0, 1.0  );
    }
    
    template< typename T > inline Mat44< T > rotm44Z (T DEG)
    {
        double s = sin( deg2rad(DEG) );
        double c = cos( deg2rad(DEG) );
        c = zero_close_to_zero( c );
        s = zero_close_to_zero( s );
        return Mat44< T >
        (   c  ,  s  , 0.0f, 0.0f
         , -s  ,  c  , 0.0f, 0.0f
         , 0.0f, 0.0f, 1.0f, 0.0f
         , 0.0f, 0.0f, 0.0f, 1.0f);
    }
    
    template< typename T > inline Mat44< T > rotm44(const Vec3< T > &a, const Vec3< T > &b, const Vec3< T > &c)
    {
        return Mat44< T >
        (  a.x, a.y, a.z, 0.0
         , b.x, b.y, b.z, 0.0
         , c.x, c.y, c.z, 0.0
         , 0.0, 0.0, 0.0, 1.0  );
    }
    
    
    /*! @brief Determinant of 4x4 matrix */
    template< typename T > inline float det (const Mat44< T >& m)
    {
        return
        ( m[ 0 ][ 0 ] * kege::det( kege::mat33(m[ 1 ][ 1 ], m[ 2 ][ 1 ], m[ 3 ][ 1 ], m[ 1 ][ 2 ], m[ 2 ][ 2 ], m[ 3 ][ 2 ], m[ 1 ][ 3 ], m[ 2 ][ 3 ], m[ 3 ][ 3 ]) )
         -m[ 1 ][ 0 ] * kege::det( kege::mat33(m[ 0 ][ 1 ], m[ 2 ][ 1 ], m[ 3 ][ 1 ], m[ 0 ][ 2 ], m[ 2 ][ 2 ], m[ 3 ][ 2 ], m[ 0 ][ 3 ], m[ 2 ][ 3 ], m[ 3 ][ 3 ]) )
         +m[ 2 ][ 0 ] * kege::det( kege::mat33(m[ 0 ][ 1 ], m[ 1 ][ 1 ], m[ 3 ][ 1 ], m[ 0 ][ 2 ], m[ 1 ][ 2 ], m[ 3 ][ 2 ], m[ 0 ][ 3 ], m[ 1 ][ 3 ], m[ 3 ][ 3 ]) )
         -m[ 3 ][ 0 ] * kege::det( kege::mat33(m[ 0 ][ 1 ], m[ 1 ][ 1 ], m[ 2 ][ 1 ], m[ 0 ][ 2 ], m[ 1 ][ 2 ], m[ 2 ][ 2 ], m[ 0 ][ 3 ], m[ 1 ][ 3 ], m[ 2 ][ 3 ]) ) );
    }
    
    template< typename T > inline Mat44< T > adj (const Mat44< T >& m)
    {
        return Mat44< T >
        (  kege::det( kege::mat33(m[ 1 ][ 1 ], m[ 2 ][ 1 ], m[ 3 ][ 1 ], m[ 1 ][ 2 ], m[ 2 ][ 2 ], m[ 3 ][ 2 ], m[ 1 ][ 3 ], m[ 2 ][ 3 ], m[ 3 ][ 3 ]) )
         ,-kege::det( kege::mat33(m[ 1 ][ 0 ], m[ 2 ][ 0 ], m[ 3 ][ 0 ], m[ 1 ][ 2 ], m[ 2 ][ 2 ], m[ 3 ][ 2 ], m[ 1 ][ 3 ], m[ 2 ][ 3 ], m[ 3 ][ 3 ]) )
         , kege::det( kege::mat33(m[ 1 ][ 0 ], m[ 2 ][ 0 ], m[ 3 ][ 0 ], m[ 1 ][ 1 ], m[ 2 ][ 1 ], m[ 3 ][ 1 ], m[ 1 ][ 3 ], m[ 2 ][ 3 ], m[ 3 ][ 3 ]) )
         ,-kege::det( kege::mat33(m[ 1 ][ 0 ], m[ 2 ][ 0 ], m[ 3 ][ 0 ], m[ 1 ][ 1 ], m[ 2 ][ 1 ], m[ 3 ][ 1 ], m[ 1 ][ 2 ], m[ 2 ][ 2 ], m[ 3 ][ 2 ]) )
         
         ,-kege::det( kege::mat33(m[ 0 ][ 1 ], m[ 2 ][ 1 ], m[ 3 ][ 1 ], m[ 0 ][ 2 ], m[ 2 ][ 2 ], m[ 3 ][ 2 ], m[ 0 ][ 3 ], m[ 2 ][ 3 ], m[ 3 ][ 3 ]) )
         , kege::det( kege::mat33(m[ 0 ][ 0 ], m[ 2 ][ 0 ], m[ 3 ][ 0 ], m[ 0 ][ 2 ], m[ 2 ][ 2 ], m[ 3 ][ 2 ], m[ 0 ][ 3 ], m[ 2 ][ 3 ], m[ 3 ][ 3 ]) )
         ,-kege::det( kege::mat33(m[ 0 ][ 0 ], m[ 2 ][ 0 ], m[ 3 ][ 0 ], m[ 0 ][ 1 ], m[ 2 ][ 1 ], m[ 3 ][ 1 ], m[ 0 ][ 3 ], m[ 2 ][ 3 ], m[ 3 ][ 3 ]) )
         , kege::det( kege::mat33(m[ 0 ][ 0 ], m[ 2 ][ 0 ], m[ 3 ][ 0 ], m[ 0 ][ 1 ], m[ 2 ][ 1 ], m[ 3 ][ 1 ], m[ 0 ][ 2 ], m[ 2 ][ 2 ], m[ 3 ][ 2 ]) )
         
         , kege::det( kege::mat33(m[ 0 ][ 1 ], m[ 1 ][ 1 ], m[ 3 ][ 1 ], m[ 0 ][ 2 ], m[ 1 ][ 2 ], m[ 3 ][ 2 ], m[ 0 ][ 3 ], m[ 1 ][ 3 ], m[ 3 ][ 3 ]) )
         ,-kege::det( kege::mat33(m[ 0 ][ 0 ], m[ 1 ][ 0 ], m[ 3 ][ 0 ], m[ 0 ][ 2 ], m[ 1 ][ 2 ], m[ 3 ][ 2 ], m[ 0 ][ 3 ], m[ 1 ][ 3 ], m[ 3 ][ 3 ]) )
         , kege::det( kege::mat33(m[ 0 ][ 0 ], m[ 1 ][ 0 ], m[ 3 ][ 0 ], m[ 0 ][ 1 ], m[ 1 ][ 1 ], m[ 3 ][ 1 ], m[ 0 ][ 3 ], m[ 1 ][ 3 ], m[ 3 ][ 3 ]) )
         ,-kege::det( kege::mat33(m[ 0 ][ 0 ], m[ 1 ][ 0 ], m[ 3 ][ 0 ], m[ 0 ][ 1 ], m[ 1 ][ 1 ], m[ 3 ][ 1 ], m[ 0 ][ 2 ], m[ 1 ][ 2 ], m[ 3 ][ 2 ]) )
         
         ,-kege::det( kege::mat33( m[ 0 ][ 1 ], m[ 1 ][ 1 ], m[ 2 ][ 1 ], m[ 0 ][ 2 ], m[ 1 ][ 2 ], m[ 2 ][ 2 ], m[ 0 ][ 3 ], m[ 1 ][ 3 ], m[ 2 ][ 3 ] ) )
         , kege::det( kege::mat33( m[ 0 ][ 0 ], m[ 1 ][ 0 ], m[ 2 ][ 0 ], m[ 0 ][ 2 ], m[ 1 ][ 2 ], m[ 2 ][ 2 ], m[ 0 ][ 3 ], m[ 1 ][ 3 ], m[ 2 ][ 3 ] ) )
         ,-kege::det( kege::mat33( m[ 0 ][ 0 ], m[ 1 ][ 0 ], m[ 2 ][ 0 ], m[ 0 ][ 1 ], m[ 1 ][ 1 ], m[ 2 ][ 1 ], m[ 0 ][ 3 ], m[ 1 ][ 3 ], m[ 2 ][ 3 ] ) )
         , kege::det( kege::mat33( m[ 0 ][ 0 ], m[ 1 ][ 0 ], m[ 2 ][ 0 ], m[ 0 ][ 1 ], m[ 1 ][ 1 ], m[ 2 ][ 1 ], m[ 0 ][ 2 ], m[ 1 ][ 2 ], m[ 2 ][ 2 ] ) ) );
    }
    
    template< typename T > inline Mat44< T > inverse(const Mat44< T >& m)
    {
        return transpose( adj(m) ) * invrs( det(m) );
    }
    
    
    /**
     build perspective projection matrix
     @return mat44
     */
    template< typename T > inline Mat44< T > frustum(T l, T r, T b, T t, T n, T f)
    {
        T n2 = 2.0 * n;
        T rml = r - l;
        T tmb = t - b;
        T fmn = f - n;

        return Mat44<T>
        (
            n2 / rml     , 0.0          , 0.0          , 0.0,
            0.0          , n2 / tmb     , 0.0          , 0.0,
            (r + l) / rml, (t + b) / tmb, -fmn / fmn   , -1.0,
            0.0          , 0.0          , -n2 * f / fmn, 0.0
        );
    }

    /**
     build perspective projection matrix
     @return mat44
     */
    template< typename T > Mat44< T > perspproj(T fov, T aspect, T znear, T zfar)
    {
        T ymax = znear * tan(deg2rad(fov/2.0));
        T xmax = ymax * aspect;
        return frustum(-xmax, xmax, -ymax, ymax, znear, zfar);
    }

    /**
     build orthographic projection matrix
     @return mat44
     */
    template< typename T > inline Mat44< T > orthoproj(T l, T r, T b, T t, T n, T f)
    {
        return Mat44< T >
        (   2.0 / (r-l),  0.0        ,  0.0        , 0.f
         ,  0.0        ,  2.0 / (t-b),  0.0        , 0.f
         ,  0.0        ,  0.0        , -2.0 / (f-n), 0.f
         , -(r+l)/(r-l), -(t+b)/(t-b), -(f+n)/(f-n), 1.0 );
    }
    
    
    template< typename T > Vec3< T > euler_angle(const Mat44< T > &m)
    {
        //check for gimbal lock
        if (EPSILON > abs(m[ 0 ][ 2 ] - (-1.0f)))
        {
            T x = 0; //gimbal lock, value of x doesn't matter
            T y = _PI_ / 2;
            T z = x + atan2(m[ 1 ][ 0 ], m[ 2 ][ 0 ]);
            return { x, y, z };
        }
        else if (EPSILON > abs(m[ 0 ][ 2 ] - 1.0f))
        {
            T x = 0;
            T y = -_PI_ / 2;
            T z = -x + atan2(-m[ 1 ][ 0 ], -m[ 2 ][ 0 ]);
            return { x, y, z };
        }
        else
        { //two solutions exist
            T x1  = -asin(m[ 0 ][ 2 ]);
            T x2  = _PI_ - x1;
            
            T cx1 = cos(x2);
            T cx2 = cos(x2);
            
            T y1 = atan2(m[ 1 ][ 2 ] / cx1, m[ 2 ][ 2 ] / cx1);
            T y2 = atan2(m[ 1 ][ 2 ] / cx2, m[ 2 ][ 2 ] / cx2);
            T z1 = atan2(m[ 0 ][ 1 ] / cx1, m[ 0 ][ 0 ] / cx1);
            T z2 = atan2(m[ 0 ][ 1 ] / cx2, m[ 0 ][ 0 ] / cx2);
            
            //choose one solution to return
            //for example the "shortest" rotation
            if ((abs(x1) + abs(y1) + abs(z1)) <=
                (abs(x2) + abs(y2) + abs(z2)))
            {
                return Vec3< T >( x1, y1, z1 );
            }
            else
            {
                return Vec3< T >( x2, y2, z2 );
            }
        }
    }
    template< typename T > void lookat(Mat44< T >& m, const Vec3< T > &eye, const Vec3< T > &target, const Vec3< T > &up)
    {
        // forward-vector
        m[ 0 ][ 2 ] = eye.x - target.x;
        m[ 1 ][ 2 ] = eye.y - target.y;
        m[ 2 ][ 2 ] = eye.z - target.z;
        
        double distsq = invrs( sqrtf( m[ 0 ][ 2 ]*m[ 0 ][ 2 ] + m[ 1 ][ 2 ]*m[ 1 ][ 2 ] + m[ 2 ][ 2 ]*m[ 2 ][ 2 ] ) );
        m[ 0 ][ 2 ] *= distsq;
        m[ 1 ][ 2 ] *= distsq;
        m[ 2 ][ 2 ] *= distsq;
        
        // right-vector - crossprod of up and forward
        m[ 0 ][ 0 ] = (up.y*m[ 2 ][ 2 ] - up.z*m[ 1 ][ 2 ]);
        m[ 1 ][ 0 ] = (up.z*m[ 0 ][ 2 ] - up.x*m[ 2 ][ 2 ]);
        m[ 2 ][ 0 ] = (up.x*m[ 1 ][ 2 ] - up.y*m[ 0 ][ 2 ]);
        
        // up-vector - crossprod of right and forward
        m[ 0 ][ 1 ] = (m[ 1 ][ 2 ]*m[ 2 ][ 0 ] - m[ 2 ][ 2 ]*m[ 1 ][ 0 ]);
        m[ 1 ][ 1 ] = (m[ 2 ][ 2 ]*m[ 0 ][ 0 ] - m[ 0 ][ 2 ]*m[ 2 ][ 0 ]);
        m[ 2 ][ 1 ] = (m[ 0 ][ 2 ]*m[ 1 ][ 0 ] - m[ 1 ][ 2 ]*m[ 0 ][ 0 ]);
        
        // position-vector
        m[ 3 ][ 0 ] = -(eye.x*m[ 0 ][ 0 ] + eye.y*m[ 1 ][ 0 ] + eye.z*m[ 2 ][ 0 ]);
        m[ 3 ][ 1 ] = -(eye.x*m[ 0 ][ 1 ] + eye.y*m[ 1 ][ 1 ] + eye.z*m[ 2 ][ 1 ]);
        m[ 3 ][ 2 ] = -(eye.x*m[ 0 ][ 2 ] + eye.y*m[ 1 ][ 2 ] + eye.z*m[ 2 ][ 2 ]);
        
        m[ 0 ][ 3 ] = 0.0;
        m[ 1 ][ 3 ] = 0.0;
        m[ 2 ][ 3 ] = 0.0;
        m[ 3 ][ 3 ] = 1.0;
    }
    
    template< typename T > Mat44< T > lookat(const Vec3< T > &eye, const Vec3< T > &target, const Vec3< T > &up)
    {
        Mat44< T > m;
        lookat(m, eye, target, up);
        return m;
    }
    
    template< typename T > Mat44< T > makeview( const Vec3< T >& position, const Vec3< T >& direction, const Vec3< T >& up )
    {
        Mat44< T > m;

        Vec3< T > zaxis = direction;
        Vec3< T > xaxis = cross( zaxis, up );
        Vec3< T > yaxis = cross( up, xaxis );
        
        m[ 0 ][ 0 ] = xaxis.x;
        m[ 0 ][ 1 ] = xaxis.y;
        m[ 0 ][ 2 ] = xaxis.z;
        m[ 0 ][ 3 ] = 0.0f;
        m[ 1 ][ 0 ] = yaxis.x;
        m[ 1 ][ 1 ] = yaxis.y;
        m[ 1 ][ 2 ] = yaxis.z;
        m[ 1 ][ 3 ] = 0.0f;
        m[ 2 ][ 0 ] = zaxis.x;
        m[ 2 ][ 1 ] = zaxis.y;
        m[ 2 ][ 2 ] = zaxis.z;
        m[ 2 ][ 3 ] = 0.0f;
        m[ 3 ][ 0 ] = -dot(xaxis, position);
        m[ 3 ][ 1 ] = -dot(yaxis, position);
        m[ 3 ][ 2 ] = -dot(zaxis, position);
        
        return m;
    }


    
    template< typename T > Mat33< T > upper33( const Mat44< T >& m )
    {
        return Mat33< T >( m.v[0].x, m.v[0].y, m.v[0].y,  m.v[1].x, m.v[1].y, m.v[1].y,  m.v[2].x, m.v[2].y, m.v[2].y );
    }

}
