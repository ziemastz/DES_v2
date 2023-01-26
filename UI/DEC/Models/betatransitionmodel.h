#ifndef BETATRANSITIONMODEL_H
#define BETATRANSITIONMODEL_H

#include <QString>

class BetaTransitionModel
{
public:
    double endpoint_energy_keV;
    QString forbiddenness;
    double coeff_a;
    double coeff_b;
    double coeff_c;
    double coeff_d;
    double coeff_e;
    QString exp_shape_factor;
    double exp_coeff_a;
    double exp_coeff_b;
    double exp_coeff_c;
    double exp_coeff_d;
    double mixing_ratio;
};

#endif // BETATRANSITIONMODEL_H
