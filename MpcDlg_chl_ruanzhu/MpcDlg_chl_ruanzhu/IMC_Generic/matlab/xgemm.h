//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: xgemm.h
//
// MATLAB Coder version            : 5.0
// C/C++ source code generated on  : 09-Oct-2020 15:23:44
//
#ifndef XGEMM_H
#define XGEMM_H

// Include Files
#include <cstddef>
#include <cstdlib>
#include "rtwtypes.h"
#include "GetFphi_types.h"

// Function Declarations
extern void b_xgemm(int m, int n, int k, const double A[1849], int ia0, const
                    double B[903], double C[1849]);
extern void xgemm(int m, int n, int k, const double A[400], int lda, const
                  double B[1849], int ib0, double C[903]);

#endif

//
// File trailer for xgemm.h
//
// [EOF]
//
