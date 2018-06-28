/*
 * File: xhseqr.c
 *
 * MATLAB Coder version            : 3.3
 * C/C++ source code generated on  : 31-May-2018 13:39:01
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "music_angle.h"
#include "xhseqr.h"
#include "xzhseqr.h"

/* Function Definitions */

/*
 * Arguments    : creal_T h[36]
 *                creal_T z[36]
 * Return Type  : int
 */
int xhseqr(creal_T h[36], creal_T z[36])
{
  int info;
  int istart;
  int j;
  int i;
  info = eml_zlahqr(h, z);
  istart = 4;
  for (j = 0; j < 3; j++) {
    for (i = istart; i < 7; i++) {
      h[(i + 6 * j) - 1].re = 0.0;
      h[(i + 6 * j) - 1].im = 0.0;
    }

    istart++;
  }

  return info;
}

/*
 * File trailer for xhseqr.c
 *
 * [EOF]
 */
