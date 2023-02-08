#include "random.h"

Random::Random(const uint &seed)
{
   std::srand(seed);
}

double Random::randNumber()
{
    return FLOAT_MIN + (double)(std::rand()) / ((double)(RAND_MAX/(FLOAT_MAX - FLOAT_MIN)));
}


