//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: quadprog.h
//
// MATLAB Coder version            : 5.0
// C/C++ source code generated on  : 09-Oct-2020 15:23:44
//
#ifndef QUADPROG_H
#define QUADPROG_H

// Include Files
#include <cstddef>
#include <cstdlib>
#include "rtwtypes.h"
#include "GetFphi_types.h"

// Function Declarations
extern void quadprog(const double H[400], const double f[20], const double
                     bineq[2], const double lb[20], const double ub[20], double
                     x[20]);

#endif

//
// File trailer for quadprog.h
//
// [EOF]
//
