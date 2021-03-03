//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: GetFphi.cpp
//
// MATLAB Coder version            : 5.0
// C/C++ source code generated on  : 09-Oct-2020 15:23:44
//

// Include Files
#include "stdafx.h"
#include "GetFphi.h"
#include "GetFphi_data.h"
#include "GetFphi_initialize.h"
#include "Getintput_u.h"
#include "mpower.h"
#include "rt_nonfinite.h"
#include <cstring>

// Function Definitions

//
// Arguments    : const double Ap[16]
//                const double Bp[4]
//                double F[320]
//                double phi[1600]
// Return Type  : void
//
void GetFphi(const double Ap[16], const double Bp[4], double F[320], double phi
             [1600])
{
  double i;
  double dv[16];
  if (!isInitialized_GetFphi) {
    GetFphi_initialize();
  }

  std::memset(&F[0], 0, 320U * sizeof(double));
  std::memset(&phi[0], 0, 1600U * sizeof(double));
  i = 1.0;
  for (int j = 0; j < 20; j++) {
    int b_i;
    int F_tmp;
    mpower(Ap, static_cast<double>(j) + 1.0, dv);
    for (b_i = 0; b_i < 4; b_i++) {
      F_tmp = b_i << 2;
      F[(static_cast<int>(i) + 80 * b_i) - 1] = dv[F_tmp];
      F[(static_cast<int>(i + 1.0) + 80 * b_i) - 1] = dv[F_tmp + 1];
      F[(static_cast<int>(i + 2.0) + 80 * b_i) - 1] = dv[F_tmp + 2];
      F[(static_cast<int>(i + 3.0) + 80 * b_i) - 1] = dv[F_tmp + 3];
    }

    for (F_tmp = 0; F_tmp < 20; F_tmp++) {
      if (F_tmp <= j) {
        mpower(Ap, static_cast<double>(j - F_tmp), dv);
        for (b_i = 0; b_i < 4; b_i++) {
          int phi_tmp;
          phi_tmp = (static_cast<int>(i + static_cast<double>(b_i)) + 80 * F_tmp)
            - 1;
          phi[phi_tmp] = 0.0;
          phi[phi_tmp] += dv[b_i] * Bp[0];
          phi[phi_tmp] += dv[b_i + 4] * Bp[1];
          phi[phi_tmp] += dv[b_i + 8] * Bp[2];
          phi[phi_tmp] += dv[b_i + 12] * Bp[3];
        }
      } else {
        phi[(static_cast<int>(i) + 80 * F_tmp) - 1] = 0.0;
        phi[(static_cast<int>(i + 1.0) + 80 * F_tmp) - 1] = 0.0;
        phi[(static_cast<int>(i + 2.0) + 80 * F_tmp) - 1] = 0.0;
        phi[(static_cast<int>(i + 3.0) + 80 * F_tmp) - 1] = 0.0;
      }
    }

    i += 4.0;
  }
}

//
// File trailer for GetFphi.cpp
//
// [EOF]
//
