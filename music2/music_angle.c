/*
 * File: music_angle.c
 *
 * MATLAB Coder version            : 3.3
 * C/C++ source code generated on  : 31-May-2018 13:39:01
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "music_angle.h"
#include "fft.h"
#include "exp.h"
#include "cosd.h"
#include "sind.h"
#include "relop.h"
#include "music_angle_emxutil.h"
#include "fliplr.h"
#include "sort1.h"
#include "diag.h"
#include "eig.h"
#include "music_angle_rtwutil.h"

/* Function Definitions */

/*
 * Arguments    : const double sig[49152]
 *                emxArray_real_T *est_phi
 *                emxArray_real_T *est_thi
 * Return Type  : void
 */
void music_angle(const double sig[49152], emxArray_real_T *est_phi,
                 emxArray_real_T *est_thi)
{
  int i;
  int i0;
  static double b_sig[8192];
  static creal_T dcv0[16384];
  static creal_T x_fft[98304];
  creal_T b_x_fft[36];
  creal_T V1[36];
  creal_T EV[36];
  int jj;
  creal_T a3[6];
  int iidx[6];
  double re;
  double im;
  int ixstart;
  double b_re;
  double br;
  creal_T Un1[30];
  int idx;
  double ksi;
  int nn;
  creal_T peak;
  creal_T maxval[360];
  static creal_T pp2[32400];
  double dv0[6];
  boolean_T exitg1;
  emxArray_int32_T *ii;
  boolean_T x[32400];
  emxArray_int32_T *b_jj;
  creal_T b_a3[6];
  double b_im;
  boolean_T guard1 = false;

  /* ���� */
  /* ���� */
  /* ���а뾶 */
  /* �źŸ��� */
  /* ��Ԫ��Ŀ */
  /* ��Ԫ�н� */
  /*  */
  for (i = 0; i < 6; i++) {
    for (i0 = 0; i0 < 8192; i0++) {
      b_sig[i0] = sig[i + 6 * i0];
    }

    fft(b_sig, dcv0);
    for (i0 = 0; i0 < 16384; i0++) {
      x_fft[i + 6 * i0] = dcv0[i0];
    }
  }

  /*  music��һ������Э������� */
  /* ������ */
  /* ��������Э������� */
  /*  music�ڶ���������ֵ�ֽ⣬��������ӿռ� */
  /* [V1,D1] = eig(R2);  %����������ֵ */
  /* Un1 = V1(:,1:m-num_s);  %�����ӿռ� */
  /* [V1,~,D1]=pca(R2); */
  for (i0 = 0; i0 < 6; i0++) {
    for (jj = 0; jj < 6; jj++) {
      re = 0.0;
      im = 0.0;
      for (ixstart = 0; ixstart < 8192; ixstart++) {
        b_re = x_fft[jj + 6 * ixstart].re;
        br = -x_fft[jj + 6 * ixstart].im;
        re += x_fft[i0 + 6 * ixstart].re * b_re - x_fft[i0 + 6 * ixstart].im *
          br;
        im += x_fft[i0 + 6 * ixstart].re * br + x_fft[i0 + 6 * ixstart].im *
          b_re;
      }

      if (im == 0.0) {
        b_x_fft[i0 + 6 * jj].re = re / 8192.0;
        b_x_fft[i0 + 6 * jj].im = 0.0;
      } else if (re == 0.0) {
        b_x_fft[i0 + 6 * jj].re = 0.0;
        b_x_fft[i0 + 6 * jj].im = im / 8192.0;
      } else {
        b_x_fft[i0 + 6 * jj].re = re / 8192.0;
        b_x_fft[i0 + 6 * jj].im = im / 8192.0;
      }
    }
  }

  eig(b_x_fft, V1, EV);
  diag(EV, a3);
  sort(a3, iidx);
  for (i0 = 0; i0 < 6; i0++) {
    for (jj = 0; jj < 6; jj++) {
      EV[jj + 6 * i0] = V1[jj + 6 * (iidx[i0] - 1)];
    }
  }

  fliplr(EV);
  for (i0 = 0; i0 < 6; i0++) {
    for (jj = 0; jj < 6; jj++) {
      b_x_fft[jj + 6 * i0] = V1[jj + 6 * (iidx[i0] - 1)];
    }
  }
#pragma omp parallel for //*********************************************************************************************omp
  fliplr(b_x_fft);
  for (i0 = 0; i0 < 5; i0++) {
    memcpy(&Un1[i0 * 6], &b_x_fft[i0 * 6 + 6], 6U * sizeof(creal_T));
  }

  /*  music���������׷����� */
  for (idx = 0; idx < 90; idx++) {
    br = 1.0 + (double)idx;
    b_sind(&br);
    ksi = 3.1415926535897931 * br;
    for (nn = 0; nn < 360; nn++) {
      peak.re = ksi * 0.0;
      peak.im = ksi;
      for (i0 = 0; i0 < 6; i0++) {
        dv0[i0] = (nn - 60 * i0) + 1;
      }

      b_cosd(dv0);
      for (i = 0; i < 6; i++) {
        a3[i].re = dv0[i] * peak.re;
        a3[i].im = dv0[i] * peak.im;
      }

      b_exp(a3);
      for (i0 = 0; i0 < 6; i0++) {
        for (jj = 0; jj < 6; jj++) {
          b_x_fft[i0 + 6 * jj].re = 0.0;
          b_x_fft[i0 + 6 * jj].im = 0.0;
          for (ixstart = 0; ixstart < 5; ixstart++) {
            br = Un1[jj + 6 * ixstart].re;
            b_re = -Un1[jj + 6 * ixstart].im;
            b_x_fft[i0 + 6 * jj].re += EV[i0 + 6 * (1 + ixstart)].re * br -
              EV[i0 + 6 * (1 + ixstart)].im * b_re;
            b_x_fft[i0 + 6 * jj].im += EV[i0 + 6 * (1 + ixstart)].re * b_re +
              EV[i0 + 6 * (1 + ixstart)].im * br;
          }
        }
      }

      re = 0.0;
      im = 0.0;
      for (i0 = 0; i0 < 6; i0++) {
        b_a3[i0].re = 0.0;
        b_a3[i0].im = 0.0;
        for (jj = 0; jj < 6; jj++) {
          b_a3[i0].re += a3[jj].re * b_x_fft[jj + 6 * i0].re - -a3[jj].im *
            b_x_fft[jj + 6 * i0].im;
          b_a3[i0].im += a3[jj].re * b_x_fft[jj + 6 * i0].im + -a3[jj].im *
            b_x_fft[jj + 6 * i0].re;
        }

        re += b_a3[i0].re * a3[i0].re - b_a3[i0].im * a3[i0].im;
        im += b_a3[i0].re * a3[i0].im + b_a3[i0].im * a3[i0].re;
      }

      b_re = 0.0;
      b_im = 0.0;
      for (i0 = 0; i0 < 6; i0++) {
        b_re += a3[i0].re * a3[i0].re - -a3[i0].im * a3[i0].im;
        b_im += a3[i0].re * a3[i0].im + -a3[i0].im * a3[i0].re;
      }

      br = rt_hypotd_snf(re, im);
      if (b_im == 0.0) {
        pp2[idx + 90 * nn].re = b_re / br;
        pp2[idx + 90 * nn].im = 0.0;
      } else if (b_re == 0.0) {
        pp2[idx + 90 * nn].re = 0.0;
        pp2[idx + 90 * nn].im = b_im / br;
      } else {
        pp2[idx + 90 * nn].re = b_re / br;
        pp2[idx + 90 * nn].im = b_im / br;
      }
    }
  }

  /*  */
  /*  figure */
  /*  imagesc(pp2); */
  /*  xlabel('��Դ��λ��'); */
  /*  ylabel('��Դ����'); */
  for (i = 0; i < 360; i++) {
    jj = i * 90 + 90;
    ixstart = i * 90;
    peak = pp2[jj - 90];
    if (rtIsNaN(pp2[ixstart].re) || rtIsNaN(pp2[ixstart].im)) {
      idx = ixstart + 1;
      exitg1 = false;
      while ((!exitg1) && (idx + 1 <= jj)) {
        ixstart = idx;
        if (!(rtIsNaN(pp2[idx].re) || rtIsNaN(pp2[idx].im))) {
          peak = pp2[idx];
          exitg1 = true;
        } else {
          idx++;
        }
      }
    }

    if (ixstart + 1 < jj) {
      for (idx = ixstart + 1; idx + 1 <= jj; idx++) {
        if (b_relop(pp2[idx], peak)) {
          peak = pp2[idx];
        }
      }
    }

    maxval[i] = peak;
  }

  ixstart = 1;
  peak = maxval[0];
  if (rtIsNaN(maxval[0].re) || rtIsNaN(maxval[0].im)) {
    jj = 1;
    exitg1 = false;
    while ((!exitg1) && (jj + 1 < 361)) {
      ixstart = jj + 1;
      if (!(rtIsNaN(maxval[jj].re) || rtIsNaN(maxval[jj].im))) {
        peak = maxval[jj];
        exitg1 = true;
      } else {
        jj++;
      }
    }
  }

  if (ixstart < 360) {
    while (ixstart + 1 < 361) {
      if (b_relop(maxval[ixstart], peak)) {
        peak = maxval[ixstart];
      }

      ixstart++;
    }
  }

  for (i0 = 0; i0 < 32400; i0++) {
    x[i0] = ((pp2[i0].re == peak.re) && (pp2[i0].im == peak.im));
  }

  emxInit_int32_T(&ii, 1);
  emxInit_int32_T(&b_jj, 1);
  idx = 0;
  i0 = ii->size[0];
  ii->size[0] = 32400;
  emxEnsureCapacity((emxArray__common *)ii, i0, sizeof(int));
  i0 = b_jj->size[0];
  b_jj->size[0] = 32400;
  emxEnsureCapacity((emxArray__common *)b_jj, i0, sizeof(int));
  ixstart = 1;
  jj = 1;
  exitg1 = false;
  while ((!exitg1) && (jj <= 360)) {
    guard1 = false;
    if (x[(ixstart + 90 * (jj - 1)) - 1]) {
      idx++;
      ii->data[idx - 1] = ixstart;
      b_jj->data[idx - 1] = jj;
      if (idx >= 32400) {
        exitg1 = true;
      } else {
        guard1 = true;
      }
    } else {
      guard1 = true;
    }

    if (guard1) {
      ixstart++;
      if (ixstart > 90) {
        ixstart = 1;
        jj++;
      }
    }
  }

  i0 = ii->size[0];
  if (1 > idx) {
    ii->size[0] = 0;
  } else {
    ii->size[0] = idx;
  }

  emxEnsureCapacity((emxArray__common *)ii, i0, sizeof(int));
  i0 = b_jj->size[0];
  if (1 > idx) {
    b_jj->size[0] = 0;
  } else {
    b_jj->size[0] = idx;
  }

  emxEnsureCapacity((emxArray__common *)b_jj, i0, sizeof(int));
  i0 = est_phi->size[0];
  est_phi->size[0] = ii->size[0];
  emxEnsureCapacity((emxArray__common *)est_phi, i0, sizeof(double));
  ixstart = ii->size[0];
  for (i0 = 0; i0 < ixstart; i0++) {
    est_phi->data[i0] = ii->data[i0];
  }

  emxFree_int32_T(&ii);
  i0 = est_thi->size[0];
  est_thi->size[0] = b_jj->size[0];
  emxEnsureCapacity((emxArray__common *)est_thi, i0, sizeof(double));
  ixstart = b_jj->size[0];
  for (i0 = 0; i0 < ixstart; i0++) {
    est_thi->data[i0] = b_jj->data[i0];
  }

  emxFree_int32_T(&b_jj);
}

/*
 * File trailer for music_angle.c
 *
 * [EOF]
 */
