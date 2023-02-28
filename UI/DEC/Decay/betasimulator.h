#ifndef BETASIMULATOR_H
#define BETASIMULATOR_H


#include "Decay/datavector.h"
#include "Models/branchmodel.h"
#include "Decay/betaspectra.h"

class BetaSimulator
{
public:
    BetaSimulator();
    void setBranch(const BranchModel &newBranch);
    double start();

private:
    BranchModel _branch;
    BetaSpectra spectrum;
    DataVector p_electron;
    float step_energy;

};

#endif // BETASIMULATOR_H
