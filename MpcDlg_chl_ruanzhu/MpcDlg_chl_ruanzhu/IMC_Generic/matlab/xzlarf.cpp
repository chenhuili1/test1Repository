//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: xzlarf.cpp
//
// MATLAB Coder version            : 5.0
// C/C++ source code generated on  : 09-Oct-2020 15:23:44
//

// Include Files
#include "stdafx.h"
#include "xzlarf.h"
#include "GetFphi.h"
#include "Getintput_u.h"
#include "rt_nonfinite.h"
#include <cstring>

// Function Definitions

//
// Arguments    : int m
//                int n
//                int iv0
//                double tau
//                double C[1849]
//                int ic0
//                double work[43]
// Return Type  : void
//
void xzlarf(int m, int n, int iv0, double tau, double C[1849], int ic0, double
            work[43])
{
  int lastv;
  int lastc;
  int i;
  int iac;
  int ia;
  double c;
  if (tau != 0.0) {
    bool exitg2;
    lastv = m;
    i = iv0 + m;
    while ((lastv > 0) && (C[i - 2] == 0.0)) {
      lastv--;
      i--;
    }

    lastc = n - 1;
    exitg2 = false;
    while ((!exitg2) && (lastc + 1 > 0)) {
      int exitg1;
      i = ic0 + lastc * 43;
      ia = i;
      do {
        exitg1 = 0;
        if (ia <= (i + lastv) - 1) {
          if (C[ia - 1] != 0.0) {
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
    int jy;
    int b_i;
    int ix;
    if (lastc + 1 != 0) {
      if (0 <= lastc) {
        std::memset(&work[0], 0, (lastc + 1) * sizeof(double));
      }

      i = 0;
      b_i = ic0 + 43 * lastc;
      for (iac = ic0; iac <= b_i; iac += 43) {
        ix = iv0;
        c = 0.0;
        jy = (iac + lastv) - 1;
        for (ia = iac; ia <= jy; ia++) {
          c += C[ia - 1] * C[ix - 1];
          ix++;
        }

        work[i] += c;
        i++;
      }
    }

    if (!(-tau == 0.0)) {
      i = ic0;
      jy = 0;
      for (iac = 0; iac <= lastc; iac++) {
        if (work[jy] != 0.0) {
          c = work[jy] * -tau;
          ix = iv0;
          b_i = lastv + i;
          for (ia = i; ia < b_i; ia++) {
            C[ia - 1] += C[ix - 1] * c;
            ix++;
          }
        }

        jy++;
        i += 43;
      }
    }
  }
}

//
// File trailer for xzlarf.cpp
//
// [EOF]
//
