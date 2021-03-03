//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: compute_lambda.cpp
//
// MATLAB Coder version            : 5.0
// C/C++ source code generated on  : 09-Oct-2020 15:23:44
//

// Include Files
#include "stdafx.h"
#include "compute_lambda.h"
#include "GetFphi.h"
#include "Getintput_u.h"
#include "rt_nonfinite.h"
#include <cmath>
#include <cstring>

// Function Definitions

//
// Arguments    : double workspace[903]
//                struct_T *solution
//                const g_struct_T *objective
//                const f_struct_T *qrmanager
// Return Type  : void
//
void compute_lambda(double workspace[903], struct_T *solution, const g_struct_T *
                    objective, const f_struct_T *qrmanager)
{
  int nActiveConstr;
  double c;
  int iac;
  nActiveConstr = qrmanager->ncols;
  if (qrmanager->ncols > 0) {
    bool nonDegenerate;
    int idx;
    c = 100.0 * static_cast<double>(qrmanager->mrows) * 2.2204460492503131E-16;
    if ((qrmanager->mrows > 0) && (qrmanager->ncols > 0)) {
      nonDegenerate = true;
    } else {
      nonDegenerate = false;
    }

    if (nonDegenerate) {
      bool guard1 = false;
      idx = qrmanager->ncols;
      guard1 = false;
      if (qrmanager->mrows < qrmanager->ncols) {
        while ((idx > qrmanager->mrows) && (std::abs(qrmanager->QR
                 [(qrmanager->mrows + 43 * (idx - 1)) - 1]) >= c)) {
          idx--;
        }

        nonDegenerate = (idx == qrmanager->mrows);
        if (nonDegenerate) {
          guard1 = true;
        }
      } else {
        guard1 = true;
      }

      if (guard1) {
        while ((idx >= 1) && (std::abs(qrmanager->QR[(idx + 43 * (idx - 1)) - 1])
                              >= c)) {
          idx--;
        }

        nonDegenerate = (idx == 0);
      }
    }

    if (!nonDegenerate) {
      solution->state = -7;
    } else {
      int j;
      int i;
      int ix;
      if (qrmanager->mrows != 0) {
        idx = qrmanager->ncols;
        if (0 <= idx - 1) {
          std::memset(&workspace[0], 0, idx * sizeof(double));
        }

        idx = 0;
        j = 43 * (qrmanager->ncols - 1) + 1;
        for (iac = 1; iac <= j; iac += 43) {
          ix = 0;
          c = 0.0;
          i = (iac + qrmanager->mrows) - 1;
          for (int ia = iac; ia <= i; ia++) {
            c += qrmanager->Q[ia - 1] * objective->grad[ix];
            ix++;
          }

          workspace[idx] += c;
          idx++;
        }
      }

      for (j = nActiveConstr; j >= 1; j--) {
        idx = (j + (j - 1) * 43) - 1;
        workspace[j - 1] /= qrmanager->QR[idx];
        for (i = 0; i <= j - 2; i++) {
          ix = (j - i) - 2;
          workspace[ix] -= workspace[j - 1] * qrmanager->QR[(idx - i) - 1];
        }
      }

      for (idx = 0; idx < nActiveConstr; idx++) {
        solution->lambda[idx] = -workspace[idx];
      }
    }
  }
}

//
// File trailer for compute_lambda.cpp
//
// [EOF]
//
