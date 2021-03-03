//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: computeFval_ReuseHx.cpp
//
// MATLAB Coder version            : 5.0
// C/C++ source code generated on  : 09-Oct-2020 15:23:44
//

// Include Files
#include "stdafx.h"
#include "computeFval_ReuseHx.h"
#include "GetFphi.h"
#include "Getintput_u.h"
#include "rt_nonfinite.h"
#include <cstring>

// Function Definitions

//
// Arguments    : const g_struct_T *obj
//                double workspace[903]
//                const double f[20]
//                const double x[21]
// Return Type  : double
//
double computeFval_ReuseHx(const g_struct_T *obj, double workspace[903], const
  double f[20], const double x[21])
{
  double val;
  switch (obj->objtype) {
   case 5:
    val = obj->gammaScalar * x[obj->nvar - 1];
    break;

   case 3:
    {
      if (obj->hasLinear) {
        int ixlast;
        int k;
        ixlast = obj->nvar;
        for (k = 0; k < ixlast; k++) {
          workspace[k] = 0.5 * obj->Hx[k] + f[k];
        }

        val = 0.0;
        if (obj->nvar >= 1) {
          ixlast = obj->nvar;
          for (k = 0; k < ixlast; k++) {
            val += x[k] * workspace[k];
          }
        }
      } else {
        val = 0.0;
        if (obj->nvar >= 1) {
          int ixlast;
          ixlast = obj->nvar;
          for (int k = 0; k < ixlast; k++) {
            val += x[k] * obj->Hx[k];
          }
        }

        val *= 0.5;
      }
    }
    break;

   default:
    {
      if (obj->hasLinear) {
        int ixlast;
        int k;
        ixlast = obj->nvar;
        if (0 <= ixlast - 1) {
          std::memcpy(&workspace[0], &f[0], ixlast * sizeof(double));
        }

        ixlast = 19 - obj->nvar;
        for (k = 0; k <= ixlast; k++) {
          workspace[obj->nvar + k] = 0.0;
        }

        val = 0.0;
        for (k = 0; k < 20; k++) {
          workspace[k] += 0.5 * obj->Hx[k];
          val += x[k] * workspace[k];
        }
      } else {
        int ixlast;
        int k;
        val = 0.0;
        for (k = 0; k < 20; k++) {
          val += x[k] * obj->Hx[k];
        }

        val *= 0.5;
        ixlast = obj->nvar + 1;
        for (k = ixlast; k < 21; k++) {
          val += x[k - 1] * 0.0;
        }
      }
    }
    break;
  }

  return val;
}

//
// File trailer for computeFval_ReuseHx.cpp
//
// [EOF]
//
