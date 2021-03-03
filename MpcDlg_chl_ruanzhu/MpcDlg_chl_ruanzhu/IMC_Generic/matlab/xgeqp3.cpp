//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: xgeqp3.cpp
//
// MATLAB Coder version            : 5.0
// C/C++ source code generated on  : 09-Oct-2020 15:23:44
//

// Include Files
#include "stdafx.h"
#include "xgeqp3.h"
#include "GetFphi.h"
#include "Getintput_u.h"
#include "rt_nonfinite.h"
#include "xzgeqp3.h"
#include <cstring>

// Function Definitions

//
// Arguments    : double A[1849]
//                int m
//                int n
//                int jpvt[43]
//                double tau[43]
// Return Type  : void
//
void xgeqp3(double A[1849], int m, int n, int jpvt[43], double tau[43])
{
  int minmn;
  if (m < n) {
    minmn = m;
  } else {
    minmn = n;
  }

  std::memset(&tau[0], 0, 43U * sizeof(double));
  if (minmn < 1) {
    for (int j = 0; j < n; j++) {
      jpvt[j] = j + 1;
    }
  } else {
    int nfxd;
    nfxd = 0;
    for (int j = 0; j < n; j++) {
      if (jpvt[j] != 0) {
        nfxd++;
        if (j + 1 != nfxd) {
          int ix;
          int iy;
          ix = j * 43;
          iy = (nfxd - 1) * 43;
          for (int k = 0; k < m; k++) {
            double temp;
            temp = A[ix];
            A[ix] = A[iy];
            A[iy] = temp;
            ix++;
            iy++;
          }

          jpvt[j] = jpvt[nfxd - 1];
          jpvt[nfxd - 1] = j + 1;
        } else {
          jpvt[j] = j + 1;
        }
      } else {
        jpvt[j] = j + 1;
      }
    }

    if (nfxd >= minmn) {
      nfxd = minmn;
    }

    qrf(A, m, n, nfxd, tau);
    if (nfxd < minmn) {
      qrpf(A, m, n, nfxd, tau, jpvt);
    }
  }
}

//
// File trailer for xgeqp3.cpp
//
// [EOF]
//
