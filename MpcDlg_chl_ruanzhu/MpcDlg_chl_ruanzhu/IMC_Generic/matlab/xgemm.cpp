//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: xgemm.cpp
//
// MATLAB Coder version            : 5.0
// C/C++ source code generated on  : 09-Oct-2020 15:23:44
//

// Include Files
#include "stdafx.h"
#include "xgemm.h"
#include "GetFphi.h"
#include "Getintput_u.h"
#include "rt_nonfinite.h"
#include <cstring>

// Function Definitions

//
// Arguments    : int m
//                int n
//                int k
//                const double A[1849]
//                int ia0
//                const double B[903]
//                double C[1849]
// Return Type  : void
//
void b_xgemm(int m, int n, int k, const double A[1849], int ia0, const double B
             [903], double C[1849])
{
  int cr;
  int br;
  int ar;
  double temp;
  if ((m != 0) && (n != 0)) {
    int lastColC;
    int i;
    int i1;
    lastColC = 43 * (n - 1);
    for (cr = 0; cr <= lastColC; cr += 43) {
      i = cr + 1;
      i1 = cr + m;
      if (i <= i1) {
        std::memset(&C[i + -1], 0, ((i1 - i) + 1) * sizeof(double));
      }
    }

    br = -1;
    for (cr = 0; cr <= lastColC; cr += 43) {
      ar = ia0;
      i = cr + 1;
      i1 = cr + m;
      for (int ic = i; ic <= i1; ic++) {
        temp = 0.0;
        for (int w = 0; w < k; w++) {
          int b_w;
          b_w = w + 1;
          temp += A[(b_w + ar) - 2] * B[b_w + br];
        }

        C[ic - 1] += temp;
        ar += 43;
      }

      br += 43;
    }
  }
}

//
// Arguments    : int m
//                int n
//                int k
//                const double A[400]
//                int lda
//                const double B[1849]
//                int ib0
//                double C[903]
// Return Type  : void
//
void xgemm(int m, int n, int k, const double A[400], int lda, const double B
           [1849], int ib0, double C[903])
{
  int br;
  int cr;
  int ar;
  if ((m != 0) && (n != 0)) {
    int lastColC;
    int i;
    int i1;
    br = ib0;
    lastColC = 43 * (n - 1);
    for (cr = 0; cr <= lastColC; cr += 43) {
      i = cr + 1;
      i1 = cr + m;
      if (i <= i1) {
        std::memset(&C[i + -1], 0, ((i1 - i) + 1) * sizeof(double));
      }
    }

    for (cr = 0; cr <= lastColC; cr += 43) {
      ar = -1;
      i = br + k;
      for (int ib = br; ib < i; ib++) {
        int ia;
        int i2;
        ia = ar;
        i1 = cr + 1;
        i2 = cr + m;
        for (int ic = i1; ic <= i2; ic++) {
          ia++;
          C[ic - 1] += B[ib - 1] * A[ia];
        }

        ar += lda;
      }

      br += 43;
    }
  }
}

//
// File trailer for xgemm.cpp
//
// [EOF]
//
