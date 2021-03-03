//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: maxConstraintViolation.cpp
//
// MATLAB Coder version            : 5.0
// C/C++ source code generated on  : 09-Oct-2020 15:23:44
//

// Include Files
#include "stdafx.h"
#include "maxConstraintViolation.h"
#include "GetFphi.h"
#include "Getintput_u.h"
#include "rt_nonfinite.h"
#include <cmath>

// Function Definitions

//
// Arguments    : e_struct_T *obj
//                const double x[21]
// Return Type  : double
//
double maxConstraintViolation(e_struct_T *obj, const double x[21])
{
  double v;
  int mLB;
  int mUB;
  int mFixed;
  int ix;
  double c;
  int idx;
  mLB = obj->sizes[3];
  mUB = obj->sizes[4];
  mFixed = obj->sizes[0];
  switch (obj->probType) {
   case 2:
    {
      int ia;
      v = 0.0;
      obj->maxConstrWorkspace[0] = obj->bineq[0];
      obj->maxConstrWorkspace[0] = -obj->maxConstrWorkspace[0];
      obj->maxConstrWorkspace[1] = obj->bineq[1];
      obj->maxConstrWorkspace[1] = -obj->maxConstrWorkspace[1];
      ix = 0;
      c = 0.0;
      for (ia = 1; ia < 21; ia++) {
        c += obj->Aineq[ia - 1] * x[ix];
        ix++;
      }

      obj->maxConstrWorkspace[0] += c;
      ix = 0;
      c = 0.0;
      for (ia = 22; ia < 42; ia++) {
        c += obj->Aineq[ia - 1] * x[ix];
        ix++;
      }

      obj->maxConstrWorkspace[1] += c;
      obj->maxConstrWorkspace[0] -= x[20];
      if ((!(0.0 > obj->maxConstrWorkspace[0])) && (!rtIsNaN
           (obj->maxConstrWorkspace[0]))) {
        v = obj->maxConstrWorkspace[0];
      }

      obj->maxConstrWorkspace[1] -= x[20];
      if ((!(v > obj->maxConstrWorkspace[1])) && (!rtIsNaN
           (obj->maxConstrWorkspace[1]))) {
        v = obj->maxConstrWorkspace[1];
      }
    }
    break;

   default:
    {
      int ia;
      v = 0.0;
      obj->maxConstrWorkspace[0] = obj->bineq[0];
      obj->maxConstrWorkspace[0] = -obj->maxConstrWorkspace[0];
      obj->maxConstrWorkspace[1] = obj->bineq[1];
      obj->maxConstrWorkspace[1] = -obj->maxConstrWorkspace[1];
      ix = 0;
      c = 0.0;
      idx = obj->nVar;
      for (ia = 1; ia <= idx; ia++) {
        c += obj->Aineq[ia - 1] * x[ix];
        ix++;
      }

      obj->maxConstrWorkspace[0] += c;
      ix = 0;
      c = 0.0;
      idx = obj->nVar + 21;
      for (ia = 22; ia <= idx; ia++) {
        c += obj->Aineq[ia - 1] * x[ix];
        ix++;
      }

      obj->maxConstrWorkspace[1] += c;
      if ((!(0.0 > obj->maxConstrWorkspace[0])) && (!rtIsNaN
           (obj->maxConstrWorkspace[0]))) {
        v = obj->maxConstrWorkspace[0];
      }

      if ((!(v > obj->maxConstrWorkspace[1])) && (!rtIsNaN
           (obj->maxConstrWorkspace[1]))) {
        v = obj->maxConstrWorkspace[1];
      }
    }
    break;
  }

  if (obj->sizes[3] > 0) {
    for (idx = 0; idx < mLB; idx++) {
      c = -x[obj->indexLB[idx] - 1] - obj->lb[obj->indexLB[idx] - 1];
      if ((!(v > c)) && (!rtIsNaN(c))) {
        v = c;
      }
    }
  }

  if (obj->sizes[4] > 0) {
    for (idx = 0; idx < mUB; idx++) {
      c = x[obj->indexUB[idx] - 1] - obj->ub[obj->indexUB[idx] - 1];
      if ((!(v > c)) && (!rtIsNaN(c))) {
        v = c;
      }
    }
  }

  if (obj->sizes[0] > 0) {
    for (idx = 0; idx < mFixed; idx++) {
      ix = obj->indexFixed[idx] - 1;
      c = std::abs(x[ix] - obj->ub[ix]);
      if ((!(v > c)) && (!rtIsNaN(c))) {
        v = c;
      }
    }
  }

  return v;
}

//
// File trailer for maxConstraintViolation.cpp
//
// [EOF]
//
