//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: compute_deltax.h
//
// MATLAB Coder version            : 5.0
// C/C++ source code generated on  : 09-Oct-2020 15:23:44
//
#ifndef COMPUTE_DELTAX_H
#define COMPUTE_DELTAX_H

// Include Files
#include <cstddef>
#include <cstdlib>
#include "rtwtypes.h"
#include "GetFphi_types.h"

// Function Declarations
extern void compute_deltax(const double H[400], struct_T *solution, c_struct_T
  *memspace, const f_struct_T *qrmanager, d_struct_T *cholmanager, const
  g_struct_T *objective);

#endif

//
// File trailer for compute_deltax.h
//
// [EOF]
//
