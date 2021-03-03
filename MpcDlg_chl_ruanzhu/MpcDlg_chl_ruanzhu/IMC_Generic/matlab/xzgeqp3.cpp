//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: xzgeqp3.cpp
//
// MATLAB Coder version            : 5.0
// C/C++ source code generated on  : 09-Oct-2020 15:23:44
//

// Include Files
#include "stdafx.h"
#include "xzgeqp3.h"
#include "GetFphi.h"
#include "Getintput_u.h"
#include "rt_nonfinite.h"
#include "xnrm2.h"
#include "xzlarf.h"
#include "xzlarfg.h"
#include <cmath>
#include <cstring>

// Function Definitions

//
// Arguments    : double A[1849]
//                int m
//                int n
//                int nfxd
//                double tau[43]
// Return Type  : void
//
void qrf(double A[1849], int m, int n, int nfxd, double tau[43])
{
  double work[43];
  double atmp;
  std::memset(&work[0], 0, 43U * sizeof(double));
  for (int i = 0; i < nfxd; i++) {
    int ii;
    int mmi;
    ii = i * 43 + i;
    mmi = m - i;
    if (i + 1 < m) {
      atmp = A[ii];
      tau[i] = xzlarfg(mmi, &atmp, A, ii + 2);
      A[ii] = atmp;
    } else {
      tau[i] = 0.0;
    }

    if (i + 1 < n) {
      atmp = A[ii];
      A[ii] = 1.0;
      xzlarf(mmi, (n - i) - 1, ii + 1, tau[i], A, ii + 44, work);
      A[ii] = atmp;
    }
  }
}

//
// Arguments    : double A[1849]
//                int m
//                int n
//                int nfxd
//                double tau[43]
//                int jpvt[43]
// Return Type  : void
//
void qrpf(double A[1849], int m, int n, int nfxd, double tau[43], int jpvt[43])
{
  int minmn;
  double work[43];
  double vn1[43];
  double vn2[43];
  int i;
  int ix;
  double smax;
  if (m < n) {
    minmn = m;
  } else {
    minmn = n;
  }

  std::memset(&work[0], 0, 43U * sizeof(double));
  std::memset(&vn1[0], 0, 43U * sizeof(double));
  std::memset(&vn2[0], 0, 43U * sizeof(double));
  i = nfxd + 1;
  for (ix = i; ix <= n; ix++) {
    smax = xnrm2(m - nfxd, A, (nfxd + (ix - 1) * 43) + 1);
    vn1[ix - 1] = smax;
    vn2[ix - 1] = smax;
  }

  i = nfxd + 1;
  for (int b_i = i; b_i <= minmn; b_i++) {
    int ip1;
    int iy;
    int ii;
    int nmi;
    int mmi;
    int itemp;
    int pvt;
    int k;
    double s;
    ip1 = b_i + 1;
    iy = (b_i - 1) * 43;
    ii = (iy + b_i) - 1;
    nmi = (n - b_i) + 1;
    mmi = m - b_i;
    if (nmi < 1) {
      itemp = -2;
    } else {
      itemp = -1;
      if (nmi > 1) {
        ix = b_i;
        smax = std::abs(vn1[b_i - 1]);
        for (k = 2; k <= nmi; k++) {
          ix++;
          s = std::abs(vn1[ix - 1]);
          if (s > smax) {
            itemp = k - 2;
            smax = s;
          }
        }
      }
    }

    pvt = b_i + itemp;
    if (pvt + 1 != b_i) {
      ix = pvt * 43;
      for (k = 0; k < m; k++) {
        smax = A[ix];
        A[ix] = A[iy];
        A[iy] = smax;
        ix++;
        iy++;
      }

      itemp = jpvt[pvt];
      jpvt[pvt] = jpvt[b_i - 1];
      jpvt[b_i - 1] = itemp;
      vn1[pvt] = vn1[b_i - 1];
      vn2[pvt] = vn2[b_i - 1];
    }

    if (b_i < m) {
      smax = A[ii];
      tau[b_i - 1] = xzlarfg(mmi + 1, &smax, A, ii + 2);
      A[ii] = smax;
    } else {
      tau[b_i - 1] = 0.0;
    }

    if (b_i < n) {
      smax = A[ii];
      A[ii] = 1.0;
      xzlarf(mmi + 1, nmi - 1, ii + 1, tau[b_i - 1], A, ii + 44, work);
      A[ii] = smax;
    }

    for (ix = ip1; ix <= n; ix++) {
      itemp = b_i + (ix - 1) * 43;
      smax = vn1[ix - 1];
      if (smax != 0.0) {
        double temp2;
        s = std::abs(A[itemp - 1]) / smax;
        s = 1.0 - s * s;
        if (s < 0.0) {
          s = 0.0;
        }

        temp2 = smax / vn2[ix - 1];
        temp2 = s * (temp2 * temp2);
        if (temp2 <= 1.4901161193847656E-8) {
          if (b_i < m) {
            smax = xnrm2(mmi, A, itemp + 1);
            vn1[ix - 1] = smax;
            vn2[ix - 1] = smax;
          } else {
            vn1[ix - 1] = 0.0;
            vn2[ix - 1] = 0.0;
          }
        } else {
          vn1[ix - 1] = smax * std::sqrt(s);
        }
      }
    }
  }
}

//
// File trailer for xzgeqp3.cpp
//
// [EOF]
//
