//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: factoryConstruct.h
//
// MATLAB Coder version            : 5.0
// C/C++ source code generated on  : 09-Oct-2020 15:23:44
//
#ifndef FACTORYCONSTRUCT_H
#define FACTORYCONSTRUCT_H

// Include Files
#include <cstddef>
#include <cstdlib>
#include "rtwtypes.h"
#include "GetFphi_types.h"

// Function Declarations
extern void factoryConstruct(const double bineq[2], int mLB, const double lb[20],
  const int indexLB[20], int mUB, const double ub[20], const int indexUB[20],
  int mFixed, const int indexFixed[20], e_struct_T *obj);

#endif

//
// File trailer for factoryConstruct.h
//
// [EOF]
//
