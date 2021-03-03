//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: main.cpp
//
// MATLAB Coder version            : 5.0
// C/C++ source code generated on  : 09-Oct-2020 15:23:44
//

//***********************************************************************
// This automatically generated example C++ main file shows how to call
// entry-point functions that MATLAB Coder generated. You must customize
// this file for your application. Do not modify this file directly.
// Instead, make a copy of this file, modify it, and integrate it into
// your development environment.
//
// This file initializes entry-point function arguments to a default
// size and value before calling the entry-point functions. It does
// not store or use any values returned from the entry-point functions.
// If necessary, it does pre-allocate memory for returned values.
// You can use this file as a starting point for a main function that
// you can deploy in your application.
//
// After you copy the file, and before you deploy it, you must make the
// following changes:
// * For variable-size function arguments, change the example sizes to
// the sizes that your application requires.
// * Change the example values of function arguments to the values that
// your application requires.
// * If the entry-point functions return values, store these values or
// otherwise use them as required by your application.
//
//***********************************************************************

// Include Files
#include "stdafx.h"
#include "Uout.h"
#include "GetFphi.h"
#include "GetFphi_terminate.h"
#include "Getintput_u.h"
#include "rt_nonfinite.h"



// Function Definitions

//
// Arguments    : void
// Return Type  : void
//
void main_GetFphi(double F[320], double phi[1600])
{
	double dv[16] = {1,0,0,0,0,0.2886,0,-2.4473,0.5,0,1,0,0,0.3746,0,0.2886};
	double dv1[4] = {0.1250,-0.726,0.5,-0.2497};

  // Initialize function 'GetFphi' input arguments.
  // Initialize function input argument 'Ap'.
  // Initialize function input argument 'Bp'.
  // Call the entry-point 'GetFphi'.
  GetFphi(dv, dv1, F, phi);
}

//
// Arguments    : void
// Return Type  : void
//
double main_Getintput_u(double F[320], double phi[1600],double Yreal[4],double dv2[2],int k)
{
	double Yref[4] = {1.8,0,0,0 };
	double dv3[7] = {5,20,1.5,9.8,0.04,0.995,0.03};
	double u_real;

  // Initialize function 'Getintput_u' input arguments.
  // Initialize function input argument 'F'.
  // Initialize function input argument 'phi'.
  // Initialize function input argument 'Yreal'.

  u_real = Getintput_u(F, phi, Yreal, Yref, dv2, 0.05, k,dv3);
  return u_real;
  //GetFphi_terminate();
}


double main_GetstopX(double F[320], double phi[1600],double Yreal[4],double dv2[2],int k,double y0[4])
{

	double dv3[4] = {1.5,9.8,0.01,1000};
	double u_real;

  // Initialize function 'Getintput_u' input arguments.
  // Initialize function input argument 'F'.
  // Initialize function input argument 'phi'.
  // Initialize function input argument 'Yreal'.

  u_real = GetStop_u(F, phi, Yreal, 0.0002, dv2, y0, 0.05, k, dv3);
  return u_real;
  //GetFphi_terminate();
}


void Xkf(double x_get, double a, double T, double xkf[2])
{
    double A[4];
    double B[2];
    double P_this[4];
    double xp[2];
    double b_A[4];
    static const double R = 0.003;
    static const double Q[4] = { 0.0, 0.0, 0.0, 0.9 };
    static double P_new[4] = { 0,0,0,0 };
    static double x_last[2] = { 0,0 };

    // 假设建立的模型  噪声方差叠加在速度上 大小为n*n方阵 n=状态向量的维数
    //  位置测量方差估计，可以改变它来看不同效果  m*m      m=z(i)的维数
    A[0] = 1.0;
    A[2] = T;
    A[1] = 0.0;
    A[3] = 1.0;

    //  n*n
    B[0] = 0.5 * (T * T);
    B[1] = T;


        int i;
        double K_idx_1;
        double K_idx_0;
        double b;
        for (i = 0; i < 2; i++) {
            K_idx_1 = A[i + 2];
            b = static_cast<double>(static_cast<int>(A[i])) * P_new[0] + K_idx_1 *
                P_new[1];
            K_idx_0 = static_cast<double>(static_cast<int>(A[i])) * P_new[2] + K_idx_1
                * P_new[3];
            xp[i] = (static_cast<double>(static_cast<int>(A[i])) * x_last[0] + K_idx_1 *
                x_last[1]) + B[i] * a;
            P_this[i] = b + K_idx_0 * T;
            P_this[i + 2] = (b * 0.0 + K_idx_0) + Q[i + 2];
        }

        K_idx_1 = (P_this[0] + 0.0 * P_this[1]) + (P_this[2] + 0.0 * P_this[3]) *
            0.0;
        K_idx_0 = (P_this[0] + P_this[2] * 0.0) / (K_idx_1 + R);
        K_idx_1 = (P_this[1] + P_this[3] * 0.0) / (K_idx_1 + R);
        b = x_get - (xp[0] + 0.0 * xp[1]);
        xkf[0] = xp[0] + K_idx_0 * b;
        b_A[0] = 1.0 - K_idx_0;
        b_A[1] = 0.0 - K_idx_1;
        xkf[1] = xp[1] + K_idx_1 * b;
        b_A[2] = 0.0 - K_idx_0 * 0.0;
        b_A[3] = 1.0 - K_idx_1 * 0.0;
        for (i = 0; i < 2; i++) {
            K_idx_1 = b_A[i + 2];
            P_new[i] = b_A[i] * P_this[0] + K_idx_1 * P_this[1];
            P_new[i + 2] = b_A[i] * P_this[2] + K_idx_1 * P_this[3];
        }
        x_last[0] = xkf[0];
        x_last[1] = xkf[1];
}



//
// Arguments    : int argc
//                const char * const argv[]
// Return Type  : int
//

/*double GetStop_u(const double F[320], const double phi[1600], const double
                 Yreal[4], double a_stop, const double r[2], double T, double k,
                 double Y0, const double init_parm_data[], const int [2])*/
//
// File trailer for main.cpp
//
// [EOF]
//
