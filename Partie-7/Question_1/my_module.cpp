#include "my_module.hpp"

#define N_VALUES   32

int32_t my_module(const int32_t values)
{
    
    int32_t sum = 0;
    
    for(int32_t i = 0; i < N_VALUES; i += 1)
    {
        sum += values[ i ];
    }
    
    return sum;

};
