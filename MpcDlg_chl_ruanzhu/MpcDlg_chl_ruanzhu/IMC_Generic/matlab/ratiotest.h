//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: ratiotest.h
//
// MATLAB Coder version            : 5.0
// C/C++ source code generated on  : 09-Oct-2020 15:23:44
//
#ifndef RATIOTEST_H
#define RATIOTEST_H

// Include Files
#include <cstddef>
#include <cstdlib>
#include "rtwtypes.h"
#include "GetFphi_types.h"

// Function Declarations
extern void ratiotest(const double solution_xstar[21], const double
                      solution_searchDir[21], double workspace[903], int
                      workingset_nVar, const double workingset_Aineq[42], const
                      double workingset_bineq[2], const double workingset_lb[21],
                      const double workingset_ub[21], const int
                      workingset_indexLB[21], const int workingset_indexUB[21],
                      const int workingset_sizes[5], const int
                      workingset_isActiveIdx[6], const bool
                      workingset_isActiveConstr[43], const int
                      workingset_nWConstr[5], double *toldelta, double *alpha,
                      bool *newBlocking, int *constrType, int *constrIdx);

#endif

//
// File trailer for ratiotest.h
//
// [EOF]
//
