//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: RemoveDependentEq_.cpp
//
// MATLAB Coder version            : 5.0
// C/C++ source code generated on  : 09-Oct-2020 15:23:44
//

// Include Files
#include "stdafx.h"
#include "RemoveDependentEq_.h"
#include "GetFphi.h"
#include "Getintput_u.h"
#include "countsort.h"
#include "factorQRE.h"
#include "removeEqConstr.h"
#include "rt_nonfinite.h"
#include "xgeqp3.h"
#include "xorgqr.h"
#include <cmath>
#include <cstring>

// Function Definitions

//
// Arguments    : c_struct_T *memspace
//                e_struct_T *workingset
//                int *nDepInd
//                f_struct_T *qrmanager
// Return Type  : void
//
void RemoveDependentEq_(c_struct_T *memspace, e_struct_T *workingset, int
  *nDepInd, f_struct_T *qrmanager)
{
  int nVar;
  int mWorkingFixed;
  double qtb;
  qrmanager->ldq = 43;
  std::memset(&qrmanager->QR[0], 0, 1849U * sizeof(double));
  std::memset(&qrmanager->Q[0], 0, 1849U * sizeof(double));
  qrmanager->mrows = 0;
  qrmanager->ncols = 0;
  std::memset(&qrmanager->jpvt[0], 0, 43U * sizeof(int));
  std::memset(&qrmanager->tau[0], 0, 43U * sizeof(double));
  qrmanager->minRowCol = 0;
  qrmanager->usedPivoting = false;
  nVar = workingset->nVar - 1;
  mWorkingFixed = workingset->nWConstr[0] - 1;
  *nDepInd = 0;
  if (workingset->nWConstr[0] > 0) {
    int iQR0;
    int iy;
    double tol;
    int idx;
    for (iQR0 = 0; iQR0 <= mWorkingFixed; iQR0++) {
      for (iy = 0; iy <= nVar; iy++) {
        qrmanager->QR[iQR0 + 43 * iy] = workingset->ATwset[iy + 21 * iQR0];
      }
    }

    *nDepInd = 0;
    if (0 <= nVar) {
      std::memset(&qrmanager->jpvt[0], 0, (nVar + 1) * sizeof(int));
    }

    qrmanager->usedPivoting = true;
    qrmanager->mrows = workingset->nWConstr[0];
    qrmanager->ncols = workingset->nVar;
    nVar = workingset->nWConstr[0];
    iQR0 = workingset->nVar;
    if (nVar < iQR0) {
      iQR0 = nVar;
    }

    qrmanager->minRowCol = iQR0;
    xgeqp3(qrmanager->QR, workingset->nWConstr[0], workingset->nVar,
           qrmanager->jpvt, qrmanager->tau);
    tol = 100.0 * static_cast<double>(workingset->nVar) * 2.2204460492503131E-16;
    nVar = workingset->nVar;
    iQR0 = workingset->nWConstr[0];
    if (nVar < iQR0) {
      iQR0 = nVar;
    }

    while ((iQR0 > 0) && (std::abs(qrmanager->QR[(iQR0 + 43 * (iQR0 - 1)) - 1]) <
                          tol)) {
      iQR0--;
      (*nDepInd)++;
    }

    if (*nDepInd > 0) {
      bool exitg1;
      nVar = qrmanager->minRowCol;
      for (idx = 0; idx < nVar; idx++) {
        iQR0 = 43 * idx + idx;
        iy = workingset->nWConstr[0] - idx;
        if (0 <= iy - 2) {
          std::memcpy(&qrmanager->Q[iQR0 + 1], &qrmanager->QR[iQR0 + 1], (iy +
            -1) * sizeof(double));
        }
      }

      xorgqr(workingset->nWConstr[0], workingset->nWConstr[0],
             qrmanager->minRowCol, qrmanager->Q, qrmanager->tau);
      idx = 0;
      exitg1 = false;
      while ((!exitg1) && (idx <= *nDepInd - 1)) {
        nVar = 43 * (mWorkingFixed - idx);
        qtb = 0.0;
        iy = 0;
        for (iQR0 = 0; iQR0 <= mWorkingFixed; iQR0++) {
          qtb += qrmanager->Q[nVar] * workingset->bwset[iy];
          nVar++;
          iy++;
        }

        if (std::abs(qtb) >= tol) {
          *nDepInd = -1;
          exitg1 = true;
        } else {
          idx++;
        }
      }
    }

    if (*nDepInd > 0) {
      for (idx = 0; idx <= mWorkingFixed; idx++) {
        qrmanager->jpvt[idx] = 1;
      }

      nVar = workingset->nWConstr[0] + 1;
      if (nVar <= mWorkingFixed + 1) {
        std::memset(&qrmanager->jpvt[nVar + -1], 0, ((mWorkingFixed - nVar) + 2)
                    * sizeof(int));
      }

      factorQRE(qrmanager, workingset->ATwset, workingset->nVar,
                workingset->nWConstr[0]);
      for (idx = 0; idx < *nDepInd; idx++) {
        memspace->workspace_int[idx] = qrmanager->jpvt[((mWorkingFixed -
          *nDepInd) + idx) + 1];
      }

      countsort(memspace->workspace_int, *nDepInd, memspace->workspace_sort, 1,
                workingset->nWConstr[0]);
      for (idx = *nDepInd; idx >= 1; idx--) {
        removeEqConstr(workingset, memspace->workspace_int[idx - 1]);
      }
    }
  }
}

//
// File trailer for RemoveDependentEq_.cpp
//
// [EOF]
//
