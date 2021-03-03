//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: compute_deltax.cpp
//
// MATLAB Coder version            : 5.0
// C/C++ source code generated on  : 09-Oct-2020 15:23:44
//

// Include Files
#include "stdafx.h"
#include "compute_deltax.h"
#include "GetFphi.h"
#include "Getintput_u.h"
#include "factor.h"
#include "fullColLDL2_.h"
#include "partialColLDL3_.h"
#include "rt_nonfinite.h"
#include "solve.h"
#include "xgemm.h"
#include <cmath>
#include <cstring>

// Function Definitions

//
// Arguments    : const double H[400]
//                struct_T *solution
//                c_struct_T *memspace
//                const f_struct_T *qrmanager
//                d_struct_T *cholmanager
//                const g_struct_T *objective
// Return Type  : void
//
void compute_deltax(const double H[400], struct_T *solution, c_struct_T
                    *memspace, const f_struct_T *qrmanager, d_struct_T
                    *cholmanager, const g_struct_T *objective)
{
  int nVar_tmp;
  int mNull_tmp;
  int idx_row;
  int ix;
  double smax;
  double dv[903];
  nVar_tmp = qrmanager->mrows - 1;
  mNull_tmp = qrmanager->mrows - qrmanager->ncols;
  if (mNull_tmp <= 0) {
    if (0 <= nVar_tmp) {
      std::memset(&solution->searchDir[0], 0, (nVar_tmp + 1) * sizeof(double));
    }
  } else {
    int order;
    for (order = 0; order <= nVar_tmp; order++) {
      solution->searchDir[order] = -objective->grad[order];
    }

    if (qrmanager->ncols <= 0) {
      switch (objective->objtype) {
       case 5:
        break;

       case 3:
        factor(cholmanager, H, qrmanager->mrows, qrmanager->mrows);
        if (cholmanager->info != 0) {
          solution->state = -6;
        } else {
          solve(cholmanager, solution->searchDir);
        }
        break;

       default:
        {
          factor(cholmanager, H, objective->nvar, objective->nvar);
          if (cholmanager->info != 0) {
            solution->state = -6;
          } else {
            int nVars;
            int i;
            solve(cholmanager, solution->searchDir);
            nVars = objective->nvar + 1;
            i = qrmanager->mrows;
            for (idx_row = nVars; idx_row <= i; idx_row++) {
              solution->searchDir[idx_row - 1] *= rtInf;
            }
          }
        }
        break;
      }
    } else {
      int nullStartIdx_tmp;
      nullStartIdx_tmp = 43 * qrmanager->ncols + 1;
      switch (objective->objtype) {
       case 5:
        {
          for (order = 0; order < mNull_tmp; order++) {
            memspace->workspace_double[order] = -qrmanager->Q[nVar_tmp + 43 *
              (qrmanager->ncols + order)];
          }

          if (qrmanager->mrows != 0) {
            int i;
            if (0 <= nVar_tmp) {
              std::memset(&solution->searchDir[0], 0, (nVar_tmp + 1) * sizeof
                          (double));
            }

            ix = 0;
            i = nullStartIdx_tmp + 43 * (mNull_tmp - 1);
            for (idx_row = nullStartIdx_tmp; idx_row <= i; idx_row += 43) {
              int nVars;
              order = 0;
              nVars = idx_row + nVar_tmp;
              for (int ia = idx_row; ia <= nVars; ia++) {
                solution->searchDir[order] += qrmanager->Q[ia - 1] *
                  memspace->workspace_double[ix];
                order++;
              }

              ix++;
            }
          }
        }
        break;

       default:
        {
          int nVars;
          int i;
          double SCALED_REG_PRIMAL;
          switch (objective->objtype) {
           case 3:
            xgemm(qrmanager->mrows, mNull_tmp, qrmanager->mrows, H,
                  qrmanager->mrows, qrmanager->Q, nullStartIdx_tmp,
                  memspace->workspace_double);
            b_xgemm(mNull_tmp, mNull_tmp, qrmanager->mrows, qrmanager->Q,
                    nullStartIdx_tmp, memspace->workspace_double,
                    cholmanager->FMat);
            break;

           default:
            nVars = qrmanager->mrows;
            xgemm(objective->nvar, mNull_tmp, objective->nvar, H,
                  objective->nvar, qrmanager->Q, nullStartIdx_tmp,
                  memspace->workspace_double);
            for (order = 0; order < mNull_tmp; order++) {
              i = objective->nvar + 1;
              for (idx_row = i; idx_row <= nVars; idx_row++) {
                memspace->workspace_double[(idx_row + 43 * order) - 1] = 0.0 *
                  qrmanager->Q[(idx_row + 43 * (order + qrmanager->ncols)) - 1];
              }
            }

            b_xgemm(mNull_tmp, mNull_tmp, qrmanager->mrows, qrmanager->Q,
                    nullStartIdx_tmp, memspace->workspace_double,
                    cholmanager->FMat);
            break;
          }

          SCALED_REG_PRIMAL = 1.4901161193847656E-6 * static_cast<double>
            (mNull_tmp);
          cholmanager->ndims = mNull_tmp;
          nVars = 1;
          if (mNull_tmp > 1) {
            ix = 0;
            smax = std::abs(cholmanager->FMat[0]);
            for (idx_row = 2; idx_row <= mNull_tmp; idx_row++) {
              double s;
              ix += 44;
              s = std::abs(cholmanager->FMat[ix]);
              if (s > smax) {
                nVars = idx_row;
                smax = s;
              }
            }
          }

          smax = std::abs(cholmanager->FMat[nVars * 44 - 1]) *
            2.2204460492503131E-16;
          if (!(smax > SCALED_REG_PRIMAL)) {
            smax = SCALED_REG_PRIMAL;
          }

          cholmanager->regTol_ = smax;
          if (mNull_tmp > 128) {
            bool exitg1;
            idx_row = 0;
            exitg1 = false;
            while ((!exitg1) && (idx_row < mNull_tmp)) {
              nVars = 44 * idx_row + 1;
              order = mNull_tmp - idx_row;
              if (idx_row + 48 <= mNull_tmp) {
                partialColLDL3_(cholmanager, nVars, order, SCALED_REG_PRIMAL);
                idx_row += 48;
              } else {
                fullColLDL2_(cholmanager, nVars, order, SCALED_REG_PRIMAL);
                exitg1 = true;
              }
            }
          } else {
            fullColLDL2_(cholmanager, 1, mNull_tmp, SCALED_REG_PRIMAL);
          }

          if (cholmanager->ConvexCheck) {
            order = 0;
            int exitg2;
            do {
              exitg2 = 0;
              if (order <= mNull_tmp - 1) {
                if (cholmanager->FMat[order + 43 * order] <= 0.0) {
                  cholmanager->info = -order - 1;
                  exitg2 = 1;
                } else {
                  order++;
                }
              } else {
                cholmanager->ConvexCheck = false;
                exitg2 = 1;
              }
            } while (exitg2 == 0);
          }

          if (cholmanager->info != 0) {
            solution->state = -6;
          } else {
            int ia;
            int b_i;
            if (qrmanager->mrows != 0) {
              std::memset(&memspace->workspace_double[0], 0, mNull_tmp * sizeof
                          (double));
              order = 0;
              i = nullStartIdx_tmp + 43 * (mNull_tmp - 1);
              for (idx_row = nullStartIdx_tmp; idx_row <= i; idx_row += 43) {
                ix = 0;
                smax = 0.0;
                nVars = idx_row + nVar_tmp;
                for (ia = idx_row; ia <= nVars; ia++) {
                  smax += qrmanager->Q[ia - 1] * objective->grad[ix];
                  ix++;
                }

                memspace->workspace_double[order] += -smax;
                order++;
              }
            }

            std::memcpy(&dv[0], &memspace->workspace_double[0], 903U * sizeof
                        (double));
            idx_row = cholmanager->ndims - 2;
            if (cholmanager->ndims != 0) {
              for (ia = 0; ia <= idx_row + 1; ia++) {
                order = ia + ia * 43;
                i = idx_row - ia;
                for (b_i = 0; b_i <= i; b_i++) {
                  nVars = b_i + 1;
                  ix = ia + nVars;
                  dv[ix] -= dv[ia] * cholmanager->FMat[order + nVars];
                }
              }
            }

            i = cholmanager->ndims;
            for (order = 0; order < i; order++) {
              dv[order] /= cholmanager->FMat[order + 43 * order];
            }

            idx_row = cholmanager->ndims;
            if (cholmanager->ndims != 0) {
              for (ia = idx_row; ia >= 1; ia--) {
                order = (ia - 1) * 43;
                smax = dv[ia - 1];
                i = ia + 1;
                for (b_i = idx_row; b_i >= i; b_i--) {
                  smax -= cholmanager->FMat[(order + b_i) - 1] * dv[b_i - 1];
                }

                dv[ia - 1] = smax;
              }
            }

            std::memcpy(&memspace->workspace_double[0], &dv[0], 903U * sizeof
                        (double));
            if (qrmanager->mrows != 0) {
              if (0 <= nVar_tmp) {
                std::memset(&solution->searchDir[0], 0, (nVar_tmp + 1) * sizeof
                            (double));
              }

              ix = 0;
              i = nullStartIdx_tmp + 43 * (mNull_tmp - 1);
              for (idx_row = nullStartIdx_tmp; idx_row <= i; idx_row += 43) {
                order = 0;
                nVars = idx_row + nVar_tmp;
                for (ia = idx_row; ia <= nVars; ia++) {
                  solution->searchDir[order] += qrmanager->Q[ia - 1] * dv[ix];
                  order++;
                }

                ix++;
              }
            }
          }
        }
        break;
      }
    }
  }
}

//
// File trailer for compute_deltax.cpp
//
// [EOF]
//
