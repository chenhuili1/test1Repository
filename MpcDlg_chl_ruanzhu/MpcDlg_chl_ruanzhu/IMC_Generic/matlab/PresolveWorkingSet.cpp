//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: PresolveWorkingSet.cpp
//
// MATLAB Coder version            : 5.0
// C/C++ source code generated on  : 09-Oct-2020 15:23:44
//

// Include Files
#include "stdafx.h"
#include "PresolveWorkingSet.h"
#include "GetFphi.h"
#include "Getintput_u.h"
#include "RemoveDependentEq_.h"
#include "RemoveDependentIneq_.h"
#include "countsort.h"
#include "factorQRE.h"
#include "feasibleX0ForWorkingSet.h"
#include "maxConstraintViolation.h"
#include "removeEqConstr.h"
#include "rtGetInf.h"
#include "rt_nonfinite.h"
#include "xgeqp3.h"
#include "xorgqr.h"
#include <cmath>
#include <cstring>

// Function Definitions

//
// Arguments    : struct_T *solution
//                c_struct_T *memspace
//                e_struct_T *workingset
//                f_struct_T *qrmanager
//                h_struct_T *options
// Return Type  : void
//
void PresolveWorkingSet(struct_T *solution, c_struct_T *memspace, e_struct_T
  *workingset, f_struct_T *qrmanager, h_struct_T *options)
{
  static h_struct_T r = { { 'f', 'o', 'r', 'w', 'a', 'r', 'd' },// FiniteDifferenceType 
    false,                             // ScaleProblem
    false,                             // SpecifyConstraintGradient
    false,                             // SpecifyObjectiveGradient
    true,                              // NonFiniteSupport
    false,                             // IterDisplaySQP
    -1.0,                              // FiniteDifferenceStepSize
    -1.0,                              // MaxFunctionEvaluations
    false,                             // IterDisplayQP
    0.0,                               // PricingTolerance
    { 'a', 'c', 't', 'i', 'v', 'e', '-', 's', 'e', 't' },// Algorithm
    -1.0E+20,                          // ObjectiveLimit
    1.0E-8,                            // ConstraintTolerance
    1.0E-8,                            // OptimalityTolerance
    1.0E-8,                            // StepTolerance
    -1.0,                              // MaxIterations
    { 'q', 'u', 'a', 'd', 'p', 'r', 'o', 'g' },// SolverName
    false,                             // CheckGradients
    { 'o', 'f', 'f' },                 // Diagnostics
    0.0,                               // DiffMaxChange
    0.0,                               // DiffMinChange
    { 'f', 'i', 'n', 'a', 'l' },       // Display
    { 'o', 'f', 'f' },                 // FunValCheck
    false,                             // UseParallel
    1.4901161193847656E-8,             // FunctionTolerance
    { 'a', 'u', 't', 'o' },            // LinearSolver
    { 'c', 'g' }                       // SubproblemAlgorithm
  };

  e_struct_T b_workingset;
  int idxStartIneq_tmp;
  r.DiffMaxChange = rtGetInf();
  *options = r;
  solution->state = 82;
  b_workingset = *workingset;
  RemoveDependentEq_(memspace, &b_workingset, &idxStartIneq_tmp, qrmanager);
  if (idxStartIneq_tmp != -1) {
    bool okWorkingSet;
    bool guard1 = false;
    RemoveDependentIneq_(&b_workingset, qrmanager, memspace, 100.0);
    *workingset = b_workingset;
    okWorkingSet = feasibleX0ForWorkingSet(memspace->workspace_double,
      solution->xstar, workingset, qrmanager);
    guard1 = false;
    if (!okWorkingSet) {
      RemoveDependentIneq_(workingset, qrmanager, memspace, 1000.0);
      okWorkingSet = feasibleX0ForWorkingSet(memspace->workspace_double,
        solution->xstar, workingset, qrmanager);
      if (!okWorkingSet) {
        solution->state = -7;
      } else {
        guard1 = true;
      }
    } else {
      guard1 = true;
    }

    if (guard1 && (workingset->nWConstr[0] + workingset->nWConstr[1] ==
                   workingset->nVar)) {
      double constrViolation;
      constrViolation = maxConstraintViolation(workingset, solution->xstar);
      if (constrViolation > 1.0E-8) {
        solution->state = -2;
      }
    }
  } else {
    int idxStartIneq;
    int idxEndIneq;
    solution->state = -3;
    *workingset = b_workingset;
    idxStartIneq_tmp = b_workingset.nWConstr[0] + b_workingset.nWConstr[1];
    idxStartIneq = idxStartIneq_tmp + 1;
    idxEndIneq = b_workingset.nActiveConstr;
    for (int idx_global = idxStartIneq; idx_global <= idxEndIneq; idx_global++)
    {
      workingset->isActiveConstr
        [(b_workingset.isActiveIdx[b_workingset.Wid[idx_global - 1] - 1] +
          b_workingset.Wlocalidx[idx_global - 1]) - 2] = false;
    }

    workingset->nWConstr[2] = 0;
    workingset->nWConstr[3] = 0;
    workingset->nWConstr[4] = 0;
    workingset->nActiveConstr = idxStartIneq_tmp;
  }
}

//
// Arguments    : struct_T *solution
//                c_struct_T *memspace
//                e_struct_T *workingset
//                f_struct_T *qrmanager
// Return Type  : void
//
void b_PresolveWorkingSet(struct_T *solution, c_struct_T *memspace, e_struct_T
  *workingset, f_struct_T *qrmanager)
{
  e_struct_T b_workingset;
  int nVar;
  int mWorkingFixed;
  int mTotalWorkingEq_tmp_tmp;
  int nDepInd;
  int iQR0;
  int ix;
  double tol;
  double qtb;
  solution->state = 82;
  b_workingset = *workingset;
  nVar = workingset->nVar - 1;
  mWorkingFixed = workingset->nWConstr[0];
  mTotalWorkingEq_tmp_tmp = workingset->nWConstr[1] + workingset->nWConstr[0];
  nDepInd = 0;
  if (mTotalWorkingEq_tmp_tmp > 0) {
    int idx;
    for (iQR0 = 0; iQR0 < mTotalWorkingEq_tmp_tmp; iQR0++) {
      for (ix = 0; ix <= nVar; ix++) {
        qrmanager->QR[iQR0 + 43 * ix] = workingset->ATwset[ix + 21 * iQR0];
      }
    }

    nDepInd = mTotalWorkingEq_tmp_tmp - workingset->nVar;
    if (0 > nDepInd) {
      nDepInd = 0;
    }

    if (0 <= nVar) {
      std::memset(&qrmanager->jpvt[0], 0, (nVar + 1) * sizeof(int));
    }

    qrmanager->usedPivoting = true;
    qrmanager->mrows = mTotalWorkingEq_tmp_tmp;
    qrmanager->ncols = workingset->nVar;
    nVar = workingset->nVar;
    if (mTotalWorkingEq_tmp_tmp < nVar) {
      nVar = mTotalWorkingEq_tmp_tmp;
    }

    qrmanager->minRowCol = nVar;
    xgeqp3(qrmanager->QR, mTotalWorkingEq_tmp_tmp, workingset->nVar,
           qrmanager->jpvt, qrmanager->tau);
    tol = 100.0 * static_cast<double>(workingset->nVar) * 2.2204460492503131E-16;
    nVar = workingset->nVar;
    if (nVar >= mTotalWorkingEq_tmp_tmp) {
      nVar = mTotalWorkingEq_tmp_tmp;
    }

    while ((nVar > 0) && (std::abs(qrmanager->QR[(nVar + 43 * (nVar - 1)) - 1]) <
                          tol)) {
      nVar--;
      nDepInd++;
    }

    if (nDepInd > 0) {
      bool exitg1;
      ix = qrmanager->minRowCol;
      for (idx = 0; idx < ix; idx++) {
        iQR0 = 43 * idx + idx;
        nVar = mTotalWorkingEq_tmp_tmp - idx;
        if (0 <= nVar - 2) {
          std::memcpy(&qrmanager->Q[iQR0 + 1], &qrmanager->QR[iQR0 + 1], (nVar +
            -1) * sizeof(double));
        }
      }

      xorgqr(mTotalWorkingEq_tmp_tmp, mTotalWorkingEq_tmp_tmp,
             qrmanager->minRowCol, qrmanager->Q, qrmanager->tau);
      idx = 0;
      exitg1 = false;
      while ((!exitg1) && (idx <= nDepInd - 1)) {
        ix = 43 * ((mTotalWorkingEq_tmp_tmp - idx) - 1);
        qtb = 0.0;
        nVar = 0;
        for (iQR0 = 0; iQR0 < mTotalWorkingEq_tmp_tmp; iQR0++) {
          qtb += qrmanager->Q[ix] * workingset->bwset[nVar];
          ix++;
          nVar++;
        }

        if (std::abs(qtb) >= tol) {
          nDepInd = -1;
          exitg1 = true;
        } else {
          idx++;
        }
      }
    }

    if (nDepInd > 0) {
      for (idx = 0; idx < mWorkingFixed; idx++) {
        qrmanager->jpvt[idx] = 1;
      }

      ix = workingset->nWConstr[0] + 1;
      if (ix <= mTotalWorkingEq_tmp_tmp) {
        std::memset(&qrmanager->jpvt[ix + -1], 0, ((mTotalWorkingEq_tmp_tmp - ix)
          + 1) * sizeof(int));
      }

      factorQRE(qrmanager, workingset->ATwset, workingset->nVar,
                mTotalWorkingEq_tmp_tmp);
      for (idx = 0; idx < nDepInd; idx++) {
        memspace->workspace_int[idx] = qrmanager->jpvt[(mTotalWorkingEq_tmp_tmp
          - nDepInd) + idx];
      }

      countsort(memspace->workspace_int, nDepInd, memspace->workspace_sort, 1,
                mTotalWorkingEq_tmp_tmp);
      for (idx = nDepInd; idx >= 1; idx--) {
        removeEqConstr(&b_workingset, memspace->workspace_int[idx - 1]);
      }
    }
  }

  if (nDepInd != -1) {
    bool okWorkingSet;
    bool guard1 = false;
    RemoveDependentIneq_(&b_workingset, qrmanager, memspace, 100.0);
    *workingset = b_workingset;
    okWorkingSet = feasibleX0ForWorkingSet(memspace->workspace_double,
      solution->xstar, workingset, qrmanager);
    guard1 = false;
    if (!okWorkingSet) {
      RemoveDependentIneq_(workingset, qrmanager, memspace, 1000.0);
      okWorkingSet = feasibleX0ForWorkingSet(memspace->workspace_double,
        solution->xstar, workingset, qrmanager);
      if (!okWorkingSet) {
        solution->state = -7;
      } else {
        guard1 = true;
      }
    } else {
      guard1 = true;
    }

    if (guard1 && (workingset->nWConstr[0] + workingset->nWConstr[1] ==
                   workingset->nVar)) {
      tol = maxConstraintViolation(workingset, solution->xstar);
      if (tol > 1.0E-8) {
        solution->state = -2;
      }
    }
  } else {
    solution->state = -3;
    *workingset = b_workingset;
    nVar = b_workingset.nWConstr[0] + b_workingset.nWConstr[1];
    ix = nVar + 1;
    iQR0 = b_workingset.nActiveConstr;
    for (nDepInd = ix; nDepInd <= iQR0; nDepInd++) {
      workingset->isActiveConstr
        [(b_workingset.isActiveIdx[b_workingset.Wid[nDepInd - 1] - 1] +
          b_workingset.Wlocalidx[nDepInd - 1]) - 2] = false;
    }

    workingset->nWConstr[2] = 0;
    workingset->nWConstr[3] = 0;
    workingset->nWConstr[4] = 0;
    workingset->nActiveConstr = nVar;
  }
}

//
// File trailer for PresolveWorkingSet.cpp
//
// [EOF]
//
