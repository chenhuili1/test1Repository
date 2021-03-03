//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: iterate.cpp
//
// MATLAB Coder version            : 5.0
// C/C++ source code generated on  : 09-Oct-2020 15:23:44
//

// Include Files
#include "stdafx.h"
#include "iterate.h"
#include "GetFphi.h"
#include "Getintput_u.h"
#include "addBoundToActiveSetMatrix_.h"
#include "checkStoppingAndUpdateFval.h"
#include "computeFval_ReuseHx.h"
#include "computeGrad_StoreHx.h"
#include "compute_deltax.h"
#include "compute_lambda.h"
#include "factorQR.h"
#include "feasibleratiotest.h"
#include "ratiotest.h"
#include "rt_nonfinite.h"
#include "xnrm2.h"
#include "xorgqr.h"
#include "xrotg.h"
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
//                double options_ObjectiveLimit
//                double options_StepTolerance
//                int runTimeOptions_MaxIterations
//                double c_runTimeOptions_ConstrRelTolFa
//                double runTimeOptions_ProbRelTolFactor
//                bool runTimeOptions_RemainFeasible
// Return Type  : void
//
void iterate(const double H[400], const double f[20], struct_T *solution,
             c_struct_T *memspace, e_struct_T *workingset, f_struct_T *qrmanager,
             d_struct_T *cholmanager, g_struct_T *objective, double
             options_ObjectiveLimit, double options_StepTolerance, int
             runTimeOptions_MaxIterations, double
             c_runTimeOptions_ConstrRelTolFa, double
             runTimeOptions_ProbRelTolFactor, bool runTimeOptions_RemainFeasible)
{
  bool subProblemChanged;
  bool updateFval;
  int activeSetChangeID;
  int TYPE;
  double tolDelta;
  int nVar;
  int globalActiveConstrIdx;
  int ix;
  int iQR0;
  double temp;
  bool newBlocking;
  double d;
  int b_ix;
  double c;
  double s;
  subProblemChanged = true;
  updateFval = true;
  activeSetChangeID = 0;
  TYPE = objective->objtype;
  tolDelta = 6.7434957617430445E-7;
  nVar = workingset->nVar;
  globalActiveConstrIdx = -1;
  computeGrad_StoreHx(objective, H, f, solution->xstar);
  solution->fstar = computeFval_ReuseHx(objective, memspace->workspace_double, f,
    solution->xstar);
  if (solution->iterations < runTimeOptions_MaxIterations) {
    solution->state = -5;
  } else {
    solution->state = 0;
  }

  std::memset(&solution->lambda[0], 0, 43U * sizeof(double));
  int exitg1;
  do {
    exitg1 = 0;
    if (solution->state == -5) {
      bool guard1 = false;
      int i;
      int b_i;
      guard1 = false;
      if (subProblemChanged) {
        int endIdx;
        int n;
        int k;
        int b_k;
        switch (activeSetChangeID) {
         case 1:
          {
            int iy;
            endIdx = 21 * (workingset->nActiveConstr - 1);
            ix = qrmanager->mrows;
            iQR0 = qrmanager->ncols + 1;
            if (ix < iQR0) {
              iQR0 = ix;
            }

            qrmanager->minRowCol = iQR0;
            iy = 43 * qrmanager->ncols;
            if (qrmanager->mrows != 0) {
              iQR0 = iy + qrmanager->mrows;
              if (iy + 1 <= iQR0) {
                std::memset(&qrmanager->QR[iy], 0, (iQR0 - iy) * sizeof(double));
              }

              b_i = 43 * (qrmanager->mrows - 1) + 1;
              for (ix = 1; ix <= b_i; ix += 43) {
                b_ix = endIdx;
                c = 0.0;
                iQR0 = (ix + qrmanager->mrows) - 1;
                for (i = ix; i <= iQR0; i++) {
                  c += qrmanager->Q[i - 1] * workingset->ATwset[b_ix];
                  b_ix++;
                }

                qrmanager->QR[iy] += c;
                iy++;
              }
            }

            qrmanager->ncols++;
            qrmanager->jpvt[qrmanager->ncols - 1] = qrmanager->ncols;
            for (i = qrmanager->mrows - 1; i + 1 > qrmanager->ncols; i--) {
              d = qrmanager->QR[i + 43 * (qrmanager->ncols - 1)];
              xrotg(&qrmanager->QR[(i + 43 * (qrmanager->ncols - 1)) - 1], &d,
                    &c, &s);
              qrmanager->QR[i + 43 * (qrmanager->ncols - 1)] = d;
              iQR0 = 43 * (i - 1);
              n = qrmanager->mrows;
              if (qrmanager->mrows >= 1) {
                iy = iQR0 + 43;
                for (k = 0; k < n; k++) {
                  temp = c * qrmanager->Q[iQR0] + s * qrmanager->Q[iy];
                  qrmanager->Q[iy] = c * qrmanager->Q[iy] - s * qrmanager->
                    Q[iQR0];
                  qrmanager->Q[iQR0] = temp;
                  iy++;
                  iQR0++;
                }
              }
            }
          }
          break;

         case -1:
          {
            i = globalActiveConstrIdx;
            if (qrmanager->usedPivoting) {
              i = 0;
              while ((i + 1 <= qrmanager->ncols) && (qrmanager->jpvt[i] !=
                      globalActiveConstrIdx + 1)) {
                i++;
              }
            }

            if (i + 1 >= qrmanager->ncols) {
              qrmanager->ncols--;
            } else {
              qrmanager->jpvt[i] = qrmanager->jpvt[qrmanager->ncols - 1];
              b_i = qrmanager->minRowCol;
              for (k = 0; k < b_i; k++) {
                qrmanager->QR[k + 43 * i] = qrmanager->QR[k + 43 *
                  (qrmanager->ncols - 1)];
              }

              qrmanager->ncols--;
              ix = qrmanager->mrows;
              iQR0 = qrmanager->ncols;
              if (ix < iQR0) {
                iQR0 = ix;
              }

              qrmanager->minRowCol = iQR0;
              if (i + 1 < qrmanager->mrows) {
                int iy;
                ix = qrmanager->mrows - 1;
                endIdx = qrmanager->ncols;
                if (ix < endIdx) {
                  endIdx = ix;
                }

                for (k = endIdx; k >= i + 1; k--) {
                  b_i = k + 43 * i;
                  d = qrmanager->QR[b_i];
                  xrotg(&qrmanager->QR[(k + 43 * i) - 1], &d, &c, &s);
                  qrmanager->QR[b_i] = d;
                  ix = 43 * (k - 1);
                  qrmanager->QR[k + ix] = 0.0;
                  iQR0 = k + 43 * (i + 1);
                  n = (qrmanager->ncols - i) - 2;
                  if (n + 1 >= 1) {
                    b_ix = iQR0 - 1;
                    for (b_k = 0; b_k <= n; b_k++) {
                      temp = c * qrmanager->QR[b_ix] + s * qrmanager->QR[iQR0];
                      qrmanager->QR[iQR0] = c * qrmanager->QR[iQR0] - s *
                        qrmanager->QR[b_ix];
                      qrmanager->QR[b_ix] = temp;
                      iQR0 += 43;
                      b_ix += 43;
                    }
                  }

                  n = qrmanager->mrows;
                  if (qrmanager->mrows >= 1) {
                    iy = ix + 43;
                    for (b_k = 0; b_k < n; b_k++) {
                      temp = c * qrmanager->Q[ix] + s * qrmanager->Q[iy];
                      qrmanager->Q[iy] = c * qrmanager->Q[iy] - s * qrmanager->
                        Q[ix];
                      qrmanager->Q[ix] = temp;
                      iy++;
                      ix++;
                    }
                  }
                }

                b_i = i + 2;
                for (k = b_i; k <= endIdx; k++) {
                  ix = 43 * (k - 1);
                  iQR0 = k + ix;
                  d = qrmanager->QR[iQR0];
                  xrotg(&qrmanager->QR[(k + 43 * (k - 1)) - 1], &d, &c, &s);
                  qrmanager->QR[iQR0] = d;
                  iQR0 = k * 44;
                  n = qrmanager->ncols - k;
                  if (n >= 1) {
                    b_ix = iQR0 - 1;
                    for (b_k = 0; b_k < n; b_k++) {
                      temp = c * qrmanager->QR[b_ix] + s * qrmanager->QR[iQR0];
                      qrmanager->QR[iQR0] = c * qrmanager->QR[iQR0] - s *
                        qrmanager->QR[b_ix];
                      qrmanager->QR[b_ix] = temp;
                      iQR0 += 43;
                      b_ix += 43;
                    }
                  }

                  n = qrmanager->mrows;
                  if (qrmanager->mrows >= 1) {
                    iy = ix + 43;
                    for (b_k = 0; b_k < n; b_k++) {
                      temp = c * qrmanager->Q[ix] + s * qrmanager->Q[iy];
                      qrmanager->Q[iy] = c * qrmanager->Q[iy] - s * qrmanager->
                        Q[ix];
                      qrmanager->Q[ix] = temp;
                      iy++;
                      ix++;
                    }
                  }
                }
              }
            }
          }
          break;

         default:
          factorQR(qrmanager, workingset->ATwset, nVar,
                   workingset->nActiveConstr);
          b_i = qrmanager->minRowCol;
          for (i = 0; i < b_i; i++) {
            iQR0 = 43 * i + i;
            n = qrmanager->mrows - i;
            if (0 <= n - 2) {
              std::memcpy(&qrmanager->Q[iQR0 + 1], &qrmanager->QR[iQR0 + 1], (n
                + -1) * sizeof(double));
            }
          }

          xorgqr(qrmanager->mrows, qrmanager->mrows, qrmanager->minRowCol,
                 qrmanager->Q, qrmanager->tau);
          break;
        }

        compute_deltax(H, solution, memspace, qrmanager, cholmanager, objective);
        if (solution->state != -5) {
          exitg1 = 1;
        } else if ((b_xnrm2(nVar, solution->searchDir) < options_StepTolerance) ||
                   (workingset->nActiveConstr >= nVar)) {
          guard1 = true;
        } else {
          updateFval = (TYPE == 5);
          if (updateFval || runTimeOptions_RemainFeasible) {
            feasibleratiotest(solution->xstar, solution->searchDir,
                              memspace->workspace_double, workingset->nVar,
                              workingset->Aineq, workingset->bineq,
                              workingset->lb, workingset->ub,
                              workingset->indexLB, workingset->indexUB,
                              workingset->sizes, workingset->isActiveIdx,
                              workingset->isActiveConstr, workingset->nWConstr,
                              updateFval, &temp, &newBlocking, &iQR0, &ix);
          } else {
            ratiotest(solution->xstar, solution->searchDir,
                      memspace->workspace_double, workingset->nVar,
                      workingset->Aineq, workingset->bineq, workingset->lb,
                      workingset->ub, workingset->indexLB, workingset->indexUB,
                      workingset->sizes, workingset->isActiveIdx,
                      workingset->isActiveConstr, workingset->nWConstr,
                      &tolDelta, &temp, &newBlocking, &iQR0, &ix);
          }

          if (newBlocking) {
            switch (iQR0) {
             case 3:
              workingset->nWConstr[2]++;
              workingset->isActiveConstr[(workingset->isActiveIdx[2] + ix) - 2] =
                true;
              workingset->nActiveConstr++;
              workingset->Wid[workingset->nActiveConstr - 1] = 3;
              workingset->Wlocalidx[workingset->nActiveConstr - 1] = ix;
              endIdx = 21 * (ix - 1);
              iQR0 = 21 * (workingset->nActiveConstr - 1);
              n = workingset->nVar;
              for (k = 0; k < n; k++) {
                b_k = k + 1;
                workingset->ATwset[(iQR0 + b_k) - 1] = workingset->Aineq[(endIdx
                  + b_k) - 1];
              }

              workingset->bwset[workingset->nActiveConstr - 1] =
                workingset->bineq[ix - 1];
              break;

             case 4:
              addBoundToActiveSetMatrix_(workingset, 4, ix);
              break;

             default:
              addBoundToActiveSetMatrix_(workingset, 5, ix);
              break;
            }

            activeSetChangeID = 1;
          } else {
            if (objective->objtype == 5) {
              if (b_xnrm2(objective->nvar, solution->searchDir) > 100.0 *
                  static_cast<double>(objective->nvar) * 1.4901161193847656E-8)
              {
                solution->state = 3;
              } else {
                solution->state = 4;
              }
            }

            subProblemChanged = false;
            if (workingset->nActiveConstr == 0) {
              solution->state = 1;
            }
          }

          if (!(temp == 0.0)) {
            iQR0 = nVar - 1;
            for (k = 0; k <= iQR0; k++) {
              solution->xstar[k] += temp * solution->searchDir[k];
            }
          }

          computeGrad_StoreHx(objective, H, f, solution->xstar);
          updateFval = true;
          checkStoppingAndUpdateFval(&activeSetChangeID, f, solution, memspace,
            objective, workingset, qrmanager, options_ObjectiveLimit,
            runTimeOptions_MaxIterations, c_runTimeOptions_ConstrRelTolFa,
            updateFval);
        }
      } else {
        if (0 <= nVar - 1) {
          std::memset(&solution->searchDir[0], 0, nVar * sizeof(double));
        }

        guard1 = true;
      }

      if (guard1) {
        compute_lambda(memspace->workspace_double, solution, objective,
                       qrmanager);
        if (solution->state != -7) {
          ix = -1;
          temp = 0.0 * runTimeOptions_ProbRelTolFactor * static_cast<double>
            (TYPE != 5);
          b_i = (workingset->nWConstr[0] + workingset->nWConstr[1]) + 1;
          iQR0 = workingset->nActiveConstr;
          for (i = b_i; i <= iQR0; i++) {
            d = solution->lambda[i - 1];
            if (d < temp) {
              temp = d;
              ix = i - 1;
            }
          }

          if (ix + 1 == 0) {
            solution->state = 1;
          } else {
            activeSetChangeID = -1;
            globalActiveConstrIdx = ix;
            subProblemChanged = true;
            iQR0 = workingset->Wid[ix] - 1;
            workingset->isActiveConstr[(workingset->isActiveIdx[workingset->
              Wid[ix] - 1] + workingset->Wlocalidx[ix]) - 2] = false;
            workingset->Wid[ix] = workingset->Wid[workingset->nActiveConstr - 1];
            workingset->Wlocalidx[ix] = workingset->Wlocalidx
              [workingset->nActiveConstr - 1];
            b_i = workingset->nVar;
            for (i = 0; i < b_i; i++) {
              workingset->ATwset[i + 21 * ix] = workingset->ATwset[i + 21 *
                (workingset->nActiveConstr - 1)];
            }

            workingset->bwset[ix] = workingset->bwset[workingset->nActiveConstr
              - 1];
            workingset->nActiveConstr--;
            workingset->nWConstr[iQR0]--;
            solution->lambda[ix] = 0.0;
          }
        } else {
          ix = workingset->nActiveConstr;
          activeSetChangeID = 0;
          globalActiveConstrIdx = workingset->nActiveConstr - 1;
          subProblemChanged = true;
          iQR0 = workingset->Wid[globalActiveConstrIdx] - 1;
          workingset->isActiveConstr[(workingset->isActiveIdx[iQR0] +
            workingset->Wlocalidx[globalActiveConstrIdx]) - 2] = false;
          workingset->nActiveConstr--;
          workingset->nWConstr[iQR0]--;
          solution->lambda[ix - 1] = 0.0;
        }

        updateFval = false;
        checkStoppingAndUpdateFval(&activeSetChangeID, f, solution, memspace,
          objective, workingset, qrmanager, options_ObjectiveLimit,
          runTimeOptions_MaxIterations, c_runTimeOptions_ConstrRelTolFa,
          updateFval);
      }
    } else {
      if (!updateFval) {
        solution->fstar = computeFval_ReuseHx(objective,
          memspace->workspace_double, f, solution->xstar);
      }

      exitg1 = 1;
    }
  } while (exitg1 == 0);
}

//
// File trailer for iterate.cpp
//
// [EOF]
//
