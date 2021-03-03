//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: removeEqConstr.cpp
//
// MATLAB Coder version            : 5.0
// C/C++ source code generated on  : 09-Oct-2020 15:23:44
//

// Include Files
#include "stdafx.h"
#include "removeEqConstr.h"
#include "GetFphi.h"
#include "Getintput_u.h"
#include "rt_nonfinite.h"

// Function Definitions

//
// Arguments    : e_struct_T *obj
//                int idx_global
// Return Type  : void
//
void removeEqConstr(e_struct_T *obj, int idx_global)
{
  int totalEq;
  totalEq = (obj->nWConstr[0] + obj->nWConstr[1]) - 1;
  if ((totalEq + 1 != 0) && (idx_global <= totalEq + 1)) {
    if ((obj->nActiveConstr == totalEq + 1) || (idx_global == totalEq + 1)) {
      int i;
      obj->mEqRemoved++;
      totalEq = obj->Wid[idx_global - 1] - 1;
      obj->isActiveConstr[(obj->isActiveIdx[totalEq] + obj->Wlocalidx[idx_global
                           - 1]) - 2] = false;
      obj->Wid[idx_global - 1] = obj->Wid[obj->nActiveConstr - 1];
      obj->Wlocalidx[idx_global - 1] = obj->Wlocalidx[obj->nActiveConstr - 1];
      i = obj->nVar;
      for (int idx = 0; idx < i; idx++) {
        obj->ATwset[idx + 21 * (idx_global - 1)] = obj->ATwset[idx + 21 *
          (obj->nActiveConstr - 1)];
      }

      obj->bwset[idx_global - 1] = obj->bwset[obj->nActiveConstr - 1];
      obj->nActiveConstr--;
      obj->nWConstr[totalEq]--;
    } else {
      int TYPE_tmp_tmp;
      int i;
      int idx;
      obj->mEqRemoved++;
      TYPE_tmp_tmp = obj->Wid[idx_global - 1] - 1;
      obj->isActiveConstr[(obj->isActiveIdx[TYPE_tmp_tmp] + obj->
                           Wlocalidx[idx_global - 1]) - 2] = false;
      obj->Wid[idx_global - 1] = obj->Wid[totalEq];
      obj->Wlocalidx[idx_global - 1] = obj->Wlocalidx[totalEq];
      i = obj->nVar;
      for (idx = 0; idx < i; idx++) {
        obj->ATwset[idx + 21 * (idx_global - 1)] = obj->ATwset[idx + 21 *
          totalEq];
      }

      obj->bwset[idx_global - 1] = obj->bwset[totalEq];
      obj->Wid[totalEq] = obj->Wid[obj->nActiveConstr - 1];
      obj->Wlocalidx[totalEq] = obj->Wlocalidx[obj->nActiveConstr - 1];
      i = obj->nVar;
      for (idx = 0; idx < i; idx++) {
        obj->ATwset[idx + 21 * totalEq] = obj->ATwset[idx + 21 *
          (obj->nActiveConstr - 1)];
      }

      obj->bwset[totalEq] = obj->bwset[obj->nActiveConstr - 1];
      obj->nActiveConstr--;
      obj->nWConstr[TYPE_tmp_tmp]--;
    }
  }
}

//
// File trailer for removeEqConstr.cpp
//
// [EOF]
//
