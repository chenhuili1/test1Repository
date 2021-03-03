//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: computeGrad_StoreHx.cpp
//
// MATLAB Coder version            : 5.0
// C/C++ source code generated on  : 09-Oct-2020 15:23:44
//

// Include Files
#include "stdafx.h"
#include "computeGrad_StoreHx.h"
#include "GetFphi.h"
#include "Getintput_u.h"
#include "rt_nonfinite.h"
#include <cstring>

// Function Definitions

//
// Arguments    : g_struct_T *obj
//                const double H[400]
//                const double f[20]
//                const double x[21]
// Return Type  : void
//
void computeGrad_StoreHx(g_struct_T *obj, const double H[400], const double f[20],
  const double x[21])
{
  int iac;
  switch (obj->objtype) {
   case 5:
    {
      int i;
      i = obj->nvar;
      if (0 <= i - 2) {
        std::memset(&obj->grad[0], 0, (i + -1) * sizeof(double));
      }

      obj->grad[obj->nvar - 1] = obj->gammaScalar;
    }
    break;

   case 3:
    {
      int m_tmp_tmp;
      int i;
      int lda;
      m_tmp_tmp = obj->nvar - 1;
      lda = obj->nvar;
      if (obj->nvar != 0) {
        int ix;
        if (0 <= m_tmp_tmp) {
          std::memset(&obj->Hx[0], 0, (m_tmp_tmp + 1) * sizeof(double));
        }

        ix = 0;
        i = obj->nvar * (obj->nvar - 1) + 1;
        for (iac = 1; lda < 0 ? iac >= i : iac <= i; iac += lda) {
          int iy;
          int i1;
          iy = 0;
          i1 = iac + m_tmp_tmp;
          for (int ia = iac; ia <= i1; ia++) {
            obj->Hx[iy] += H[ia - 1] * x[ix];
            iy++;
          }

          ix++;
        }
      }

      i = obj->nvar;
      if (0 <= i - 1) {
        std::memcpy(&obj->grad[0], &obj->Hx[0], i * sizeof(double));
      }

      if (obj->hasLinear && (obj->nvar >= 1)) {
        i = obj->nvar - 1;
        for (m_tmp_tmp = 0; m_tmp_tmp <= i; m_tmp_tmp++) {
          obj->grad[m_tmp_tmp] += f[m_tmp_tmp];
        }
      }
    }
    break;

   default:
    {
      int m_tmp_tmp;
      int i;
      int lda;
      m_tmp_tmp = obj->nvar - 1;
      lda = obj->nvar;
      if (obj->nvar != 0) {
        int ix;
        if (0 <= m_tmp_tmp) {
          std::memset(&obj->Hx[0], 0, (m_tmp_tmp + 1) * sizeof(double));
        }

        ix = 0;
        i = obj->nvar * (obj->nvar - 1) + 1;
        for (iac = 1; lda < 0 ? iac >= i : iac <= i; iac += lda) {
          int iy;
          int i1;
          iy = 0;
          i1 = iac + m_tmp_tmp;
          for (int ia = iac; ia <= i1; ia++) {
            obj->Hx[iy] += H[ia - 1] * x[ix];
            iy++;
          }

          ix++;
        }
      }

      i = obj->nvar + 1;
      for (m_tmp_tmp = i; m_tmp_tmp < 21; m_tmp_tmp++) {
        obj->Hx[m_tmp_tmp - 1] = 0.0 * x[m_tmp_tmp - 1];
      }

      std::memcpy(&obj->grad[0], &obj->Hx[0], 20U * sizeof(double));
      if (obj->hasLinear && (obj->nvar >= 1)) {
        i = obj->nvar - 1;
        for (m_tmp_tmp = 0; m_tmp_tmp <= i; m_tmp_tmp++) {
          obj->grad[m_tmp_tmp] += f[m_tmp_tmp];
        }
      }
    }
    break;
  }
}

//
// File trailer for computeGrad_StoreHx.cpp
//
// [EOF]
//
