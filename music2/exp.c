/*
 * File: exp.c
 *
 * MATLAB Coder version            : 3.3
 * C/C++ source code generated on  : 31-May-2018 13:39:01
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "music_angle.h"
#include "exp.h"

/* Function Definitions */

/*
 * Arguments    : creal_T x[6]
 * Return Type  : void
 */
void b_exp(creal_T x[6])
{
  int k;
  double x_re;
  double r;
  for (k = 0; k < 6; k++) {
    if (x[k].im == 0.0) {
      x_re = exp(x[k].re);
      r = 0.0;
    } else if (rtIsInf(x[k].im) && rtIsInf(x[k].re) && (x[k].re < 0.0)) {
      x_re = 0.0;
      r = 0.0;
    } else {
      r = exp(x[k].re / 2.0);
      x_re = r * (r * cos(x[k].im));
      r *= r * sin(x[k].im);
    }

    x[k].re = x_re;
    x[k].im = r;
  }
}

/*
 * File trailer for exp.c
 *
 * [EOF]
 */
