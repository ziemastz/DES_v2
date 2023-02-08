#ifndef RANDOM_H
#define RANDOM_H

#include <ctime>
#include <random>

class Random
{
public:
    Random(const unsigned int &seed = std::time(NULL));
    double randNumber();
private:
    const int FLOAT_MIN = 0;
    const int FLOAT_MAX = 1;
};


#endif // RANDOM_H
