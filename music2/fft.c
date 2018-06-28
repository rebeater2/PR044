/*
 * File: fft.c
 *
 * MATLAB Coder version            : 3.3
 * C/C++ source code generated on  : 31-May-2018 13:39:01
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "music_angle.h"
#include "fft.h"

/* Function Declarations */
static void generate_twiddle_tables(double costab[8193], double sintab[8193]);

/* Function Definitions */

/*
 * Arguments    : double costab[8193]
 *                double sintab[8193]
 * Return Type  : void
 */
static void generate_twiddle_tables(double costab[8193], double sintab[8193])
{
  double costab1q[4097];
  int k;
  costab1q[0] = 1.0;
  for (k = 0; k < 2048; k++) {
    costab1q[k + 1] = cos(0.00038349519697141029 * ((double)k + 1.0));
  }

  for (k = 0; k < 2047; k++) {
    costab1q[k + 2049] = sin(0.00038349519697141029 * (4096.0 - ((double)k +
      2049.0)));
  }

  costab1q[4096] = 0.0;
  costab[0] = 1.0;
  sintab[0] = 0.0;
  for (k = 0; k < 4096; k++) {
    costab[k + 1] = costab1q[k + 1];
    sintab[k + 1] = -costab1q[4095 - k];
    costab[k + 4097] = -costab1q[4095 - k];
    sintab[k + 4097] = -costab1q[k + 1];
  }
}

/*
 * Arguments    : const double x[8192]
 *                creal_T y[16384]
 * Return Type  : void
 */
void fft(const double x[8192], creal_T y[16384])
{
  static double costab[8193];
  double sintab[8193];
  int i;
  int ix;
  static creal_T b_y1[16384];
  int ju;
  int iy;
  boolean_T tst;
  double temp_re;
  double temp_im;
  int iheight;
  int istart;
  int j;
  double twid_re;
  double twid_im;
  int ihi;
  generate_twiddle_tables(costab, sintab);
  for (i = 0; i < 16384; i++) {
    b_y1[i].re = 0.0;
    b_y1[i].im = 0.0;
  }

  ix = 0;
  ju = 0;
  iy = 0;
  for (i = 0; i < 8191; i++) {
    b_y1[iy].re = x[ix];
    b_y1[iy].im = 0.0;
    iy = 16384;
    tst = true;
    while (tst) {
      iy >>= 1;
      ju ^= iy;
      tst = ((ju & iy) == 0);
    }

    iy = ju;
    ix++;
  }

  b_y1[iy].re = x[ix];
  b_y1[iy].im = 0.0;
  for (i = 0; i <= 16383; i += 2) {
    temp_re = b_y1[i + 1].re;
    temp_im = b_y1[i + 1].im;
    b_y1[i + 1].re = b_y1[i].re - b_y1[i + 1].re;
    b_y1[i + 1].im = b_y1[i].im - b_y1[i + 1].im;
    b_y1[i].re += temp_re;
    b_y1[i].im += temp_im;
  }

  iy = 2;
  ix = 4;
  ju = 4096;
  iheight = 16381;
  while (ju > 0) {
    for (i = 0; i < iheight; i += ix) {
      temp_re = b_y1[i + iy].re;
      temp_im = b_y1[i + iy].im;
      b_y1[i + iy].re = b_y1[i].re - temp_re;
      b_y1[i + iy].im = b_y1[i].im - temp_im;
      b_y1[i].re += temp_re;
      b_y1[i].im += temp_im;
    }

    istart = 1;
    for (j = ju; j < 8192; j += ju) {
      twid_re = costab[j];
      twid_im = sintab[j];
      i = istart;
      ihi = istart + iheight;
      while (i < ihi) {
        temp_re = twid_re * b_y1[i + iy].re - twid_im * b_y1[i + iy].im;
        temp_im = twid_re * b_y1[i + iy].im + twid_im * b_y1[i + iy].re;
        b_y1[i + iy].re = b_y1[i].re - temp_re;
        b_y1[i + iy].im = b_y1[i].im - temp_im;
        b_y1[i].re += temp_re;
        b_y1[i].im += temp_im;
        i += ix;
      }

      istart++;
    }

    ju /= 2;
    iy = ix;
    ix += ix;
    iheight -= iy;
  }

  memcpy(&y[0], &b_y1[0], sizeof(creal_T) << 14);
}

/*
 * File trailer for fft.c
 *
 * [EOF]
 */
