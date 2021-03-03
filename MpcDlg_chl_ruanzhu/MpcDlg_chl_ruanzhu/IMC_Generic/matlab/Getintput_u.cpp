//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: Getintput_u.cpp
//
// MATLAB Coder version            : 5.0
// C/C++ source code generated on  : 09-Oct-2020 15:23:44
//

// Include Files
#include "stdafx.h"
#include "Getintput_u.h"
#include "GetFphi.h"
#include "GetFphi_data.h"
#include "GetFphi_initialize.h"
#include "quadprog.h"
#include "rt_nonfinite.h"
#include "coder_array.h"
#include <cmath>
#include <cstring>

// Function Definitions

//
// MPCMODE 此处显示有关此函数的摘要
//    此处显示详细说明
// Arguments    : const double F[320]
//                const double phi[1600]
//                const double Yreal[4]
//                const double yref[4]
//                const double r[2]
//                double T
//                const double init_parm[7]
// Return Type  : double
//
double Getintput_u(const double F[320], const double phi[1600], const double
                   Yreal[4], const double yref[4], const double r[2], double T,int k,
                   const double init_parm[7])
{
  double M;
  double C;
  double R_idx_0;
  double R_idx_1;
  double R_idx_2;
  double a_max;
  double Rs[80];
  double i;
  double lb_tmp;
  int j;
  int b_i;
  double dv[400];
  double dv1[20];
  double lb[20];
  double ub[20];
  double U[20];
  double b_Rs[80];
  double y_tmp[1600];
  if (!isInitialized_GetFphi) {
    GetFphi_initialize();
  }

  M = init_parm[1];

  //
  C = init_parm[5] * std::exp(-init_parm[4] * (k*T *k* T));
  R_idx_0 = C * Yreal[0] + (1.0 - C) * yref[0];
  R_idx_1 = C * Yreal[1] + (1.0 - C) * yref[1];
  R_idx_2 = C * Yreal[2] + (1.0 - C) * yref[2];
  C = C * Yreal[3] + (1.0 - C) * yref[3];
  a_max = std::sqrt(init_parm[2] * init_parm[3]) / T * (init_parm[6] - std::sqrt
    (Yreal[1] * Yreal[1] + init_parm[2] / init_parm[3] * (Yreal[3] * Yreal[3])));
  std::memset(&Rs[0], 0, 80U * sizeof(double));
  i = 1.0;
  lb_tmp = init_parm[0] * init_parm[3] * Yreal[1];
  for (j = 0; j < 20; j++) {
    Rs[static_cast<int>(i) - 1] = R_idx_0;
    Rs[static_cast<int>(i + 1.0) - 1] = R_idx_1;
    Rs[static_cast<int>(i + 2.0) - 1] = R_idx_2;
    Rs[static_cast<int>(i + 3.0) - 1] = C;
    i += 4.0;
    lb[j] = std::sqrt(init_parm[2] * init_parm[3]) / T * (-init_parm[6] - std::sqrt
    (Yreal[1] * Yreal[1] + init_parm[2] / init_parm[3] * (Yreal[3] * Yreal[3])));;
    ub[j] = a_max;
  }

  // 标准二次规划问题
  for (j = 0; j < 80; j++) {
    for (b_i = 0; b_i < 20; b_i++) {
      y_tmp[b_i + 20 * j] = phi[j + 80 * b_i];
    }

    b_Rs[j] = Rs[j] - (((F[j] * Yreal[0] + F[j + 80] * Yreal[1]) + F[j + 160] *
                        Yreal[2]) + F[j + 240] * Yreal[3]);
  }

  for (j = 0; j < 20; j++) {
    for (b_i = 0; b_i < 20; b_i++) {
      C = 0.0;
      for (int i1 = 0; i1 < 80; i1++) {
        C += 2.0 * y_tmp[j + 20 * i1] * phi[i1 + 80 * b_i];
      }

      dv[j + 20 * b_i] = C;
    }

    C = 0.0;
    for (b_i = 0; b_i < 80; b_i++) {
      C += -2.0 * y_tmp[j + 20 * b_i] * b_Rs[b_i];
    }

    dv1[j] = C;
  }

  quadprog(dv, dv1, r, lb, ub, U);
  return U[0];
}

//
// File trailer for Getintput_u.cpp
//
// [EOF]
//
// MPCMODE 此处显示有关此函数的摘要
//    此处显示详细说明
// Arguments    : const double F[320]
//                const double phi[1600]
//                const double Yreal[4]
//                double a_stop
//                const double r[2]
//                double T
//                double k
//                double Y0
//                const double init_parm_data[]
//                const int init_parm_size[2]
// Return Type  : double
 double GetStop_u(const double F[320], const double phi[1600], const double
                 Yreal[4], double a_stop, const double r[2], const double Y0[4],
                 double T, double k, const double init_parm_data[4])
{
  double N;
  signed char Q[6400];
  int j;
  int i;
  coder::array<double, 2U> Xout;
  int loop_ub;
  double x;
  double a_max_tmp;
  double b_a_max_tmp;
  double a_max;
  double Rs[80];
  double b_i;
  double d;
  double y_tmp[1600];
  double dv[400];
  double dv1[20];
  double lb[20];
  double ub[20];
  double U[20];
  double b_Rs[80];
  double dv2[1600];
  if (!isInitialized_GetFphi) {
    GetFphi_initialize();
  }
  N = init_parm_data[3];
  std::memset(&Q[0], 0, 6400U * sizeof(signed char));
  for (j = 0; j < 80; j++) {
    if (std::fmod(static_cast<double>(j) + 1.0, 4.0) != 1.0) {
      Q[j + 80 * j] = 1;
    }
  }

  i = static_cast<int>(init_parm_data[3]);
  Xout.set_size(i, 4);
  loop_ub = i << 2;
  for (j = 0; j < loop_ub; j++) {
    Xout[j] = 0.0;
  }

  for (loop_ub = 0; loop_ub < i; loop_ub++) {
	  x = std::tanh(a_stop * (((static_cast<double>(loop_ub) + 1.0) - 1.0) * T));
	  if(Xout[loop_ub + Xout.size(0) * 2]<=0.002)
		Xout[loop_ub + Xout.size(0) * 2]=0;
	  else
		 Xout[loop_ub + Xout.size(0) * 2] = Y0[2] * (1.0 - x);

	  if(Xout[loop_ub + Xout.size(0)]<=0.002)
		Xout[loop_ub + Xout.size(0)]=0;
	  else
		 Xout[loop_ub + Xout.size(0)] = Y0[1] * (1.0 - x)*5;

	  if(Xout[loop_ub + Xout.size(0) * 3]<=0.003)
		Xout[loop_ub + Xout.size(0) * 3]=0;
	  else
		 Xout[loop_ub + Xout.size(0) * 3] = Y0[3] * (1.0 - x);


  }

  a_max_tmp = std::sqrt(Yreal[1] * Yreal[1] + init_parm_data[0] /
                        init_parm_data[1] * (Yreal[3] * Yreal[3]));
  b_a_max_tmp = std::sqrt(init_parm_data[0] * init_parm_data[1]) / T;
  a_max = b_a_max_tmp * (init_parm_data[2] - a_max_tmp);
  std::memset(&Rs[0], 0, 80U * sizeof(double));
  b_i = 1.0;
  for (j = 0; j < 20; j++) {
    d = k + (static_cast<double>(j) + 1.0);
    if (d <= N) {
      loop_ub = static_cast<int>(d);
      Rs[static_cast<int>(b_i) - 1] = Xout[loop_ub - 1];
      Rs[static_cast<int>(b_i + 1.0) - 1] = Xout[(loop_ub + Xout.size(0)) - 1];
      Rs[static_cast<int>(b_i + 2.0) - 1] = Xout[(loop_ub + Xout.size(0) * 2) -
        1];
      Rs[static_cast<int>(b_i + 3.0) - 1] = Xout[(loop_ub + Xout.size(0) * 3) -
        1];
    } else {
      loop_ub = i - 1;
      Rs[static_cast<int>(b_i) - 1] = Xout[loop_ub];
      Rs[static_cast<int>(b_i + 1.0) - 1] = Xout[loop_ub + Xout.size(0)];
      Rs[static_cast<int>(b_i + 2.0) - 1] = Xout[loop_ub + Xout.size(0) * 2];
      Rs[static_cast<int>(b_i + 3.0) - 1] = Xout[loop_ub + Xout.size(0) * 3];
    }

    b_i += 4.0;
    lb[j] = b_a_max_tmp * (-init_parm_data[2] - a_max_tmp);
    ub[j] = a_max;
  }

  for (i = 0; i < 80; i++) {
    for (j = 0; j < 20; j++) {
      y_tmp[j + 20 * i] = phi[i + 80 * j];
    }
  }

  // 标准二次规划问题
  for (i = 0; i < 20; i++) {
    for (j = 0; j < 80; j++) {
      d = 0.0;
      for (loop_ub = 0; loop_ub < 80; loop_ub++) {
        d += 2.0 * y_tmp[i + 20 * loop_ub] * static_cast<double>(Q[loop_ub + 80 *
          j]);
      }

      dv2[i + 20 * j] = d;
    }
  }

  for (i = 0; i < 80; i++) {
    d = 0.0;
    for (j = 0; j < 4; j++) {
      N = 0.0;
      for (loop_ub = 0; loop_ub < 80; loop_ub++) {
        N += static_cast<double>(Q[i + 80 * loop_ub]) * F[loop_ub + 80 * j];
      }

      d += N * Yreal[j];
    }

    b_Rs[i] = Rs[i] - d;
  }

  for (i = 0; i < 20; i++) {
    for (j = 0; j < 20; j++) {
      d = 0.0;
      for (loop_ub = 0; loop_ub < 80; loop_ub++) {
        d += dv2[i + 20 * loop_ub] * phi[loop_ub + 80 * j];
      }

      dv[i + 20 * j] = d;
    }

    d = 0.0;
    for (j = 0; j < 80; j++) {
      d += -2.0 * y_tmp[i + 20 * j] * b_Rs[j];
    }

    dv1[i] = d;
  }

  quadprog(dv, dv1, r, lb, ub, U);
  return U[0];
}