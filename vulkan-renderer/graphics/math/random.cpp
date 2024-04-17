//
//  random.cpp
//  column-major
//
//  Created by Kenneth A Esdaile on 7/13/18.
//  Copyright © 2018 Kenneth A Esdaile. All rights reserved.
//

#include "../math/math.hpp"

namespace kege
{
    void urand1i::reset(const int start, const int end)
    {
        _start = start;
        _end = end;
        _count = _end - _start;
        _arry.resize(_count);
        for (int i=0; i<_arry.size(); i++) 
        {
            _arry[ i ] = _start + i;
        }
    }
    
    void urand1i::reset()
    {
        _count = _end - _start;
    }
    
    int urand1i::gen(void)
    {
        if (_count < 0) reset();
        int index = randi(0, --_count);
        if (index == _count)
        {
            index = _count - 1;
        }
        int temp = _arry[index];
        _arry[index] = _arry[_count];
        _arry[_count] = temp;
 
        return temp;
    }
    
    urand1i::urand1i(const int start, const int end)
    {
        srand( (int)time(NULL) );
        reset(start, end);
    }
    
    urand1i::~urand1i()
    {
        _arry.clear();
    }
    
    urand1i::urand1i() 
    :   _start(0)
    ,   _end(1)
    ,   _count(0)
    {
        srand( (int)time(NULL) );
    }
    
}



namespace kege{
    
    urand1f::urand1f (void) :last_index(0),min(0),asize(0),rand_array(0)
    {
        srand((int)time(NULL));
    }
    
    urand1f::urand1f (const float from, const float to) :last_index(0),min(0),asize(0),rand_array(0)
    {
        srand((int)time(NULL));
        if (from > to) throw ("UniqueRand ERROR! 'left #' must be lessthan 'right #'.\n");
        set(from, to);
    }
    
    urand1f::~urand1f (void)
    {
        if (rand_array != 0)
        {
            delete [] rand_array;
            rand_array = 0;
        }
    }
    
    float urand1f::gen(void)
    {
        /* pervent error EXC_BAD_ACCESS because of accessing a null pointer*/
        if (rand_array==0 || asize==0) return 0;
        /* reset min to 0 if it is graterthan or equal max
         * prevent error get a random number btw 0 */
        if (min >= asize) min = 0;
        
        last_index = (asize-1)- min;
        if (last_index<0) last_index=0;
        
        int rand_index = rand() % (asize-min);
        
        float  tmp = 0;
        
        swap(rand_array[last_index], rand_array[rand_index], tmp);
        
        min++;
        return rand_array[last_index];
    }
    
    void urand1f::set(const float from, const float to)
    {
        if (from > to) throw ("UniqueRand ERROR! 'left #' must be lessthan 'right #'.\n");
        last_index = 0;
        min  = 0;
        asize  = (to-from);
        float val = 1.0 / asize;
        
        if (rand_array != 0) delete [] rand_array;
        // calcuate the size of the array
        rand_array = new float[asize];
        // popluate the random array with digits from a to b
        float nmbr = from;
        for (int i=0; i<asize; i++)
        {
            nmbr = (from+i) + (i*val);
            rand_array[i] = nmbr;
        }
    }
}


namespace kege{
    
    /**
     * return true or false base on a parcentage
     * @param pct is a number range from 0 to 100.
     * @return boolean probable chance
     */
    bool chance_luck(short pct)
    {
        /* if pct <= 0% always return false, if pct >= 100% always
         * return true, else return rand(0-100) <= pct */
        return (pct <= 0)? false: (pct >= 100)? true: (rand() % 101) <= pct;
    }
    
    double chance_amount(double pct, double amount)
    {
        if (pct >= 100) return amount;
        if (pct <=   0) return 0;
        double min = amount * (pct * 0.01);
        return min + ((amount - min) * ((double) rand() / RAND_MAX));
    }
    
    double probable_amount(double pct, double amount)
    {   using namespace kege;
        int mim = pct * (pct * 0.01);
        int min = randi(mim, pct);
        int max = randi(pct, 100);
        pct = randi(min, max);
        return (pct * 0.01) * amount;
    }
}


