//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: phaseone.cpp
//
// MATLAB Coder version            : 5.0
// C/C++ source code generated on  : 09-Oct-2020 15:23:44
//

// Include Files
#include "stdafx.h"
#include "phaseone.h"
#include "GetFphi.h"
#include "Getintput_u.h"
#include "computeFval.h"
#include "iterate.h"
#include "rt_nonfinite.h"
#include "setProblemType.h"
#include <cstring>

// Function Definitions

//
// Arguments    : const double H[400]
//                const double f[20]
//                struct_T *solution
//                c_struct_T *memspace
//                e_struct_T *workingset
//                f_struct_T *qrmanager
//                d_struct_T *cholmanager
//                g_struct_T *objective
//                h_struct_T *options
//                const b_struct_T *runTimeOptions
// Return Type  : void
//
void b_phaseone(const double H[400], const double f[20], struct_T *solution,
                c_struct_T *memspace, e_struct_T *workingset, f_struct_T
                *qrmanager, d_struct_T *cholmanager, g_struct_T *objective,
                h_struct_T *options, const b_struct_T *runTimeOptions)
{
  int PROBTYPE_ORIG;
  int nVar;
  int PHASEONE;
  int idxStartIneq;
  int idxEndIneq;
  int idx_global;
  PROBTYPE_ORIG = workingset->probType;
  nVar = workingset->nVar;
  solution->xstar[20] = solution->maxConstr + 1.0;
  if (workingset->probType == 3) {
    PHASEONE = 1;
  } else {
    PHASEONE = 4;
  }

  idxStartIneq = (workingset->nWConstr[0] + workingset->nWConstr[1]) + 1;
  idxEndIneq = workingset->nActiveConstr;
  for (idx_global = idxStartIneq; idx_global <= idxEndIneq; idx_global++) {
    workingset->isActiveConstr[(workingset->isActiveIdx[workingset->
      Wid[idx_global - 1] - 1] + workingset->Wlocalidx[idx_global - 1]) - 2] =
      false;
  }

  workingset->nWConstr[2] = 0;
  workingset->nWConstr[3] = 0;
  workingset->nWConstr[4] = 0;
  workingset->nActiveConstr = workingset->nWConstr[0] + workingset->nWConstr[1];
  setProblemType(workingset, PHASEONE);
  objective->prev_objtype = objective->objtype;
  objective->prev_nvar = objective->nvar;
  objective->prev_hasLinear = objective->hasLinear;
  objective->objtype = 5;
  objective->nvar = 21;
  objective->gammaScalar = 1.0;
  objective->hasLinear = true;
  options->ObjectiveLimit = 1.0E-8 * runTimeOptions->ConstrRelTolFactor;
  options->StepTolerance = 1.4901161193847657E-10;
  solution->fstar = computeFval(objective, memspace->workspace_double, H, f,
    solution->xstar);
  solution->state = 5;
  iterate(H, f, solution, memspace, workingset, qrmanager, cholmanager,
          objective, options->ObjectiveLimit, options->StepTolerance,
          runTimeOptions->MaxIterations, runTimeOptions->ConstrRelTolFactor,
          runTimeOptions->ProbRelTolFactor, runTimeOptions->RemainFeasible);
  if (workingset->isActiveConstr[(workingset->isActiveIdx[3] + workingset->
       sizes[3]) - 2]) {
    bool exitg1;
    idx_global = workingset->sizes[0];
    exitg1 = false;
    while ((!exitg1) && (idx_global + 1 <= workingset->nActiveConstr)) {
      if ((workingset->Wid[idx_global] == 4) && (workingset->
           Wlocalidx[idx_global] == workingset->sizes[3])) {
        idxStartIneq = workingset->Wid[idx_global] - 1;
        workingset->isActiveConstr[(workingset->isActiveIdx[workingset->
          Wid[idx_global] - 1] + workingset->Wlocalidx[idx_global]) - 2] = false;
        workingset->Wid[idx_global] = workingset->Wid[workingset->nActiveConstr
          - 1];
        workingset->Wlocalidx[idx_global] = workingset->Wlocalidx
          [workingset->nActiveConstr - 1];
        idxEndIneq = workingset->nVar;
        for (PHASEONE = 0; PHASEONE < idxEndIneq; PHASEONE++) {
          workingset->ATwset[PHASEONE + 21 * idx_global] = workingset->
            ATwset[PHASEONE + 21 * (workingset->nActiveConstr - 1)];
        }

        workingset->bwset[idx_global] = workingset->bwset
          [workingset->nActiveConstr - 1];
        workingset->nActiveConstr--;
        workingset->nWConstr[idxStartIneq]--;
        exitg1 = true;
      } else {
        idx_global++;
      }
    }
  }

  PHASEONE = workingset->nActiveConstr - 1;
  while ((PHASEONE + 1 > workingset->sizes[0]) && (PHASEONE + 1 > nVar)) {
    idxStartIneq = workingset->Wid[PHASEONE] - 1;
    workingset->isActiveConstr[(workingset->isActiveIdx[workingset->Wid[PHASEONE]
      - 1] + workingset->Wlocalidx[PHASEONE]) - 2] = false;
    workingset->Wid[PHASEONE] = workingset->Wid[workingset->nActiveConstr - 1];
    workingset->Wlocalidx[PHASEONE] = workingset->Wlocalidx
      [workingset->nActiveConstr - 1];
    idxEndIneq = workingset->nVar;
    for (idx_global = 0; idx_global < idxEndIneq; idx_global++) {
      workingset->ATwset[idx_global + 21 * PHASEONE] = workingset->
        ATwset[idx_global + 21 * (workingset->nActiveConstr - 1)];
    }

    workingset->bwset[PHASEONE] = workingset->bwset[workingset->nActiveConstr -
      1];
    workingset->nActiveConstr--;
    workingset->nWConstr[idxStartIneq]--;
    PHASEONE--;
  }

  solution->maxConstr = solution->xstar[20];
  setProblemType(workingset, PROBTYPE_ORIG);
  objective->objtype = objective->prev_objtype;
  objective->nvar = objective->prev_nvar;
  objective->hasLinear = objective->prev_hasLinear;
  options->ObjectiveLimit = -1.0E+20;
  options->StepTolerance = 1.0E-8;
}

//
// Arguments    : const double H[400]
//                const double f[20]
//                struct_T *solution
//                c_struct_T *memspace
//                e_struct_T *workingset
//                f_struct_T *qrmanager
//                d_struct_T *cholmanager
//                h_struct_T *options
//                const b_struct_T *runTimeOptions
//                g_struct_T *objective
// Return Type  : void
//
void phaseone(const double H[400], const double f[20], struct_T *solution,
              c_struct_T *memspace, e_struct_T *workingset, f_struct_T
              *qrmanager, d_struct_T *cholmanager, h_struct_T *options, const
              b_struct_T *runTimeOptions, g_struct_T *objective)
{
  int nVar;
  int idxStartIneq;
  int idxEndIneq;
  int idx_global;
  int idx;
  nVar = workingset->nVar;
  solution->xstar[20] = solution->maxConstr + 1.0;
  idxStartIneq = (workingset->nWConstr[0] + workingset->nWConstr[1]) + 1;
  idxEndIneq = workingset->nActiveConstr;
  for (idx_global = idxStartIneq; idx_global <= idxEndIneq; idx_global++) {
    workingset->isActiveConstr[(workingset->isActiveIdx[workingset->
      Wid[idx_global - 1] - 1] + workingset->Wlocalidx[idx_global - 1]) - 2] =
      false;
  }

  workingset->nWConstr[2] = 0;
  workingset->nWConstr[3] = 0;
  workingset->nWConstr[4] = 0;
  workingset->nActiveConstr = workingset->nWConstr[0] + workingset->nWConstr[1];
  setProblemType(workingset, 1);
  std::memset(&objective->grad[0], 0, 21U * sizeof(double));
  std::memset(&objective->Hx[0], 0, 20U * sizeof(double));
  objective->maxVar = 21;
  objective->beta = 0.0;
  objective->rho = 0.0;
  objective->prev_objtype = 3;
  objective->prev_nvar = 20;
  objective->prev_hasLinear = true;
  objective->objtype = 5;
  objective->nvar = 21;
  objective->gammaScalar = 1.0;
  objective->hasLinear = true;
  options->ObjectiveLimit = 1.0E-8 * runTimeOptions->ConstrRelTolFactor;
  options->StepTolerance = 1.4901161193847657E-10;
  solution->fstar = computeFval(objective, memspace->workspace_double, H, f,
    solution->xstar);
  solution->state = 5;
  iterate(H, f, solution, memspace, workingset, qrmanager, cholmanager,
          objective, options->ObjectiveLimit, options->StepTolerance,
          runTimeOptions->MaxIterations, runTimeOptions->ConstrRelTolFactor,
          runTimeOptions->ProbRelTolFactor, runTimeOptions->RemainFeasible);
  if (workingset->isActiveConstr[(workingset->isActiveIdx[3] + workingset->
       sizes[3]) - 2]) {
    bool exitg1;
    idx = workingset->sizes[0];
    exitg1 = false;
    while ((!exitg1) && (idx + 1 <= workingset->nActiveConstr)) {
      if ((workingset->Wid[idx] == 4) && (workingset->Wlocalidx[idx] ==
           workingset->sizes[3])) {
        idxEndIneq = workingset->Wid[idx] - 1;
        workingset->isActiveConstr[(workingset->isActiveIdx[workingset->Wid[idx]
          - 1] + workingset->Wlocalidx[idx]) - 2] = false;
        workingset->Wid[idx] = workingset->Wid[workingset->nActiveConstr - 1];
        workingset->Wlocalidx[idx] = workingset->Wlocalidx
          [workingset->nActiveConstr - 1];
        idx_global = workingset->nVar;
        for (idxStartIneq = 0; idxStartIneq < idx_global; idxStartIneq++) {
          workingset->ATwset[idxStartIneq + 21 * idx] = workingset->
            ATwset[idxStartIneq + 21 * (workingset->nActiveConstr - 1)];
        }

        workingset->bwset[idx] = workingset->bwset[workingset->nActiveConstr - 1];
        workingset->nActiveConstr--;
        workingset->nWConstr[idxEndIneq]--;
        exitg1 = true;
      } else {
        idx++;
      }
    }
  }

  idxStartIneq = workingset->nActiveConstr - 1;
  while ((idxStartIneq + 1 > workingset->sizes[0]) && (idxStartIneq + 1 > nVar))
  {
    idxEndIneq = workingset->Wid[idxStartIneq] - 1;
    workingset->isActiveConstr[(workingset->isActiveIdx[workingset->
      Wid[idxStartIneq] - 1] + workingset->Wlocalidx[idxStartIneq]) - 2] = false;
    workingset->Wid[idxStartIneq] = workingset->Wid[workingset->nActiveConstr -
      1];
    workingset->Wlocalidx[idxStartIneq] = workingset->Wlocalidx
      [workingset->nActiveConstr - 1];
    idx_global = workingset->nVar;
    for (idx = 0; idx < idx_global; idx++) {
      workingset->ATwset[idx + 21 * idxStartIneq] = workingset->ATwset[idx + 21 *
        (workingset->nActiveConstr - 1)];
    }

    workingset->bwset[idxStartIneq] = workingset->bwset
      [workingset->nActiveConstr - 1];
    workingset->nActiveConstr--;
    workingset->nWConstr[idxEndIneq]--;
    idxStartIneq--;
  }

  solution->maxConstr = solution->xstar[20];
  setProblemType(workingset, 3);
  objective->objtype = objective->prev_objtype;
  objective->nvar = objective->prev_nvar;
  objective->hasLinear = objective->prev_hasLinear;
  options->ObjectiveLimit = -1.0E+20;
  options->StepTolerance = 1.0E-8;
}

//
// File trailer for phaseone.cpp
//
// [EOF]
//
