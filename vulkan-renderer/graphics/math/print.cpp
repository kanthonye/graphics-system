//
//  print.cpp
//  column-major
//
//  Created by Kenneth A Esdaile on 7/12/18.
//  Copyright © 2018 Kenneth A Esdaile. All rights reserved.
//
#include <stdio.h>
#include <sys/stat.h>
#include <stdarg.h>
#include <stdlib.h>
#include "../math/math.hpp"


namespace kege{

    std::ostream& operator <<( std::ostream& os, const quat& v)
    {
        int w = 10;
        int p = 4;
        os <<"{ " << std::setw(w) << std::setprecision( p ) << v.x << ", " << std::setw(w) << std::setprecision( p ) << v.y << ", " << std::setw(w) << std::setprecision( p ) << v.z << ", " << std::setw(w) << std::setprecision( p ) << v.w << " }";
        return os;
    }

    std::ostream& operator <<( std::ostream& os, const vec4& v)
    {
        int w = 10;
        int p = 4;
        os <<"{ " << std::setw(w) << std::setprecision( p ) << v.x << ", " << std::setw(w) << std::setprecision( p ) << v.y << ", " << std::setw(w) << std::setprecision( p ) << v.z << ", " << std::setw(w) << std::setprecision( p ) << v.w << " }";
        return os;
    }
    
    
    std::ostream& operator <<( std::ostream& os, const vec3& v)
    {
        int w = 10;
        int p = 6;
        os <<"{ " << std::setw(w) << std::setprecision( p ) << v[0] << ", " << std::setw(w) << std::setprecision( p ) << v[1] << ", " << std::setw(w) << std::setprecision( p ) << v[2]  << " }";
        return os;
    }
    
    std::ostream& operator <<( std::ostream& os, const vec2& v)
    {
        int w = 10;
        int p = 4;
        os <<"{ " << std::setw(w) << std::setprecision( p ) << v[0] << ", " << std::setw(w) << std::setprecision( p ) << v[1]  << " }";
        return os;
    }
    
    std::ostream& operator <<( std::ostream& os, const mat22& m)
    {
        os << m.v[0] << "\n";
        os << m.v[1] << "\n";
        return os;
    }
    std::ostream& operator <<( std::ostream& os, const mat33& m)
    {
        os << m[ 0 ] << "\n";
        os << m[ 1 ] << "\n";
        os << m[ 2 ] << "\n";
        return os;
    }
    
    std::ostream& operator <<( std::ostream& os, const mat44& m)
    {
        int w = 10;
        int p = 4;
        os <<"{ " << std::setw(w) << std::setprecision( p ) << m[ 0 ][ 0 ] << ", " << std::setw(w) << std::setprecision( p ) << m[ 0 ][ 1 ] << ", " << std::setw(w) << std::setprecision( p ) << m[ 0 ][ 2 ] << std::setw(w) << std::setprecision( p ) << m[ 0 ][ 3 ] << " }\n";
        os <<"{ " << std::setw(w) << std::setprecision( p ) << m[ 1 ][ 0 ] << ", " << std::setw(w) << std::setprecision( p ) << m[ 1 ][ 1 ] << ", " << std::setw(w) << std::setprecision( p ) << m[ 1 ][ 2 ] << std::setw(w) << std::setprecision( p ) << m[ 1 ][ 3 ] << " }\n";
        os <<"{ " << std::setw(w) << std::setprecision( p ) << m[ 2 ][ 0 ] << ", " << std::setw(w) << std::setprecision( p ) << m[ 2 ][ 1 ] << ", " << std::setw(w) << std::setprecision( p ) << m[ 2 ][ 2 ] << std::setw(w) << std::setprecision( p ) << m[ 2 ][ 3 ] << " }\n";
        os <<"{ " << std::setw(w) << std::setprecision( p ) << m[ 3 ][ 0 ] << ", " << std::setw(w) << std::setprecision( p ) << m[ 3 ][ 1 ] << ", " << std::setw(w) << std::setprecision( p ) << m[ 3 ][ 2 ] << std::setw(w) << std::setprecision( p ) << m[ 3 ][ 3 ] << " }\n";
        return os;
    }

}
