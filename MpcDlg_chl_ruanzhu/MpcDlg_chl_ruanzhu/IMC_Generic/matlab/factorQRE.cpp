//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: factorQRE.cpp
//
// MATLAB Coder version            : 5.0
// C/C++ source code generated on  : 09-Oct-2020 15:23:44
//

// Include Files
#include "stdafx.h"
#include "factorQRE.h"
#include "GetFphi.h"
#include "Getintput_u.h"
#include "rt_nonfinite.h"
#include "xgeqp3.h"

// Function Definitions

//
// Arguments    : f_struct_T *obj
//                const double A[903]
//                int mrows
//                int ncols
// Return Type  : void
//
void factorQRE(f_struct_T *obj, const double A[903], int mrows, int ncols)
{
  int ix0;
  bool guard1 = false;
  ix0 = mrows * ncols;
  guard1 = false;
  if (ix0 > 0) {
    for (int idx = 0; idx < ncols; idx++) {
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
    obj->usedPivoting = true;
    obj->mrows = mrows;
    obj->ncols = ncols;
    if (mrows < ncols) {
      ix0 = mrows;
    } else {
      ix0 = ncols;
    }

    obj->minRowCol = ix0;
    xgeqp3(obj->QR, mrows, ncols, obj->jpvt, obj->tau);
  }
}

//
// File trailer for factorQRE.cpp
//
// [EOF]
//
