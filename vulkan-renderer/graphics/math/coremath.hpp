//
//  coremath.hpp
//  vector-math
//
//  Created by Kenneth A Esdaile on 6/6/18.
//  Copyright © 2018 Kenneth A Esdaile. All rights reserved.
//

#ifndef core_math_hpp
#define core_math_hpp
#include <math.h>
#include <cmath>
#include <time.h>
#include <stdlib.h>
#include <iomanip>
#include <iostream>

#define OR ||
#define AND &&

#define FALSE           0x0
#define TRUE            0x1
#define VALID           0x0
#define INVALID         0x1

#define _CLOSE_TO_ZERO_ 1e-06
#define _1_DIV_255      0.0039215686
#define _1_DIV_765      0.0013071895
#define EPSILON         1.19209e-07

#define _E_             2.71828182845904509079559829843
#define _GOLDEN_RATIO_  1.61803398874989490252573887119
#define _PI_            3.14159265358979311599796346854
#define _2PI_           6.28318530717958623199592693709
#define _PI_OVER_180_   0.01745329251994329547437168059
#define _180_OVER_PI_   57.2957795130823228646477218717
#define _PI_OVER_360_   0.00872664625
#define ONE_DEG_IN_RAD  0.01745329251

#define _sqrt_2_        1.4142135623730951454746218587
#define _sqrt_3_        0.7320508075688772935274463415
#define _sqrt_5_        2.2360679774997898050514777423
#define _sqrt_6_        2.4494897427831778813356322643
#define _sqrt_7_        2.6457513110645907161710965738
#define _sqrt_8_        2.8284271247461902909492437174
#define _sqrt_10_       3.1622776601683795227870632516
#define _sqrt_13_       3.6055512754639891248586991423
#define _sqrt_14_       3.7416573867739413294941641652
#define _sqrt_15_       3.8729833462074170213895740744
#define _1_OVER_sqrt2_  0.7071067811865474617150084668
#define _1_OVER_sqrt5_  0.4472135954999579277036048097

// scalar math
namespace kege{

    enum Axes
    {
        X_AXIS = 0x0,
        Y_AXIS = 0x1,
        Z_AXIS = 0x2,
    };


    /** check for division by zero @return 1.0 if value is zero, or value if value is not zero */
    template <typename var>
    var assert_zero(var val)
    {
        return (val == 0)? 1.0: val;
    }
    
    inline double zero_close_to_zero(double val)
    {
        return (_CLOSE_TO_ZERO_ >= val) ? 0x0: val;
    }
    
    /** invert a value @return (1.0 / val) */
    inline double invrs(double val)
    {
        return (val == 0.0)? 1.0: 1.0 / val;
    }
    
    /** converts degree to radian @return radian */
    template <typename var>
    inline var deg2rad(var deg)
    {
        return deg * (var(_PI_) / 180.0);//_PI_OVER_180_;
    }
    
    /** converts radian to degree @return degree */
    template <typename var>
    inline var rad2deg(var deg)
    {
        return deg * _180_OVER_PI_;
    }
    
    /** return the val*val */
    template <typename var>
    inline var sq(var v)
    {
        return v*v;
    }
    
    /** return the +val */
    template <typename var>
    inline var abs(var v)
    {
        return (v < 0x0) ? -v : v;
    }
    
    template <typename var>
    /** @brief return the fraction part of a floating point number ex: 5.125 returns 0.125 */
    inline var fract(var n)
    {
        return n - int(n);
    }
    
    /** keep value v between values a and b */
    template<typename type, typename typa, typename typb>  type clamp(type val, typa min, typb max)
    {
        return (val <= min) ? min: (val >= max)? max: val;
    }

    /** @brief return the smallest of the two values */
    template<typename T1, typename T2>
    inline T1 min(T1 x, T2 y)
    {
        return (x<y) ? x: y;
    }

    /** return the smallest of the three values */
    template<typename type, typename typa, typename typb>
    inline type min(type x, typa y, typb z)
    {
        return (x<y && x<z) ? x: (y<z)? y: z;
    }
    
    /** return the smallest of the four values */
    template<typename type, typename typa, typename typb, typename typc>
    inline type min(type x, typa y, typb z, typc w)
    {
        return (x<y && x<z && x<w) ? x: (y<z && y<w)? y: (z<w)? z: w;
    }
    
    /** return the largest of the two values */
    template<typename type, typename typa>  inline type max(type x, typa y)
    {
        return (x>y) ? x: y;
    }
    
    /** return the largest of the three values */
    template<typename type, typename typa, typename typb>
    inline type max(type x, typa y, typb z)
    {
        return (x>y&&x>z) ? x: (y>z)? y: z;
    }
    
    /** return the largest of the four values */
    template<typename type, typename typa, typename typb, typename typc>
    inline type max(type x, typa y, typb z, typc w)
    {
        return (x>y && x>z && x>w) ? x: (y>z && y>w)? y: (z>w)? z: w;
    }
    
    /** cycle function loop a value between values min and max */
    template<typename type, typename typa, typename typb>
    type cycle(type val, typa min, typb max)
    {
        return (val > max)? val-max : (val < min) ? min-val : val;
    }
    
    /** linear interpulate between values a and b using t. t being {0 <= t <= 1} */
    template<typename type, typename typa>  inline type lerp(type a, typa b, double t)
    {
        return (b - a) * t + a;
    }
    
    /** linear interpulate between values a and b using t. t being {0 <= t <= 1} */
    template<typename type>  inline void swap(type& a, type& b, type& t)
    {
        t=a;
        a=b;
        b=t;
    }
    
    inline bool samesign( double a, double b )
    {
        return (a < 0) ? b < 0 : b >= 0;
    }
    
    /** start is starting speed, end is the final speed, step is the speed to increment by */
    inline float smoothing(float start, const float end,const float step)
    {
        //if(start >= -step && start <= step) start = 0.0f;
        float ds = end - start;
        return (ds > step) ? (start + step) : ( (ds < -step) ? (start - step) : end );
    }
    
    inline float smoothin(float start, const float end,const float step)
    {
        if (start >= -step && start <= step) start = 0.0f;
        float ds = end - start;
        return (ds > step)? start + step: end;
    }
    
    inline float smoothout(float start, const float end,const float step)
    {
        if (start >= -step && start <= step) start = 0.0f;
        float ds = end - start;
        return (ds < step)? start - step: end;
    }
    
    template<typename typa, typename typb, typename typc>
    inline typa unitize(typa val, typb min, typc max)
    {
        val = kege::clamp(val, min, max);
        return (val - min) / (max - min);
    }
    
    /** flip an image or array along its horizontal */
    template<typename type> void flip_hori(int width, int height, type* m)
    {
        type temp;
        long a,b,wz,x,z;
        long w  = width-1;
        long hw = width/2;
        for (z=0; z<height; z++)
        {
            wz = (width*z);
            for (x=0; x<hw; x++)
            {
                a = wz + x;
                b = wz + w - x;
                temp = m[a];
                m[a] = m[b];
                m[b] = temp;
            }
        }
    }
    
    /** flip an image or array along its vertical */
    template<typename type> void flip_vert(int width, int height, type* m)
    {
        type temp;
        long a,b,x,z;
        long h  = height-1;
        long hh = height/2;
        for (x=0; x<width; x++)
        {
            for (z=0; z<hh; z++)
            {
                a = (width * z) + x;
                b = (width * (h-z)) + x;
                temp = m[a];
                m[a] = m[b];
                m[b] = temp;
            }
        }
    }
    
    inline double unitize(double val, double minval, double maxval)
    {
        double length = maxval - minval;
        return kege::min(1.0, kege::max(0.0, ((length - (maxval - val)) / length)));
    }
    
    float invsqrt(float x);
    
    int stoai( int size, int* a, const char* data );
    int stoaf( int size, float* a, const char* data );
    int stoad( int size, double* a, const char* data );


    template<typename A, typename B> void clampToZero(A& value, B epsilon)
    {
        if (value < epsilon && value > 0.0f)
        {
            value = A(0.0);
        }
        else if (value > -epsilon && value < 0.0f)
        {
            value = A(0.0);
        }
    }
}


namespace kege{

    typedef float          real;
    typedef float          f32;
    typedef double         f64;
    typedef float          real32;
    typedef double         real64;

    typedef long           int64;
    typedef int            int32;
    typedef short          int16;
    typedef char           int8;
    typedef char           byte;
    
    typedef unsigned int   uint;
    typedef unsigned char  uchar;
    typedef unsigned short ushort;
    typedef unsigned long  ulong;
    
    typedef unsigned long  uint64;
    typedef unsigned int   uint32;
    typedef unsigned short uint16;
    typedef unsigned char  uint8;
    typedef unsigned char  ubyte;
}
#endif /* core_math_hpp */
