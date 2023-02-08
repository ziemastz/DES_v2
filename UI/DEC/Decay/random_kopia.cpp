#include "random_kopia.h"
#include <ctime>
#include <random>

RandomA::RandomA()
{
   std::srand(std::time(nullptr));
}

double RandomA::randNumber()
{
    return FLOAT_MIN + (double)(std::rand()) / ((double)(RAND_MAX/(FLOAT_MAX - FLOAT_MIN)));
}


