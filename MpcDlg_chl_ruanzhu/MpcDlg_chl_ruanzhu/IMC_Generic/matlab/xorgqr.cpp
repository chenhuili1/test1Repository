//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: xorgqr.cpp
//
// MATLAB Coder version            : 5.0
// C/C++ source code generated on  : 09-Oct-2020 15:23:44
//

// Include Files
#include "stdafx.h"
#include "xorgqr.h"
#include "GetFphi.h"
#include "Getintput_u.h"
#include "rt_nonfinite.h"
#include <cstring>

// Function Definitions

//
// Arguments    : int m
//                int n
//                int k
//                double A[1849]
//                const double tau[43]
// Return Type  : void
//
void xorgqr(int m, int n, int k, double A[1849], const double tau[43])
{
  double work[43];
  int c_i;
  int jy;
  double c;
  if (n >= 1) {
    int i;
    int j;
    int itau;
    int ia;
    int i1;
    i = n - 1;
    for (j = k; j <= i; j++) {
      ia = j * 43;
      i1 = m - 1;
      if (0 <= i1) {
        std::memset(&A[ia], 0, (((i1 + ia) - ia) + 1) * sizeof(double));
      }

      A[ia + j] = 1.0;
    }

    itau = k - 1;
    std::memset(&work[0], 0, 43U * sizeof(double));
    for (int b_i = k; b_i >= 1; b_i--) {
      int iaii;
      iaii = b_i + (b_i - 1) * 43;
      if (b_i < n) {
        int lastv;
        int lastc;
        A[iaii - 1] = 1.0;
        c_i = (m - b_i) - 1;
        j = iaii + 43;
        if (tau[itau] != 0.0) {
          bool exitg2;
          lastv = c_i + 2;
          c_i += iaii;
          while ((lastv > 0) && (A[c_i] == 0.0)) {
            lastv--;
            c_i--;
          }

          lastc = (n - b_i) - 1;
          exitg2 = false;
          while ((!exitg2) && (lastc + 1 > 0)) {
            int exitg1;
            c_i = (iaii + lastc * 43) + 42;
            ia = c_i;
            do {
              exitg1 = 0;
              if (ia + 1 <= c_i + lastv) {
                if (A[ia] != 0.0) {
                  exitg1 = 1;
                } else {
                  ia++;
                }
              } else {
                lastc--;
                exitg1 = 2;
              }
            } while (exitg1 == 0);

            if (exitg1 == 1) {
              exitg2 = true;
            }
          }
        } else {
          lastv = 0;
          lastc = -1;
        }

        if (lastv > 0) {
          int ix;
          if (lastc + 1 != 0) {
            if (0 <= lastc) {
              std::memset(&work[0], 0, (lastc + 1) * sizeof(double));
            }

            c_i = 0;
            i = (iaii + 43 * lastc) + 43;
            for (jy = j; jy <= i; jy += 43) {
              ix = iaii;
              c = 0.0;
              i1 = (jy + lastv) - 1;
              for (ia = jy; ia <= i1; ia++) {
                c += A[ia - 1] * A[ix - 1];
                ix++;
              }

              work[c_i] += c;
              c_i++;
            }
          }

          if (!(-tau[itau] == 0.0)) {
            c_i = iaii;
            jy = 0;
            for (j = 0; j <= lastc; j++) {
              if (work[jy] != 0.0) {
                c = work[jy] * -tau[itau];
                ix = iaii;
                i = c_i + 43;
                i1 = lastv + c_i;
                for (ia = i; ia <= i1 + 42; ia++) {
                  A[ia - 1] += A[ix - 1] * c;
                  ix++;
                }
              }

              jy++;
              c_i += 43;
            }
          }
        }
      }

      if (b_i < m) {
        c_i = iaii + 1;
        i = (iaii + m) - b_i;
        for (jy = c_i; jy <= i; jy++) {
          A[jy - 1] *= -tau[itau];
        }
      }

      A[iaii - 1] = 1.0 - tau[itau];
      for (j = 0; j <= b_i - 2; j++) {
        A[(iaii - j) - 2] = 0.0;
      }

      itau--;
    }
  }
}

//
// File trailer for xorgqr.cpp
//
// [EOF]
//
