//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: setProblemType.cpp
//
// MATLAB Coder version            : 5.0
// C/C++ source code generated on  : 09-Oct-2020 15:23:44
//

// Include Files
#include "stdafx.h"
#include "setProblemType.h"
#include "GetFphi.h"
#include "Getintput_u.h"
#include "rt_nonfinite.h"
#include <cstring>

// Function Definitions

//
// Arguments    : e_struct_T *obj
//                int PROBLEM_TYPE
// Return Type  : void
//
void setProblemType(e_struct_T *obj, int PROBLEM_TYPE)
{
  switch (PROBLEM_TYPE) {
   case 3:
    {
      int i;
      obj->nVar = 20;
      obj->mConstr = obj->mConstrOrig;
      for (i = 0; i < 5; i++) {
        obj->sizes[i] = obj->sizesNormal[i];
      }

      for (i = 0; i < 6; i++) {
        obj->isActiveIdx[i] = obj->isActiveIdxNormal[i];
      }
    }
    break;

   case 1:
    {
      int i;
      int idx;
      int idxStartIneq;
      obj->nVar = 21;
      obj->mConstr = obj->mConstrOrig + 1;
      for (i = 0; i < 5; i++) {
        obj->sizes[i] = obj->sizesPhaseOne[i];
      }

      for (i = 0; i < 6; i++) {
        obj->isActiveIdx[i] = obj->isActiveIdxPhaseOne[i];
      }

      i = obj->sizes[0];
      for (idx = 0; idx < i; idx++) {
        obj->ATwset[21 * idx + 20] = 0.0;
      }

      obj->Aineq[20] = -1.0;
      obj->Aineq[41] = -1.0;
      obj->indexLB[obj->sizes[3] - 1] = 21;
      obj->lb[20] = obj->SLACK0;
      idxStartIneq = obj->isActiveIdx[2];
      i = obj->nActiveConstr;
      for (idx = idxStartIneq; idx <= i; idx++) {
        obj->ATwset[21 * (idx - 1) + 20] = -1.0;
      }
    }
    break;

   case 2:
    {
      int i;
      obj->nVar = 20;
      obj->mConstr = 42;
      for (i = 0; i < 5; i++) {
        obj->sizes[i] = obj->sizesRegularized[i];
      }

      for (i = 0; i < 6; i++) {
        obj->isActiveIdx[i] = obj->isActiveIdxRegularized[i];
      }

      if (obj->probType != 4) {
        int idx;
        int idx_lb;
        int i1;
        int idxStartIneq;
        obj->Aineq[20] = -1.0;
        obj->Aineq[41] = 0.0;
        obj->Aineq[41] = -1.0;
        idx_lb = 20;
        i = obj->sizesNormal[3] + 1;
        i1 = obj->sizesRegularized[3];
        for (idx = i; idx <= i1; idx++) {
          idx_lb++;
          obj->indexLB[idx - 1] = idx_lb;
        }

        obj->lb[20] = 0.0;
        idxStartIneq = obj->isActiveIdx[2];
        i = obj->nActiveConstr;
        for (idx = idxStartIneq; idx <= i; idx++) {
          switch (obj->Wid[idx - 1]) {
           case 3:
            i1 = obj->Wlocalidx[idx - 1] + 19;
            for (idx_lb = 21; idx_lb <= i1; idx_lb++) {
              obj->ATwset[21 * (idx - 1) + 20] = 0.0;
            }

            i1 = 21 * (idx - 1);
            obj->ATwset[(obj->Wlocalidx[idx - 1] + i1) + 19] = -1.0;
            idx_lb = obj->Wlocalidx[idx - 1] + 21;
            if (idx_lb <= 20) {
              std::memset(&obj->ATwset[(idx_lb + i1) + -1], 0, (((i1 - idx_lb) -
                i1) + 21) * sizeof(double));
            }
            break;
          }
        }
      }
    }
    break;

   default:
    {
      int i;
      int idx;
      int idxStartIneq;
      obj->nVar = 21;
      obj->mConstr = 43;
      for (i = 0; i < 5; i++) {
        obj->sizes[i] = obj->sizesRegPhaseOne[i];
      }

      for (i = 0; i < 6; i++) {
        obj->isActiveIdx[i] = obj->isActiveIdxRegPhaseOne[i];
      }

      i = obj->sizes[0];
      for (idx = 0; idx < i; idx++) {
        obj->ATwset[21 * idx + 20] = 0.0;
      }

      obj->Aineq[20] = -1.0;
      obj->Aineq[41] = -1.0;
      obj->indexLB[obj->sizes[3] - 1] = 21;
      obj->lb[20] = obj->SLACK0;
      idxStartIneq = obj->isActiveIdx[2];
      i = obj->nActiveConstr;
      for (idx = idxStartIneq; idx <= i; idx++) {
        obj->ATwset[21 * (idx - 1) + 20] = -1.0;
      }
    }
    break;
  }

  obj->probType = PROBLEM_TYPE;
}

//
// File trailer for setProblemType.cpp
//
// [EOF]
//
