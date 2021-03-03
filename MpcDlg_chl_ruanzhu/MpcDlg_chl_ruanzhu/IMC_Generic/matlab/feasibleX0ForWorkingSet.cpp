//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: feasibleX0ForWorkingSet.cpp
//
// MATLAB Coder version            : 5.0
// C/C++ source code generated on  : 09-Oct-2020 15:23:44
//

// Include Files
#include "stdafx.h"
#include "feasibleX0ForWorkingSet.h"
#include "GetFphi.h"
#include "Getintput_u.h"
#include "factorQR.h"
#include "rt_nonfinite.h"
#include "xorgqr.h"
#include "xzgeqp3.h"
#include <cmath>
#include <cstring>

// Function Definitions

//
// Arguments    : double workspace[903]
//                double xCurrent[21]
//                e_struct_T *workingset
//                f_struct_T *qrmanager
// Return Type  : bool
//
bool feasibleX0ForWorkingSet(double workspace[903], double xCurrent[21],
  e_struct_T *workingset, f_struct_T *qrmanager)
{
  bool nonDegenerateWset;
  int mWConstr_tmp;
  int nVar;
  int ar;
  int mFixed;
  double c;
  double B[903];
  double A[1849];
  double tau[43];
  mWConstr_tmp = workingset->nActiveConstr - 1;
  nVar = workingset->nVar;
  nonDegenerateWset = true;
  if (workingset->nActiveConstr != 0) {
    int ix;
    int iy;
    int i;
    int i1;
    int ia;
    for (ix = 0; ix <= mWConstr_tmp; ix++) {
      workspace[ix] = workingset->bwset[ix];
      workspace[ix + 43] = workingset->bwset[ix];
    }

    if (workingset->nActiveConstr != 0) {
      iy = 0;
      i = 21 * mWConstr_tmp + 1;
      for (mFixed = 1; mFixed <= i; mFixed += 21) {
        ix = 0;
        c = 0.0;
        i1 = (mFixed + nVar) - 1;
        for (ia = mFixed; ia <= i1; ia++) {
          c += workingset->ATwset[ia - 1] * xCurrent[ix];
          ix++;
        }

        workspace[iy] += -c;
        iy++;
      }
    }

    if (workingset->nActiveConstr >= workingset->nVar) {
      for (ar = 0; ar < nVar; ar++) {
        for (iy = 0; iy <= mWConstr_tmp; iy++) {
          qrmanager->QR[iy + 43 * ar] = workingset->ATwset[ar + 21 * iy];
        }
      }

      iy = workingset->nVar;
      qrmanager->usedPivoting = false;
      qrmanager->mrows = workingset->nActiveConstr;
      qrmanager->ncols = workingset->nVar;
      for (ix = 0; ix < iy; ix++) {
        qrmanager->jpvt[ix] = ix + 1;
      }

      iy = workingset->nActiveConstr;
      ar = workingset->nVar;
      if (iy < ar) {
        ar = iy;
      }

      qrmanager->minRowCol = ar;
      std::memcpy(&A[0], &qrmanager->QR[0], 1849U * sizeof(double));
      std::memset(&tau[0], 0, 43U * sizeof(double));
      if (ar >= 1) {
        std::memcpy(&qrmanager->QR[0], &A[0], 1849U * sizeof(double));
        qrf(qrmanager->QR, workingset->nActiveConstr, workingset->nVar, ar, tau);
      }

      std::memcpy(&qrmanager->tau[0], &tau[0], 43U * sizeof(double));
      i = qrmanager->minRowCol;
      for (ix = 0; ix < i; ix++) {
        iy = 43 * ix + ix;
        ar = workingset->nActiveConstr - ix;
        if (0 <= ar - 2) {
          std::memcpy(&qrmanager->Q[iy + 1], &qrmanager->QR[iy + 1], (ar + -1) *
                      sizeof(double));
        }
      }

      xorgqr(workingset->nActiveConstr, workingset->nActiveConstr,
             qrmanager->minRowCol, qrmanager->Q, tau);
      std::memcpy(&B[0], &workspace[0], 903U * sizeof(double));
      if (1 <= nVar) {
        std::memset(&workspace[0], 0, nVar * sizeof(double));
      }

      i = nVar + 43;
      if (44 <= i) {
        std::memset(&workspace[43], 0, (i + -43) * sizeof(double));
      }

      ar = -1;
      for (ix = 1; ix <= nVar; ix++) {
        c = 0.0;
        for (mFixed = 0; mFixed <= mWConstr_tmp; mFixed++) {
          iy = mFixed + 1;
          c += qrmanager->Q[iy + ar] * B[iy + -1];
        }

        workspace[ix - 1] += c;
        ar += 43;
      }

      ar = -1;
      i = nVar + 43;
      for (ix = 44; ix <= i; ix++) {
        c = 0.0;
        for (mFixed = 0; mFixed <= mWConstr_tmp; mFixed++) {
          iy = mFixed + 1;
          c += qrmanager->Q[iy + ar] * B[iy + 42];
        }

        workspace[ix - 1] += c;
        ar += 43;
      }

      for (ix = nVar; ix >= 1; ix--) {
        iy = 43 * (ix - 1) - 1;
        i = ix + -1;
        if (workspace[i] != 0.0) {
          workspace[i] /= qrmanager->QR[ix + iy];
          for (mFixed = 0; mFixed <= ix - 2; mFixed++) {
            workspace[mFixed] -= workspace[i] * qrmanager->QR[(mFixed + iy) + 1];
          }
        }
      }

      for (ix = nVar; ix >= 1; ix--) {
        iy = 43 * (ix - 1) - 1;
        i = ix + 42;
        if (workspace[i] != 0.0) {
          workspace[i] /= qrmanager->QR[ix + iy];
          for (mFixed = 0; mFixed <= ix - 2; mFixed++) {
            i1 = mFixed + 43;
            workspace[i1] -= workspace[i] * qrmanager->QR[(mFixed + iy) + 1];
          }
        }
      }
    } else {
      factorQR(qrmanager, workingset->ATwset, workingset->nVar,
               workingset->nActiveConstr);
      i = qrmanager->minRowCol;
      for (ix = 0; ix < i; ix++) {
        iy = 43 * ix + ix;
        ar = qrmanager->mrows - ix;
        if (0 <= ar - 2) {
          std::memcpy(&qrmanager->Q[iy + 1], &qrmanager->QR[iy + 1], (ar + -1) *
                      sizeof(double));
        }
      }

      xorgqr(qrmanager->mrows, qrmanager->minRowCol, qrmanager->minRowCol,
             qrmanager->Q, qrmanager->tau);
      for (mFixed = 0; mFixed <= mWConstr_tmp; mFixed++) {
        iy = 43 * mFixed;
        c = workspace[mFixed];
        for (ix = 0; ix < mFixed; ix++) {
          c -= qrmanager->QR[ix + iy] * workspace[ix];
        }

        workspace[mFixed] = c / qrmanager->QR[mFixed + iy];
      }

      for (mFixed = 0; mFixed <= mWConstr_tmp; mFixed++) {
        iy = 43 * mFixed;
        ar = mFixed + 43;
        c = workspace[ar];
        for (ix = 0; ix < mFixed; ix++) {
          c -= qrmanager->QR[ix + iy] * workspace[ix + 43];
        }

        workspace[ar] = c / qrmanager->QR[mFixed + iy];
      }

      std::memcpy(&B[0], &workspace[0], 903U * sizeof(double));
      if (1 <= nVar) {
        std::memset(&workspace[0], 0, nVar * sizeof(double));
      }

      i = nVar + 43;
      if (44 <= i) {
        std::memset(&workspace[43], 0, (i + -43) * sizeof(double));
      }

      ar = -1;
      i = mWConstr_tmp + 1;
      for (iy = 1; iy <= i; iy++) {
        ia = ar;
        for (ix = 1; ix <= nVar; ix++) {
          ia++;
          workspace[ix - 1] += B[iy - 1] * qrmanager->Q[ia];
        }

        ar += 43;
      }

      ar = -1;
      i = mWConstr_tmp + 44;
      for (iy = 44; iy <= i; iy++) {
        ia = ar;
        i1 = nVar + 43;
        for (ix = 44; ix <= i1; ix++) {
          ia++;
          workspace[ix - 1] += B[iy - 1] * qrmanager->Q[ia];
        }

        ar += 43;
      }
    }

    ix = 0;
    int exitg1;
    do {
      exitg1 = 0;
      if (ix <= nVar - 1) {
        if (rtIsInf(workspace[ix]) || rtIsNaN(workspace[ix])) {
          nonDegenerateWset = false;
          exitg1 = 1;
        } else {
          c = workspace[ix + 43];
          if (rtIsInf(c) || rtIsNaN(c)) {
            nonDegenerateWset = false;
            exitg1 = 1;
          } else {
            ix++;
          }
        }
      } else {
        double v;
        double b_v;
        iy = nVar - 1;
        for (ix = 0; ix <= iy; ix++) {
          workspace[ix] += xCurrent[ix];
        }

        ar = workingset->sizes[3];
        iy = workingset->sizes[4];
        mFixed = workingset->sizes[0];
        switch (workingset->probType) {
         case 2:
          v = 0.0;
          workingset->maxConstrWorkspace[0] = workingset->bineq[0];
          workingset->maxConstrWorkspace[0] = -workingset->maxConstrWorkspace[0];
          workingset->maxConstrWorkspace[1] = workingset->bineq[1];
          workingset->maxConstrWorkspace[1] = -workingset->maxConstrWorkspace[1];
          ix = 0;
          c = 0.0;
          for (ia = 1; ia < 21; ia++) {
            c += workingset->Aineq[ia - 1] * workspace[ix];
            ix++;
          }

          workingset->maxConstrWorkspace[0] += c;
          ix = 0;
          c = 0.0;
          for (ia = 22; ia < 42; ia++) {
            c += workingset->Aineq[ia - 1] * workspace[ix];
            ix++;
          }

          workingset->maxConstrWorkspace[1] += c;
          workingset->maxConstrWorkspace[0] -= workspace[20];
          if ((!(0.0 > workingset->maxConstrWorkspace[0])) && (!rtIsNaN
               (workingset->maxConstrWorkspace[0]))) {
            v = workingset->maxConstrWorkspace[0];
          }

          workingset->maxConstrWorkspace[1] -= workspace[21];
          if ((!(v > workingset->maxConstrWorkspace[1])) && (!rtIsNaN
               (workingset->maxConstrWorkspace[1]))) {
            v = workingset->maxConstrWorkspace[1];
          }
          break;

         default:
          v = 0.0;
          workingset->maxConstrWorkspace[0] = workingset->bineq[0];
          workingset->maxConstrWorkspace[0] = -workingset->maxConstrWorkspace[0];
          workingset->maxConstrWorkspace[1] = workingset->bineq[1];
          workingset->maxConstrWorkspace[1] = -workingset->maxConstrWorkspace[1];
          ix = 0;
          c = 0.0;
          i = workingset->nVar;
          for (ia = 1; ia <= i; ia++) {
            c += workingset->Aineq[ia - 1] * workspace[ix];
            ix++;
          }

          workingset->maxConstrWorkspace[0] += c;
          ix = 0;
          c = 0.0;
          i = workingset->nVar + 21;
          for (ia = 22; ia <= i; ia++) {
            c += workingset->Aineq[ia - 1] * workspace[ix];
            ix++;
          }

          workingset->maxConstrWorkspace[1] += c;
          if ((!(0.0 > workingset->maxConstrWorkspace[0])) && (!rtIsNaN
               (workingset->maxConstrWorkspace[0]))) {
            v = workingset->maxConstrWorkspace[0];
          }

          if ((!(v > workingset->maxConstrWorkspace[1])) && (!rtIsNaN
               (workingset->maxConstrWorkspace[1]))) {
            v = workingset->maxConstrWorkspace[1];
          }
          break;
        }

        if (workingset->sizes[3] > 0) {
          for (ix = 0; ix < ar; ix++) {
            c = -workspace[workingset->indexLB[ix] - 1] - workingset->
              lb[workingset->indexLB[ix] - 1];
            if ((!(v > c)) && (!rtIsNaN(c))) {
              v = c;
            }
          }
        }

        if (workingset->sizes[4] > 0) {
          for (ix = 0; ix < iy; ix++) {
            c = workspace[workingset->indexUB[ix] - 1] - workingset->
              ub[workingset->indexUB[ix] - 1];
            if ((!(v > c)) && (!rtIsNaN(c))) {
              v = c;
            }
          }
        }

        if (workingset->sizes[0] > 0) {
          for (ix = 0; ix < mFixed; ix++) {
            iy = workingset->indexFixed[ix] - 1;
            c = std::abs(workspace[iy] - workingset->ub[iy]);
            if ((!(v > c)) && (!rtIsNaN(c))) {
              v = c;
            }
          }
        }

        ar = workingset->sizes[3];
        iy = workingset->sizes[4];
        mFixed = workingset->sizes[0];
        switch (workingset->probType) {
         case 2:
          b_v = 0.0;
          workingset->maxConstrWorkspace[0] = workingset->bineq[0];
          workingset->maxConstrWorkspace[0] = -workingset->maxConstrWorkspace[0];
          workingset->maxConstrWorkspace[1] = workingset->bineq[1];
          workingset->maxConstrWorkspace[1] = -workingset->maxConstrWorkspace[1];
          ix = 43;
          c = 0.0;
          for (ia = 1; ia < 21; ia++) {
            c += workingset->Aineq[ia - 1] * workspace[ix];
            ix++;
          }

          workingset->maxConstrWorkspace[0] += c;
          ix = 43;
          c = 0.0;
          for (ia = 22; ia < 42; ia++) {
            c += workingset->Aineq[ia - 1] * workspace[ix];
            ix++;
          }

          workingset->maxConstrWorkspace[1] += c;
          workingset->maxConstrWorkspace[0] -= workspace[63];
          if ((!(0.0 > workingset->maxConstrWorkspace[0])) && (!rtIsNaN
               (workingset->maxConstrWorkspace[0]))) {
            b_v = workingset->maxConstrWorkspace[0];
          }

          workingset->maxConstrWorkspace[1] -= workspace[64];
          if ((!(b_v > workingset->maxConstrWorkspace[1])) && (!rtIsNaN
               (workingset->maxConstrWorkspace[1]))) {
            b_v = workingset->maxConstrWorkspace[1];
          }
          break;

         default:
          b_v = 0.0;
          workingset->maxConstrWorkspace[0] = workingset->bineq[0];
          workingset->maxConstrWorkspace[0] = -workingset->maxConstrWorkspace[0];
          workingset->maxConstrWorkspace[1] = workingset->bineq[1];
          workingset->maxConstrWorkspace[1] = -workingset->maxConstrWorkspace[1];
          ix = 43;
          c = 0.0;
          i = workingset->nVar;
          for (ia = 1; ia <= i; ia++) {
            c += workingset->Aineq[ia - 1] * workspace[ix];
            ix++;
          }

          workingset->maxConstrWorkspace[0] += c;
          ix = 43;
          c = 0.0;
          i = workingset->nVar + 21;
          for (ia = 22; ia <= i; ia++) {
            c += workingset->Aineq[ia - 1] * workspace[ix];
            ix++;
          }

          workingset->maxConstrWorkspace[1] += c;
          if ((!(0.0 > workingset->maxConstrWorkspace[0])) && (!rtIsNaN
               (workingset->maxConstrWorkspace[0]))) {
            b_v = workingset->maxConstrWorkspace[0];
          }

          if ((!(b_v > workingset->maxConstrWorkspace[1])) && (!rtIsNaN
               (workingset->maxConstrWorkspace[1]))) {
            b_v = workingset->maxConstrWorkspace[1];
          }
          break;
        }

        if (workingset->sizes[3] > 0) {
          for (ix = 0; ix < ar; ix++) {
            c = -workspace[workingset->indexLB[ix] + 42] - workingset->
              lb[workingset->indexLB[ix] - 1];
            if ((!(b_v > c)) && (!rtIsNaN(c))) {
              b_v = c;
            }
          }
        }

        if (workingset->sizes[4] > 0) {
          for (ix = 0; ix < iy; ix++) {
            c = workspace[workingset->indexUB[ix] + 42] - workingset->
              ub[workingset->indexUB[ix] - 1];
            if ((!(b_v > c)) && (!rtIsNaN(c))) {
              b_v = c;
            }
          }
        }

        if (workingset->sizes[0] > 0) {
          for (ix = 0; ix < mFixed; ix++) {
            iy = workingset->indexFixed[ix];
            c = std::abs(workspace[iy + 42] - workingset->ub[iy - 1]);
            if ((!(b_v > c)) && (!rtIsNaN(c))) {
              b_v = c;
            }
          }
        }

        if ((v <= 2.2204460492503131E-16) || (v < b_v)) {
          if (0 <= nVar - 1) {
            std::memcpy(&xCurrent[0], &workspace[0], nVar * sizeof(double));
          }
        } else {
          if (0 <= nVar - 1) {
            std::memcpy(&xCurrent[0], &workspace[43], nVar * sizeof(double));
          }
        }

        exitg1 = 1;
      }
    } while (exitg1 == 0);
  }

  return nonDegenerateWset;
}

//
// File trailer for feasibleX0ForWorkingSet.cpp
//
// [EOF]
//
