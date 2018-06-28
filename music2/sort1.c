/*
 * File: sort1.c
 *
 * MATLAB Coder version            : 3.3
 * C/C++ source code generated on  : 31-May-2018 13:39:01
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "music_angle.h"
#include "sort1.h"
#include "relop.h"

/* Function Definitions */

/*
 * Arguments    : creal_T x[6]
 *                int idx[6]
 * Return Type  : void
 */
void sort(creal_T x[6], int idx[6])
{
  int k;
  int i;
  boolean_T p;
  creal_T xwork[6];
  int i2;
  int j;
  int pEnd;
  int b_p;
  int q;
  int qEnd;
  int kEnd;
  int iwork[6];
  for (k = 0; k <= 5; k += 2) {
    if (relop(x[k], x[k + 1]) || (rtIsNaN(x[k + 1].re) || rtIsNaN(x[k + 1].im)))
    {
      p = true;
    } else {
      p = false;
    }

    if (p) {
      idx[k] = k + 1;
      idx[k + 1] = k + 2;
    } else {
      idx[k] = k + 2;
      idx[k + 1] = k + 1;
    }
  }

  i = 2;
  while (i < 6) {
    i2 = i << 1;
    j = 1;
    for (pEnd = 1 + i; pEnd < 7; pEnd = qEnd + i) {
      b_p = j;
      q = pEnd - 1;
      qEnd = j + i2;
      if (qEnd > 7) {
        qEnd = 7;
      }

      k = 0;
      kEnd = qEnd - j;
      while (k + 1 <= kEnd) {
        if (relop(x[idx[b_p - 1] - 1], x[idx[q] - 1]) || (rtIsNaN(x[idx[q] - 1].
              re) || rtIsNaN(x[idx[q] - 1].im))) {
          p = true;
        } else {
          p = false;
        }

        if (p) {
          iwork[k] = idx[b_p - 1];
          b_p++;
          if (b_p == pEnd) {
            while (q + 1 < qEnd) {
              k++;
              iwork[k] = idx[q];
              q++;
            }
          }
        } else {
          iwork[k] = idx[q];
          q++;
          if (q + 1 == qEnd) {
            while (b_p < pEnd) {
              k++;
              iwork[k] = idx[b_p - 1];
              b_p++;
            }
          }
        }

        k++;
      }

      for (k = 0; k + 1 <= kEnd; k++) {
        idx[(j + k) - 1] = iwork[k];
      }

      j = qEnd;
    }

    i = i2;
  }

  memcpy(&xwork[0], &x[0], 6U * sizeof(creal_T));
  for (k = 0; k < 6; k++) {
    x[k] = xwork[idx[k] - 1];
  }
}

/*
 * File trailer for sort1.c
 *
 * [EOF]
 */
