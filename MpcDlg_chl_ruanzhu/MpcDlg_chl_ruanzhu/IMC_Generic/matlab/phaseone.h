//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: phaseone.h
//
// MATLAB Coder version            : 5.0
// C/C++ source code generated on  : 09-Oct-2020 15:23:44
//
#ifndef PHASEONE_H
#define PHASEONE_H

// Include Files
#include <cstddef>
#include <cstdlib>
#include "rtwtypes.h"
#include "GetFphi_types.h"

// Function Declarations
extern void b_phaseone(const double H[400], const double f[20], struct_T
  *solution, c_struct_T *memspace, e_struct_T *workingset, f_struct_T *qrmanager,
  d_struct_T *cholmanager, g_struct_T *objective, h_struct_T *options, const
  b_struct_T *runTimeOptions);
extern void phaseone(const double H[400], const double f[20], struct_T *solution,
                     c_struct_T *memspace, e_struct_T *workingset, f_struct_T
                     *qrmanager, d_struct_T *cholmanager, h_struct_T *options,
                     const b_struct_T *runTimeOptions, g_struct_T *objective);

#endif

//
// File trailer for phaseone.h
//
// [EOF]
//
