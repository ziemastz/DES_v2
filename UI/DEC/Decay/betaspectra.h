#ifndef BETASPECTRA_H
#define BETASPECTRA_H

#include "Models/nuclidemodel.h"
#include "Models/betatransitionmodel.h"
#include <cmath>

// CONSTANS
const double ELECTRON_MASS_KEV = 510.998902;  /**< the electron rest mass in keV */
const double NEUTRON_MASS_KEV = 939565.378;   /**< the neutron rest mass in keV */
const double PROTON_MASS_KEV = 938271.998;    /**< the proton rest mass in keV */
const double NUCLEON_MASS_KEV = (NEUTRON_MASS_KEV + PROTON_MASS_KEV) / 2.; /**< the average nucleus mass in keV */
const double HBAR = 6.58211889e-16;       /**< reduced Planck's constant in units eV*s */
const double SPEED_OF_LIGHT = 299792458.0;  /**< the speed of light in m/s */
const double PION_MASS_KEV = 134976.6; /**< the pion rest mass in unuts in keV */

const double NATURAL_LENGTH = HBAR * SPEED_OF_LIGHT / 1e3 / ELECTRON_MASS_KEV; /**< the beta decay natural length scale using HBAR=c=m_e=1 3.861592643659598e-13 m*/

const double ALPHA = 0.0072973525664; /**< the fine-structure constant */
const double EULER_MASCHERONI_CONSTANT = 0.577215664901532;  /**< the Euler-Mascheroni constant */

const double gAxial = 1.2723; /**< Axial vector coupling constant */
const double gPseudoscalar = 0.0;        /**< Induced pseudoscalar coupling constant, relative to the nucleon mass */
const double gMagnetism = 4.706;


class BetaSpectra
{
public:
    enum BETA_TYPE {
        BETA_PLUS = -1,
        BETA_MINUS = 1
    };
    enum TRANSITION_TYPE {
        SUPERALLOWED = 0,               // Fermi decay
        ALLOWED,                        // Gamow-Teller decay
        MIXED,                          // Fermi vs Gamow-Teller decay
        FIRST_FORBIDDEN,
        FIRST_FORBIDDEN_NON_UNIQUE,
        SECOND_FORBIDDEN,
        SECOND_FORBIDDEN_NON_UNIQUE,
        THIRD_FORBIDDEN,
        THIRD_FORBIDDEN_NON_UNIQUE
    };
    enum EXPSHAPEFACTORFOMR_TYPE {
        EXPSHAPEFACTOR_1 = 0,
        EXPSHAPEFACTOR_2,
        EXPSHAPEFACTOR_3,
        EXPSHAPEFACTOR_4,
        EXPSHAPEFACTOR_5
    };

    BetaSpectra();
    void config(const BetaTransitionModel &beta, const NuclideModel &daughter);
    double value(const double energy_keV);
    void setBetaType(int newBetaType);

private:
    double W0;
    int A;
    int Z;
    double R;
    int betaType;
    int decayType;
    QStringList forbiddenness;
    double coeff[5] = {0,0,0,0,0};
    int expShapeFactorType;
    QStringList exp_shape_factor;
    double expCoeff[4] = {0,0,0,0};

    double PhaseSpace(const double &W);
    double FermiFunction(const double &W);
    double Form(const double &W);
    double ExpShapeFactorForm(const double &W);

    double CGammaFunction(double r, double im, int OPT);
    double RGammaFunction(double x);
};

#endif // BETASPECTRA_H
