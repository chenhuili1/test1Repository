//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: solve.cpp
//
// MATLAB Coder version            : 5.0
// C/C++ source code generated on  : 09-Oct-2020 15:23:44
//

// Include Files
#include "stdafx.h"
#include "solve.h"
#include "GetFphi.h"
#include "Getintput_u.h"
#include "rt_nonfinite.h"

// Function Definitions

//
// Arguments    : const d_struct_T *obj
//                double rhs[21]
// Return Type  : void
//
void solve(const d_struct_T *obj, double rhs[21])
{
  int n;
  int j;
  int i;
  int jjA;
  int b_i;
  double temp;
  n = obj->ndims - 2;
  if (obj->ndims != 0) {
    for (j = 0; j <= n + 1; j++) {
      jjA = j + j * 43;
      i = n - j;
      for (b_i = 0; b_i <= i; b_i++) {
        int c_i;
        int ix;
        c_i = b_i + 1;
        ix = j + c_i;
        rhs[ix] -= rhs[j] * obj->FMat[jjA + c_i];
      }
    }
  }

  i = obj->ndims;
  for (jjA = 0; jjA < i; jjA++) {
    rhs[jjA] /= obj->FMat[jjA + 43 * jjA];
  }

  n = obj->ndims;
  if (obj->ndims != 0) {
    for (j = n; j >= 1; j--) {
      jjA = (j - 1) * 43;
      temp = rhs[j - 1];
      i = j + 1;
      for (b_i = n; b_i >= i; b_i--) {
        temp -= obj->FMat[(jjA + b_i) - 1] * rhs[b_i - 1];
      }

      rhs[j - 1] = temp;
    }
  }
}

//
// File trailer for solve.cpp
//
// [EOF]
//
