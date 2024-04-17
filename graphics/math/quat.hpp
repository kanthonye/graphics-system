//
//  quat.hpp
//  column-major
//
//  Created by Kenneth A Esdaile on 7/12/18.
//  Copyright © 2018 Kenneth A Esdaile. All rights reserved.
//

#ifndef quat_hpp
#define quat_hpp
#include "mat44.hpp"
namespace kege{
    
    template< typename T > class Quat
    {   public:

        template< typename G > friend inline bool operator ==( const Quat< T > &a, const Quat< G > &b)
        {
            return (a.x == b.x) && (a.y == b.y) && (a.z == b.z) && (a.w == b.w);
        }
    
        template< typename G > friend inline bool operator !=( const Quat< T > &a, const Quat< G > &b)
        {
            return (a.x != b.x) || (a.y != b.y) || (a.z != b.z) || (a.w != b.w);
        }
        
        /**
         * This multiplication operator multiplies the quaternion, q,
         * by the vector v as though vector v is a quaternion with its
         * scalar component w equal to 0
         */
        friend inline Quat< T > operator * (const Quat< T >& q, const Vec3< T > &v)
        {
            return Quat< T >
            ( -(q.x*v.x + q.y*v.y + q.z*v.z)
             ,  q.w*v.x + q.y*v.z - q.z*v.y
             ,  q.w*v.y + q.z*v.x - q.x*v.z
             ,  q.w*v.z + q.x*v.y - q.y*v.x );
        }
        
        /**
         * This multiplication operator multiplies the quaternion, q,
         * by the vector v as though vector v is a quaternion with its
         * scalar component w equal to 0
         */
        friend inline Quat< T > operator * (const Vec3< T > &v, const Quat< T >& q)
        {
            return Quat< T >
            ( -(q.x*v.x + q.y*v.y + q.z*v.z)
             ,  q.w*v.x + q.z*v.y - q.y*v.z
             ,  q.w*v.y + q.x*v.z - q.z*v.x
             ,  q.w*v.z + q.y*v.x - q.x*v.y );
        }
        
        friend inline Quat< T > operator +(T k, const Quat< T > &q)
        {
            return Quat< T >(k+q.w, k+q.x, k+q.y, k+q.z);
        }
        
        friend inline Quat< T > operator -(T k, const Quat< T > &q)
        {
            return Quat< T >(k-q.w, k-q.x, k-q.y, k-q.z);
        }
        
        friend inline Quat< T > operator *(T k, const Quat< T > &q)
        {
            return Quat< T >(k*q.w, k*q.x, k*q.y, k*q.z);
        }
        
        friend inline Quat< T > operator /(T k, const Quat< T > &q)
        {
            return Quat< T >
            (  k/assert_zero(q.w)
             , k/assert_zero(q.x)
             , k/assert_zero(q.y)
             , k/assert_zero(q.z) );
        }
        
        inline void operator () (T w, T x, T y, T z)
        {
            this->w = w;
            this->x = x;
            this->y = y;
            this->z = z;
        }
        
        inline void operator () ( T angle, const Vec3< T >& v)
        {
            double radian = deg2rad(angle * 0.5f);
            
            double s = sin(radian);
            this->x = v[0] * s;
            this->y = v[1] * s;
            this->z = v[2] * s;
            this->w = cos(radian);
        }
        
        inline void operator () ( T const (*v)[4] )
        {
            Quat< T >::operator()((*v)[3], Vec3< T >((*v)[0], (*v)[1], (*v)[2]));
        }
        
        inline void operator () (const Mat33< T >& m)
        {
            float trace = kege::trace(m);
            if (trace > 0.0f)
            {
                float s = 0.5f / sqrtf(trace + 1.0f);
                this->w = 0.25f / s;
                this->x = ( m[ 1 ][ 2 ] - m[ 2 ][ 1 ] ) * s;
                this->y = ( m[ 2 ][ 0 ] - m[ 0 ][ 2 ] ) * s;
                this->z = ( m[ 0 ][ 1 ] - m[ 1 ][ 0 ] ) * s;
//                this->y = (m.m20 - m.m02) * s;
//                this->z = (m.m01 - m.m10) * s;
            }
            // Negative diagonal
            else if ( m[ 0 ][ 0 ] > m[ 1 ][ 1 ] && m[ 0 ][ 0 ] > m[ 2 ][ 2 ] )
            {
                float s = 2.0f * sqrtf(m[ 0 ][ 0 ] - m[ 1 ][ 1 ] - m[ 2 ][ 2 ] +  1.0f);
                this->w = (m[ 1 ][ 2 ] - m[ 2 ][ 1 ]) / s;
                this->x = 0.25f * s;
                this->y = (m[ 1 ][ 0 ] + m[ 0 ][ 1 ]) / s;
                this->z = (m[ 2 ][ 0 ] + m[ 0 ][ 2 ]) / s;
            }
            else if (m[ 1 ][ 1 ] > m[ 2 ][ 2 ])
            {
                float s = 2.0f * sqrtf(m[ 1 ][ 1 ] - m[ 0 ][ 0 ] - m[ 2 ][ 2 ] +  1.0f);
                this->w = (m[ 2 ][ 0 ] - m[ 0 ][ 2 ]) / s;
                this->x = (m[ 1 ][ 0 ] + m[ 0 ][ 1 ]) / s;
                this->y = 0.25f * s;
                this->z = (m[ 2 ][ 1 ] + m[ 1 ][ 2 ]) / s;
            }
            else
            {
                float s = 2.0f * sqrtf(m[ 2 ][ 2 ] - m[ 0 ][ 0 ] - m[ 1 ][ 1 ] +  1.0f);
                this->w = (m[ 0 ][ 1 ] - m[ 1 ][ 0 ]) / s;
                this->x = (m[ 2 ][ 0 ] + m[ 0 ][ 2 ]) / s;
                this->y = (m[ 2 ][ 1 ] + m[ 1 ][ 2 ]) / s;
                this->z = 0.25f * s;
            }
        }

        inline void operator () (const Mat44< T >& m)
        {
            operator()( m );
        }
         
        inline Quat< T > operator + (const Quat< T > &q)const
        {
            return Quat< T >(w+q.w, x+q.x, y+q.y, z+q.z);
        }
        
        inline Quat< T > operator - (const Quat< T > &q)const
        {
            return Quat< T >(w-q.w, x-q.x, y-q.y, z-q.z);
        }
        
        inline Quat< T > operator * (const Quat< T > &q)const
        {
            return Quat< T >
            (  w*q.w - x*q.x - y*q.y - z*q.z
             , w*q.x + x*q.w + y*q.z - z*q.y
             , w*q.y - x*q.z + y*q.w + z*q.x
             , w*q.z + x*q.y - y*q.x + z*q.w  );
            return *this;
        }
        
        inline Quat< T > operator / (const Quat< T > &q)const
        {
            return (*this * q) * invrs( sq(conjugate(*this)).w );
        }
        
        inline Quat< T > operator + (T s)const
        {
            return Quat< T >(w+s, x+s, y+s, z+s);
        }
        
        inline Quat< T > operator - (T s)const
        {
            return Quat< T >(w-s, x-s, y-s, z-s);
        }
        
        inline Quat< T > operator * (T s)const
        {
            return Quat< T >(w*s, x*s, y*s, z*s);
        }
        
        inline Quat< T > operator / (T s)const
        {
            return Quat< T >(w/s, x/s, y/s, z/s);
        }
        
        inline void operator += (const Quat< T > &v)
        {
            this->operator()(w+v.w, x+v.x, y+v.y, z+v.z);
        }
        
        inline void operator -= (const Quat< T > &v)
        {
            this->operator()(w-v.w, x-v.x, y-v.y, z-v.z);
        }
        
        inline void operator *= (const Quat< T > &q)
        {
            *this = operator*(q);
        }
        
        inline void operator += ( T s )
        {
            this->operator()(w+s, x+s, y+s, z+s);
        }
        
        inline void operator -= ( T s )
        {
            x -= s;
            y -= s;
            z -= s;
            w -= s;
        }
        
        inline void operator *= ( T s )
        {
            x *= s;
            y *= s;
            z *= s;
            w *= s;
        }
        
        inline void operator /= ( T s )
        {
            x /= s;
            y /= s;
            z /= s;
            w /= s;
        }
        
        inline Quat< T > operator - (void)const
        {
            return Quat< T >(-w, -x, -y, -z);
        }
        
        /// ~q is the conjugate of the unit quaternion
        inline Quat< T > operator ~(void)const
        {
            return Quat< T >( w, -x, -y, -z);
        }
        
        inline const T& operator [](int i)const
        {
            return xyzw()[i];
        }
        
        inline T& operator [](int i)
        {
            return xyzw()[i];
        }
        
        inline const T* xyzw()const
        {
            return (T*) this;
        }
        
        inline T* xyzw()
        {
            return (T*) this;
        }
        
        /* conversion operator */
        template<typename S> inline operator Quat<S>()const
        {
            return Quat< S >( w, x, y, z );
        }
        
        Quat
        (  T a00, T a01, T a02
         , T a10, T a11, T a12
         , T a20, T a21, T a22 )
        {
            float trace = a00 + a11 + a22;
            if (trace > 1e-6)
            {
                float s = 0.5f / sqrtf(trace + 1.0f);
                w = 0.25f / s;
                x = (a12 - a21) * s;
                y = (a20 - a02) * s;
                z = (a01 - a10) * s;
            }
            // Negative diagonal
            else if ( a00 > a11 && a00 > a22 )
            {
                float s = 2.0f * sqrtf(a00 - a11 - a22 +  1.0f);
                w = (a12 - a21) / s;
                x = 0.25f * s;
                y = (a10 + a01) / s;
                z = (a20 + a02) / s;
            }
            else if (a11 > a22)
            {
                float s = 2.0f * sqrtf(a11 - a00 - a22 +  1.0f);
                w = (a20 - a02) / s;
                x = (a10 + a01) / s;
                y = 0.25f * s;
                z = (a21 + a12) / s;
            }
            else
            {
                float s = 2.0f * sqrtf(a22 - a00 - a11 +  1.0f);
                w = (a01 - a10) / s;
                x = (a20 + a02) / s;
                y = (a21 + a12) / s;
                z = 0.25f * s;
            }


//            if (trace > 1e-6)
//            {
//                float s = 0.5 / sqrt(trace);
//                x = (a21 - a12) * s;
//                y = (a02 - a20) * s;
//                z = (a10 - a01) * s;
//                w = 0.25 / s;
//            }
//            else
//            {
//                if (a00 > a11 && a00 > a22)
//                {
//                    float s = 2.0 * sqrt(1.0 + a00 - a11 - a22);
//                    x = 0.25 * s;
//                    y = (a01 + a10) / s;
//                    z = (a02 + a20) / s;
//                    w = (a21 - a12) / s;
//                }
//                else if (a11 > a22)
//                {
//                    float s = 2.0 * sqrt(1.0 + a11 - a00 - a22);
//                    x = (a01 + a10) / s;
//                    y = 0.25 * s;
//                    z = (a12 + a21) / s;
//                    w = (a02 - a20) / s;
//                }
//                else
//                {
//                    float s = 2.0 * sqrt(1.0 + a22 - a00 - a11);
//                    x = (a02 + a20) / s;
//                    y = (a12 + a21) / s;
//                    z = 0.25 * s;
//                    w = (a10 - a01) / s;
//                }
//            }
        }
        
        inline Quat(T w, T x, T y, T z)
        :  x(x) , y(y) , z(z) , w(w)
        {}
        
        inline Quat(T angle, const Vec3< T >& v)
        {
            this->operator()(angle, v);
        }
        
        inline Quat (const T (*v)[4])
        {
            operator()(v);
        }
//        
//        inline Quat(const Mat44< T >& m)
//        {
//            Quat< T >::operator()(m);
//        }
//        inline Quat(const Mat33< T >& m)
//        {
//            Quat< T >::operator()(m);
//        }
//        
        inline Quat(const Quat< T >& q)
        :  x(q.x) , y(q.y) , z(q.z) , w(q.w)
        {}
        
        inline Quat< T >()
        :  x(0.0) , y(0.0) , z(0.0) , w(1.0)
        {}
        
        T x, y, z, w;
    };
    
    typedef Quat< double > dquat;
    typedef Quat< double > quatd;
    typedef Quat< float > fquat;
    typedef Quat< float > quat;
    typedef Quat< int > quati;
}
#include "quat.inl"
#endif /* quat_hpp */
