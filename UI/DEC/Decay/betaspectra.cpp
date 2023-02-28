#include "betaspectra.h"

BetaSpectra::BetaSpectra()
{
    forbiddenness << "SUPERALLOWED [ 1 ]"
            << "ALLOWED [ 1 ]"
            << "MIXED [ 1 ]"
            << "FIRST FORBIDDEN [ a * q^2)+ b * p^2 ]"
            << "FIRST FORBIDDEN NON UNIQUE [ 1 + a*W + b/W + c*W^2 + d*q^2 + e*p^2 ]"
            << "SECOND FORBIDDEN [ a*q^4 + b*q^2*p^2 + c*p^4 ]"
            << "SECOND FORBIDDEN NON UNIQUE [ a * q^2)+ b * p^2 ]"
            << "THIRD FORBIDDEN [ a*q^6 + b*q^4*p^2+ c*q^2*p^4 + d*p^6 ]"
            << "THIRD FORBIDDEN NON UNIQUE [ a*q^4 + b*q^2*p^2 + c*p^4 ]";
    exp_shape_factor << "1 + a*W"
                        << "a + b*W + c*W^2"
                        << "1 + a*W + b/W + c*W^2"
                        << "1 + a*W + b/W + c*W^2 + d*W^3"
                        << "1 + a*W + b*W^2 + c*W^3";
}

void BetaSpectra::config(const BetaTransitionModel &beta, const NuclideModel &daughter)
{
    A = daughter.a;
    Z = daughter.z;
    R = 0.002908*std::pow(A,1.0/3.0) - 0.002437*std::pow(A,-1.0/3.0);   // The nuclear radius in units of the Compton wave (GOVE and MARTIN, NUCLEAR DATA TABLES, 10, P210)

    decayType = forbiddenness.indexOf(beta.forbiddenness);
    expShapeFactorType = exp_shape_factor.indexOf(beta.exp_shape_factor);

    if(betaType == BETA_MINUS) {
        W0 = beta.endpoint_energy_keV/ELECTRON_MASS_KEV + 1;
    }else {
        W0 = beta.endpoint_energy_keV/ELECTRON_MASS_KEV - 1;
    }
    W0 = W0 - (W0 * W0 - 1) / 2. / A / (NUCLEON_MASS_KEV / ELECTRON_MASS_KEV);

    // coeffciency of forms
    coeff[0] = beta.coeff_a;
    coeff[1] = beta.coeff_b;
    coeff[2] = beta.coeff_c;
    coeff[3] = beta.coeff_d;
    coeff[4] = beta.coeff_e;
    // coeffciency of shape factor forms
    expCoeff[0] = beta.exp_coeff_a;
    expCoeff[1] = beta.exp_coeff_b;
    expCoeff[2] = beta.exp_coeff_c;
    expCoeff[3] = beta.exp_coeff_d;
}

double BetaSpectra::value(const double energy_keV)
{
    double W;
    if(betaType == BETA_MINUS) {
        W = energy_keV/ELECTRON_MASS_KEV + 1;
    }else {
        W = energy_keV/ELECTRON_MASS_KEV - 1;
    }
    W = W - (W * W - 1) / 2. / A / (NUCLEON_MASS_KEV / ELECTRON_MASS_KEV);

    double res = 1;

    res *= PhaseSpace(W);
    res *= FermiFunction(W);
    res *= Form(W);
    res *= ExpShapeFactorForm(W);

    return res;
}

void BetaSpectra::setBetaType(int newBetaType)
{
    betaType = newBetaType;
}

 double BetaSpectra::PhaseSpace(const double &W)
{
     return std::sqrt(W * W - 1.) * W * std::pow(W0 - W, 2.);
 }

 double BetaSpectra::FermiFunction(const double &W)
 {
     double gamma = std::sqrt(1. - std::pow(ALPHA * Z, 2.));
     double p = std::sqrt(W * W - 1.);
     double first = 2. * (gamma + 1.);
     // the second term will be incorporated in the fifth
     // double second = 1/std::pow(gsl_sf_gamma(2*gamma+1),2);
     double third = std::pow(2. * p * R, 2. * (gamma - 1.));
     double fourth = std::exp(betaType * M_PI * ALPHA * Z * W / p);


     double cgamma = CGammaFunction(gamma,ALPHA * Z * W / p,0); // Returns gamma function for complex argument 'z'
     double rgamma = RGammaFunction(2*gamma+1);

     double fifth = cgamma/std::pow(rgamma,2);

     return first * third * fourth * fifth;
 }

 double BetaSpectra::Form(const double &W)
 {
     double p = sqrt(W * W - 1.);
     double q = W0 - W;
     double A = coeff[0];
     double B = coeff[1];
     double C = coeff[2];
     double D = coeff[3];
     double E = coeff[4];

     double form = 1.;

     switch (decayType) {
     case SUPERALLOWED:
     case ALLOWED:
     case MIXED:
         form = 1;
         break;
     case FIRST_FORBIDDEN:
     case SECOND_FORBIDDEN_NON_UNIQUE:
         form = A * pow(q, 2) + B * pow(p, 2);
         break;
     case FIRST_FORBIDDEN_NON_UNIQUE:
         form = 1 + (A * W) + (B / W) + (C * pow(W, 2)) + (D * (pow(q, 2) + E*pow(p, 2)));
         break;
     case SECOND_FORBIDDEN:
     case THIRD_FORBIDDEN_NON_UNIQUE:
         form = A * pow(q, 4) + B * pow(q, 2) * pow(p, 2) + C * pow(p, 4);
         break;
     case THIRD_FORBIDDEN:
         form = A * pow(q, 6) + B * pow(q, 4) * pow(p, 2) + C * pow(q, 2) * pow(p, 4) + D * pow(p, 6);
         break;
     default:
         form = 1.0;
         break;
     }

     return form;
 }

 double BetaSpectra::ExpShapeFactorForm(const double &W)
 {
     double shape = 1.;
     double A = expCoeff[0];
     double B = expCoeff[1];
     double C = expCoeff[2];
     double D = expCoeff[3];

     switch (expShapeFactorType) {
     case EXPSHAPEFACTOR_1:
         shape = 1 + A*W;
         break;
     case EXPSHAPEFACTOR_2:
         shape = A + B*W+C*W*W;
         break;
     case EXPSHAPEFACTOR_3:
         shape = 1 + A*W + B/W + C*W*W;
         break;
     case EXPSHAPEFACTOR_4:
         shape = 1 + A*W + B/W + C*W*W + D*W*W*W;
         break;
     case EXPSHAPEFACTOR_5:
         shape = 1 + A*W + B*W*W + C*W*W*W;
         break;
     default:
         shape = 1.;
         break;
     }

     return shape;
 }

 double BetaSpectra::CGammaFunction(double r, double im, int OPT)
 {
     //  Complex gamma function.
     //      Algorithms and coefficient values from "Computation of Special
     //      Functions", Zhang and Jin, John Wiley and Sons, 1996.
     //
     //  (C) 2003, C. Bond. All rights reserved.
     //
     //  Returns gamma function or log(gamma) for complex argument 'z'.
     //
     //  OPT value       function
     //  ---------       --------
     //      0           complex gamma
     //      1           complex log(gamma)
     //
     //  Returns (1e308,0) if the real part of the argument is a negative integer
     //  or 0 or exceeds 171.
     // Source: http://www.crbond.com/math.htm
     double g;
     double x0,q1,q2,x,y,th,th1,th2,g0,gr,gi,gr1,gi1;
     double na,t,x1,y1,sr,si;
     int j,k;

     static double a[] = {
         8.333333333333333e-02,
        -2.777777777777778e-03,
         7.936507936507937e-04,
        -5.952380952380952e-04,
         8.417508417508418e-04,
        -1.917526917526918e-03,
         6.410256410256410e-03,
        -2.955065359477124e-02,
         1.796443723688307e-01,
        -1.39243221690590};

     x = r;
     y = im;
     if (x > 171) return 1e308;
     if ((y == 0.0) && (x == (int)(x)) && (x <= 0.0))
         return 1e308;
     else if (x < 0.0) {
         x1 = x;
         y1 = y;
         x = -x;
         y = -y;
     }
     x0 = x;
     if (x <= 7.0) {
         na = (int)(7.0-x);
         x0 = x+na;
     }
     q1 = sqrt(x0*x0+y*y);
     th = atan(y/x0);
     gr = (x0-0.5)*log(q1)-th*y-x0+0.5*log(2.0*M_PI);
     gi = th*(x0-0.5)+y*log(q1)-y;
     for (k=0;k<10;k++){
         t = pow(q1,-1.0-2.0*k);
         gr += (a[k]*t*cos((2.0*k+1.0)*th));
         gi -= (a[k]*t*sin((2.0*k+1.0)*th));
     }
     if (x <= 7.0) {
         gr1 = 0.0;
         gi1 = 0.0;
         for (j=0;j<na;j++) {
             gr1 += (0.5*log((x+j)*(x+j)+y*y));
             gi1 += atan(y/(x+j));
         }
         gr -= gr1;
         gi -= gi1;
     }
     if (x1 <= 0.0) {
         q1 = sqrt(x*x+y*y);
         th1 = atan(y/x);
         sr = -sin(M_PI*x)*cosh(M_PI*y);
         si = -cos(M_PI*x)*sinh(M_PI*y);
         q2 = sqrt(sr*sr+si*si);
         th2 = atan(si/sr);
         if (sr < 0.0) th2 += M_PI;
         gr = log(M_PI/(q1*q2))-gr;
         gi = -th1-th2-gi;
         x = x1;
         y = y1;
     }
     if (OPT == 0) {
         g0 = exp(gr);
         gr = g0*cos(gi);
         gi = g0*sin(gi);
     }
     g = pow(gr,2)+pow(gi,2);
     return g;
 }

 double BetaSpectra::RGammaFunction(double x)
 {
     //  Computation of gamma function.
     //      Algorithms and coefficient values from "Computation of Special
     //      Functions", Zhang and Jin, John Wiley and Sons, 1996.
     //
     //  (C) 2003, C. Bond. All rights reserved.
     //
     // Returns gamma function of argument 'x'.
     //
     // NOTE: Returns 1e308 if argument is a negative integer or 0,
     //      or if argument exceeds 171.
     // Source: http://www.crbond.com/math.htm
     int i,k,m;
     double ga,gr,r=1.0,z;

     static double g[] = {
         1.0,
         0.5772156649015329,
        -0.6558780715202538,
        -0.420026350340952e-1,
         0.1665386113822915,
        -0.421977345555443e-1,
        -0.9621971527877e-2,
         0.7218943246663e-2,
        -0.11651675918591e-2,
        -0.2152416741149e-3,
         0.1280502823882e-3,
        -0.201348547807e-4,
        -0.12504934821e-5,
         0.1133027232e-5,
        -0.2056338417e-6,
         0.6116095e-8,
         0.50020075e-8,
        -0.11812746e-8,
         0.1043427e-9,
         0.77823e-11,
        -0.36968e-11,
         0.51e-12,
        -0.206e-13,
        -0.54e-14,
         0.14e-14};

     if (x > 171.0) return 1e308;    // This value is an overflow flag.
     if (x == (int)(x)) {
         if (x > 0.0) {
             ga = 1.0;               // use factorial
             for (i=2;i<x;i++) {
                ga *= i;
             }
          }
          else
             ga = 1e308;
      }
      else {
         if (fabs(x) > 1.0) {
             z = fabs(x);
             m = (int)(z);
             r = 1.0;
             for (k=1;k<=m;k++) {
                 r *= (z-k);
             }
             z -= m;
         }
         else
             z = x;
         gr = g[24];
         for (k=23;k>=0;k--) {
             gr = gr*z+g[k];
         }
         ga = 1.0/(gr*z);
         if (fabs(x) > 1.0) {
             ga *= r;
             if (x < 0.0) {
                 ga = -M_PI/(x*ga*sin(M_PI*x));
             }
         }
     }
     return ga;
 }
