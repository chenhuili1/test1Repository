//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: computeFirstOrderOpt.h
//
// MATLAB Coder version            : 5.0
// C/C++ source code generated on  : 09-Oct-2020 15:23:44
//
#ifndef COMPUTEFIRSTORDEROPT_H
#define COMPUTEFIRSTORDEROPT_H

// Include Files
#include <cstddef>
#include <cstdlib>
#include "rtwtypes.h"
#include "GetFphi_types.h"

// Function Declarations
extern void computeFirstOrderOpt(struct_T *solution, const g_struct_T *objective,
  int workingset_nVar, const double workingset_ATwset[903], int
  workingset_nActiveConstr, double workspace[903]);

#endif

//
// File trailer for computeFirstOrderOpt.h
//
// [EOF]
//
