/*
 * File: schur.c
 *
 * MATLAB Coder version            : 3.3
 * C/C++ source code generated on  : 31-May-2018 13:39:01
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "music_angle.h"
#include "schur.h"
#include "xhseqr.h"
#include "xungorghr.h"
#include "xgehrd.h"
#include "anyNonFinite.h"

/* Function Definitions */

/*
 * Arguments    : const creal_T A[36]
 *                creal_T V[36]
 *                creal_T T[36]
 * Return Type  : void
 */
void schur(const creal_T A[36], creal_T V[36], creal_T T[36])
{
  int istart;
  creal_T tau[5];
  int j;
  int i;
  if (anyNonFinite(A)) {
    for (istart = 0; istart < 36; istart++) {
      V[istart].re = rtNaN;
      V[istart].im = 0.0;
    }

    istart = 2;
    for (j = 0; j < 5; j++) {
      for (i = istart; i < 7; i++) {
        V[(i + 6 * j) - 1].re = 0.0;
        V[(i + 6 * j) - 1].im = 0.0;
      }

      istart++;
    }

    for (istart = 0; istart < 36; istart++) {
      T[istart].re = rtNaN;
      T[istart].im = 0.0;
    }
  } else {
    memcpy(&T[0], &A[0], 36U * sizeof(creal_T));
    xgehrd(T, tau);
    memcpy(&V[0], &T[0], 36U * sizeof(creal_T));
    xungorghr(V, tau);
    xhseqr(T, V);
  }
}

/*
 * File trailer for schur.c
 *
 * [EOF]
 */
