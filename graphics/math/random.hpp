//
//  random.hpp
//  column-major
//
//  Created by Kenneth A Esdaile on 7/13/18.
//  Copyright © 2018 Kenneth A Esdaile. All rights reserved.
//

#ifndef random_hpp
#define random_hpp
#include "vec2.hpp"
#include "vec3.hpp"
#include "vec4.hpp"
namespace kege{
    
    inline int randi(const int from, const int to)
    {
        return from + (rand() % (to-from+1)); // range from (from) to (to)
    }
    
    inline float randf(const float from, const float to)
    {
        if (from==0 && to==0) return 0;
        double num = (double) rand() / RAND_MAX;
        return from + ((to - from) * num);
    }
    
    template<typename var> var rand_range(var from, var to)
    {
        if (from==0 && to==0) return 0;
        double num = (double) rand() / RAND_MAX;
        return from + ((to - from) * num);
    }
    
    
    /**
     * return true or false base on a parcentage
     * @param pct is a number range from 0 to 100.
     * @return boolean probable chance
     */
    bool chance_luck(short pct);
    
    double chance_amount(double pct, double amount);
    
    double probable_amount(double pct, double amount);
}

namespace kege{
    
    class rand1i
    {
    public:
        
        int max;
        int min;
        
    public:
        
        int gen() const
        { return randi(min, max); }
        
        rand1i()
        {}
        rand1i(float min,float max)
        :   min(min)
        ,   max(max)
        {}
    };
}

namespace kege{
    
    class rand1f
    {
    public:
        
        float max;
        float min;
        
    public:
        
        float gen() const
        { return randf(min, max); }
        
        rand1f()
        {}
        rand1f(float min,float max)
        :   min(min)
        ,   max(max)
        {}
    };
}

namespace kege{
    
    struct rand2f
    {
    public:
        
        rand1f x;
        rand1f y;
        
    public:
        
        vec2 gen() const { return vec2(x.gen(), y.gen()); }
        
        rand2f(rand1f const &x,rand1f const &y)
        : x(x)
        , y(y)
        {}
        rand2f(rand1f const &xy)
        : x(xy)
        , y(xy)
        {}
        rand2f()
        {}
    };
}

namespace kege{
    
    class rand3f
    {
    public:
        
        rand1f x;
        rand1f y;
        rand1f z;
        
    public:
        
        vec3 gen() const
        { return { x.gen(), y.gen(), z.gen() }; }
        
        rand3f()
        {}
        rand3f(rand1f const &x,rand1f const &y,rand1f const &z )
        : x(x)
        , y(y)
        , z(z)
        {}
    };
}

namespace kege{
    
    class rand4f
    {
    public:
        
        rand1f x;
        rand1f y;
        rand1f z;
        rand1f w;
        
    public:
        
        vec4 gen() const 
        { return vec4(x.gen(), y.gen(), z.gen(), w.gen()); }
        
        rand4f()
        {}
        rand4f(rand1f const &x,rand1f const &y,rand1f const &z,rand1f const &w)
        : x(x)
        , y(y)
        , z(z)
        , w(w)
        {}
    };
}
#include <vector>
namespace kege{
    class urand1i
    {
    public:
        
        void reset(const int start, const int end);
        void reset();
        int gen(void);
        
        urand1i(const int start, const int end);
        ~urand1i();
        urand1i();
        
    private:
        
        std::vector<int> _arry;
        int _count;
        int _start;
        int _end;
        
    };
}

namespace kege{
    
    class urand1f
    {
    private:
        
        int   asize;
        int   min;
        int   last_index;
        float *rand_array;
        
    public:
        
        urand1f(void);
        urand1f(const float from, const float to);
        ~urand1f(void);
        float gen(void);
        void set(const float from, const float to);
    };
    
}
#endif /* random_hpp */
