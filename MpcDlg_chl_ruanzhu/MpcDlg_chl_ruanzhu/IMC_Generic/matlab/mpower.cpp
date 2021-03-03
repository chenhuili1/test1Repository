//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: mpower.cpp
//
// MATLAB Coder version            : 5.0
// C/C++ source code generated on  : 09-Oct-2020 15:23:44
//

// Include Files
#include "stdafx.h"
#include "mpower.h"
#include "GetFphi.h"
#include "Getintput_u.h"
#include "inv.h"
#include "rt_nonfinite.h"
#include <cmath>
#include <cstring>

// Function Definitions

//
// Arguments    : const double a[16]
//                double b
//                double c[16]
// Return Type  : void
//
void mpower(const double a[16], double b, double c[16])
{
  double b_a[16];
  int n;
  int b_n;
  double aBuffer[16];
  double cBuffer[16];
  if (b == b) {
    int nbitson;
    int nb;
    std::memcpy(&b_a[0], &a[0], 16U * sizeof(double));
    n = static_cast<int>(std::abs(b));
    b_n = n;
    nbitson = 0;
    nb = -2;
    while (b_n > 0) {
      nb++;
      if ((b_n & 1) != 0) {
        nbitson++;
      }

      b_n >>= 1;
    }

    if (n <= 2) {
      if (b == 2.0) {
        for (nbitson = 0; nbitson < 4; nbitson++) {
          for (int i = 0; i < 4; i++) {
            int i1;
            i1 = i << 2;
            c[nbitson + i1] = ((a[nbitson] * a[i1] + a[nbitson + 4] * a[i1 + 1])
                               + a[nbitson + 8] * a[i1 + 2]) + a[nbitson + 12] *
              a[i1 + 3];
          }
        }
      } else if (b == 1.0) {
        std::memcpy(&c[0], &a[0], 16U * sizeof(double));
      } else if (b == -1.0) {
        inv(a, c);
      } else if (b == -2.0) {
        for (nbitson = 0; nbitson < 4; nbitson++) {
          for (int i = 0; i < 4; i++) {
            int i1;
            i1 = i << 2;
            b_a[nbitson + i1] = ((a[nbitson] * a[i1] + a[nbitson + 4] * a[i1 + 1])
                                 + a[nbitson + 8] * a[i1 + 2]) + a[nbitson + 12]
              * a[i1 + 3];
          }
        }

        inv(b_a, c);
      } else {
        std::memset(&c[0], 0, 16U * sizeof(double));
        c[0] = 1.0;
        c[5] = 1.0;
        c[10] = 1.0;
        c[15] = 1.0;
      }
    } else {
      bool first;
      bool aBufferInUse;
      bool lsb;
      int i;
      int i1;
      double d;
      double d1;
      double d2;
      first = true;
      aBufferInUse = false;
      lsb = ((nbitson & 1) != 0);
      if ((lsb && (b < 0.0)) || ((!lsb) && (b >= 0.0))) {
        lsb = true;
      } else {
        lsb = false;
      }

      for (b_n = 0; b_n <= nb; b_n++) {
        if ((n & 1) != 0) {
          if (first) {
            first = false;
            if (lsb) {
              if (aBufferInUse) {
                std::memcpy(&cBuffer[0], &aBuffer[0], 16U * sizeof(double));
              } else {
                std::memcpy(&cBuffer[0], &b_a[0], 16U * sizeof(double));
              }
            } else if (aBufferInUse) {
              std::memcpy(&c[0], &aBuffer[0], 16U * sizeof(double));
            } else {
              std::memcpy(&c[0], &b_a[0], 16U * sizeof(double));
            }
          } else {
            if (aBufferInUse) {
              if (lsb) {
                for (nbitson = 0; nbitson < 4; nbitson++) {
                  d = cBuffer[nbitson + 4];
                  d1 = cBuffer[nbitson + 8];
                  d2 = cBuffer[nbitson + 12];
                  for (i = 0; i < 4; i++) {
                    i1 = i << 2;
                    c[nbitson + i1] = ((cBuffer[nbitson] * aBuffer[i1] + d *
                                        aBuffer[i1 + 1]) + d1 * aBuffer[i1 + 2])
                      + d2 * aBuffer[i1 + 3];
                  }
                }
              } else {
                for (nbitson = 0; nbitson < 4; nbitson++) {
                  d = c[nbitson + 4];
                  d1 = c[nbitson + 8];
                  d2 = c[nbitson + 12];
                  for (i = 0; i < 4; i++) {
                    i1 = i << 2;
                    cBuffer[nbitson + i1] = ((c[nbitson] * aBuffer[i1] + d *
                      aBuffer[i1 + 1]) + d1 * aBuffer[i1 + 2]) + d2 * aBuffer[i1
                      + 3];
                  }
                }
              }
            } else if (lsb) {
              for (nbitson = 0; nbitson < 4; nbitson++) {
                d = cBuffer[nbitson + 4];
                d1 = cBuffer[nbitson + 8];
                d2 = cBuffer[nbitson + 12];
                for (i = 0; i < 4; i++) {
                  i1 = i << 2;
                  c[nbitson + i1] = ((cBuffer[nbitson] * b_a[i1] + d * b_a[i1 +
                                      1]) + d1 * b_a[i1 + 2]) + d2 * b_a[i1 + 3];
                }
              }
            } else {
              for (nbitson = 0; nbitson < 4; nbitson++) {
                d = c[nbitson + 4];
                d1 = c[nbitson + 8];
                d2 = c[nbitson + 12];
                for (i = 0; i < 4; i++) {
                  i1 = i << 2;
                  cBuffer[nbitson + i1] = ((c[nbitson] * b_a[i1] + d * b_a[i1 +
                    1]) + d1 * b_a[i1 + 2]) + d2 * b_a[i1 + 3];
                }
              }
            }

            lsb = !lsb;
          }
        }

        n >>= 1;
        if (aBufferInUse) {
          for (nbitson = 0; nbitson < 4; nbitson++) {
            for (i = 0; i < 4; i++) {
              i1 = i << 2;
              b_a[nbitson + i1] = ((aBuffer[nbitson] * aBuffer[i1] +
                                    aBuffer[nbitson + 4] * aBuffer[i1 + 1]) +
                                   aBuffer[nbitson + 8] * aBuffer[i1 + 2]) +
                aBuffer[nbitson + 12] * aBuffer[i1 + 3];
            }
          }
        } else {
          for (nbitson = 0; nbitson < 4; nbitson++) {
            for (i = 0; i < 4; i++) {
              i1 = i << 2;
              aBuffer[nbitson + i1] = ((b_a[nbitson] * b_a[i1] + b_a[nbitson + 4]
                * b_a[i1 + 1]) + b_a[nbitson + 8] * b_a[i1 + 2]) + b_a[nbitson +
                12] * b_a[i1 + 3];
            }
          }
        }

        aBufferInUse = !aBufferInUse;
      }

      if (first) {
        if (b < 0.0) {
          if (aBufferInUse) {
            inv(aBuffer, c);
          } else {
            inv(b_a, c);
          }
        } else if (aBufferInUse) {
          std::memcpy(&c[0], &aBuffer[0], 16U * sizeof(double));
        } else {
          std::memcpy(&c[0], &b_a[0], 16U * sizeof(double));
        }
      } else if (b < 0.0) {
        if (aBufferInUse) {
          for (nbitson = 0; nbitson < 4; nbitson++) {
            d = c[nbitson + 4];
            d1 = c[nbitson + 8];
            d2 = c[nbitson + 12];
            for (i = 0; i < 4; i++) {
              i1 = i << 2;
              cBuffer[nbitson + i1] = ((c[nbitson] * aBuffer[i1] + d *
                aBuffer[i1 + 1]) + d1 * aBuffer[i1 + 2]) + d2 * aBuffer[i1 + 3];
            }
          }
        } else {
          for (nbitson = 0; nbitson < 4; nbitson++) {
            d = c[nbitson + 4];
            d1 = c[nbitson + 8];
            d2 = c[nbitson + 12];
            for (i = 0; i < 4; i++) {
              i1 = i << 2;
              cBuffer[nbitson + i1] = ((c[nbitson] * b_a[i1] + d * b_a[i1 + 1])
                + d1 * b_a[i1 + 2]) + d2 * b_a[i1 + 3];
            }
          }
        }

        inv(cBuffer, c);
      } else if (aBufferInUse) {
        for (nbitson = 0; nbitson < 4; nbitson++) {
          d = cBuffer[nbitson + 4];
          d1 = cBuffer[nbitson + 8];
          d2 = cBuffer[nbitson + 12];
          for (i = 0; i < 4; i++) {
            i1 = i << 2;
            c[nbitson + i1] = ((cBuffer[nbitson] * aBuffer[i1] + d * aBuffer[i1
                                + 1]) + d1 * aBuffer[i1 + 2]) + d2 * aBuffer[i1
              + 3];
          }
        }
      } else {
        for (nbitson = 0; nbitson < 4; nbitson++) {
          d = cBuffer[nbitson + 4];
          d1 = cBuffer[nbitson + 8];
          d2 = cBuffer[nbitson + 12];
          for (i = 0; i < 4; i++) {
            i1 = i << 2;
            c[nbitson + i1] = ((cBuffer[nbitson] * b_a[i1] + d * b_a[i1 + 1]) +
                               d1 * b_a[i1 + 2]) + d2 * b_a[i1 + 3];
          }
        }
      }
    }
  }
}

//
// File trailer for mpower.cpp
//
// [EOF]
//
