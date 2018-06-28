/*
 * File: cosd.c
 *
 * MATLAB Coder version            : 3.3
 * C/C++ source code generated on  : 31-May-2018 13:39:01
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "music_angle.h"
#include "cosd.h"
#include "music_angle_rtwutil.h"

/* Function Definitions */

/*
 * Arguments    : double x[6]
 * Return Type  : void
 */
void b_cosd(double x[6])
{
  int k;
  double b_x;
  double absx;
  signed char n;
  for (k = 0; k < 6; k++) {
    if (!((!rtIsInf(x[k])) && (!rtIsNaN(x[k])))) {
      b_x = rtNaN;
    } else {
      b_x = rt_remd_snf(x[k], 360.0);
      absx = fabs(b_x);
      if (absx > 180.0) {
        if (b_x > 0.0) {
          b_x -= 360.0;
        } else {
          b_x += 360.0;
        }

        absx = fabs(b_x);
      }

      if (absx <= 45.0) {
        b_x *= 0.017453292519943295;
        n = 0;
      } else if (absx <= 135.0) {
        if (b_x > 0.0) {
          b_x = 0.017453292519943295 * (b_x - 90.0);
          n = 1;
        } else {
          b_x = 0.017453292519943295 * (b_x + 90.0);
          n = -1;
        }
      } else if (b_x > 0.0) {
        b_x = 0.017453292519943295 * (b_x - 180.0);
        n = 2;
      } else {
        b_x = 0.017453292519943295 * (b_x + 180.0);
        n = -2;
      }

      if (n == 0) {
        b_x = cos(b_x);
      } else if (n == 1) {
        b_x = -sin(b_x);
      } else if (n == -1) {
        b_x = sin(b_x);
      } else {
        b_x = -cos(b_x);
      }
    }

    x[k] = b_x;
  }
}

/*
 * File trailer for cosd.c
 *
 * [EOF]
 */
