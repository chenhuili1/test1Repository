//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: factor.cpp
//
// MATLAB Coder version            : 5.0
// C/C++ source code generated on  : 09-Oct-2020 15:23:44
//

// Include Files
#include "stdafx.h"
#include "factor.h"
#include "GetFphi.h"
#include "Getintput_u.h"
#include "fullColLDL2_.h"
#include "partialColLDL3_.h"
#include "rt_nonfinite.h"
#include <cmath>

// Function Definitions

//
// Arguments    : d_struct_T *obj
//                const double A[400]
//                int ndims
//                int ldA
// Return Type  : void
//
void factor(d_struct_T *obj, const double A[400], int ndims, int ldA)
{
  double SCALED_REG_PRIMAL;
  int idx;
  int A_maxDiag_idx;
  int ix;
  int k;
  double smax;
  double s;
  SCALED_REG_PRIMAL = 1.4901161193847656E-6 * static_cast<double>(ndims);
  obj->ndims = ndims;
  for (idx = 0; idx < ndims; idx++) {
    A_maxDiag_idx = ldA * idx;
    ix = 43 * idx;
    for (k = 0; k < ndims; k++) {
      int b_k;
      b_k = k + 1;
      obj->FMat[(ix + b_k) - 1] = A[(A_maxDiag_idx + b_k) - 1];
    }
  }

  if (ndims < 1) {
    A_maxDiag_idx = 0;
  } else {
    A_maxDiag_idx = 1;
    if (ndims > 1) {
      ix = 0;
      smax = std::abs(obj->FMat[0]);
      for (k = 2; k <= ndims; k++) {
        ix += 44;
        s = std::abs(obj->FMat[ix]);
        if (s > smax) {
          A_maxDiag_idx = k;
          smax = s;
        }
      }
    }
  }

  smax = std::abs(obj->FMat[A_maxDiag_idx * 44 - 1]) * 2.2204460492503131E-16;
  s = std::abs(SCALED_REG_PRIMAL);
  if (smax > s) {
    s = smax;
  }

  obj->regTol_ = s;
  if (ndims > 128) {
    bool exitg1;
    k = 0;
    exitg1 = false;
    while ((!exitg1) && (k < ndims)) {
      A_maxDiag_idx = 44 * k + 1;
      ix = ndims - k;
      if (k + 48 <= ndims) {
        partialColLDL3_(obj, A_maxDiag_idx, ix, SCALED_REG_PRIMAL);
        k += 48;
      } else {
        fullColLDL2_(obj, A_maxDiag_idx, ix, SCALED_REG_PRIMAL);
        exitg1 = true;
      }
    }
  } else {
    fullColLDL2_(obj, 1, ndims, SCALED_REG_PRIMAL);
  }

  if (obj->ConvexCheck) {
    idx = 0;
    int exitg2;
    do {
      exitg2 = 0;
      if (idx <= ndims - 1) {
        if (obj->FMat[idx + 43 * idx] <= 0.0) {
          obj->info = -idx - 1;
          exitg2 = 1;
        } else {
          idx++;
        }
      } else {
        obj->ConvexCheck = false;
        exitg2 = 1;
      }
    } while (exitg2 == 0);
  }
}

//
// File trailer for factor.cpp
//
// [EOF]
//
