//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: partialColLDL3_.cpp
//
// MATLAB Coder version            : 5.0
// C/C++ source code generated on  : 09-Oct-2020 15:23:44
//

// Include Files
#include "stdafx.h"
#include "partialColLDL3_.h"
#include "GetFphi.h"
#include "Getintput_u.h"
#include "rt_nonfinite.h"
#include <cmath>

// Function Definitions

//
// Arguments    : d_struct_T *obj
//                int LD_offset
//                int NColsRemain
//                double REG_PRIMAL
// Return Type  : void
//
void partialColLDL3_(d_struct_T *obj, int LD_offset, int NColsRemain, double
                     REG_PRIMAL)
{
  int k;
  int i;
  int subRows;
  int j;
  int LD_diagOffset;
  int W_diagOffset;
  int iy;
  int offsetColK;
  int i1;
  int ix;
  int iac;
  int ia;
  for (k = 0; k < 48; k++) {
    double a;
    subRows = (NColsRemain - k) - 1;
    LD_diagOffset = (LD_offset + 44 * k) - 1;
    W_diagOffset = 44 * k;
    for (iy = 0; iy <= subRows; iy++) {
      obj->workspace_[W_diagOffset + iy] = obj->FMat[LD_diagOffset + iy];
    }

    offsetColK = 43 * k;
    for (iy = 0; iy < NColsRemain; iy++) {
      obj->workspace2_[iy] = obj->workspace_[offsetColK + iy];
    }

    if ((NColsRemain != 0) && (k != 0)) {
      ix = LD_offset + k;
      i = 43 * (k - 1) + 1;
      for (iac = 1; iac <= i; iac += 43) {
        iy = 0;
        i1 = (iac + NColsRemain) - 1;
        for (ia = iac; ia <= i1; ia++) {
          obj->workspace2_[iy] += obj->workspace_[ia - 1] * -obj->FMat[ix - 1];
          iy++;
        }

        ix += 43;
      }
    }

    for (iy = 0; iy < NColsRemain; iy++) {
      obj->workspace_[offsetColK + iy] = obj->workspace2_[iy];
    }

    for (iy = 0; iy <= subRows; iy++) {
      obj->FMat[LD_diagOffset + iy] = obj->workspace_[W_diagOffset + iy];
    }

    if (std::abs(obj->FMat[LD_diagOffset]) <= obj->regTol_) {
      obj->FMat[LD_diagOffset] += REG_PRIMAL;
    }

    a = 1.0 / obj->FMat[LD_diagOffset];
    offsetColK = LD_diagOffset + 2;
    i = (LD_diagOffset + subRows) + 1;
    for (iy = offsetColK; iy <= i; iy++) {
      obj->FMat[iy - 1] *= a;
    }
  }

  i = NColsRemain - 1;
  for (j = 48; j <= i; j += 48) {
    int ia0;
    int m;
    int iy0;
    int i2;
    int i3;
    subRows = NColsRemain - j;
    if (48 < subRows) {
      LD_diagOffset = 48;
    } else {
      LD_diagOffset = subRows;
    }

    ia0 = j + LD_diagOffset;
    i1 = ia0 - 1;
    for (k = j; k <= i1; k++) {
      m = ia0 - k;
      iy0 = (LD_offset + 44 * k) - 1;
      offsetColK = LD_offset + k;
      for (iy = 0; iy < 48; iy++) {
        obj->workspace2_[iy] = obj->FMat[(offsetColK + iy * 43) - 1];
      }

      W_diagOffset = k + 1;
      if (m != 0) {
        ix = 0;
        i2 = k + 2022;
        for (iac = W_diagOffset; iac <= i2; iac += 43) {
          iy = iy0;
          i3 = (iac + m) - 1;
          for (ia = iac; ia <= i3; ia++) {
            obj->FMat[iy] += obj->workspace_[ia - 1] * -obj->workspace2_[ix];
            iy++;
          }

          ix++;
        }
      }
    }

    if (ia0 < NColsRemain) {
      m = subRows - LD_diagOffset;
      iac = ((LD_offset + LD_diagOffset) + 44 * j) - 1;
      for (W_diagOffset = 0; W_diagOffset < 48; W_diagOffset++) {
        offsetColK = (LD_offset + j) + W_diagOffset * 43;
        iy0 = W_diagOffset * 43;
        for (k = 0; k < LD_diagOffset; k++) {
          iy = k + 1;
          obj->workspace2_[(iy0 + iy) - 1] = obj->FMat[(offsetColK + iy) - 2];
        }
      }

      if ((m != 0) && (LD_diagOffset != 0)) {
        W_diagOffset = iac + 43 * (LD_diagOffset - 1);
        offsetColK = 0;
        for (LD_diagOffset = iac; LD_diagOffset <= W_diagOffset; LD_diagOffset +=
             43) {
          subRows = ia0 - 1;
          offsetColK++;
          i1 = offsetColK + 2021;
          for (iy = offsetColK; iy <= i1; iy += 43) {
            ia = subRows;
            i2 = LD_diagOffset + 1;
            i3 = LD_diagOffset + m;
            for (ix = i2; ix <= i3; ix++) {
              ia++;
              obj->FMat[ix - 1] += -obj->workspace2_[iy - 1] * obj->
                workspace_[ia];
            }

            subRows += 43;
          }
        }
      }
    }
  }
}

//
// File trailer for partialColLDL3_.cpp
//
// [EOF]
//
