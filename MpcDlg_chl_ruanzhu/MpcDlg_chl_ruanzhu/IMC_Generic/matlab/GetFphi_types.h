//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: GetFphi_types.h
//
// MATLAB Coder version            : 5.0
// C/C++ source code generated on  : 09-Oct-2020 15:23:44
//
#ifndef GETFPHI_TYPES_H
#define GETFPHI_TYPES_H

// Include Files
#include "rtwtypes.h"

// Type Definitions
struct struct_T
{
  double xstar[21];
  double fstar;
  double firstorderopt;
  double lambda[43];
  int state;
  double maxConstr;
  int iterations;
  double searchDir[21];
};

struct b_struct_T
{
  int MaxIterations;
  double ConstrRelTolFactor;
  double ProbRelTolFactor;
  bool RemainFeasible;
};

struct c_struct_T
{
  double workspace_double[903];
  int workspace_int[43];
  int workspace_sort[43];
};

struct d_struct_T
{
  double FMat[1849];
  int ldm;
  int ndims;
  int info;
  double scaleFactor;
  bool ConvexCheck;
  double regTol_;
  double workspace_[2064];
  double workspace2_[2064];
};

struct e_struct_T
{
  int mConstr;
  int mConstrOrig;
  int mConstrMax;
  int nVar;
  int nVarOrig;
  int nVarMax;
  int ldA;
  double Aineq[42];
  double bineq[2];
  double lb[21];
  double ub[21];
  int indexLB[21];
  int indexUB[21];
  int indexFixed[21];
  int mEqRemoved;
  double ATwset[903];
  double bwset[43];
  int nActiveConstr;
  double maxConstrWorkspace[43];
  int sizes[5];
  int sizesNormal[5];
  int sizesPhaseOne[5];
  int sizesRegularized[5];
  int sizesRegPhaseOne[5];
  int isActiveIdx[6];
  int isActiveIdxNormal[6];
  int isActiveIdxPhaseOne[6];
  int isActiveIdxRegularized[6];
  int isActiveIdxRegPhaseOne[6];
  bool isActiveConstr[43];
  int Wid[43];
  int Wlocalidx[43];
  int nWConstr[5];
  int probType;
  double SLACK0;
};

struct f_struct_T
{
  int ldq;
  double QR[1849];
  double Q[1849];
  int jpvt[43];
  int mrows;
  int ncols;
  double tau[43];
  int minRowCol;
  bool usedPivoting;
};

struct g_struct_T
{
  double grad[21];
  double Hx[20];
  bool hasLinear;
  int nvar;
  int maxVar;
  double beta;
  double rho;
  int objtype;
  int prev_objtype;
  int prev_nvar;
  bool prev_hasLinear;
  double gammaScalar;
};

struct h_struct_T
{
  char FiniteDifferenceType[7];
  bool ScaleProblem;
  bool SpecifyConstraintGradient;
  bool SpecifyObjectiveGradient;
  bool NonFiniteSupport;
  bool IterDisplaySQP;
  double FiniteDifferenceStepSize;
  double MaxFunctionEvaluations;
  bool IterDisplayQP;
  double PricingTolerance;
  char Algorithm[10];
  double ObjectiveLimit;
  double ConstraintTolerance;
  double OptimalityTolerance;
  double StepTolerance;
  double MaxIterations;
  char SolverName[8];
  bool CheckGradients;
  char Diagnostics[3];
  double DiffMaxChange;
  double DiffMinChange;
  char Display[5];
  char FunValCheck[3];
  bool UseParallel;
  double FunctionTolerance;
  char LinearSolver[4];
  char SubproblemAlgorithm[2];
};

#endif

//
// File trailer for GetFphi_types.h
//
// [EOF]
//
