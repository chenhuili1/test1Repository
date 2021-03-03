//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: quadprog.cpp
//
// MATLAB Coder version            : 5.0
// C/C++ source code generated on  : 09-Oct-2020 15:23:44
//

// Include Files
#include "stdafx.h"
#include "quadprog.h"
#include "GetFphi.h"
#include "Getintput_u.h"
#include "driver.h"
#include "factoryConstruct.h"
#include "rt_nonfinite.h"
#include "setProblemType.h"
#include <cmath>
#include <cstring>

// Function Definitions

//
// Arguments    : const double H[400]
//                const double f[20]
//                const double bineq[2]
//                const double lb[20]
//                const double ub[20]
//                double x[20]
// Return Type  : void
//
void quadprog(const double H[400], const double f[20], const double bineq[2],
              const double lb[20], const double ub[20], double x[20])
{
  struct_T solution;
  d_struct_T CholRegManager;
  int mLB;
  int mUB;
  int mFixed;
  int idxFillStart;
  int indexLB[20];
  int indexUB[20];
  int indexFixed[20];
  e_struct_T WorkingSet;
  int idx;
  double tol;
  double b_tol;
  double colSum;
  double H_infnrm;
  double f_infnrm;
  b_struct_T expl_temp;
  c_struct_T memspace;
  f_struct_T QRManager;
  g_struct_T QPObjective;
  solution.fstar = 0.0;
  solution.firstorderopt = 0.0;
  std::memset(&solution.lambda[0], 0, 43U * sizeof(double));
  solution.state = 0;
  solution.maxConstr = 0.0;
  solution.iterations = 0;
  std::memset(&solution.searchDir[0], 0, 21U * sizeof(double));
  CholRegManager.ldm = 43;
  CholRegManager.ndims = 0;
  CholRegManager.info = 0;
  CholRegManager.ConvexCheck = true;
  CholRegManager.scaleFactor = 100.0;
  mLB = 0;
  mUB = 0;
  mFixed = 0;
  for (idxFillStart = 0; idxFillStart < 20; idxFillStart++) {
    bool guard1 = false;
    solution.xstar[idxFillStart] = 0.0;
    guard1 = false;
    if ((!rtIsInf(lb[idxFillStart])) && (!rtIsNaN(lb[idxFillStart]))) {
      if (std::abs(lb[idxFillStart] - ub[idxFillStart]) < 1.0E-8) {
        mFixed++;
        indexFixed[mFixed - 1] = idxFillStart + 1;
      } else {
        mLB++;
        indexLB[mLB - 1] = idxFillStart + 1;
        guard1 = true;
      }
    } else {
      guard1 = true;
    }

    if (guard1 && ((!rtIsInf(ub[idxFillStart])) && (!rtIsNaN(ub[idxFillStart]))))
    {
      mUB++;
      indexUB[mUB - 1] = idxFillStart + 1;
    }
  }

  factoryConstruct(bineq, mLB, lb, indexLB, mUB, ub, indexUB, mFixed, indexFixed,
                   &WorkingSet);
  setProblemType(&WorkingSet, 3);
  idxFillStart = WorkingSet.isActiveIdx[2];
  for (idx = idxFillStart; idx < 44; idx++) {
    WorkingSet.isActiveConstr[idx - 1] = false;
  }

  WorkingSet.nWConstr[0] = WorkingSet.sizes[0];
  WorkingSet.nWConstr[1] = 0;
  WorkingSet.nWConstr[2] = 0;
  WorkingSet.nWConstr[3] = 0;
  WorkingSet.nWConstr[4] = 0;
  WorkingSet.nActiveConstr = WorkingSet.nWConstr[0];
  idxFillStart = WorkingSet.sizes[0];
  for (idx = 0; idx < idxFillStart; idx++) {
    int i;
    int i1;
    WorkingSet.Wid[idx] = 1;
    WorkingSet.Wlocalidx[idx] = idx + 1;
    WorkingSet.isActiveConstr[idx] = true;
    i = WorkingSet.indexFixed[idx];
    if (0 <= i - 2) {
      std::memset(&WorkingSet.ATwset[idx * 21], 0, (i + -1) * sizeof(double));
    }

    WorkingSet.ATwset[(WorkingSet.indexFixed[idx] + 21 * idx) - 1] = 1.0;
    i = WorkingSet.indexFixed[idx] + 1;
    i1 = WorkingSet.nVar;
    if (i <= i1) {
      std::memset(&WorkingSet.ATwset[(idx * 21 + i) + -1], 0, ((i1 - i) + 1) *
                  sizeof(double));
    }

    WorkingSet.bwset[idx] = WorkingSet.ub[WorkingSet.indexFixed[idx] - 1];
  }

  WorkingSet.SLACK0 = 0.0;
  tol = 1.0;
  for (idxFillStart = 0; idxFillStart < 2; idxFillStart++) {
    colSum = 0.0;
    for (idx = 0; idx < 20; idx++) {
      colSum += std::abs(WorkingSet.Aineq[idx + 21 * idxFillStart]);
    }

    if ((!(tol > colSum)) && (!rtIsNaN(colSum))) {
      tol = colSum;
    }
  }

  b_tol = tol;
  H_infnrm = 0.0;
  f_infnrm = 0.0;
  for (idxFillStart = 0; idxFillStart < 20; idxFillStart++) {
    colSum = 0.0;
    for (idx = 0; idx < 20; idx++) {
      colSum += std::abs(H[idx + 20 * idxFillStart]);
    }

    if ((!(H_infnrm > colSum)) && (!rtIsNaN(colSum))) {
      H_infnrm = colSum;
    }

    colSum = std::abs(f[idxFillStart]);
    if ((!(f_infnrm > colSum)) && (!rtIsNaN(colSum))) {
      f_infnrm = colSum;
    }
  }

  if ((!(tol > f_infnrm)) && (!rtIsNaN(f_infnrm))) {
    b_tol = f_infnrm;
  }

  if ((!(b_tol > H_infnrm)) && (!rtIsNaN(H_infnrm))) {
    b_tol = H_infnrm;
  }

  if ((1.0 > b_tol) || rtIsNaN(b_tol)) {
    b_tol = 1.0;
  }

  expl_temp.RemainFeasible = false;
  expl_temp.ProbRelTolFactor = b_tol;
  expl_temp.ConstrRelTolFactor = tol;
  expl_temp.MaxIterations = 10 * (((mFixed + mLB) + mUB) + 22);
  driver(H, f, &solution, &memspace, &WorkingSet, &CholRegManager, expl_temp,
         &QRManager, &QPObjective);
  std::memcpy(&x[0], &solution.xstar[0], 20U * sizeof(double));
}

//
// File trailer for quadprog.cpp
//
// [EOF]
//
