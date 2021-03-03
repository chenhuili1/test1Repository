//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: addBoundToActiveSetMatrix_.cpp
//
// MATLAB Coder version            : 5.0
// C/C++ source code generated on  : 09-Oct-2020 15:23:44
//

// Include Files
#include "stdafx.h"
#include "addBoundToActiveSetMatrix_.h"
#include "GetFphi.h"
#include "Getintput_u.h"
#include "rt_nonfinite.h"
#include <cstring>

// Function Definitions

//
// Arguments    : e_struct_T *obj
//                int TYPE
//                int idx_local
// Return Type  : void
//
void addBoundToActiveSetMatrix_(e_struct_T *obj, int TYPE, int idx_local)
{
  int i;
  int idx_bnd_local;
  int i1;
  obj->nWConstr[TYPE - 1]++;
  obj->isActiveConstr[(obj->isActiveIdx[TYPE - 1] + idx_local) - 2] = true;
  obj->nActiveConstr++;
  obj->Wid[obj->nActiveConstr - 1] = TYPE;
  obj->Wlocalidx[obj->nActiveConstr - 1] = idx_local;
  i = obj->nActiveConstr - 1;
  switch (TYPE) {
   case 5:
    idx_bnd_local = obj->indexUB[idx_local - 1];
    obj->bwset[obj->nActiveConstr - 1] = obj->ub[idx_bnd_local - 1];
    break;

   default:
    idx_bnd_local = obj->indexLB[idx_local - 1];
    obj->bwset[obj->nActiveConstr - 1] = obj->lb[idx_bnd_local - 1];
    break;
  }

  if (0 <= idx_bnd_local - 2) {
    std::memset(&obj->ATwset[i * 21], 0, (((idx_bnd_local + i * 21) - i * 21) +
      -1) * sizeof(double));
  }

  obj->ATwset[(idx_bnd_local + 21 * (obj->nActiveConstr - 1)) - 1] = 2.0 *
    static_cast<double>(TYPE == 5) - 1.0;
  idx_bnd_local++;
  i1 = obj->nVar;
  if (idx_bnd_local <= i1) {
    std::memset(&obj->ATwset[(idx_bnd_local + i * 21) + -1], 0, ((((i1 + i * 21)
      - idx_bnd_local) - i * 21) + 1) * sizeof(double));
  }

  switch (obj->probType) {
   case 3:
   case 2:
    break;

   default:
    obj->ATwset[(obj->nVar + 21 * (obj->nActiveConstr - 1)) - 1] = -1.0;
    break;
  }
}

//
// File trailer for addBoundToActiveSetMatrix_.cpp
//
// [EOF]
//
