//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: factorQR.cpp
//
// MATLAB Coder version            : 5.0
// C/C++ source code generated on  : 09-Oct-2020 15:23:44
//

// Include Files
#include "stdafx.h"
#include "factorQR.h"
#include "GetFphi.h"
#include "Getintput_u.h"
#include "rt_nonfinite.h"
#include "xzgeqp3.h"
#include <cstring>

// Function Definitions

//
// Arguments    : f_struct_T *obj
//                const double A[903]
//                int mrows
//                int ncols
// Return Type  : void
//
void factorQR(f_struct_T *obj, const double A[903], int mrows, int ncols)
{
  int ix0;
  bool guard1 = false;
  int idx;
  double b_A[1849];
  double tau[43];
  ix0 = mrows * ncols;
  guard1 = false;
  if (ix0 > 0) {
    for (idx = 0; idx < ncols; idx++) {
      int iy0;
      ix0 = 21 * idx;
      iy0 = 43 * idx;
      for (int k = 0; k < mrows; k++) {
        int b_k;
        b_k = k + 1;
        obj->QR[(iy0 + b_k) - 1] = A[(ix0 + b_k) - 1];
      }
    }

    guard1 = true;
  } else if (ix0 == 0) {
    obj->mrows = mrows;
    obj->ncols = ncols;
    obj->minRowCol = 0;
  } else {
    guard1 = true;
  }

  if (guard1) {
    obj->usedPivoting = false;
    obj->mrows = mrows;
    obj->ncols = ncols;
    for (idx = 0; idx < ncols; idx++) {
      obj->jpvt[idx] = idx + 1;
    }

    if (mrows < ncols) {
      ix0 = mrows;
    } else {
      ix0 = ncols;
    }

    obj->minRowCol = ix0;
    std::memcpy(&b_A[0], &obj->QR[0], 1849U * sizeof(double));
    std::memset(&tau[0], 0, 43U * sizeof(double));
    if (ix0 >= 1) {
      std::memcpy(&obj->QR[0], &b_A[0], 1849U * sizeof(double));
      qrf(obj->QR, mrows, ncols, ix0, tau);
    }

    std::memcpy(&obj->tau[0], &tau[0], 43U * sizeof(double));
  }
}

//
// File trailer for factorQR.cpp
//
// [EOF]
//
