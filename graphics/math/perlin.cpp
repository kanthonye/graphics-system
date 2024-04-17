//
//  noise.cpp
//  column-major
//
//  Created by Kenneth A Esdaile on 7/13/18.
//  Copyright © 2018 Kenneth A Esdaile. All rights reserved.
//

#include "../math/math.hpp"

namespace kege{namespace noise{

    static int p[512] =
    {
        151,160,137, 91, 90, 15,131, 13,201, 95, 96, 53,194,233,  7,225,
        140, 36,103, 30, 69,142,  8, 99, 37,240, 21, 10, 23,190,  6,148,
        247,120,234, 75,  0, 26,197, 62, 94,252,219,203,117, 35, 11, 32,
        57 ,177, 33, 88,237,149, 56, 87,174, 20,125,136,171,168, 68,175,
        74 ,165, 71,134,139, 48, 27,166, 77,146,158,231, 83,111,229,122,
        60 ,211,133,230,220,105, 92, 41, 55, 46,245, 40,244,102,143, 54,
        65 , 25, 63,161,  1,216, 80, 73,209, 76,132,187,208, 89, 18,169,
        200,196,135,130,116,188,159, 86,164,100,109,198,173,186,  3, 64,
        52 ,217,226,250,124,123,  5,202, 38,147,118,126,255, 82, 85,212,
        207,206, 59,227, 47, 16, 58, 17,182,189, 28, 42,223,183,170,213,
        119,248,152,  2, 44,154,163, 70,221,153,101,155,167, 43,172,  9,
        129, 22, 39,253, 19, 98,108,110, 79,113,224,232,178,185,112,104,
        218,246, 97,228,251, 34,242,193,238,210,144, 12,191,179,162,241,
        81 , 51,145,235,249, 14,239,107, 49,192,214, 31,181,199,106,157,
        184, 84,204,176,115,121, 50, 45,127,  4,150,254,138,236,205, 93,
        222,114, 67, 29, 24, 72,243,141,128,195, 78, 66,215, 61,156,180,
        
        151,160,137, 91, 90, 15,131, 13,201, 95, 96, 53,194,233,  7,225,
        140, 36,103, 30, 69,142,  8, 99, 37,240, 21, 10, 23,190,  6,148,
        247,120,234, 75,  0, 26,197, 62, 94,252,219,203,117, 35, 11, 32,
        57 ,177, 33, 88,237,149, 56, 87,174, 20,125,136,171,168, 68,175,
        74 ,165, 71,134,139, 48, 27,166, 77,146,158,231, 83,111,229,122,
        60 ,211,133,230,220,105, 92, 41, 55, 46,245, 40,244,102,143, 54,
        65 , 25, 63,161,  1,216, 80, 73,209, 76,132,187,208, 89, 18,169,
        200,196,135,130,116,188,159, 86,164,100,109,198,173,186,  3, 64,
        52 ,217,226,250,124,123,  5,202, 38,147,118,126,255, 82, 85,212,
        207,206, 59,227, 47, 16, 58, 17,182,189, 28, 42,223,183,170,213,
        119,248,152,  2, 44,154,163, 70,221,153,101,155,167, 43,172,  9,
        129, 22, 39,253, 19, 98,108,110, 79,113,224,232,178,185,112,104,
        218,246, 97,228,251, 34,242,193,238,210,144, 12,191,179,162,241,
        81 , 51,145,235,249, 14,239,107, 49,192,214, 31,181,199,106,157,
        184, 84,204,176,115,121, 50, 45,127,  4,150,254,138,236,205, 93,
        222,114, 67, 29, 24, 72,243,141,128,195, 78, 66,215, 61,156,180
    };

    double fade(double t)
    {
        return t * t * t * (t * (t * 6 - 15) + 10);
    }

    double grad(int hash, double x, double y, double z)
    {
        int h = hash & 15;                      // CONVERT LO 4 BITS OF HASH CODE
        double u = h<8 ? x : y,                 // INTO 12 GRADIENT DIRECTIONS.
        v = h<4 ? y : h==12||h==14 ? x : z;
        return ((h&1) == 0 ? u : -u) + ((h&2) == 0 ? v : -v);
    }

    double perlin(double x, double y, double z)
    {
        int X = (int)floor(x) & 255; // FIND UNIT CUBE THAT
        int Y = (int)floor(y) & 255; // CONTAINS POINT.
        int Z = (int)floor(z) & 255;

        x -= floor(x); // FIND RELATIVE X,Y,Z
        y -= floor(y); // OF POINT IN CUBE.
        z -= floor(z);

        double u = fade(x); // COMPUTE FADE CURVES
        double v = fade(y); // FOR EACH OF X,Y,Z.
        double w = fade(z);

        int A  = p[ X ] + Y;
        int AA = p[ A ] + Z;
        int AB = p[ A+1 ] + Z;
        int B  = p[ X+1 ] + Y;
        int BA = p[ B ] + Z;
        int BB = p[ B+1 ] + Z;

        float l0 = kege::lerp( grad( p[AB+1], x  , y-1, z-1 ), grad( p[BB+1], x-1, y-1, z-1 ), u );
        float l1 = kege::lerp( grad( p[AA+1], x  , y  , z-1 ), grad( p[BA+1], x-1, y  , z-1 ), u );
        float l3 = kege::lerp( grad( p[AB  ], x  , y-1, z   ), grad( p[BB  ], x-1, y-1, z   ), u );
        float l4 = kege::lerp( grad( p[AA  ], x  , y  , z   ), grad( p[BA  ], x-1, y  , z   ), u );
        return kege::lerp( kege::lerp( l4, l3, v ), kege::lerp( l1, l0, v ), w );
    }
    
    double noise(double x, double y)
    {
        // Determine grid cell coordinates
        int x0 = (int)x;
        int x1 = x0 + 1;
        int y0 = (int)y;
        int y1 = y0 + 1;

        // Determine interpolation weights
        // Could also use higher order polynomial/s-curve here
        float sx = x - (float)x0;
        float sy = y - (float)y0;

        // Interpolate between grid point gradients
        float n0, n1, ix0, ix1;

        n0 = grad(x0, y0, x, y);
        n1 = grad(x1, y0, x, y);
        ix0 = lerp(n0, n1, sx);

        n0 = grad(x0, y1, x, y);
        n1 = grad(x1, y1, x, y);
        ix1 = lerp(n0, n1, sx);

        return lerp(ix0, ix1, sy);
    }
    
    void setseed(int seed)
    {
        srand(seed);
        for (int i=0; i<256; i++) 
        {
            p[ i ] = rand() % 255;
            p[ i + 256 ] = p[ i ];
        }
    }
    
}}
