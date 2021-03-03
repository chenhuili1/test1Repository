//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: Getintput_u.h
//
// MATLAB Coder version            : 5.0
// C/C++ source code generated on  : 09-Oct-2020 15:23:44
//
#ifndef GETINTPUT_U_H
#define GETINTPUT_U_H

// Include Files
#include <cstddef>
#include <cstdlib>
#include "rtwtypes.h"
#include "GetFphi_types.h"

// Function Declarations
extern double Getintput_u(const double F[320], const double phi[1600], const
  double Yreal[4], const double yref[4], const double r[2], double T,int k, const
  double init_parm[7]);
extern double GetStop_u(const double F[320], const double phi[1600], const double
                 Yreal[4], double a_stop, const double r[2], const double Y0[4],
                 double T, double k, const double init_parm_data[4]);

#endif

//
// File trailer for Getintput_u.h
//
// [EOF]
//
