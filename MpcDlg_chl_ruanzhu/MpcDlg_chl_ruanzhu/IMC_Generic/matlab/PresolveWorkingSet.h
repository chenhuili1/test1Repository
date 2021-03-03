//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: PresolveWorkingSet.h
//
// MATLAB Coder version            : 5.0
// C/C++ source code generated on  : 09-Oct-2020 15:23:44
//
#ifndef PRESOLVEWORKINGSET_H
#define PRESOLVEWORKINGSET_H

// Include Files
#include <cstddef>
#include <cstdlib>
#include "rtwtypes.h"
#include "GetFphi_types.h"

// Function Declarations
extern void PresolveWorkingSet(struct_T *solution, c_struct_T *memspace,
  e_struct_T *workingset, f_struct_T *qrmanager, h_struct_T *options);
extern void b_PresolveWorkingSet(struct_T *solution, c_struct_T *memspace,
  e_struct_T *workingset, f_struct_T *qrmanager);

#endif

//
// File trailer for PresolveWorkingSet.h
//
// [EOF]
//
