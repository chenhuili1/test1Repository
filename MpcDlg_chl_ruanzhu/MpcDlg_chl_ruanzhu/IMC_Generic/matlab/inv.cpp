//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: inv.cpp
//
// MATLAB Coder version            : 5.0
// C/C++ source code generated on  : 09-Oct-2020 15:23:44
//

// Include Files
#include "stdafx.h"
#include "inv.h"
#include "GetFphi.h"
#include "Getintput_u.h"
#include "rt_nonfinite.h"
#include <cmath>

// Function Definitions

//
// Arguments    : const double x[16]
//                double y[16]
// Return Type  : void
//
void inv(const double x[16], double y[16])
{
  int i;
  signed char ipiv[4];
  double b_x[16];
  int j;
  signed char p[4];
  int jp1j;
  int jy;
  int iy;
  int ix;
  double smax;
  int k;
  signed char i1;
  for (i = 0; i < 16; i++) {
    y[i] = 0.0;
    b_x[i] = x[i];
  }

  ipiv[0] = 1;
  ipiv[1] = 2;
  ipiv[2] = 3;
  for (j = 0; j < 3; j++) {
    int mmj_tmp;
    int b;
    int jj;
    mmj_tmp = 2 - j;
    b = j * 5;
    jj = j * 5;
    jp1j = b + 2;
    jy = 4 - j;
    iy = 0;
    ix = b;
    smax = std::abs(b_x[jj]);
    for (k = 2; k <= jy; k++) {
      double s;
      ix++;
      s = std::abs(b_x[ix]);
      if (s > smax) {
        iy = k - 1;
        smax = s;
      }
    }

    if (b_x[jj + iy] != 0.0) {
      if (iy != 0) {
        iy += j;
        ipiv[j] = static_cast<signed char>(iy + 1);
        smax = b_x[j];
        b_x[j] = b_x[iy];
        b_x[iy] = smax;
        ix = j + 4;
        iy += 4;
        smax = b_x[ix];
        b_x[ix] = b_x[iy];
        b_x[iy] = smax;
        ix += 4;
        iy += 4;
        smax = b_x[ix];
        b_x[ix] = b_x[iy];
        b_x[iy] = smax;
        ix += 4;
        iy += 4;
        smax = b_x[ix];
        b_x[ix] = b_x[iy];
        b_x[iy] = smax;
      }

      i = (jj - j) + 4;
      for (k = jp1j; k <= i; k++) {
        b_x[k - 1] /= b_x[jj];
      }
    }

    jy = b + 4;
    iy = jj;
    for (k = 0; k <= mmj_tmp; k++) {
      smax = b_x[jy];
      if (b_x[jy] != 0.0) {
        ix = jj + 1;
        i = iy + 6;
        jp1j = (iy - j) + 8;
        for (b = i; b <= jp1j; b++) {
          b_x[b - 1] += b_x[ix] * -smax;
          ix++;
        }
      }

      jy += 4;
      iy += 4;
    }
  }

  p[0] = 1;
  p[1] = 2;
  p[2] = 3;
  p[3] = 4;
  if (ipiv[0] > 1) {
    jy = ipiv[0] - 1;
    iy = p[jy];
    p[jy] = 1;
    p[0] = static_cast<signed char>(iy);
  }

  if (ipiv[1] > 2) {
    jy = ipiv[1] - 1;
    iy = p[jy];
    p[jy] = p[1];
    p[1] = static_cast<signed char>(iy);
  }

  if (ipiv[2] > 3) {
    jy = ipiv[2] - 1;
    iy = p[jy];
    p[jy] = p[2];
    p[2] = static_cast<signed char>(iy);
  }

  i1 = p[0];
  y[(p[0] - 1) << 2] = 1.0;
  for (j = 1; j < 5; j++) {
    if (y[(j + ((i1 - 1) << 2)) - 1] != 0.0) {
      i = j + 1;
      for (k = i; k < 5; k++) {
        iy = (k + ((i1 - 1) << 2)) - 1;
        y[iy] -= y[(j + ((i1 - 1) << 2)) - 1] * b_x[(k + ((j - 1) << 2)) - 1];
      }
    }
  }

  i1 = p[1];
  y[((p[1] - 1) << 2) + 1] = 1.0;
  for (j = 2; j < 5; j++) {
    if (y[(j + ((i1 - 1) << 2)) - 1] != 0.0) {
      i = j + 1;
      for (k = i; k < 5; k++) {
        iy = (k + ((i1 - 1) << 2)) - 1;
        y[iy] -= y[(j + ((i1 - 1) << 2)) - 1] * b_x[(k + ((j - 1) << 2)) - 1];
      }
    }
  }

  i1 = p[2];
  y[((p[2] - 1) << 2) + 2] = 1.0;
  for (j = 3; j < 5; j++) {
    jp1j = (j + ((i1 - 1) << 2)) - 1;
    if (y[jp1j] != 0.0) {
      i = j + 1;
      for (k = i; k < 5; k++) {
        iy = ((i1 - 1) << 2) + 3;
        y[iy] -= y[jp1j] * b_x[((j - 1) << 2) + 3];
      }
    }
  }

  y[((p[3] - 1) << 2) + 3] = 1.0;
  for (j = 0; j < 4; j++) {
    jy = j << 2;
    smax = y[jy + 3];
    if (smax != 0.0) {
      y[jy + 3] = smax / b_x[15];
      for (k = 0; k < 3; k++) {
        iy = k + jy;
        y[iy] -= y[jy + 3] * b_x[k + 12];
      }
    }

    smax = y[jy + 2];
    if (smax != 0.0) {
      y[jy + 2] = smax / b_x[10];
      for (k = 0; k < 2; k++) {
        iy = k + jy;
        y[iy] -= y[jy + 2] * b_x[k + 8];
      }
    }

    smax = y[jy + 1];
    if (smax != 0.0) {
      y[jy + 1] = smax / b_x[5];
      for (k = 0; k < 1; k++) {
        y[jy] -= y[jy + 1] * b_x[4];
      }
    }

    if (y[jy] != 0.0) {
      y[jy] /= b_x[0];
    }
  }
}

//
// File trailer for inv.cpp
//
// [EOF]
//
