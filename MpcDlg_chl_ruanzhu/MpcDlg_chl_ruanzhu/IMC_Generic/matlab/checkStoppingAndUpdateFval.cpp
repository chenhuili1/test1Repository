//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: checkStoppingAndUpdateFval.cpp
//
// MATLAB Coder version            : 5.0
// C/C++ source code generated on  : 09-Oct-2020 15:23:44
//

// Include Files
#include "stdafx.h"
#include "checkStoppingAndUpdateFval.h"
#include "GetFphi.h"
#include "Getintput_u.h"
#include "computeFval_ReuseHx.h"
#include "feasibleX0ForWorkingSet.h"
#include "maxConstraintViolation.h"
#include "rt_nonfinite.h"
#include <cstring>

// Function Definitions

//
// Arguments    : int *activeSetChangeID
//                const double f[20]
//                struct_T *solution
//                c_struct_T *memspace
//                const g_struct_T *objective
//                e_struct_T *workingset
//                f_struct_T *qrmanager
//                double options_ObjectiveLimit
//                int runTimeOptions_MaxIterations
//                double c_runTimeOptions_ConstrRelTolFa
//                bool updateFval
// Return Type  : void
//
void checkStoppingAndUpdateFval(int *activeSetChangeID, const double f[20],
  struct_T *solution, c_struct_T *memspace, const g_struct_T *objective,
  e_struct_T *workingset, f_struct_T *qrmanager, double options_ObjectiveLimit,
  int runTimeOptions_MaxIterations, double c_runTimeOptions_ConstrRelTolFa, bool
  updateFval)
{
  int nVar;
  solution->iterations++;
  nVar = objective->nvar - 1;
  if ((solution->iterations >= runTimeOptions_MaxIterations) &&
      ((solution->state != 1) || (objective->objtype == 5))) {
    solution->state = 0;
  }

  if (solution->iterations - solution->iterations / 50 * 50 == 0) {
    solution->maxConstr = maxConstraintViolation(workingset, solution->xstar);
    if (solution->maxConstr > 1.0E-8 * c_runTimeOptions_ConstrRelTolFa) {
      bool nonDegenerateWset;
      double constrViolation_new;
      if (0 <= nVar) {
        std::memcpy(&solution->searchDir[0], &solution->xstar[0], (nVar + 1) *
                    sizeof(double));
      }

      nonDegenerateWset = feasibleX0ForWorkingSet(memspace->workspace_double,
        solution->searchDir, workingset, qrmanager);
      if ((!nonDegenerateWset) && (solution->state != 0)) {
        solution->state = -2;
      }

      *activeSetChangeID = 0;
      constrViolation_new = maxConstraintViolation(workingset,
        solution->searchDir);
      if (constrViolation_new < solution->maxConstr) {
        if (0 <= nVar) {
          std::memcpy(&solution->xstar[0], &solution->searchDir[0], (nVar + 1) *
                      sizeof(double));
        }

        solution->maxConstr = constrViolation_new;
      }
    }
  }

  if ((options_ObjectiveLimit > rtMinusInf) && updateFval) {
    solution->fstar = computeFval_ReuseHx(objective, memspace->workspace_double,
      f, solution->xstar);
    if ((solution->fstar < options_ObjectiveLimit) && ((solution->state != 0) ||
         (objective->objtype != 5))) {
      solution->state = 2;
    }
  }
}

//
// File trailer for checkStoppingAndUpdateFval.cpp
//
// [EOF]
//
