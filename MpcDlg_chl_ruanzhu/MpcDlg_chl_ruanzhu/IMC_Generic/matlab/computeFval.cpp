//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: computeFval.cpp
//
// MATLAB Coder version            : 5.0
// C/C++ source code generated on  : 09-Oct-2020 15:23:44
//

// Include Files
#include "stdafx.h"
#include "computeFval.h"
#include "GetFphi.h"
#include "Getintput_u.h"
#include "rt_nonfinite.h"
#include <cstring>

// Function Definitions

//
// Arguments    : const g_struct_T *obj
//                double workspace[903]
//                const double H[400]
//                const double f[20]
//                const double x[21]
// Return Type  : double
//
double computeFval(const g_struct_T *obj, double workspace[903], const double H
                   [400], const double f[20], const double x[21])
{
  double val;
  int iac;
  switch (obj->objtype) {
   case 5:
    val = x[obj->nvar - 1];
    break;

   case 3:
    {
      int i;
      int ixlast;
      int ix;
      i = obj->nvar;
      if (0 <= i - 1) {
        std::memcpy(&workspace[0], &f[0], i * sizeof(double));
      }

      ixlast = obj->nvar;
      ix = 0;
      i = obj->nvar * (obj->nvar - 1) + 1;
      for (iac = 1; ixlast < 0 ? iac >= i : iac <= i; iac += ixlast) {
        double c;
        int iy;
        int i1;
        c = 0.5 * x[ix];
        iy = 0;
        i1 = (iac + obj->nvar) - 1;
        for (int ia = iac; ia <= i1; ia++) {
          workspace[iy] += H[ia - 1] * c;
          iy++;
        }

        ix++;
      }

      val = 0.0;
      if (obj->nvar >= 1) {
        ixlast = obj->nvar;
        for (ix = 0; ix < ixlast; ix++) {
          val += x[ix] * workspace[ix];
        }
      }
    }
    break;

   default:
    {
      int i;
      int ixlast;
      int ix;
      i = obj->nvar;
      if (0 <= i - 1) {
        std::memcpy(&workspace[0], &f[0], i * sizeof(double));
      }

      ixlast = obj->nvar;
      ix = 0;
      i = obj->nvar * (obj->nvar - 1) + 1;
      for (iac = 1; ixlast < 0 ? iac >= i : iac <= i; iac += ixlast) {
        double c;
        int iy;
        int i1;
        c = 0.5 * x[ix];
        iy = 0;
        i1 = (iac + obj->nvar) - 1;
        for (int ia = iac; ia <= i1; ia++) {
          workspace[iy] += H[ia - 1] * c;
          iy++;
        }

        ix++;
      }

      i = obj->nvar + 1;
      for (ixlast = i; ixlast < 21; ixlast++) {
        workspace[ixlast - 1] = 0.0 * x[ixlast - 1];
      }

      val = 0.0;
      for (ix = 0; ix < 20; ix++) {
        val += x[ix] * workspace[ix];
      }
    }
    break;
  }

  return val;
}

//
// File trailer for computeFval.cpp
//
// [EOF]
//
