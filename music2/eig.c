/*
 * File: eig.c
 *
 * MATLAB Coder version            : 3.3
 * C/C++ source code generated on  : 31-May-2018 13:39:01
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "music_angle.h"
#include "eig.h"
#include "schur.h"
#include "xzggev.h"
#include "anyNonFinite.h"

/* Function Definitions */

/*
 * Arguments    : const creal_T A[36]
 *                creal_T V[36]
 *                creal_T D[36]
 * Return Type  : void
 */
void eig(const creal_T A[36], creal_T V[36], creal_T D[36])
{
  boolean_T p;
  int i;
  int j;
  boolean_T exitg2;
  creal_T At[36];
  creal_T alpha1[6];
  creal_T beta1[6];
  int exitg1;
  int coltop;
  double colnorm;
  double scale;
  double absxk;
  double t;
  if (anyNonFinite(A)) {
    for (i = 0; i < 36; i++) {
      V[i].re = rtNaN;
      V[i].im = 0.0;
      D[i].re = 0.0;
      D[i].im = 0.0;
    }

    for (i = 0; i < 6; i++) {
      D[i + 6 * i].re = rtNaN;
      D[i + 6 * i].im = 0.0;
    }
  } else {
    p = true;
    j = 0;
    exitg2 = false;
    while ((!exitg2) && (j < 6)) {
      i = 0;
      do {
        exitg1 = 0;
        if (i <= j) {
          if (!((A[i + 6 * j].re == A[j + 6 * i].re) && (A[i + 6 * j].im == -A[j
                + 6 * i].im))) {
            p = false;
            exitg1 = 1;
          } else {
            i++;
          }
        } else {
          j++;
          exitg1 = 2;
        }
      } while (exitg1 == 0);

      if (exitg1 == 1) {
        exitg2 = true;
      }
    }

    if (p) {
      schur(A, V, D);
      D[0].im = 0.0;
      for (j = 0; j < 5; j++) {
        D[(j + 6 * (j + 1)) + 1].im = 0.0;
        D[(j + 6 * j) + 1].re = 0.0;
        D[(j + 6 * j) + 1].im = 0.0;
        for (i = 1; i <= j + 1; i++) {
          D[(i + 6 * (j + 1)) - 1].re = 0.0;
          D[(i + 6 * (j + 1)) - 1].im = 0.0;
        }
      }
    } else {
      memcpy(&At[0], &A[0], 36U * sizeof(creal_T));
      xzggev(At, &i, alpha1, beta1, V);
      for (coltop = 0; coltop <= 31; coltop += 6) {
        colnorm = 0.0;
        scale = 2.2250738585072014E-308;
        for (i = coltop; i + 1 <= coltop + 6; i++) {
          absxk = fabs(V[i].re);
          if (absxk > scale) {
            t = scale / absxk;
            colnorm = 1.0 + colnorm * t * t;
            scale = absxk;
          } else {
            t = absxk / scale;
            colnorm += t * t;
          }

          absxk = fabs(V[i].im);
          if (absxk > scale) {
            t = scale / absxk;
            colnorm = 1.0 + colnorm * t * t;
            scale = absxk;
          } else {
            t = absxk / scale;
            colnorm += t * t;
          }
        }

        colnorm = scale * sqrt(colnorm);
        for (j = coltop; j + 1 <= coltop + 6; j++) {
          if (V[j].im == 0.0) {
            V[j].re /= colnorm;
            V[j].im = 0.0;
          } else if (V[j].re == 0.0) {
            V[j].re = 0.0;
            V[j].im /= colnorm;
          } else {
            V[j].re /= colnorm;
            V[j].im /= colnorm;
          }
        }
      }

      for (i = 0; i < 36; i++) {
        D[i].re = 0.0;
        D[i].im = 0.0;
      }

      for (i = 0; i < 6; i++) {
        if (beta1[i].im == 0.0) {
          if (alpha1[i].im == 0.0) {
            D[i + 6 * i].re = alpha1[i].re / beta1[i].re;
            D[i + 6 * i].im = 0.0;
          } else if (alpha1[i].re == 0.0) {
            D[i + 6 * i].re = 0.0;
            D[i + 6 * i].im = alpha1[i].im / beta1[i].re;
          } else {
            D[i + 6 * i].re = alpha1[i].re / beta1[i].re;
            D[i + 6 * i].im = alpha1[i].im / beta1[i].re;
          }
        } else if (beta1[i].re == 0.0) {
          if (alpha1[i].re == 0.0) {
            D[i + 6 * i].re = alpha1[i].im / beta1[i].im;
            D[i + 6 * i].im = 0.0;
          } else if (alpha1[i].im == 0.0) {
            D[i + 6 * i].re = 0.0;
            D[i + 6 * i].im = -(alpha1[i].re / beta1[i].im);
          } else {
            D[i + 6 * i].re = alpha1[i].im / beta1[i].im;
            D[i + 6 * i].im = -(alpha1[i].re / beta1[i].im);
          }
        } else {
          absxk = fabs(beta1[i].re);
          colnorm = fabs(beta1[i].im);
          if (absxk > colnorm) {
            colnorm = beta1[i].im / beta1[i].re;
            scale = beta1[i].re + colnorm * beta1[i].im;
            D[i + 6 * i].re = (alpha1[i].re + colnorm * alpha1[i].im) / scale;
            D[i + 6 * i].im = (alpha1[i].im - colnorm * alpha1[i].re) / scale;
          } else if (colnorm == absxk) {
            if (beta1[i].re > 0.0) {
              colnorm = 0.5;
            } else {
              colnorm = -0.5;
            }

            if (beta1[i].im > 0.0) {
              scale = 0.5;
            } else {
              scale = -0.5;
            }

            D[i + 6 * i].re = (alpha1[i].re * colnorm + alpha1[i].im * scale) /
              absxk;
            D[i + 6 * i].im = (alpha1[i].im * colnorm - alpha1[i].re * scale) /
              absxk;
          } else {
            colnorm = beta1[i].re / beta1[i].im;
            scale = beta1[i].im + colnorm * beta1[i].re;
            D[i + 6 * i].re = (colnorm * alpha1[i].re + alpha1[i].im) / scale;
            D[i + 6 * i].im = (colnorm * alpha1[i].im - alpha1[i].re) / scale;
          }
        }
      }
    }
  }
}

/*
 * File trailer for eig.c
 *
 * [EOF]
 */
