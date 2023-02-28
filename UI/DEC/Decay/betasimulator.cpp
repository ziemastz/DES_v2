#include "betasimulator.h"


BetaSimulator::BetaSimulator()
{
   step_energy = 1; // 1 keV
}

void BetaSimulator::setBranch(const BranchModel &newBranch)
{
    if(_branch.id != newBranch.id) {
        _branch = newBranch;
        spectrum.config(_branch.beta,_branch.daughter);

        if(_branch.transition == "BETA-")
            spectrum.setBetaType(BetaSpectra::BETA_MINUS);
        else if(_branch.transition == "BETA+")
            spectrum.setBetaType(BetaSpectra::BETA_PLUS);
        else
            spectrum.setBetaType(0);

        p_electron.clear();

        step_energy = _branch.beta.endpoint_energy_keV / 2000.0;
        float i = _branch.beta.endpoint_energy_keV;
        while(i>=0) {
            p_electron.put(i,spectrum.value(i));
            i-=step_energy;
        }
    }

}

double BetaSimulator::start()
{
    return p_electron.random();
}
