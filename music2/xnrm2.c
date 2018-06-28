/*
 * File: xnrm2.c
 *
 * MATLAB Coder version            : 3.3
 * C/C++ source code generated on  : 31-May-2018 13:39:01
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "music_angle.h"
#include "xnrm2.h"
#include "music_angle_rtwutil.h"

/* Function Definitions */

/*
 * Arguments    : int n
 *                const creal_T x[36]
 *                int ix0
 * Return Type  : double
 */
double xnrm2(int n, const creal_T x[36], int ix0)
{
  double y;
  double scale;
  int kend;
  int k;
  double absxk;
  double t;
  y = 0.0;
  if (!(n < 1)) {
    if (n == 1) {
      y = rt_hypotd_snf(x[ix0 - 1].re, x[ix0 - 1].im);
    } else {
      scale = 2.2250738585072014E-308;
      kend = (ix0 + n) - 1;
      for (k = ix0; k <= kend; k++) {
        absxk = fabs(x[k - 1].re);
        if (absxk > scale) {
          t = scale / absxk;
          y = 1.0 + y * t * t;
          scale = absxk;
        } else {
          t = absxk / scale;
          y += t * t;
        }

        absxk = fabs(x[k - 1].im);
        if (absxk > scale) {
          t = scale / absxk;
          y = 1.0 + y * t * t;
          scale = absxk;
        } else {
          t = absxk / scale;
          y += t * t;
        }
      }

      y = scale * sqrt(y);
    }
  }

  return y;
}

/*
 * File trailer for xnrm2.c
 *
 * [EOF]
 */
