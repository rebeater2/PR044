/*
 * File: xgerc.c
 *
 * MATLAB Coder version            : 3.3
 * C/C++ source code generated on  : 31-May-2018 13:39:01
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "music_angle.h"
#include "xgerc.h"

/* Function Definitions */

/*
 * Arguments    : int m
 *                int n
 *                const creal_T alpha1
 *                int ix0
 *                const creal_T y[6]
 *                creal_T A[36]
 *                int ia0
 * Return Type  : void
 */
void xgerc(int m, int n, const creal_T alpha1, int ix0, const creal_T y[6],
           creal_T A[36], int ia0)
{
  int jA;
  int jy;
  int j;
  double temp_re;
  double temp_im;
  int ix;
  int i4;
  int ijA;
  double A_im;
  if (!((alpha1.re == 0.0) && (alpha1.im == 0.0))) {
    jA = ia0 - 1;
    jy = 0;
    for (j = 1; j <= n; j++) {
      if ((y[jy].re != 0.0) || (y[jy].im != 0.0)) {
        temp_re = y[jy].re * alpha1.re + y[jy].im * alpha1.im;
        temp_im = y[jy].re * alpha1.im - y[jy].im * alpha1.re;
        ix = ix0;
        i4 = m + jA;
        for (ijA = jA; ijA + 1 <= i4; ijA++) {
          A_im = A[ix - 1].re * temp_im + A[ix - 1].im * temp_re;
          A[ijA].re += A[ix - 1].re * temp_re - A[ix - 1].im * temp_im;
          A[ijA].im += A_im;
          ix++;
        }
      }

      jy++;
      jA += 6;
    }
  }
}

/*
 * File trailer for xgerc.c
 *
 * [EOF]
 */
