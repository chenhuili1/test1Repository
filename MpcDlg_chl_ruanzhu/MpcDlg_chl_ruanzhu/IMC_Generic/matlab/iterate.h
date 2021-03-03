//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: iterate.h
//
// MATLAB Coder version            : 5.0
// C/C++ source code generated on  : 09-Oct-2020 15:23:44
//
#ifndef ITERATE_H
#define ITERATE_H

// Include Files
#include <cstddef>
#include <cstdlib>
#include "rtwtypes.h"
#include "GetFphi_types.h"

// Function Declarations
extern void iterate(const double H[400], const double f[20], struct_T *solution,
                    c_struct_T *memspace, e_struct_T *workingset, f_struct_T
                    *qrmanager, d_struct_T *cholmanager, g_struct_T *objective,
                    double options_ObjectiveLimit, double options_StepTolerance,
                    int runTimeOptions_MaxIterations, double
                    c_runTimeOptions_ConstrRelTolFa, double
                    runTimeOptions_ProbRelTolFactor, bool
                    runTimeOptions_RemainFeasible);

#endif

//
// File trailer for iterate.h
//
// [EOF]
//
