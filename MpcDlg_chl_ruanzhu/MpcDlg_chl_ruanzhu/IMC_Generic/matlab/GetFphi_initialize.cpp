//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: GetFphi_initialize.cpp
//
// MATLAB Coder version            : 5.0
// C/C++ source code generated on  : 09-Oct-2020 15:23:44
//

// Include Files
#include "stdafx.h"
#include "GetFphi_initialize.h"
#include "GetFphi.h"
#include "GetFphi_data.h"
#include "Getintput_u.h"
#include "rt_nonfinite.h"

// Function Definitions

//
// Arguments    : void
// Return Type  : void
//
void GetFphi_initialize()
{
  rt_InitInfAndNaN();
  isInitialized_GetFphi = true;
}

//
// File trailer for GetFphi_initialize.cpp
//
// [EOF]
//
