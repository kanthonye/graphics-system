//
//  quat.cpp
//  column-major
//
//  Created by Kenneth A Esdaile on 7/12/18.
//  Copyright © 2018 Kenneth A Esdaile. All rights reserved.
//

#include "quat.hpp"

template< typename T > std::ostream& operator <<( std::ostream& os, const kege::Quat< T >& q)
{
    return (os <<"{ " << q.x <<", " << q.y <<", " << q.z <<", " << q.w << " }");
}
namespace kege{
    
    
    template< typename T > void get_zaxis( const Quat< T >& q, T& x, T& y, T& z );
    template< typename T > void get_xaxis( const Quat< T >& q, T& x, T& y, T& z );
    template< typename T > void get_yaxis( const Quat< T >& q, T& x, T& y, T& z );
    template< typename T > inline void get_xaxis( const Quat< T >& q, Vec3< T >& v ) { get_xaxis( q, v.x, v.y, v.z ); }
    template< typename T > inline void get_yaxis( const Quat< T >& q, Vec3< T >& v ) { get_yaxis( q, v.x, v.y, v.z ); }
    template< typename T > inline void get_zaxis( const Quat< T >& q, Vec3< T >& v ) { get_zaxis( q, v.x, v.y, v.z ); }
    
    /* convert Euler angles to quaternion */
    template< typename T > Quat< T > euler_to_quat(T pitch, T yaw, T roll)
    {
        float rad_pitch = deg2rad( 0.5f * pitch );
        float rad_yaw   = deg2rad( 0.5f * yaw );
        float rad_roll  = deg2rad( 0.5f * roll );
        
        const float cp = cos( rad_pitch );
        const float cy = cos( rad_yaw );
        const float cr = cos( rad_roll );
        
        const float sp = sin( rad_pitch );
        const float sy = sin( rad_yaw );
        const float sr = sin( rad_roll );
        
        const float w = cp * cy * cr + sp * sy * sr;
        const float x = sp * cy * cr - cp * sy * sr;
        const float y = cp * sy * cr + sp * cy * sr;
        const float z = cp * cy * sr - sp * sy * cr;
        
        return Quat< T >( w, x, y, z );
    }
    
    /** convert euler angles to quaternions. @return quaternion */
    template< typename T >  Quat< T > euler_to_quat(const Vec3< T >& angles)
    {
        return euler_to_quat(angles.x, angles.y, angles.z);
    }
    
    /** convert from rotation to euler angles. */
    template< typename T >  Vec3< T > quat2euler(const Quat< T >& q)
    {
        Vec3< T > euler;
        euler_angle(q, euler.x, euler.y, euler.z);
        return euler;
    }
    
    /** convert from rotation to euler angles. */
    //    Vec3< T > euler_angle(Quat< T > const& q);
    
    /** convert quaternion to euler angle roll. @return float. */
    template< typename T >  float euler_roll(const Quat< T >& q)
    {
        // roll (x-axis rotation)
        double sinr = +2.0 * (q.w * q.x + q.y * q.z);
        double cosr = +1.0 - 2.0 * (q.x * q.x + q.y * q.y);
        return atan2(sinr, cosr);
    }
    
    /** convert quaternion to euler angle pitch. @return float */
    template< typename T >  float euler_pitch(const Quat< T >& q)
    {
        // pitch (y-axis rotation)
        double sinp = +2.0 * (q.w * q.y - q.z * q.x);
        if (fabs(sinp) >= 1)
            return copysign(M_PI / 2, sinp); // use 90 degrees if out of range
        else
            return asin(sinp);
    }
    
    /** convert quaternion to euler angle yaw. @return float */
    template< typename T >  float euler_yaw(const Quat< T >& q)
    {
        // yaw (z-axis rotation)
        double siny = +2.0 * (q.w * q.z + q.x * q.y);
        double cosy = +1.0 - 2.0 * (q.y * q.y + q.z * q.z);
        return atan2(siny, cosy);
    }
    
    template< typename T > void euler_angle(const Quat< T >& q, T& roll, T& pitch, T& yaw)
    {
        // roll (x-axis rotation)
        double sinr = +2.0 * (q.w * q.x + q.y * q.z);
        double cosr = +1.0 - 2.0 * (q.x * q.x + q.y * q.y);
        roll = atan2(sinr, cosr);
        
        // pitch (y-axis rotation)
        double sinp = +2.0 * (q.w * q.y - q.z * q.x);
        if (fabs(sinp) >= 1)
            pitch = copysign(M_PI / 2, sinp); // use 90 degrees if out of range
        else
            pitch = asin(sinp);
        
        // yaw (z-axis rotation)
        double siny = +2.0 * (q.w * q.z + q.x * q.y);
        double cosy = +1.0 - 2.0 * (q.y * q.y + q.z * q.z);
        yaw = atan2(siny, cosy);
    }
    
    /* convert Euler angles to quaternion */
    template< typename T > Vec3< T > euler_angle(Quat< T > const& q)
    {
        Vec3< T > v;
        euler_angle( q, v.x, v.y, v.z);
        return v;
    }
    
    
    /** build mat44 rotation matrix using quaternion axis angle rotation. */
    template< typename T >  Quat< T > axis_angle(T angle, T x, T y, T z)
    {
        return Quat< T >(angle, Vec3< T >(x,y,z));
    }
    
    template< typename T >  Quat< T > axis_angleX(T angle)
    {
        return axis_angle(angle, 1.0, 0.0, 0.0);
    }
    
    template< typename T >  Quat< T > axis_angleY(T angle)
    {
        return axis_angle(angle, 0.0, 1.0, 0.0);
    }
    
    template< typename T >  Quat< T > axis_angleZ(T angle)
    {
        return axis_angle(angle, 0.0, 0.0, 1.0);
    }
    
    template< typename T >  Quat< T > abs(const Quat< T >& a)
    {
        return Quat< T >(abs(a.x), abs(a.y), abs(a.z), abs(a.w));
    }
    
    /** dot product of two quaternion. @return float */
    template< typename T >  T dot (const Quat< T > &a, const Quat< T > &b)
    {
        return (a.x * b.x) + (a.y * b.y) + (a.z * b.z) + (a.w * b.w);
    }
    
    /** inline function. compute the math::square magnitude of a vectors. */
    template< typename T >  double magnsq (const Quat< T >& v)
    {
        return dot(v,v);
    }
    
    /** compute the quaternion magnitude/length. @return float */
    template< typename T >  double magn (const Quat< T > &A)
    {
        return sqrt(dot(A, A));
    }
    
    /** compute the negation of a quaternion. @return quaternion */
    template< typename T >  Quat< T > conjugate (const Quat< T > &q)
    {
        return Quat< T >(q.w, -q.x, -q.y, -q.z);
    }
    
    /** computer the inverse of a quaternion. @return quaternion */
    template< typename T >  Quat< T > inverse (const Quat< T > &q)
    {
        return conjugate(q) * invrs(dot(q,q));
    }
    
    template< typename T >  Quat< T > square( const Quat< T > &q )
    {
        float s = 2.0f * q.w;
        return Quat< T >( dot(q, q), s*q.x, s*q.y, s * q.z );
    }
    
    /** normalize a quaternion. @return quaternion */
    template< typename T >  Quat< T > normalize (const Quat< T > &q)
    {
        double m = q.w*q.w + q.x*q.x + q.y*q.y + q.z*q.z;
        if (m == 0) return Quat< T >(q.x, q.y, q.z, (0.0f > q.w) ? -1.0 : 1.0);
        return q * (1.0f / sqrt(m));
    }
    
    template< typename T >  Quat< T > cross(const Quat< T >& q1, const Quat< T >& q2)
    {
        return Quat< T >
        (q1.w * q2.z + q1.z * q2.w + q1.x * q2.y - q1.y * q2.x,
         q1.w * q2.w - q1.x * q2.x - q1.y * q2.y - q1.z * q2.z,
         q1.w * q2.x + q1.x * q2.w + q1.y * q2.z - q1.z * q2.y,
         q1.w * q2.y + q1.y * q2.w + q1.z * q2.x - q1.x * q2.z);
    }
    
    
    
    
//    template< typename T > void vmp_QuatToMatrix(const Quat< T >& const pqA, Mat33< T > dMx)
//    {
//        float fMag;
//        float fxx, fyy, fzz, fwx, fwy, fwz, fxy, fxz, fyz;
//
//        fxx = pqA->x * pqA->x;
//        fyy = pqA->y * pqA->y;
//        fzz = pqA->z * pqA->z;
//
//        fMag = fxx + fyy + fzz + (pqA->w * pqA->w);
//        if (0.0f < fMag)
//        {
//            fMag = 2.0f / fMag;
//            fxx *= fMag;
//            fyy *= fMag;
//            fzz *= fMag;
//        }
//
//        fwx = pqA->w * pqA->x * fMag;
//        fwy = pqA->w * pqA->y * fMag;
//        fwz = pqA->w * pqA->z * fMag;
//        fxy = pqA->x * pqA->y * fMag;
//        fxz = pqA->x * pqA->z * fMag;
//        fyz = pqA->y * pqA->z * fMag;
//    }
    
//    template< typename T > void exp( const Quat< T > &pqD, const Quat< T > &pqA)
//    {
//        float fMag, fSin;
//
//        fMag = pqA->x*pqA->x + pqA->y*pqA->y + pqA->z*pqA->z;
//        if (0.00005f <= fMag) // Not too close to zero?
//        {
//            fMag = sqrt(fMag);
//            vmp_FSinCos(&fSin, &(pqD->w), fMag);
//
//            fMag = fSin / fMag;
//            pqD->x = pqA->x * fMag;
//            pqD->y = pqA->y * fMag;
//            pqD->z = pqA->z * fMag;
//        }
//        else
//        {
//            pqD->w = 1.0f;
//            pqD->x = pqD->y = pqD->z = 0.0f;
//        }
//    }
    
    template< typename T > void lnq(Quat< T > * const r, const Quat< T > * const a)
    {
        float fMag, fSin;
        
        fMag = acosf( a->w );
        fSin = sinf( fMag );
        r->w = 0.0f;
        if (0.0f != fSin)
        {
            fSin = fMag / fSin;
            r->x = a->x * fSin; r->y = a->y * fSin; r->z = a->z * fSin;
        }
        else
        {
            r->x = r->y = r->z = 0.0f;
        }
    }
    
    template< typename T > void sqrtq(Quat< T > * const a, const Quat< T > * const b)
    {
        Quat< T > q;
        float fx, fy, fMag, fLen;
        
        fLen = sqrtf(b->x * b->x + b->y * b->y + b->w * b->w);
        fLen = (0.0f != fLen) ? 1.0f / fLen : 1.0f;
        q.x = b->x * fLen;
        q.y = b->z * fLen;
        q.z = b->z;
        q.w = b->w * fLen;
        
        fMag = 1.0 / sqrtf( q.w * q.w + q.x * q.x );
        fx = sqrtf( (1.0f - q.y) * 0.5f );
        fy = sqrtf( (1.0f + q.y) * 0.5f );
        fLen = sqrtf( fLen );
        
        a->x = q.x * fLen * fx * fMag;
        a->y = fLen * fy;
        a->z = q.z;
        a->w = q.w * fLen * fy * fMag;
    }
    
    template< typename T > void normalize (Quat< T > &p, const Quat< T > &q)
    {
        float m = dot(p,p);
        if (m == 0)
        {
            p.x = q.x;
            p.y = q.y;
            p.z = q.z;
            if (0.0f > q.w) p.w = -1.0f;
            else p.w = 1.0f;
        }
        else
        {
            m = 1.0f / sqrt( m );
            p.x = q.x*m;
            p.y = q.y*m;
            p.z = q.z*m;
            p.w = q.w*m;
        }
    }
    
    template< typename T > Quat< T > log(const Quat< T > &q)
    {
        float m, s;
        
        m = acosf( q.w );
        s = sinf( m );
        
        if (0.0f != s) {
            s  = m / s;
            return Quat< T >(0.0f, q.x*s, q.y*s, q.z*s);
        } else {
            return Quat< T >(0.0f, 0.0f, 0.0f, 0.0f);
        }
    }
    
    template<typename T> kege::Quat<T> mix(const kege::Quat<T>& from, const kege::Quat<T>& to, float t)
    {
        return from * (1.0f - t) + to * t;
    }
    
    template<typename T> kege::Quat<T> nlerp(const kege::Quat<T>& from, const kege::Quat<T>& to, float t)
    {
        return kege::normalize( kege::mix(from, to, t) );
    }
    
    template<typename T> kege::Quat<T> from_to(const vec3& from, const vec3& to) 
    { 
        Vec3<T> f = normalize(from); 
        Vec3<T> t = normalize(to);
        if (f == t) 
        { 
            return kege::Quat<T>(); 
        }
        else if (f == t * -1.0f) 
        { 
            kege::Vec3<T> ortho = kege::Vec3<T>(1, 0, 0); 
            if ( fabsf(f.y) < fabsf(f.x)) 
            { 
                ortho = kege::Vec3<T>(0, 1, 0); 
            } 
            if ( fabsf(f.z) < fabs(f.y) && fabs(f.z) < fabsf(f.x) )
            { 
                ortho = kege::Vec3<T>(0, 0, 1);
            } 
            Vec3<T> axis = kege::normalize( kege::cross(f, ortho) ); 
            return kege::Quat<T>(axis.x, axis.y, axis.z, 0); 
        }
        kege::Vec3<T> half = kege::normalize(f + t);
        kege::Vec3<T> axis = kege::cross(f, half); 
        return kege::Quat<T>(axis.x, axis.y, axis.z, kege::dot(f, half));
    }

    template<typename T> kege::Quat<T> look_rotation(const kege::Quat<T>& direction, const kege::Quat<T>& up) 
    { 
        // Find orthonormal basis vectors 
        kege::Vec3<T> f = normalize(direction); // Object Forward 
        kege::Vec3<T> u = normalize(up); // Desired Up 
        kege::Vec3<T> r = cross(u, f); // Object Right 
        u = kege::cross(f, r); // Object Up
        // From world forward to object forward 
        kege::Quat<T> world_to_object = from_to( kege::Vec3<T>(0, 0, 1), f );  // what direction is the new object up? 
        kege::Vec3<T> object_up = world_to_object * kege::Vec3<T>(0, 1, 0);  // From object up to desired up 
        kege::Quat<T> u2u = from_to(object_up, u); 
        // Rotate to forward direction first 
        // then twist to correct up 
        kege::Quat<T> result = world_to_object * u2u; 
        // Don't forget to normalize the result
        return normalize(result);
    }

    template< typename T > Quat< T > slerp(const Quat< T >& start, const Quat< T >& end, double t)
    {
        // slerp = (q0 * sin((1-t) + theta) + q1 * sin(theta)) / sin(theta)
        // Compute the cosine of the angle between the two vectors.
        // cos(theta/2) = qa.w*qb.w + qa.x*qb.x + qa.y*qb.y+ qa.z*qb.z
        double d = kege::dot(start, end);

        // If the dot product is negative, slerp won't take
        // the shorter path. Note that v1 and -v1 are equivalent when
        // the negation is applied to all four components. Fix by
        // reversing one quaternion.
        Quat< T > q = end;
        if (d < 0.0f)
        {
            q = -q;
            d = -d;
        }

        if (d > 0.9995)
        {
            // If the inputs are too close, linearly interpolate
            return lerp(start, q, t);
        }

        // Since dot is in range [0, DOT_THRESHOLD], acos is safe
        double theta_0 = acos(d);        // theta_0 = angle between input vectors
        double theta = theta_0*t;          // theta = angle between v0 and result
        double sin_theta = sin(theta);     // compute this value only once
        double sin_theta_0 = sin(theta_0); // compute this value only once

        double s0 = cos(theta) - d * sin_theta / sin_theta_0;  // == sin(theta_0 - theta) / sin(theta_0)
        double s1 = sin_theta / sin_theta_0;

        return (s0 * start) + (s1 * q);
    }
    
    template< typename T > Quat< T > power(const Quat< T > &q, float exponent)
    {
        // Check for the case of an identity quaternion.
        // This will protect against divide by zero
        if (fabs(q.w) > .9999f) {
            return q;
        }
        // Extract the half angle alpha (alpha = theta/2)
        float alpha = acos(q.w);
        // Compute new alpha value
        float newAlpha = alpha * exponent;
        // Compute new w value
        Quat< T > result;
        result.w = cos(newAlpha);
        // Compute new xyz values
        float mult = sin(newAlpha) / sin(alpha); result.x = q.x * mult;
        result.y = q.y * mult;
        result.z = q.z * mult;
        // Return it
        return result;
    }
    
    
    template< typename T > Quat< T > quatsqrt(const Quat< T > &pqA)
    {
        Quat< T > qT;
        float fx, fy, fMag, fLen;
        fLen = sqrtf(pqA.x * pqA.x + pqA.y * pqA.y + pqA.w * pqA.w);
        
        fLen = (0.0f != fLen) ? 1.0f / fLen : 1.0f;
        qT.x = pqA.x * fLen;
        qT.y = pqA.z * fLen;
        qT.z = pqA.z;
        qT.w = pqA.w * fLen;
        
        fMag = 1.0f / sqrtf( qT.w * qT.w + qT.x * qT.x );
        fx   = sqrtf( (1.0f - qT.y) * 0.5f );
        fy   = sqrtf( (1.0f + qT.y) * 0.5f );
        fLen = sqrtf( fLen );
        
        return Quat< T >
        (  qT.w * fLen * fy * fMag
         , qT.x* fLen * fx * fMag
         , fLen * fy
         , qT.z  );
    }
    
//    // Converting a normalized quaternion to a 3 × 3 rotation matrix takes the following form:
//    // | 1 - 2 * (yy - zz) |     2 * (xy - zw) |     2 * (xz + yw) |
//    // |     2 * (xy + zw) | 1 - 2 * (xx - zz) |     2 * (yz - xw) |
//    // |     2 * (xz - yw) |     2 * (yz + xw) | 1 - 2 * (xx - yy) |
//    template< typename T > void normalized_quaternion_3x3
//    (  T& Xx, T& Xy, T& Xz
//     , T& Yx, T& Yy, T& Yz
//     , T& Zx, T& Zy, T& Zz
//     , const Quat< T >& q )
//    {
//        T xx = (q.x * q.x);
//        T xy = (q.x * q.y);
//        T xz = (q.x * q.z);
//        T xw = (q.w * q.x);
//
//        T yy = (q.y * q.y);
//        T yz = (q.y * q.z);
//        T yw = (q.w * q.y);
//
//        T zz = (q.z * q.z);
//        T zw = (q.w * q.z);
//
//        Xx = 1 - (yy - zz) * 2.0;
//        Xy =     (xy + zw) * 2.0;
//        Xz =     (xz - yw) * 2.0;
//
//        Yx =     (xy - zw) * 2.0;
//        Yy = 1 - (xx - zz) * 2.0;
//        Yz =     (yz + xw) * 2.0;
//
//        Zx =     (xz + yw) * 2.0;
//        Zy =     (yz - xw) * 2.0;
//        Zz = 1 - (xx - yy) * 2.0;
//    }
//    
    
    

    
    template< typename T > void quat2m33
    (  const Quat< T >& q
     , T& Xx, T& Xy, T& Xz
     , T& Yx, T& Yy, T& Yz
     , T& Zx, T& Zy, T& Zz  )
    {
        double xx = (q.x * q.x);
        double yy = (q.y * q.y);
        double zz = (q.z * q.z);
        
        double xy = (q.x * q.y);
        double xz = (q.x * q.z);
        double yz = (q.y * q.z);
        
        double xw = (q.w * q.x);
        double yw = (q.w * q.y);
        double zw = (q.w * q.z);
        
        Xx = 1.0 - (yy + zz) * 2.0; // 0
        Xy =       (xy + zw) * 2.0; // 1
        Xz =       (xz - yw) * 2.0; // 2
        
        Yx =       (xy - zw) * 2.0; // 3
        Yy = 1.0 - (xx + zz) * 2.0; // 4
        Yz =       (yz + xw) * 2.0; // 5
        
        Zx =       (xz + yw) * 2.0; // 6
        Zy =       (yz - xw) * 2.0; // 7
        Zz = 1.0 - (xx + yy) * 2.0; // 8
    }

    template< typename T > void quat2m33
    (  const Quat< T >& q
     , Vec3< T >& x
     , Vec3< T >& y
     , Vec3< T >& z  )
    {
        quat2m33
        (  q
         , x[0], x[1], x[2]
         , y[0], y[1], y[2]
         , z[0], z[1], z[2]  );
    }

    template< typename T > void get_xaxis( const Quat< T >& q, T& x, T& y, T& z )
    {
        T xy = (q.x * q.y);
        T xz = (q.x * q.z);
        
        T yy = (q.y * q.y);
        T yw = (q.w * q.y);

        T zz = (q.z * q.z);
        T zw = (q.w * q.z);
        
        x = 1 - (yy + zz) * 2.0;
        y =     (xy + zw) * 2.0;
        z =     (xz - yw) * 2.0;
    }
    
    template< typename T > void get_yaxis( const Quat< T >& q, T& x, T& y, T& z )
    {
        T xx = (q.x * q.x);
        T xy = (q.x * q.y);
        T xw = (q.w * q.x);
        
        T yz = (q.y * q.z);
        
        T zz = (q.z * q.z);
        T zw = (q.w * q.z);
        
        x =     (xy - zw) * 2.0;
        y = 1 - (xx + zz) * 2.0;
        z =     (yz + xw) * 2.0;
    }
    
    template< typename T > void get_zaxis( const Quat< T >& q, T& x, T& y, T& z )
    {
        T xx = (q.x * q.x);
        T xz = (q.x * q.z);
        T xw = (q.w * q.x);
        
        T yy = (q.y * q.y);
        T yz = (q.y * q.z);
        T yw = (q.w * q.y);
        
        x =     (xz + yw) * 2.0;
        y =     (yz - xw) * 2.0;
        z = 1 - (xx + yy) * 2.0;
    }
    
    
    /** build mat44 rotation matrix using quaternion. */
    template< typename T >  Mat44< T > rotm44(T angle, T x, T y, T z)
    {
        return quat_to_mat44( axis_angle(angle, x,y,z) );
    }
    
    /** build mat44 rotation matrix using quaternion. */
    template< typename T >  Mat44< T > rotm44(T pitch, T yaw, T roll)
    {
        return quat_to_mat44( euler_to_quat(pitch,yaw,roll) );
    }
    
    template< typename T > Mat33< T > quat_to_mat33(const Quat< T > & q)
    {
        Mat33< T > mat;
        quat_to_mat33(mat, q);
        return mat;
    }
    
    template< typename T > void mat33_to_quat(const Mat33< T > &m, Quat< T > &q)
    {
        float trace = m[ 0 ][ 0 ] + m[ 1 ][ 1 ] + m[ 2 ][ 2 ];
        if (trace > 0.0f)
        {
            float s = 0.5f / sqrtf(trace + 1.0f);
            q.w = 0.25f / s;
            q.x = (m[ 1 ][ 2 ] - m[ 2 ][ 1 ]) * s;
            q.y = (m[ 2 ][ 0 ] - m[ 0 ][ 2 ]) * s;
            q.z = (m[ 0 ][ 1 ] - m[ 1 ][ 0 ]) * s;
        }
        // Negative diagonal
        else if ( m[ 0 ][ 0 ] > m[ 1 ][ 1 ] && m[ 0 ][ 0 ] > m[ 2 ][ 2 ] )
        {
            float s = 2.0f * sqrtf(m[ 0 ][ 0 ] - m[ 1 ][ 1 ] - m[ 2 ][ 2 ] +  1.0f);
            q.w = (m[ 1 ][ 2 ] - m[ 2 ][ 1 ]) / s;
            q.x = 0.25f * s;
            q.y = (m[ 1 ][ 0 ] + m[ 0 ][ 1 ]) / s;
            q.z = (m[ 2 ][ 0 ] + m[ 0 ][ 2 ]) / s;
        }
        else if (m[ 1 ][ 1 ] > m[ 2 ][ 2 ])
        {
            float s = 2.0f * sqrtf(m[ 1 ][ 1 ] - m[ 0 ][ 0 ] - m[ 2 ][ 2 ] +  1.0f);
            q.w = (m[ 2 ][ 0 ] - m[ 0 ][ 2 ]) / s;
            q.x = (m[ 1 ][ 0 ] + m[ 0 ][ 1 ]) / s;
            q.y = 0.25f * s;
            q.z = (m[ 2 ][ 1 ] + m[ 1 ][ 2 ]) / s;
        }
        else
        {
            float s = 2.0f * sqrtf(m[ 2 ][ 2 ] - m[ 0 ][ 0 ] - m[ 1 ][ 1 ] +  1.0f);
            q.w = (m[ 0 ][ 1 ] - m[ 1 ][ 0 ]) / s;
            q.x = (m[ 2 ][ 0 ] + m[ 0 ][ 2 ]) / s;
            q.y = (m[ 2 ][ 1 ] + m[ 1 ][ 2 ]) / s;
            q.z = 0.25f * s;
        }
    }
    
    template< typename T > void mat44_to_quat(Quat< T > &q, const Mat44< T > &m)
    {
        float trace = m[ 0 ][ 0 ] + m[ 1 ][ 1 ] + m[ 2 ][ 2 ];
        if (trace > 0.0f)
        {
            float s = 0.5f / sqrtf(trace + 1.0f);
            q.w = 0.25f / s;
            q.x = (m[ 1 ][ 2 ] - m[ 2 ][ 1 ]) * s;
            q.y = (m[ 2 ][ 0 ] - m[ 0 ][ 2 ]) * s;
            q.z = (m[ 0 ][ 1 ] - m[ 1 ][ 0 ]) * s;
        }
        // Negative diagonal
        else if ( m[ 0 ][ 0 ] > m[ 1 ][ 1 ] && m[ 0 ][ 0 ] > m[ 2 ][ 2 ] )
        {
            float s = 2.0f * sqrtf(m[ 0 ][ 0 ] - m[ 1 ][ 1 ] - m[ 2 ][ 2 ] +  1.0f);
            q.w = (m[ 1 ][ 2 ] - m[ 2 ][ 1 ]) / s;
            q.x = 0.25f * s;
            q.y = (m[ 1 ][ 0 ] + m[ 0 ][ 1 ]) / s;
            q.z = (m[ 2 ][ 0 ] + m[ 0 ][ 2 ]) / s;
        }
        else if (m[ 1 ][ 1 ] > m[ 2 ][ 2 ])
        {
            float s = 2.0f * sqrtf(m[ 1 ][ 1 ] - m[ 0 ][ 0 ] - m[ 2 ][ 2 ] +  1.0f);
            q.w = (m[ 2 ][ 0 ] - m[ 0 ][ 2 ]) / s;
            q.x = (m[ 1 ][ 0 ] + m[ 0 ][ 1 ]) / s;
            q.y = 0.25f * s;
            q.z = (m[ 2 ][ 1 ] + m[ 1 ][ 2 ]) / s;
        }
        else
        {
            float s = 2.0f * sqrtf(m[ 2 ][ 2 ] - m[ 0 ][ 0 ] - m[ 1 ][ 1 ] +  1.0f);
            q.w = (m[ 0 ][ 1 ] - m[ 1 ][ 0 ]) / s;
            q.x = (m[ 2 ][ 0 ] + m[ 0 ][ 2 ]) / s;
            q.y = (m[ 2 ][ 1 ] + m[ 1 ][ 2 ]) / s;
            q.z = 0.25f * s;
        }
    }
    
    template< typename T > void view_matrix(Mat44< T >& m, const Vec3< T >& p, const Vec3< T >& r, const Vec3< T >& u, const Vec3< T >& f)
    {
        m.col( 0, r );
        m.col( 1, r );
        m.col( 2, r );
        
        m[ 3 ][ 0 ] = -dot(r, p);
        m[ 3 ][ 1 ] = -dot(u, p);
        m[ 3 ][ 2 ] = -dot(f, p);
        
        m[ 0 ][ 3 ] = 0.0f;
        m[ 1 ][ 3 ] = 0.0f;
        m[ 2 ][ 3 ] = 0.0f;
        m[ 3 ][ 3 ] = 1.0f;
    }
    
    template< typename T > void quat_to_basis(const Quat< T >& q, Vec3< T > &r, Vec3< T > &u, Vec3< T > &f)
    {
        quat2m33( q, r.dptr(), u.dptr(), f.dptr() );
    }
    
    template< typename T > void quat_to_mat33(Mat33< T > &m, const Quat< T >& q)
    {
        quat2m33
        (  q
         , m[ 0 ][ 0 ], m[ 0 ][ 1 ], m[ 0 ][ 2 ]
         , m[ 1 ][ 0 ], m[ 1 ][ 1 ], m[ 1 ][ 2 ]
         , m[ 2 ][ 0 ], m[ 2 ][ 1 ], m[ 2 ][ 2 ]  );
//        quat2m33( q, m[ 0 ], m[ 1 ], m[ 2 ] );
    }
    
    // set quaternion rotation to matrix @mat.
    template< typename T > void quat_to_mat44(const Quat< T > & q, Mat44< T > &m)
    {
        quat2m33
        (  q
         , m[ 0 ][ 0 ], m[ 0 ][ 1 ], m[ 0 ][ 2 ]
         , m[ 1 ][ 0 ], m[ 1 ][ 1 ], m[ 1 ][ 2 ]
         , m[ 2 ][ 0 ], m[ 2 ][ 1 ], m[ 2 ][ 2 ] );
        
        m[ 0 ][ 3 ] = 0.0;
        m[ 1 ][ 3 ] = 0.0;
        m[ 2 ][ 3 ] = 0.0;
        m[ 3 ][ 0 ] = 0.0;
        m[ 3 ][ 1 ] = 0.0;
        m[ 3 ][ 2 ] = 0.0;
        m[ 3 ][ 3 ] = 1.0;
    }
    
    template< typename T > Mat44< T > quat_to_mat44(const Quat< T > & q)
    {
        Mat44< T > mat;
        quat_to_mat44(q, mat);
        return mat;
    }
    
    /** build view matrix from quaternion rotation and position. */
    template< typename T > void view_matrix(Mat44< T >& m, const Quat< T >& rotation, const Vec3< T >& eye)
    {
        m.zero();
        m[ 3 ][ 3 ] = 1.0f;
        
//        quat2m33
//        (  rotation
//         , m[ 0 ][ 0 ], m[ 0 ][ 1 ], m[ 0 ][ 2 ]
//         , m[ 0 ][ 1 ], m[ 1 ][ 1 ], m[ 1 ][ 2 ]
//         , m[ 0 ][ 2 ], m[ 2 ][ 1 ], m[ 2 ][ 2 ]  );

        quat2m33
        (  rotation
         , m[ 0 ][ 0 ], m[ 1 ][ 0 ], m[ 2 ][ 0 ]
         , m[ 0 ][ 1 ], m[ 1 ][ 1 ], m[ 2 ][ 1 ]
         , m[ 0 ][ 2 ], m[ 1 ][ 2 ], m[ 2 ][ 2 ]  );

        m[ 3 ][ 0 ] = -dot(eye, m[0].xyz());
        m[ 3 ][ 1 ] = -dot(eye, m[1].xyz());
        m[ 3 ][ 2 ] = -dot(eye, m[2].xyz());
        m[ 3 ][ 3 ] = 1.0;
    }
    
    /** build view matrix from quaternion rotation and position. */
    template< typename T > Mat44< T > view_matrix(const Quat< T > & q, const Vec3< T >& eye)
    {
        Mat44< T > m;
        view_matrix(m, q, eye);
        return m;
    }
    
    /** build model matrix from quaternion rotation and position. */
    template< typename T > Mat44< T > model_matrix(const Quat< T >& rotation, const Vec3< T >& position)
    {
        Mat44< T > m;
        m.zero();
        
        quat2m33
        (  rotation
         , m[ 0 ][ 0 ], m[ 0 ][ 1 ], m[ 0 ][ 2 ]
         , m[ 1 ][ 0 ], m[ 1 ][ 1 ], m[ 1 ][ 2 ]
         , m[ 2 ][ 0 ], m[ 2 ][ 1 ], m[ 2 ][ 2 ]  );
        
        m[ 3 ][ 0 ] = position.x;
        m[ 3 ][ 1 ] = position.y;
        m[ 3 ][ 2 ] = position.z;
        m[ 3 ][ 3 ] = 1.0;
        
        return m;
    }
    
    template< typename T > Mat44< T > model_matrix(const Quat< T > & rotation, const Vec3< T >& scale, const Vec3< T >& position)
    {
        Mat44< T > m;
        
        quat2m33
        (  rotation
         , m[ 0 ][ 0 ], m[ 0 ][ 1 ], m[ 0 ][ 2 ]
         , m[ 1 ][ 0 ], m[ 1 ][ 1 ], m[ 1 ][ 2 ]
         , m[ 2 ][ 0 ], m[ 2 ][ 1 ], m[ 2 ][ 2 ]  );
        
        m[ 0 ][ 0 ] *= scale[0];
        m[ 1 ][ 0 ] *= scale[0];
        m[ 2 ][ 0 ] *= scale[0];
        m[ 3 ][ 0 ]  = position[0];
        
        m[ 0 ][ 1 ] *= scale[1];
        m[ 1 ][ 1 ] *= scale[1];
        m[ 2 ][ 1 ] *= scale[1];
        m[ 3 ][ 1 ]  = position[1];
        
        m[ 0 ][ 2 ] *= scale[2];
        m[ 1 ][ 2 ] *= scale[2];
        m[ 2 ][ 2 ] *= scale[2];
        m[ 3 ][ 2 ]  = position[2];
        
        m[ 0 ][ 3 ] = 0.0f;
        m[ 1 ][ 3 ] = 0.0f;
        m[ 2 ][ 3 ] = 0.0f;
        m[ 3 ][ 3 ] = 1.0f;
        return m;
    }
    
    
    template< typename T, typename J > Vec3< T > rotate(const Quat< T >& q, const Vec3< J >& v)
    {
        // Extract the vector part of the quaternion
        Vec3< J > u(q.x, q.y, q.z);
        
        // Extract the scalar part of the quaternion
        float s = q.w;
        
        // Do the math
        return 2.0f * dot(u, v) * u + (s*s - dot(u, u)) * v + 2.0f * s * cross(u, v);
    }
    
    template< typename T > Mat44< T > fps_view_RH( vec3 eye, float pitch, float yaw )
    {
        // I assume the values are already converted to radians.
        float cos_pitch = cos(pitch);
        float sin_pitch = sin(pitch);
        float cos_yaw   = cos(yaw);
        float sin_yaw   = sin(yaw);

        vec3 xaxis = { cos_yaw            , 0        , -sin_yaw             };
        vec3 yaxis = { sin_yaw * sin_pitch, cos_pitch, cos_yaw * sin_pitch  };
        vec3 zaxis = { sin_yaw * cos_pitch, -sin_pitch, cos_pitch * cos_yaw };

        // Create a 4x4 view matrix from the right, up, forward and eye position vectors
        Mat44< T > view_matrix = 
        {
            Vec4< T >(         xaxis.a[0],         yaxis.a[0],         zaxis.a[0], 0 ),
            Vec4< T >(         xaxis.a[1],         yaxis.a[1],         zaxis.a[1], 0 ),
            Vec4< T >(         xaxis.a[2],         yaxis.a[2],         zaxis.a[2], 0 ),
            Vec4< T >( -dot( xaxis, eye ), -dot( yaxis, eye ), -dot( zaxis, eye ), 1 )
        };
        return view_matrix;
    }
}
