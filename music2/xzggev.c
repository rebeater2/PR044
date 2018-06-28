/*
 * File: xzggev.c
 *
 * MATLAB Coder version            : 3.3
 * C/C++ source code generated on  : 31-May-2018 13:39:01
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "music_angle.h"
#include "xzggev.h"
#include "xzlartg.h"
#include "xztgevc.h"
#include "xzhgeqz.h"
#include "xzggbal.h"
#include "music_angle_rtwutil.h"

/* Function Definitions */

/*
 * Arguments    : creal_T A[36]
 *                int *info
 *                creal_T alpha1[6]
 *                creal_T beta1[6]
 *                creal_T V[36]
 * Return Type  : void
 */
void xzggev(creal_T A[36], int *info, creal_T alpha1[6], creal_T beta1[6],
            creal_T V[36])
{
  double anrm;
  int jrow;
  boolean_T exitg1;
  double absxk;
  boolean_T ilascl;
  int i;
  double anrmto;
  int ilo;
  int ihi;
  int rscale[6];
  double ctoc;
  boolean_T notdone;
  signed char I[36];
  double cfrom1;
  double stemp_re;
  double stemp_im;
  int jcol;
  creal_T tmp;
  int j;
  *info = 0;
  anrm = 0.0;
  jrow = 0;
  exitg1 = false;
  while ((!exitg1) && (jrow < 36)) {
    absxk = rt_hypotd_snf(A[jrow].re, A[jrow].im);
    if (rtIsNaN(absxk)) {
      anrm = rtNaN;
      exitg1 = true;
    } else {
      if (absxk > anrm) {
        anrm = absxk;
      }

      jrow++;
    }
  }

  if (!((!rtIsInf(anrm)) && (!rtIsNaN(anrm)))) {
    for (i = 0; i < 6; i++) {
      alpha1[i].re = rtNaN;
      alpha1[i].im = 0.0;
      beta1[i].re = rtNaN;
      beta1[i].im = 0.0;
    }

    for (jrow = 0; jrow < 36; jrow++) {
      V[jrow].re = rtNaN;
      V[jrow].im = 0.0;
    }
  } else {
    ilascl = false;
    anrmto = anrm;
    if ((anrm > 0.0) && (anrm < 6.7178761075670888E-139)) {
      anrmto = 6.7178761075670888E-139;
      ilascl = true;
    } else {
      if (anrm > 1.4885657073574029E+138) {
        anrmto = 1.4885657073574029E+138;
        ilascl = true;
      }
    }

    if (ilascl) {
      absxk = anrm;
      ctoc = anrmto;
      notdone = true;
      while (notdone) {
        cfrom1 = absxk * 2.0041683600089728E-292;
        stemp_re = ctoc / 4.9896007738368E+291;
        if ((cfrom1 > ctoc) && (ctoc != 0.0)) {
          stemp_im = 2.0041683600089728E-292;
          absxk = cfrom1;
        } else if (stemp_re > absxk) {
          stemp_im = 4.9896007738368E+291;
          ctoc = stemp_re;
        } else {
          stemp_im = ctoc / absxk;
          notdone = false;
        }

        for (jrow = 0; jrow < 36; jrow++) {
          A[jrow].re *= stemp_im;
          A[jrow].im *= stemp_im;
        }
      }
    }

    xzggbal(A, &ilo, &ihi, rscale);
    for (jrow = 0; jrow < 36; jrow++) {
      I[jrow] = 0;
    }

    for (jrow = 0; jrow < 6; jrow++) {
      I[jrow + 6 * jrow] = 1;
    }

    for (jrow = 0; jrow < 36; jrow++) {
      V[jrow].re = I[jrow];
      V[jrow].im = 0.0;
    }

    if (!(ihi < ilo + 2)) {
      for (jcol = ilo - 1; jcol + 1 < ihi - 1; jcol++) {
        for (jrow = ihi - 1; jrow + 1 > jcol + 2; jrow--) {
          xzlartg(A[(jrow + 6 * jcol) - 1], A[jrow + 6 * jcol], &cfrom1, &tmp,
                  &A[(jrow + 6 * jcol) - 1]);
          A[jrow + 6 * jcol].re = 0.0;
          A[jrow + 6 * jcol].im = 0.0;
          for (j = jcol + 1; j + 1 < 7; j++) {
            stemp_re = cfrom1 * A[(jrow + 6 * j) - 1].re + (tmp.re * A[jrow + 6 *
              j].re - tmp.im * A[jrow + 6 * j].im);
            stemp_im = cfrom1 * A[(jrow + 6 * j) - 1].im + (tmp.re * A[jrow + 6 *
              j].im + tmp.im * A[jrow + 6 * j].re);
            absxk = A[(jrow + 6 * j) - 1].im;
            ctoc = A[(jrow + 6 * j) - 1].re;
            A[jrow + 6 * j].re = cfrom1 * A[jrow + 6 * j].re - (tmp.re * A[(jrow
              + 6 * j) - 1].re + tmp.im * A[(jrow + 6 * j) - 1].im);
            A[jrow + 6 * j].im = cfrom1 * A[jrow + 6 * j].im - (tmp.re * absxk -
              tmp.im * ctoc);
            A[(jrow + 6 * j) - 1].re = stemp_re;
            A[(jrow + 6 * j) - 1].im = stemp_im;
          }

          tmp.re = -tmp.re;
          tmp.im = -tmp.im;
          for (i = 0; i + 1 <= ihi; i++) {
            stemp_re = cfrom1 * A[i + 6 * jrow].re + (tmp.re * A[i + 6 * (jrow -
              1)].re - tmp.im * A[i + 6 * (jrow - 1)].im);
            stemp_im = cfrom1 * A[i + 6 * jrow].im + (tmp.re * A[i + 6 * (jrow -
              1)].im + tmp.im * A[i + 6 * (jrow - 1)].re);
            absxk = A[i + 6 * jrow].im;
            ctoc = A[i + 6 * jrow].re;
            A[i + 6 * (jrow - 1)].re = cfrom1 * A[i + 6 * (jrow - 1)].re -
              (tmp.re * A[i + 6 * jrow].re + tmp.im * A[i + 6 * jrow].im);
            A[i + 6 * (jrow - 1)].im = cfrom1 * A[i + 6 * (jrow - 1)].im -
              (tmp.re * absxk - tmp.im * ctoc);
            A[i + 6 * jrow].re = stemp_re;
            A[i + 6 * jrow].im = stemp_im;
          }

          for (i = 0; i < 6; i++) {
            stemp_re = cfrom1 * V[i + 6 * jrow].re + (tmp.re * V[i + 6 * (jrow -
              1)].re - tmp.im * V[i + 6 * (jrow - 1)].im);
            stemp_im = cfrom1 * V[i + 6 * jrow].im + (tmp.re * V[i + 6 * (jrow -
              1)].im + tmp.im * V[i + 6 * (jrow - 1)].re);
            absxk = V[i + 6 * jrow].re;
            V[i + 6 * (jrow - 1)].re = cfrom1 * V[i + 6 * (jrow - 1)].re -
              (tmp.re * V[i + 6 * jrow].re + tmp.im * V[i + 6 * jrow].im);
            V[i + 6 * (jrow - 1)].im = cfrom1 * V[i + 6 * (jrow - 1)].im -
              (tmp.re * V[i + 6 * jrow].im - tmp.im * absxk);
            V[i + 6 * jrow].re = stemp_re;
            V[i + 6 * jrow].im = stemp_im;
          }
        }
      }
    }

    xzhgeqz(A, ilo, ihi, V, info, alpha1, beta1);
    if (*info == 0) {
      xztgevc(A, V);
      if (ilo > 1) {
        for (i = ilo - 2; i + 1 >= 1; i--) {
          jrow = rscale[i] - 1;
          if (rscale[i] != i + 1) {
            for (j = 0; j < 6; j++) {
              tmp = V[i + 6 * j];
              V[i + 6 * j] = V[jrow + 6 * j];
              V[jrow + 6 * j] = tmp;
            }
          }
        }
      }

      if (ihi < 6) {
        while (ihi + 1 < 7) {
          jrow = rscale[ihi] - 1;
          if (rscale[ihi] != ihi + 1) {
            for (j = 0; j < 6; j++) {
              tmp = V[ihi + 6 * j];
              V[ihi + 6 * j] = V[jrow + 6 * j];
              V[jrow + 6 * j] = tmp;
            }
          }

          ihi++;
        }
      }

      for (jrow = 0; jrow < 6; jrow++) {
        absxk = fabs(V[6 * jrow].re) + fabs(V[6 * jrow].im);
        for (jcol = 0; jcol < 5; jcol++) {
          ctoc = fabs(V[(jcol + 6 * jrow) + 1].re) + fabs(V[(jcol + 6 * jrow) +
            1].im);
          if (ctoc > absxk) {
            absxk = ctoc;
          }
        }

        if (absxk >= 6.7178761075670888E-139) {
          absxk = 1.0 / absxk;
          for (jcol = 0; jcol < 6; jcol++) {
            V[jcol + 6 * jrow].re *= absxk;
            V[jcol + 6 * jrow].im *= absxk;
          }
        }
      }

      if (ilascl) {
        notdone = true;
        while (notdone) {
          cfrom1 = anrmto * 2.0041683600089728E-292;
          stemp_re = anrm / 4.9896007738368E+291;
          if ((cfrom1 > anrm) && (anrm != 0.0)) {
            stemp_im = 2.0041683600089728E-292;
            anrmto = cfrom1;
          } else if (stemp_re > anrmto) {
            stemp_im = 4.9896007738368E+291;
            anrm = stemp_re;
          } else {
            stemp_im = anrm / anrmto;
            notdone = false;
          }

          for (jrow = 0; jrow < 6; jrow++) {
            alpha1[jrow].re *= stemp_im;
            alpha1[jrow].im *= stemp_im;
          }
        }
      }
    }
  }
}

/*
 * File trailer for xzggev.c
 *
 * [EOF]
 */
