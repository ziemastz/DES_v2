#include "random.h"
#include <ctime>
#include <random>

Random::Random()
{
   std::srand(std::time(nullptr));
}

double Random::randNumber()
{
    return FLOAT_MIN + (double)(std::rand()) / ((double)(RAND_MAX/(FLOAT_MAX - FLOAT_MIN)));
}


