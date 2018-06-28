/*
 * File: xztgevc.c
 *
 * MATLAB Coder version            : 3.3
 * C/C++ source code generated on  : 31-May-2018 13:39:01
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "music_angle.h"
#include "xztgevc.h"

/* Function Definitions */

/*
 * Arguments    : const creal_T A[36]
 *                creal_T V[36]
 * Return Type  : void
 */
void xztgevc(const creal_T A[36], creal_T V[36])
{
  int i;
  double anorm;
  double rworka[6];
  int j;
  double xmx;
  double ascale;
  double d_re;
  int je;
  double temp;
  double salpha_re;
  double salpha_im;
  double acoeff;
  boolean_T lscalea;
  boolean_T lscaleb;
  double scale;
  double acoefa;
  int jr;
  creal_T work1[6];
  double dmin;
  int b_j;
  creal_T work2[6];
  double d_im;
  double work1_re;
  for (i = 0; i < 6; i++) {
    rworka[i] = 0.0;
  }

  anorm = fabs(A[0].re) + fabs(A[0].im);
  for (j = 0; j < 5; j++) {
    for (i = 0; i <= j; i++) {
      rworka[j + 1] += fabs(A[i + 6 * (j + 1)].re) + fabs(A[i + 6 * (j + 1)].im);
    }

    d_re = rworka[j + 1] + (fabs(A[(j + 6 * (j + 1)) + 1].re) + fabs(A[(j + 6 *
      (j + 1)) + 1].im));
    if (d_re > anorm) {
      anorm = d_re;
    }
  }

  xmx = anorm;
  if (2.2250738585072014E-308 > anorm) {
    xmx = 2.2250738585072014E-308;
  }

  ascale = 1.0 / xmx;
  for (je = 0; je < 6; je++) {
    xmx = (fabs(A[(6 * (5 - je) - je) + 5].re) + fabs(A[(6 * (5 - je) - je) + 5]
            .im)) * ascale;
    if (1.0 > xmx) {
      xmx = 1.0;
    }

    temp = 1.0 / xmx;
    salpha_re = ascale * (temp * A[(6 * (5 - je) - je) + 5].re);
    salpha_im = ascale * (temp * A[(6 * (5 - je) - je) + 5].im);
    acoeff = temp * ascale;
    if ((fabs(temp) >= 2.2250738585072014E-308) && (fabs(acoeff) <
         6.0125050800269183E-292)) {
      lscalea = true;
    } else {
      lscalea = false;
    }

    if ((fabs(salpha_re) + fabs(salpha_im) >= 2.2250738585072014E-308) && (fabs
         (salpha_re) + fabs(salpha_im) < 6.0125050800269183E-292)) {
      lscaleb = true;
    } else {
      lscaleb = false;
    }

    scale = 1.0;
    if (lscalea) {
      xmx = anorm;
      if (1.6632002579455998E+291 < anorm) {
        xmx = 1.6632002579455998E+291;
      }

      scale = 6.0125050800269183E-292 / fabs(temp) * xmx;
    }

    if (lscaleb) {
      d_re = 6.0125050800269183E-292 / (fabs(salpha_re) + fabs(salpha_im));
      if (d_re > scale) {
        scale = d_re;
      }
    }

    if (lscalea || lscaleb) {
      xmx = fabs(acoeff);
      d_re = fabs(salpha_re) + fabs(salpha_im);
      if (1.0 > xmx) {
        xmx = 1.0;
      }

      if (d_re > xmx) {
        xmx = d_re;
      }

      d_re = 1.0 / (2.2250738585072014E-308 * xmx);
      if (d_re < scale) {
        scale = d_re;
      }

      if (lscalea) {
        acoeff = ascale * (scale * temp);
      } else {
        acoeff *= scale;
      }

      salpha_re *= scale;
      salpha_im *= scale;
    }

    acoefa = fabs(acoeff);
    for (jr = 0; jr < 6; jr++) {
      work1[jr].re = 0.0;
      work1[jr].im = 0.0;
    }

    work1[5 - je].re = 1.0;
    work1[5 - je].im = 0.0;
    dmin = 2.2204460492503131E-16 * acoefa * anorm;
    d_re = 2.2204460492503131E-16 * (fabs(salpha_re) + fabs(salpha_im));
    if (d_re > dmin) {
      dmin = d_re;
    }

    if (2.2250738585072014E-308 > dmin) {
      dmin = 2.2250738585072014E-308;
    }

    for (jr = 0; jr <= 4 - je; jr++) {
      work1[jr].re = acoeff * A[jr + 6 * (5 - je)].re;
      work1[jr].im = acoeff * A[jr + 6 * (5 - je)].im;
    }

    work1[5 - je].re = 1.0;
    work1[5 - je].im = 0.0;
    i = (int)((1.0 + (-1.0 - ((6.0 + -(double)je) - 1.0))) / -1.0);
    for (j = 0; j < i; j++) {
      b_j = 4 - (je + j);
      d_re = acoeff * A[b_j + 6 * b_j].re - salpha_re;
      d_im = acoeff * A[b_j + 6 * b_j].im - salpha_im;
      if (fabs(d_re) + fabs(d_im) <= dmin) {
        d_re = dmin;
        d_im = 0.0;
      }

      if ((fabs(d_re) + fabs(d_im) < 1.0) && (fabs(work1[b_j].re) + fabs
           (work1[b_j].im) >= 7.4903880619263159E+306 * (fabs(d_re) + fabs(d_im))))
      {
        temp = 1.0 / (fabs(work1[b_j].re) + fabs(work1[b_j].im));
        for (jr = 0; jr <= 5 - je; jr++) {
          work1[jr].re *= temp;
          work1[jr].im *= temp;
        }
      }

      work1_re = -work1[b_j].re;
      if (d_im == 0.0) {
        if (-work1[b_j].im == 0.0) {
          work1[b_j].re = -work1[b_j].re / d_re;
          work1[b_j].im = 0.0;
        } else if (-work1[b_j].re == 0.0) {
          work1[b_j].re = 0.0;
          work1[b_j].im = -work1[b_j].im / d_re;
        } else {
          work1[b_j].re = -work1[b_j].re / d_re;
          work1[b_j].im = -work1[b_j].im / d_re;
        }
      } else if (d_re == 0.0) {
        if (-work1[b_j].re == 0.0) {
          work1[b_j].re = -work1[b_j].im / d_im;
          work1[b_j].im = 0.0;
        } else if (-work1[b_j].im == 0.0) {
          work1[b_j].re = 0.0;
          work1[b_j].im = -(work1_re / d_im);
        } else {
          work1[b_j].re = -work1[b_j].im / d_im;
          work1[b_j].im = -(work1_re / d_im);
        }
      } else {
        temp = fabs(d_re);
        xmx = fabs(d_im);
        if (temp > xmx) {
          scale = d_im / d_re;
          xmx = d_re + scale * d_im;
          work1[b_j].re = (-work1[b_j].re + scale * -work1[b_j].im) / xmx;
          work1[b_j].im = (-work1[b_j].im - scale * work1_re) / xmx;
        } else if (xmx == temp) {
          if (d_re > 0.0) {
            scale = 0.5;
          } else {
            scale = -0.5;
          }

          if (d_im > 0.0) {
            xmx = 0.5;
          } else {
            xmx = -0.5;
          }

          work1[b_j].re = (-work1[b_j].re * scale + -work1[b_j].im * xmx) / temp;
          work1[b_j].im = (-work1[b_j].im * scale - work1_re * xmx) / temp;
        } else {
          scale = d_re / d_im;
          xmx = d_im + scale * d_re;
          work1[b_j].re = (scale * -work1[b_j].re + -work1[b_j].im) / xmx;
          work1[b_j].im = (scale * -work1[b_j].im - work1_re) / xmx;
        }
      }

      if (b_j + 1 > 1) {
        if (fabs(work1[b_j].re) + fabs(work1[b_j].im) > 1.0) {
          temp = 1.0 / (fabs(work1[b_j].re) + fabs(work1[b_j].im));
          if (acoefa * rworka[b_j] >= 7.4903880619263159E+306 * temp) {
            for (jr = 0; jr <= 5 - je; jr++) {
              work1[jr].re *= temp;
              work1[jr].im *= temp;
            }
          }
        }

        d_re = acoeff * work1[b_j].re;
        d_im = acoeff * work1[b_j].im;
        for (jr = 0; jr < b_j; jr++) {
          work1[jr].re += d_re * A[jr + 6 * b_j].re - d_im * A[jr + 6 * b_j].im;
          work1[jr].im += d_re * A[jr + 6 * b_j].im + d_im * A[jr + 6 * b_j].re;
        }
      }
    }

    for (jr = 0; jr < 6; jr++) {
      work2[jr].re = 0.0;
      work2[jr].im = 0.0;
    }

    for (i = 0; i <= 5 - je; i++) {
      for (jr = 0; jr < 6; jr++) {
        work2[jr].re += V[jr + 6 * i].re * work1[i].re - V[jr + 6 * i].im *
          work1[i].im;
        work2[jr].im += V[jr + 6 * i].re * work1[i].im + V[jr + 6 * i].im *
          work1[i].re;
      }
    }

    xmx = fabs(work2[0].re) + fabs(work2[0].im);
    for (jr = 0; jr < 5; jr++) {
      d_re = fabs(work2[jr + 1].re) + fabs(work2[jr + 1].im);
      if (d_re > xmx) {
        xmx = d_re;
      }
    }

    if (xmx > 2.2250738585072014E-308) {
      temp = 1.0 / xmx;
      for (jr = 0; jr < 6; jr++) {
        V[jr + 6 * (5 - je)].re = temp * work2[jr].re;
        V[jr + 6 * (5 - je)].im = temp * work2[jr].im;
      }
    } else {
      for (jr = 0; jr < 6; jr++) {
        V[jr + 6 * (5 - je)].re = 0.0;
        V[jr + 6 * (5 - je)].im = 0.0;
      }
    }
  }
}

/*
 * File trailer for xztgevc.c
 *
 * [EOF]
 */
