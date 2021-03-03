//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: checkStoppingAndUpdateFval.h
//
// MATLAB Coder version            : 5.0
// C/C++ source code generated on  : 09-Oct-2020 15:23:44
//
#ifndef CHECKSTOPPINGANDUPDATEFVAL_H
#define CHECKSTOPPINGANDUPDATEFVAL_H

// Include Files
#include <cstddef>
#include <cstdlib>
#include "rtwtypes.h"
#include "GetFphi_types.h"

// Function Declarations
extern void checkStoppingAndUpdateFval(int *activeSetChangeID, const double f[20],
  struct_T *solution, c_struct_T *memspace, const g_struct_T *objective,
  e_struct_T *workingset, f_struct_T *qrmanager, double options_ObjectiveLimit,
  int runTimeOptions_MaxIterations, double c_runTimeOptions_ConstrRelTolFa, bool
  updateFval);

#endif

//
// File trailer for checkStoppingAndUpdateFval.h
//
// [EOF]
//
