//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: computeFirstOrderOpt.cpp
//
// MATLAB Coder version            : 5.0
// C/C++ source code generated on  : 09-Oct-2020 15:23:44
//

// Include Files
#include "stdafx.h"
#include "computeFirstOrderOpt.h"
#include "GetFphi.h"
#include "Getintput_u.h"
#include "rt_nonfinite.h"
#include <cmath>
#include <cstring>

// Function Definitions

//
// Arguments    : struct_T *solution
//                const g_struct_T *objective
//                int workingset_nVar
//                const double workingset_ATwset[903]
//                int workingset_nActiveConstr
//                double workspace[903]
// Return Type  : void
//
void computeFirstOrderOpt(struct_T *solution, const g_struct_T *objective, int
  workingset_nVar, const double workingset_ATwset[903], int
  workingset_nActiveConstr, double workspace[903])
{
  int ix;
  int idxmax;
  int iac;
  double smax;
  int iy;
  if (0 <= workingset_nVar - 1) {
    std::memcpy(&workspace[0], &objective->grad[0], workingset_nVar * sizeof
                (double));
  }

  if (workingset_nActiveConstr != 0) {
    ix = 0;
    idxmax = 21 * (workingset_nActiveConstr - 1) + 1;
    for (iac = 1; iac <= idxmax; iac += 21) {
      int i;
      iy = 0;
      i = (iac + workingset_nVar) - 1;
      for (int ia = iac; ia <= i; ia++) {
        workspace[iy] += workingset_ATwset[ia - 1] * solution->lambda[ix];
        iy++;
      }

      ix++;
    }
  }

  idxmax = 1;
  ix = 0;
  smax = std::abs(workspace[0]);
  for (iy = 2; iy <= workingset_nVar; iy++) {
    double s;
    ix++;
    s = std::abs(workspace[ix]);
    if (s > smax) {
      idxmax = iy;
      smax = s;
    }
  }

  solution->firstorderopt = std::abs(workspace[idxmax - 1]);
}

//
// File trailer for computeFirstOrderOpt.cpp
//
// [EOF]
//
