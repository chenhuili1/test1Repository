//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: driver.h
//
// MATLAB Coder version            : 5.0
// C/C++ source code generated on  : 09-Oct-2020 15:23:44
//
#ifndef DRIVER_H
#define DRIVER_H

// Include Files
#include <cstddef>
#include <cstdlib>
#include "rtwtypes.h"
#include "GetFphi_types.h"

// Function Declarations
extern void driver(const double H[400], const double f[20], struct_T *solution,
                   c_struct_T *memspace, e_struct_T *workingset, d_struct_T
                   *cholmanager, b_struct_T runTimeOptions, f_struct_T
                   *qrmanager, g_struct_T *objective);

#endif

//
// File trailer for driver.h
//
// [EOF]
//
