/*
 * File: xgehrd.c
 *
 * MATLAB Coder version            : 3.3
 * C/C++ source code generated on  : 31-May-2018 13:39:01
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "music_angle.h"
#include "xgehrd.h"
#include "xgerc.h"
#include "recip.h"
#include "xdlapy3.h"
#include "xnrm2.h"

/* Function Definitions */

/*
 * Arguments    : creal_T a[36]
 *                creal_T tau[5]
 * Return Type  : void
 */
void xgehrd(creal_T a[36], creal_T tau[5])
{
  int i;
  creal_T work[6];
  int im1n;
  int in;
  creal_T alpha1;
  int ia0;
  double c_re;
  double c_im;
  double xnorm;
  double beta1;
  int knt;
  int jy;
  double temp_im;
  int i1;
  int lastv;
  int lastc;
  int k;
  creal_T b_a;
  boolean_T exitg2;
  int ix;
  int ia;
  int exitg1;
  int i2;
  for (i = 0; i < 6; i++) {
    work[i].re = 0.0;
    work[i].im = 0.0;
  }

  for (i = 0; i < 5; i++) {
    im1n = i * 6 + 2;
    in = (i + 1) * 6;
    alpha1 = a[(i + 6 * i) + 1];
    ia0 = i + 3;
    if (!(ia0 < 6)) {
      ia0 = 6;
    }

    ia0 += i * 6;
    c_re = 0.0;
    c_im = 0.0;
    xnorm = xnrm2(4 - i, a, ia0);
    if ((xnorm != 0.0) || (a[(i + 6 * i) + 1].im != 0.0)) {
      beta1 = xdlapy3(a[(i + 6 * i) + 1].re, a[(i + 6 * i) + 1].im, xnorm);
      if (a[(i + 6 * i) + 1].re >= 0.0) {
        beta1 = -beta1;
      }

      if (fabs(beta1) < 1.0020841800044864E-292) {
        knt = 0;
        i1 = (ia0 - i) + 3;
        do {
          knt++;
          for (k = ia0; k <= i1; k++) {
            xnorm = a[k - 1].re;
            temp_im = a[k - 1].im;
            a[k - 1].re = 9.9792015476736E+291 * xnorm - 0.0 * temp_im;
            a[k - 1].im = 9.9792015476736E+291 * temp_im + 0.0 * xnorm;
          }

          beta1 *= 9.9792015476736E+291;
          alpha1.re *= 9.9792015476736E+291;
          alpha1.im *= 9.9792015476736E+291;
        } while (!(fabs(beta1) >= 1.0020841800044864E-292));

        beta1 = xdlapy3(alpha1.re, alpha1.im, xnrm2(4 - i, a, ia0));
        if (alpha1.re >= 0.0) {
          beta1 = -beta1;
        }

        xnorm = beta1 - alpha1.re;
        if (0.0 - alpha1.im == 0.0) {
          c_re = xnorm / beta1;
          c_im = 0.0;
        } else if (xnorm == 0.0) {
          c_re = 0.0;
          c_im = (0.0 - alpha1.im) / beta1;
        } else {
          c_re = xnorm / beta1;
          c_im = (0.0 - alpha1.im) / beta1;
        }

        b_a.re = alpha1.re - beta1;
        b_a.im = alpha1.im;
        alpha1 = recip(b_a);
        i1 = (ia0 - i) + 3;
        while (ia0 <= i1) {
          xnorm = a[ia0 - 1].re;
          temp_im = a[ia0 - 1].im;
          a[ia0 - 1].re = alpha1.re * xnorm - alpha1.im * temp_im;
          a[ia0 - 1].im = alpha1.re * temp_im + alpha1.im * xnorm;
          ia0++;
        }

        for (k = 1; k <= knt; k++) {
          beta1 *= 1.0020841800044864E-292;
        }

        alpha1.re = beta1;
        alpha1.im = 0.0;
      } else {
        xnorm = beta1 - a[(i + 6 * i) + 1].re;
        temp_im = 0.0 - a[(i + 6 * i) + 1].im;
        if (temp_im == 0.0) {
          c_re = xnorm / beta1;
          c_im = 0.0;
        } else if (xnorm == 0.0) {
          c_re = 0.0;
          c_im = temp_im / beta1;
        } else {
          c_re = xnorm / beta1;
          c_im = temp_im / beta1;
        }

        b_a.re = a[(i + 6 * i) + 1].re - beta1;
        b_a.im = a[(i + 6 * i) + 1].im;
        alpha1 = recip(b_a);
        i1 = (ia0 - i) + 3;
        while (ia0 <= i1) {
          xnorm = a[ia0 - 1].re;
          temp_im = a[ia0 - 1].im;
          a[ia0 - 1].re = alpha1.re * xnorm - alpha1.im * temp_im;
          a[ia0 - 1].im = alpha1.re * temp_im + alpha1.im * xnorm;
          ia0++;
        }

        alpha1.re = beta1;
        alpha1.im = 0.0;
      }
    }

    tau[i].re = c_re;
    tau[i].im = c_im;
    a[(i + 6 * i) + 1].re = 1.0;
    a[(i + 6 * i) + 1].im = 0.0;
    jy = (i + im1n) - 1;
    if ((tau[i].re != 0.0) || (tau[i].im != 0.0)) {
      lastv = 5 - i;
      ia0 = (jy - i) + 4;
      while ((lastv > 0) && ((a[ia0].re == 0.0) && (a[ia0].im == 0.0))) {
        lastv--;
        ia0--;
      }

      lastc = 6;
      exitg2 = false;
      while ((!exitg2) && (lastc > 0)) {
        ia0 = in + lastc;
        ia = ia0;
        do {
          exitg1 = 0;
          if (ia <= ia0 + (lastv - 1) * 6) {
            if ((a[ia - 1].re != 0.0) || (a[ia - 1].im != 0.0)) {
              exitg1 = 1;
            } else {
              ia += 6;
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
        for (ia0 = 1; ia0 <= lastc; ia0++) {
          work[ia0 - 1].re = 0.0;
          work[ia0 - 1].im = 0.0;
        }

        ix = jy;
        i1 = (in + 6 * (lastv - 1)) + 1;
        for (k = in + 1; k <= i1; k += 6) {
          c_re = a[ix].re - 0.0 * a[ix].im;
          c_im = a[ix].im + 0.0 * a[ix].re;
          ia0 = 0;
          i2 = (k + lastc) - 1;
          for (ia = k; ia <= i2; ia++) {
            work[ia0].re += a[ia - 1].re * c_re - a[ia - 1].im * c_im;
            work[ia0].im += a[ia - 1].re * c_im + a[ia - 1].im * c_re;
            ia0++;
          }

          ix++;
        }
      }

      c_re = -tau[i].re;
      c_im = -tau[i].im;
      if (!((-tau[i].re == 0.0) && (-tau[i].im == 0.0))) {
        ia0 = in;
        for (knt = 1; knt <= lastv; knt++) {
          if ((a[jy].re != 0.0) || (a[jy].im != 0.0)) {
            xnorm = a[jy].re * c_re + a[jy].im * c_im;
            temp_im = a[jy].re * c_im - a[jy].im * c_re;
            ix = 0;
            i1 = lastc + ia0;
            for (k = ia0; k + 1 <= i1; k++) {
              a[k].re += work[ix].re * xnorm - work[ix].im * temp_im;
              a[k].im += work[ix].re * temp_im + work[ix].im * xnorm;
              ix++;
            }
          }

          jy++;
          ia0 += 6;
        }
      }
    }

    jy = i + im1n;
    knt = (i + in) + 2;
    if ((tau[i].re != 0.0) || (-tau[i].im != 0.0)) {
      lastv = 5 - i;
      ia0 = (jy - i) + 3;
      while ((lastv > 0) && ((a[ia0].re == 0.0) && (a[ia0].im == 0.0))) {
        lastv--;
        ia0--;
      }

      lastc = 5 - i;
      exitg2 = false;
      while ((!exitg2) && (lastc > 0)) {
        ia0 = knt + (lastc - 1) * 6;
        ia = ia0;
        do {
          exitg1 = 0;
          if (ia <= (ia0 + lastv) - 1) {
            if ((a[ia - 1].re != 0.0) || (a[ia - 1].im != 0.0)) {
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
        for (ia0 = 1; ia0 <= lastc; ia0++) {
          work[ia0 - 1].re = 0.0;
          work[ia0 - 1].im = 0.0;
        }

        ia0 = 0;
        i1 = knt + 6 * (lastc - 1);
        for (k = knt; k <= i1; k += 6) {
          ix = jy - 1;
          c_re = 0.0;
          c_im = 0.0;
          i2 = (k + lastv) - 1;
          for (ia = k - 1; ia + 1 <= i2; ia++) {
            c_re += a[ia].re * a[ix].re + a[ia].im * a[ix].im;
            c_im += a[ia].re * a[ix].im - a[ia].im * a[ix].re;
            ix++;
          }

          work[ia0].re += c_re - 0.0 * c_im;
          work[ia0].im += c_im + 0.0 * c_re;
          ia0++;
        }
      }

      b_a.re = -tau[i].re;
      b_a.im = -(-tau[i].im);
      xgerc(lastv, lastc, b_a, jy, work, a, knt);
    }

    a[(i + 6 * i) + 1] = alpha1;
  }
}

/*
 * File trailer for xgehrd.c
 *
 * [EOF]
 */
