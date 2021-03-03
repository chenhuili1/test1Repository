//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: driver.cpp
//
// MATLAB Coder version            : 5.0
// C/C++ source code generated on  : 09-Oct-2020 15:23:44
//

// Include Files
#include "stdafx.h"
#include "driver.h"
#include "GetFphi.h"
#include "Getintput_u.h"
#include "PresolveWorkingSet.h"
#include "computeFirstOrderOpt.h"
#include "computeFval.h"
#include "feasibleX0ForWorkingSet.h"
#include "iterate.h"
#include "maxConstraintViolation.h"
#include "phaseone.h"
#include "rt_nonfinite.h"
#include <cstring>

// Function Definitions

//
// Arguments    : const double H[400]
//                const double f[20]
//                struct_T *solution
//                c_struct_T *memspace
//                e_struct_T *workingset
//                d_struct_T *cholmanager
//                b_struct_T runTimeOptions
//                f_struct_T *qrmanager
//                g_struct_T *objective
// Return Type  : void
//
void driver(const double H[400], const double f[20], struct_T *solution,
            c_struct_T *memspace, e_struct_T *workingset, d_struct_T
            *cholmanager, b_struct_T runTimeOptions, f_struct_T *qrmanager,
            g_struct_T *objective)
{
  int nVar;
  int i;
  int idx;
  h_struct_T options;
  static const char cv[128] = { '\x00', '\x01', '\x02', '\x03', '\x04', '\x05',
    '\x06', '\x07', '\x08', '	', '\x0a', '\x0b', '\x0c', '\x0d', '\x0e', '\x0f',
    '\x10', '\x11', '\x12', '\x13', '\x14', '\x15', '\x16', '\x17', '\x18',
    '\x19', '\x1a', '\x1b', '\x1c', '\x1d', '\x1e', '\x1f', ' ', '!', '\"', '#',
    '$', '%', '&', '\'', '(', ')', '*', '+', ',', '-', '.', '/', '0', '1', '2',
    '3', '4', '5', '6', '7', '8', '9', ':', ';', '<', '=', '>', '?', '@', 'a',
    'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p',
    'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '[', '\\', ']', '^', '_',
    '`', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',
    'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '{', '|', '}',
    '~', '\x7f' };

  static const char cv1[8] = { 'q', 'u', 'a', 'd', 'p', 'r', 'o', 'g' };

  std::memset(&objective->grad[0], 0, 21U * sizeof(double));
  std::memset(&objective->Hx[0], 0, 20U * sizeof(double));
  objective->hasLinear = true;
  objective->nvar = 20;
  objective->maxVar = 21;
  objective->beta = 0.0;
  objective->rho = 0.0;
  objective->objtype = 3;
  objective->prev_objtype = 3;
  objective->prev_nvar = 0;
  objective->prev_hasLinear = false;
  objective->gammaScalar = 0.0;
  solution->iterations = 0;
  runTimeOptions.RemainFeasible = true;
  nVar = workingset->nVar - 1;
  i = workingset->sizes[0];
  for (idx = 0; idx < i; idx++) {
    solution->xstar[workingset->indexFixed[idx] - 1] = workingset->ub
      [workingset->indexFixed[idx] - 1];
  }

  i = workingset->sizes[3];
  for (idx = 0; idx < i; idx++) {
    if (workingset->isActiveConstr[(workingset->isActiveIdx[3] + idx) - 1]) {
      solution->xstar[workingset->indexLB[idx] - 1] = -workingset->lb
        [workingset->indexLB[idx] - 1];
    }
  }

  i = workingset->sizes[4];
  for (idx = 0; idx < i; idx++) {
    if (workingset->isActiveConstr[(workingset->isActiveIdx[4] + idx) - 1]) {
      solution->xstar[workingset->indexUB[idx] - 1] = workingset->ub
        [workingset->indexUB[idx] - 1];
    }
  }

  PresolveWorkingSet(solution, memspace, workingset, qrmanager, &options);
  if (solution->state >= 0) {
    double maxConstr_new;
    bool guard1 = false;
    solution->iterations = 0;
    solution->maxConstr = maxConstraintViolation(workingset, solution->xstar);
    maxConstr_new = 1.0E-8 * runTimeOptions.ConstrRelTolFactor;
    guard1 = false;
    if (solution->maxConstr > maxConstr_new) {
      phaseone(H, f, solution, memspace, workingset, qrmanager, cholmanager,
               &options, &runTimeOptions, objective);
      if (solution->state != 0) {
        solution->maxConstr = maxConstraintViolation(workingset, solution->xstar);
        if (solution->maxConstr > maxConstr_new) {
          std::memset(&solution->lambda[0], 0, 43U * sizeof(double));
          solution->fstar = computeFval(objective, memspace->workspace_double, H,
            f, solution->xstar);
          solution->state = -2;
        } else {
          if (solution->maxConstr > 0.0) {
            if (0 <= nVar) {
              std::memcpy(&solution->searchDir[0], &solution->xstar[0], (nVar +
                1) * sizeof(double));
            }

            b_PresolveWorkingSet(solution, memspace, workingset, qrmanager);
            maxConstr_new = maxConstraintViolation(workingset, solution->xstar);
            if (maxConstr_new >= solution->maxConstr) {
              solution->maxConstr = maxConstr_new;
              if (0 <= nVar) {
                std::memcpy(&solution->xstar[0], &solution->searchDir[0], (nVar
                  + 1) * sizeof(double));
              }
            }
          }

          guard1 = true;
        }
      }
    } else {
      guard1 = true;
    }

    if (guard1) {
      bool b_bool;
      iterate(H, f, solution, memspace, workingset, qrmanager, cholmanager,
              objective, options.ObjectiveLimit, options.StepTolerance,
              runTimeOptions.MaxIterations, runTimeOptions.ConstrRelTolFactor,
              runTimeOptions.ProbRelTolFactor, true);
      b_bool = false;
      nVar = 0;
      int exitg1;
      do {
        exitg1 = 0;
        if (nVar < 8) {
          if (cv[static_cast<unsigned char>(options.SolverName[nVar])] != cv[
              static_cast<int>(cv1[nVar])]) {
            exitg1 = 1;
          } else {
            nVar++;
          }
        } else {
          b_bool = true;
          exitg1 = 1;
        }
      } while (exitg1 == 0);

      if (b_bool && (solution->state != -6)) {
        solution->maxConstr = maxConstraintViolation(workingset, solution->xstar);
        computeFirstOrderOpt(solution, objective, workingset->nVar,
                             workingset->ATwset, workingset->nActiveConstr,
                             memspace->workspace_double);
        runTimeOptions.RemainFeasible = false;
        while ((solution->iterations < runTimeOptions.MaxIterations) &&
               ((solution->state == -7) || ((solution->state == 1) &&
                 ((solution->maxConstr > 1.0E-8 *
                   runTimeOptions.ConstrRelTolFactor) ||
                  (solution->firstorderopt > 1.0E-8 *
                   runTimeOptions.ProbRelTolFactor))))) {
          feasibleX0ForWorkingSet(memspace->workspace_double, solution->xstar,
            workingset, qrmanager);
          b_PresolveWorkingSet(solution, memspace, workingset, qrmanager);
          b_phaseone(H, f, solution, memspace, workingset, qrmanager,
                     cholmanager, objective, &options, &runTimeOptions);
          iterate(H, f, solution, memspace, workingset, qrmanager, cholmanager,
                  objective, options.ObjectiveLimit, options.StepTolerance,
                  runTimeOptions.MaxIterations,
                  runTimeOptions.ConstrRelTolFactor,
                  runTimeOptions.ProbRelTolFactor, false);
          solution->maxConstr = maxConstraintViolation(workingset,
            solution->xstar);
          computeFirstOrderOpt(solution, objective, workingset->nVar,
                               workingset->ATwset, workingset->nActiveConstr,
                               memspace->workspace_double);
        }
      }
    }
  }
}

//
// File trailer for driver.cpp
//
// [EOF]
//
