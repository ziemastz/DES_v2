#include "datavector.h"
#include "Decay/random.h"

DataVector::DataVector()
{

}

void DataVector::put(const double &X, const double &Y)
{
    _X.push_back(X);
    _Y.push_back(Y);
    normalize();
}

double DataVector::random() const
{
    if(_histo.size() == 0)
        return -1;

    Random rn;
    double gn = rn.randNumber();
    double sum = 0;
    size_t i=0;

    for(i=0; i < _histo.size(); i++)
    {
        sum += _histo.at(i);
        if(gn <= sum)
            break;
    }

    return _X.at(i);
}

bool DataVector::isEmpty() const
{
    if(_X.size()==0)
        return true;
    else
        return false;
}

void DataVector::normalize()
{
    _histo.clear();
    double sum = 0.0;
    for(size_t i=0; i<_Y.size(); i++) {
        sum += _Y.at(i);
    }
    for(size_t i=0; i<_Y.size(); i++) {
        _histo.push_back(_Y.at(i)/sum);
    }
}
