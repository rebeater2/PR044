/*
 * File: xungorghr.c
 *
 * MATLAB Coder version            : 3.3
 * C/C++ source code generated on  : 31-May-2018 13:39:01
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "music_angle.h"
#include "xungorghr.h"
#include "xgerc.h"

/* Function Definitions */

/*
 * Arguments    : creal_T A[36]
 *                const creal_T tau[5]
 * Return Type  : void
 */
void xungorghr(creal_T A[36], const creal_T tau[5])
{
  int coltop;
  int i;
  int b_i;
  int itau;
  creal_T work[6];
  int iaii;
  int lastv;
  int lastc;
  double c_re;
  boolean_T exitg2;
  double c_im;
  creal_T b_tau;
  int i5;
  int ia;
  double A_re;
  int exitg1;
  double A_im;
  int ix;
  int i6;
  for (coltop = 4; coltop >= 0; coltop += -1) {
    b_i = (coltop + 1) * 6 - 1;
    for (i = 1; i <= coltop + 1; i++) {
      A[b_i + i].re = 0.0;
      A[b_i + i].im = 0.0;
    }

    for (i = coltop + 3; i < 7; i++) {
      A[b_i + i] = A[(b_i + i) - 6];
    }
  }

  for (i = 0; i < 6; i++) {
    A[i].re = 0.0;
    A[i].im = 0.0;
    work[i].re = 0.0;
    work[i].im = 0.0;
  }

  A[0].re = 1.0;
  A[0].im = 0.0;
  itau = 4;
  for (i = 4; i >= 0; i += -1) {
    iaii = (i + i * 6) + 8;
    if (i + 1 < 5) {
      A[iaii - 1].re = 1.0;
      A[iaii - 1].im = 0.0;
      if ((tau[itau].re != 0.0) || (tau[itau].im != 0.0)) {
        lastv = 5 - i;
        b_i = (iaii - i) + 3;
        while ((lastv > 0) && ((A[b_i].re == 0.0) && (A[b_i].im == 0.0))) {
          lastv--;
          b_i--;
        }

        lastc = 4 - i;
        exitg2 = false;
        while ((!exitg2) && (lastc > 0)) {
          coltop = (iaii + (lastc - 1) * 6) + 5;
          ia = coltop;
          do {
            exitg1 = 0;
            if (ia + 1 <= coltop + lastv) {
              if ((A[ia].re != 0.0) || (A[ia].im != 0.0)) {
                exitg1 = 1;
              } else {
                ia++;
              }
            } else {
              lastc--;
              exitg1 = 2;
            }
          } while (exitg1 == 0);

          if (exitg1 == 1) {
            exitg2 = true;
          }
        }
      } else {
        lastv = 0;
        lastc = 0;
      }

      if (lastv > 0) {
        if (lastc != 0) {
          for (b_i = 1; b_i <= lastc; b_i++) {
            work[b_i - 1].re = 0.0;
            work[b_i - 1].im = 0.0;
          }

          b_i = 0;
          i5 = (iaii + 6 * (lastc - 1)) + 6;
          for (coltop = iaii + 6; coltop <= i5; coltop += 6) {
            ix = iaii - 1;
            c_re = 0.0;
            c_im = 0.0;
            i6 = (coltop + lastv) - 1;
            for (ia = coltop - 1; ia + 1 <= i6; ia++) {
              c_re += A[ia].re * A[ix].re + A[ia].im * A[ix].im;
              c_im += A[ia].re * A[ix].im - A[ia].im * A[ix].re;
              ix++;
            }

            work[b_i].re += c_re - 0.0 * c_im;
            work[b_i].im += c_im + 0.0 * c_re;
            b_i++;
          }
        }

        b_tau.re = -tau[itau].re;
        b_tau.im = -tau[itau].im;
        xgerc(lastv, lastc, b_tau, iaii, work, A, iaii + 6);
      }

      c_re = -tau[itau].re;
      c_im = -tau[itau].im;
      i5 = (iaii - i) + 4;
      for (coltop = iaii; coltop + 1 <= i5; coltop++) {
        A_re = A[coltop].re;
        A_im = A[coltop].im;
        A[coltop].re = c_re * A_re - c_im * A_im;
        A[coltop].im = c_re * A_im + c_im * A_re;
      }
    }

    A[iaii - 1].re = 1.0 - tau[itau].re;
    A[iaii - 1].im = 0.0 - tau[itau].im;
    for (coltop = 1; coltop <= i; coltop++) {
      A[(iaii - coltop) - 1].re = 0.0;
      A[(iaii - coltop) - 1].im = 0.0;
    }

    itau--;
  }
}

/*
 * File trailer for xungorghr.c
 *
 * [EOF]
 */
