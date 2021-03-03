//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: ratiotest.cpp
//
// MATLAB Coder version            : 5.0
// C/C++ source code generated on  : 09-Oct-2020 15:23:44
//

// Include Files
#include "stdafx.h"
#include "ratiotest.h"
#include "GetFphi.h"
#include "Getintput_u.h"
#include "rt_nonfinite.h"
#include "xnrm2.h"
#include <cmath>

// Function Definitions

//
// Arguments    : const double solution_xstar[21]
//                const double solution_searchDir[21]
//                double workspace[903]
//                int workingset_nVar
//                const double workingset_Aineq[42]
//                const double workingset_bineq[2]
//                const double workingset_lb[21]
//                const double workingset_ub[21]
//                const int workingset_indexLB[21]
//                const int workingset_indexUB[21]
//                const int workingset_sizes[5]
//                const int workingset_isActiveIdx[6]
//                const bool workingset_isActiveConstr[43]
//                const int workingset_nWConstr[5]
//                double *toldelta
//                double *alpha
//                bool *newBlocking
//                int *constrType
//                int *constrIdx
// Return Type  : void
//
void ratiotest(const double solution_xstar[21], const double solution_searchDir
               [21], double workspace[903], int workingset_nVar, const double
               workingset_Aineq[42], const double workingset_bineq[2], const
               double workingset_lb[21], const double workingset_ub[21], const
               int workingset_indexLB[21], const int workingset_indexUB[21],
               const int workingset_sizes[5], const int workingset_isActiveIdx[6],
               const bool workingset_isActiveConstr[43], const int
               workingset_nWConstr[5], double *toldelta, double *alpha, bool
               *newBlocking, int *constrType, int *constrIdx)
{
  int totalUB;
  double p_max;
  double denomTol;
  double phaseOneCorrectionX;
  double phaseOneCorrectionP;
  int i;
  int ix;
  double c;
  double pk_corrected;
  double ratio_tmp;
  double u0;
  totalUB = workingset_sizes[4];
  *alpha = 1.0E+30;
  *newBlocking = false;
  *constrType = 0;
  *constrIdx = 0;
  p_max = 0.0;
  denomTol = 2.2204460492503131E-13 * b_xnrm2(workingset_nVar,
    solution_searchDir);
  if (workingset_nWConstr[2] < 2) {
    int ia;
    workspace[0] = workingset_bineq[0];
    workspace[1] = workingset_bineq[1];
    workspace[0] = -workspace[0];
    workspace[1] = -workspace[1];
    ix = 0;
    c = 0.0;
    for (ia = 1; ia <= workingset_nVar; ia++) {
      c += workingset_Aineq[ia - 1] * solution_xstar[ix];
      ix++;
    }

    workspace[0] += c;
    ix = 0;
    c = 0.0;
    i = workingset_nVar + 21;
    for (ia = 22; ia <= i; ia++) {
      c += workingset_Aineq[ia - 1] * solution_xstar[ix];
      ix++;
    }

    workspace[1] += c;
    workspace[43] = 0.0;
    workspace[44] = 0.0;
    ix = 0;
    c = 0.0;
    for (ia = 1; ia <= workingset_nVar; ia++) {
      c += workingset_Aineq[ia - 1] * solution_searchDir[ix];
      ix++;
    }

    workspace[43] += c;
    ix = 0;
    c = 0.0;
    i = workingset_nVar + 21;
    for (ia = 22; ia <= i; ia++) {
      c += workingset_Aineq[ia - 1] * solution_searchDir[ix];
      ix++;
    }

    workspace[44] += c;
    if ((workspace[43] > denomTol) &&
        (!workingset_isActiveConstr[workingset_isActiveIdx[2] - 1])) {
      u0 = std::abs(workspace[0] - *toldelta);
      c = (1.0E-8 - workspace[0]) + *toldelta;
      if ((u0 < c) || rtIsNaN(c)) {
        c = u0;
      }

      c /= workspace[43];
      if ((c <= 1.0E+30) && (std::abs(workspace[43]) > 0.0)) {
        *alpha = c;
        *constrType = 3;
        *constrIdx = 1;
        *newBlocking = true;
      }

      u0 = std::abs(workspace[0]);
      if ((!(u0 < 1.0E-8 - workspace[0])) && (!rtIsNaN(1.0E-8 - workspace[0])))
      {
        u0 = 1.0E-8 - workspace[0];
      }

      c = u0 / workspace[43];
      if (c < *alpha) {
        *alpha = c;
        *constrType = 3;
        *constrIdx = 1;
        *newBlocking = true;
        p_max = std::abs(workspace[43]);
      }
    }

    if ((workspace[44] > denomTol) &&
        (!workingset_isActiveConstr[workingset_isActiveIdx[2]])) {
      u0 = std::abs(workspace[1] - *toldelta);
      c = (1.0E-8 - workspace[1]) + *toldelta;
      if ((u0 < c) || rtIsNaN(c)) {
        c = u0;
      }

      c /= workspace[44];
      if ((c <= *alpha) && (std::abs(workspace[44]) > p_max)) {
        *alpha = c;
        *constrType = 3;
        *constrIdx = 2;
        *newBlocking = true;
      }

      u0 = std::abs(workspace[1]);
      if ((!(u0 < 1.0E-8 - workspace[1])) && (!rtIsNaN(1.0E-8 - workspace[1])))
      {
        u0 = 1.0E-8 - workspace[1];
      }

      c = u0 / workspace[44];
      if (c < *alpha) {
        *alpha = c;
        *constrType = 3;
        *constrIdx = 2;
        *newBlocking = true;
        p_max = std::abs(workspace[44]);
      }
    }
  }

  if (workingset_nWConstr[3] < workingset_sizes[3]) {
    phaseOneCorrectionX = 0.0 * solution_xstar[workingset_nVar - 1];
    phaseOneCorrectionP = 0.0 * solution_searchDir[workingset_nVar - 1];
    i = workingset_sizes[3];
    for (ix = 0; ix <= i - 2; ix++) {
      pk_corrected = -solution_searchDir[workingset_indexLB[ix] - 1] -
        phaseOneCorrectionP;
      if ((pk_corrected > denomTol) && (!workingset_isActiveConstr
           [(workingset_isActiveIdx[3] + ix) - 1])) {
        ratio_tmp = -solution_xstar[workingset_indexLB[ix] - 1] -
          workingset_lb[workingset_indexLB[ix] - 1];
        c = (ratio_tmp - *toldelta) - phaseOneCorrectionX;
        u0 = std::abs(c);
        if ((!(u0 < 1.0E-8 - c)) && (!rtIsNaN(1.0E-8 - c))) {
          u0 = 1.0E-8 - c;
        }

        c = u0 / pk_corrected;
        if ((c <= *alpha) && (std::abs(pk_corrected) > p_max)) {
          *alpha = c;
          *constrType = 4;
          *constrIdx = ix + 1;
          *newBlocking = true;
        }

        c = ratio_tmp - phaseOneCorrectionX;
        u0 = std::abs(c);
        if ((!(u0 < 1.0E-8 - c)) && (!rtIsNaN(1.0E-8 - c))) {
          u0 = 1.0E-8 - c;
        }

        c = u0 / pk_corrected;
        if (c < *alpha) {
          *alpha = c;
          *constrType = 4;
          *constrIdx = ix + 1;
          *newBlocking = true;
          p_max = std::abs(pk_corrected);
        }
      }
    }

    i = workingset_indexLB[workingset_sizes[3] - 1] - 1;
    if ((-solution_searchDir[i] > denomTol) && (!workingset_isActiveConstr
         [(workingset_isActiveIdx[3] + workingset_sizes[3]) - 2])) {
      ratio_tmp = -solution_xstar[i] - workingset_lb[i];
      c = ratio_tmp - *toldelta;
      u0 = std::abs(c);
      if ((!(u0 < 1.0E-8 - c)) && (!rtIsNaN(1.0E-8 - c))) {
        u0 = 1.0E-8 - c;
      }

      c = u0 / -solution_searchDir[i];
      if ((c <= *alpha) && (std::abs(solution_searchDir[i]) > p_max)) {
        *alpha = c;
        *constrType = 4;
        *constrIdx = workingset_sizes[3];
        *newBlocking = true;
      }

      u0 = std::abs(ratio_tmp);
      if ((!(u0 < 1.0E-8 - ratio_tmp)) && (!rtIsNaN(1.0E-8 - ratio_tmp))) {
        u0 = 1.0E-8 - ratio_tmp;
      }

      c = u0 / -solution_searchDir[i];
      if (c < *alpha) {
        *alpha = c;
        *constrType = 4;
        *constrIdx = workingset_sizes[3];
        *newBlocking = true;
        p_max = std::abs(solution_searchDir[i]);
      }
    }
  }

  if (workingset_nWConstr[4] < workingset_sizes[4]) {
    phaseOneCorrectionX = 0.0 * solution_xstar[workingset_nVar - 1];
    phaseOneCorrectionP = 0.0 * solution_searchDir[workingset_nVar - 1];
    for (ix = 0; ix < totalUB; ix++) {
      pk_corrected = solution_searchDir[workingset_indexUB[ix] - 1] -
        phaseOneCorrectionP;
      if ((pk_corrected > denomTol) && (!workingset_isActiveConstr
           [(workingset_isActiveIdx[4] + ix) - 1])) {
        ratio_tmp = solution_xstar[workingset_indexUB[ix] - 1] -
          workingset_ub[workingset_indexUB[ix] - 1];
        c = (ratio_tmp - *toldelta) - phaseOneCorrectionX;
        u0 = std::abs(c);
        if ((!(u0 < 1.0E-8 - c)) && (!rtIsNaN(1.0E-8 - c))) {
          u0 = 1.0E-8 - c;
        }

        c = u0 / pk_corrected;
        if ((c <= *alpha) && (std::abs(pk_corrected) > p_max)) {
          *alpha = c;
          *constrType = 5;
          *constrIdx = ix + 1;
          *newBlocking = true;
        }

        c = ratio_tmp - phaseOneCorrectionX;
        u0 = std::abs(c);
        if ((!(u0 < 1.0E-8 - c)) && (!rtIsNaN(1.0E-8 - c))) {
          u0 = 1.0E-8 - c;
        }

        c = u0 / pk_corrected;
        if (c < *alpha) {
          *alpha = c;
          *constrType = 5;
          *constrIdx = ix + 1;
          *newBlocking = true;
          p_max = std::abs(pk_corrected);
        }
      }
    }
  }

  *toldelta += 6.608625846508183E-7;
  if (p_max > 0.0) {
    c = 6.608625846508183E-7 / p_max;
    if (!(*alpha > c)) {
      *alpha = c;
    }
  }

  if ((*newBlocking) && (*alpha > 1.0)) {
    *newBlocking = false;
  }

  if (!(*alpha < 1.0)) {
    *alpha = 1.0;
  }
}

//
// File trailer for ratiotest.cpp
//
// [EOF]
//
