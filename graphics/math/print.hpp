//
//  print.hpp
//  column-major
//
//  Created by Kenneth A Esdaile on 7/12/18.
//  Copyright © 2018 Kenneth A Esdaile. All rights reserved.
//

#ifndef print_hpp
#define print_hpp
#include <iomanip>
#include <iostream>
#include "mat22.hpp"
#include "mat33.hpp"
#include "mat44.hpp"
#include "quat.hpp"


namespace kege{
    
    std::ostream& operator <<( std::ostream& os, const quat& v);
    std::ostream& operator <<( std::ostream& os, const vec4& v);
    std::ostream& operator <<( std::ostream& os, const vec3& v);
    std::ostream& operator <<( std::ostream& os, const vec2& v);
    std::ostream& operator <<( std::ostream& os, const mat22& v);
    std::ostream& operator <<( std::ostream& os, const mat33& v);
    std::ostream& operator <<( std::ostream& os, const mat44& v);
}
#endif /* print_hpp */
