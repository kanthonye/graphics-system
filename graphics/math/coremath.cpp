//
//  core.cpp
//  vector-math
//
//  Created by Kenneth A Esdaile on 6/6/18.
//  Copyright © 2018 Kenneth A Esdaile. All rights reserved.
//

#include "coremath.hpp"

namespace kege{
   
    float invsqrt(float x)
    {
        float hx = 0.5f * x;
        int i = *(int*)&x;         // store floating-point bits in integer
        i = 0x5f3759df - (i >> 1); // initial guess for Newton's method
        x = *(float*)&i;           // convert new bits into float
        x = x*(1.5f - hx*x*x);     // One round of Newton's method
        return x;
    }
    
    
    int stoai( int size, int* a, const char* data )
    {
        int i=0,j=0,n;
        char val[64];
        for ( j=0; j<size && data[ i ] != 0; j++ )
        {
            n = 0;
            while ( data[ i ] != ' ' && data[ i ] != 0 ) 
            {
                val[ n++ ] = data[ i++ ];
            }
            i++;
            val[ n ] = 0;
            a[ i ] = atoi( val );
        }
        return i;
    }
    
    int stoaf( int size, float* a, const char* data )
    {
          int i=0,j=0,n;
        char val[64];
        for ( j=0; j<size && data[ i ] != 0; j++ )
        {
            n = 0;
            while ( data[ i ] != ' ' && data[ i ] != 0 ) 
            {
                val[ n++ ] = data[ i++ ];
            }
            i++;
            val[ n ] = 0;
            a[ j ] = atof( val );
        }
        return i;
    }
    
    int stoad( int size, double* a, const char* data )
    {
        int i=0,j=0,n;
        char val[64];
        for ( j=0; j<size && data[ i ] != 0; j++ )
        {
            n = 0;
            while ( data[ i ] != ' ' && data[ i ] != 0 ) 
            {
                val[ n++ ] = data[ i++ ];
            }
            i++;
            val[ n ] = 0;
            a[ i ] = atof( val );
        }
        return i;
    }
}
