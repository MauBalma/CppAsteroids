#pragma once

#include <cstdlib>

namespace Random
{
    inline void setSeed(unsigned seed)
    {
        srand(seed);
    }

    inline float value01()
    {
        return (float)rand() / RAND_MAX;
    }

    inline float range(float min, float max)
    {
        return min + (max - min) * ((float)rand() / RAND_MAX);
    }

    inline float range(float max)
    {
        return max * ((float)rand() / RAND_MAX);
    }
}
