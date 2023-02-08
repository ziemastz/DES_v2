#ifndef DATAVECTOR_H
#define DATAVECTOR_H

#include "Decay/random.h"
#include <vector>

class DataVector
{
public:
    DataVector();
    void put(const double& X, const double& Y);
    double random() const;
    bool isEmpty() const;
private:
    std::vector<double> _X;
    std::vector<double> _Y;
    std::vector<double> _histo;
    void normalize();
    static Random rn;
};

#endif // DATAVECTOR_H
