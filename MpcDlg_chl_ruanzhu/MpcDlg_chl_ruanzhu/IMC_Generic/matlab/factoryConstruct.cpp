//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: factoryConstruct.cpp
//
// MATLAB Coder version            : 5.0
// C/C++ source code generated on  : 09-Oct-2020 15:23:44
//

// Include Files
#include "stdafx.h"
#include "factoryConstruct.h"
#include "GetFphi.h"
#include "Getintput_u.h"
#include "rt_nonfinite.h"
#include <cstring>

// Function Definitions

//
// Arguments    : const double bineq[2]
//                int mLB
//                const double lb[20]
//                const int indexLB[20]
//                int mUB
//                const double ub[20]
//                const int indexUB[20]
//                int mFixed
//                const int indexFixed[20]
//                e_struct_T *obj
// Return Type  : void
//
void factoryConstruct(const double bineq[2], int mLB, const double lb[20], const
                      int indexLB[20], int mUB, const double ub[20], const int
                      indexUB[20], int mFixed, const int indexFixed[20],
                      e_struct_T *obj)
{
  int k;
  int obj_tmp[5];
  int b_obj_tmp[6];
  static const signed char Aineq[40] = { 1, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0 };

  k = ((mLB + mUB) + mFixed) + 2;
  obj->mConstr = k;
  obj->mConstrOrig = k;
  obj->mConstrMax = 43;
  obj->nVar = 20;
  obj->nVarOrig = 20;
  obj->nVarMax = 21;
  obj->ldA = 21;
  obj->mEqRemoved = 0;
  obj->nActiveConstr = 0;
  obj_tmp[0] = mFixed;
  obj_tmp[1] = 0;
  obj_tmp[2] = 2;
  obj_tmp[3] = mLB;
  obj_tmp[4] = mUB;
  obj->sizesPhaseOne[0] = mFixed;
  obj->sizesPhaseOne[1] = 0;
  obj->sizesPhaseOne[2] = 2;
  obj->sizesPhaseOne[3] = mLB + 1;
  obj->sizesPhaseOne[4] = mUB;
  obj->sizesRegularized[0] = mFixed;
  obj->sizesRegularized[1] = 0;
  obj->sizesRegularized[2] = 2;
  obj->sizesRegularized[3] = mLB + 2;
  obj->sizesRegularized[4] = mUB;
  obj->sizesRegPhaseOne[0] = mFixed;
  obj->sizesRegPhaseOne[1] = 0;
  obj->sizesRegPhaseOne[2] = 2;
  obj->sizesRegPhaseOne[3] = mLB + 3;
  obj->sizesRegPhaseOne[4] = mUB;
  b_obj_tmp[0] = 1;
  b_obj_tmp[1] = mFixed;
  b_obj_tmp[2] = 0;
  b_obj_tmp[3] = 2;
  b_obj_tmp[4] = mLB;
  b_obj_tmp[5] = mUB;
  for (k = 0; k < 5; k++) {
    obj->sizes[k] = obj_tmp[k];
    obj->sizesNormal[k] = obj_tmp[k];
    b_obj_tmp[k + 1] += b_obj_tmp[k];
  }

  for (k = 0; k < 6; k++) {
    obj->isActiveIdx[k] = b_obj_tmp[k];
    obj->isActiveIdxNormal[k] = b_obj_tmp[k];
  }

  b_obj_tmp[0] = 1;
  b_obj_tmp[1] = mFixed;
  b_obj_tmp[2] = 0;
  b_obj_tmp[3] = 2;
  b_obj_tmp[4] = mLB + 1;
  b_obj_tmp[5] = mUB;
  for (k = 0; k < 5; k++) {
    b_obj_tmp[k + 1] += b_obj_tmp[k];
  }

  for (k = 0; k < 6; k++) {
    obj->isActiveIdxPhaseOne[k] = b_obj_tmp[k];
  }

  b_obj_tmp[0] = 1;
  b_obj_tmp[1] = mFixed;
  b_obj_tmp[2] = 0;
  b_obj_tmp[3] = 2;
  b_obj_tmp[4] = mLB + 2;
  b_obj_tmp[5] = mUB;
  for (k = 0; k < 5; k++) {
    b_obj_tmp[k + 1] += b_obj_tmp[k];
  }

  for (k = 0; k < 6; k++) {
    obj->isActiveIdxRegularized[k] = b_obj_tmp[k];
  }

  b_obj_tmp[0] = 1;
  b_obj_tmp[1] = mFixed;
  b_obj_tmp[2] = 0;
  b_obj_tmp[3] = 2;
  b_obj_tmp[4] = mLB + 3;
  b_obj_tmp[5] = mUB;
  for (k = 0; k < 5; k++) {
    b_obj_tmp[k + 1] += b_obj_tmp[k];
  }

  for (k = 0; k < 6; k++) {
    obj->isActiveIdxRegPhaseOne[k] = b_obj_tmp[k];
  }

  for (k = 0; k < 5; k++) {
    obj->nWConstr[k] = 0;
  }

  obj->probType = 3;
  obj->SLACK0 = 1.0E-5;
  for (k = 0; k < 2; k++) {
    for (int idx_row = 0; idx_row < 20; idx_row++) {
      obj->Aineq[idx_row + 21 * k] = Aineq[k + (idx_row << 1)];
    }

    obj->bineq[k] = bineq[k];
  }

  for (k = 0; k < 20; k++) {
    obj->lb[k] = -lb[k];
    obj->ub[k] = ub[k];
  }

  if (0 <= mLB - 1) {
    std::memcpy(&obj->indexLB[0], &indexLB[0], mLB * sizeof(int));
  }

  if (0 <= mUB - 1) {
    std::memcpy(&obj->indexUB[0], &indexUB[0], mUB * sizeof(int));
  }

  if (0 <= mFixed - 1) {
    std::memcpy(&obj->indexFixed[0], &indexFixed[0], mFixed * sizeof(int));
  }
}

//
// File trailer for factoryConstruct.cpp
//
// [EOF]
//
