/*
 * File: xzhseqr.c
 *
 * MATLAB Coder version            : 3.3
 * C/C++ source code generated on  : 31-May-2018 13:39:01
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "music_angle.h"
#include "xzhseqr.h"
#include "xscal.h"
#include "xzlarfg.h"
#include "sqrt.h"
#include "music_angle_rtwutil.h"

/* Function Definitions */

/*
 * Arguments    : creal_T h[36]
 *                creal_T z[36]
 * Return Type  : int
 */
int eml_zlahqr(creal_T h[36], creal_T z[36])
{
  int info;
  int j;
  int i;
  boolean_T exitg1;
  double tst;
  double htmp1;
  double ba;
  int L;
  boolean_T goto140;
  creal_T u2;
  int its;
  boolean_T exitg2;
  int k;
  boolean_T exitg3;
  creal_T y;
  int b_k;
  double t_re;
  double ab;
  boolean_T goto70;
  int m;
  double u_re;
  double u_im;
  double aa;
  double s;
  int c_k;
  double d0;
  creal_T v[2];
  int c;
  double b_u_re;
  info = 0;
  for (j = 0; j < 3; j++) {
    h[(j + 6 * j) + 2].re = 0.0;
    h[(j + 6 * j) + 2].im = 0.0;
    h[(j + 6 * j) + 3].re = 0.0;
    h[(j + 6 * j) + 3].im = 0.0;
  }

  h[23].re = 0.0;
  h[23].im = 0.0;
  for (i = 0; i < 5; i++) {
    if (h[(i + 6 * i) + 1].im != 0.0) {
      tst = h[(i + 6 * i) + 1].re;
      htmp1 = h[(i + 6 * i) + 1].im;
      ba = fabs(h[(i + 6 * i) + 1].re) + fabs(h[(i + 6 * i) + 1].im);
      if (htmp1 == 0.0) {
        u2.re = tst / ba;
        u2.im = 0.0;
      } else if (tst == 0.0) {
        u2.re = 0.0;
        u2.im = htmp1 / ba;
      } else {
        u2.re = tst / ba;
        u2.im = htmp1 / ba;
      }

      ba = rt_hypotd_snf(u2.re, u2.im);
      if (-u2.im == 0.0) {
        u2.re /= ba;
        u2.im = 0.0;
      } else if (u2.re == 0.0) {
        u2.re = 0.0;
        u2.im = -u2.im / ba;
      } else {
        u2.re /= ba;
        u2.im = -u2.im / ba;
      }

      h[(i + 6 * i) + 1].re = rt_hypotd_snf(h[(i + 6 * i) + 1].re, h[(i + 6 * i)
        + 1].im);
      h[(i + 6 * i) + 1].im = 0.0;
      b_xscal(5 - i, u2, h, (i + (i + 1) * 6) + 2);
      y.re = u2.re;
      y.im = -u2.im;
      b_k = i + 3;
      if (6 < b_k) {
        b_k = 6;
      }

      xscal(b_k, y, h, 1 + (i + 1) * 6);
      y.re = u2.re;
      y.im = -u2.im;
      c_xscal(y, z, 1 + (i + 1) * 6);
    }
  }

  i = 5;
  exitg1 = false;
  while ((!exitg1) && (i + 1 >= 1)) {
    L = -1;
    goto140 = false;
    its = 0;
    exitg2 = false;
    while ((!exitg2) && (its < 31)) {
      k = i;
      exitg3 = false;
      while ((!exitg3) && ((k + 1 > L + 2) && (!(fabs(h[k + 6 * (k - 1)].re) +
                fabs(h[k + 6 * (k - 1)].im) <= 6.0125050800269183E-292)))) {
        tst = (fabs(h[(k + 6 * (k - 1)) - 1].re) + fabs(h[(k + 6 * (k - 1)) - 1]
                .im)) + (fabs(h[k + 6 * k].re) + fabs(h[k + 6 * k].im));
        if (tst == 0.0) {
          if (k - 1 >= 1) {
            tst = fabs(h[(k + 6 * (k - 2)) - 1].re);
          }

          if (k + 2 <= 6) {
            tst += fabs(h[(k + 6 * k) + 1].re);
          }
        }

        if (fabs(h[k + 6 * (k - 1)].re) <= 2.2204460492503131E-16 * tst) {
          htmp1 = fabs(h[k + 6 * (k - 1)].re) + fabs(h[k + 6 * (k - 1)].im);
          tst = fabs(h[(k + 6 * k) - 1].re) + fabs(h[(k + 6 * k) - 1].im);
          if (htmp1 > tst) {
            ab = htmp1;
            ba = tst;
          } else {
            ab = tst;
            ba = htmp1;
          }

          htmp1 = fabs(h[k + 6 * k].re) + fabs(h[k + 6 * k].im);
          tst = fabs(h[(k + 6 * (k - 1)) - 1].re - h[k + 6 * k].re) + fabs(h[(k
            + 6 * (k - 1)) - 1].im - h[k + 6 * k].im);
          if (htmp1 > tst) {
            aa = htmp1;
            htmp1 = tst;
          } else {
            aa = tst;
          }

          s = aa + ab;
          tst = 2.2204460492503131E-16 * (htmp1 * (aa / s));
          if ((6.0125050800269183E-292 > tst) || rtIsNaN(tst)) {
            d0 = 6.0125050800269183E-292;
          } else {
            d0 = tst;
          }

          if (ba * (ab / s) <= d0) {
            exitg3 = true;
          } else {
            k--;
          }
        } else {
          k--;
        }
      }

      L = k - 1;
      if (k + 1 > 1) {
        h[k + 6 * (k - 1)].re = 0.0;
        h[k + 6 * (k - 1)].im = 0.0;
      }

      if (k + 1 >= i + 1) {
        goto140 = true;
        exitg2 = true;
      } else {
        if (its == 10) {
          t_re = 0.75 * fabs(h[(k + 6 * k) + 1].re) + h[k + 6 * k].re;
          ba = h[k + 6 * k].im;
        } else if (its == 20) {
          t_re = 0.75 * fabs(h[i + 6 * (i - 1)].re) + h[i + 6 * i].re;
          ba = h[i + 6 * i].im;
        } else {
          t_re = h[i + 6 * i].re;
          ba = h[i + 6 * i].im;
          y = h[(i + 6 * i) - 1];
          b_sqrt(&y);
          u2 = h[i + 6 * (i - 1)];
          b_sqrt(&u2);
          u_re = y.re * u2.re - y.im * u2.im;
          u_im = y.re * u2.im + y.im * u2.re;
          s = fabs(u_re) + fabs(u_im);
          if (s != 0.0) {
            htmp1 = 0.5 * (h[(i + 6 * (i - 1)) - 1].re - h[i + 6 * i].re);
            ab = 0.5 * (h[(i + 6 * (i - 1)) - 1].im - h[i + 6 * i].im);
            aa = fabs(htmp1) + fabs(ab);
            tst = fabs(htmp1) + fabs(ab);
            if (!((s > tst) || rtIsNaN(tst))) {
              s = tst;
            }

            if (ab == 0.0) {
              t_re = htmp1 / s;
              ba = 0.0;
            } else if (htmp1 == 0.0) {
              t_re = 0.0;
              ba = ab / s;
            } else {
              t_re = htmp1 / s;
              ba = ab / s;
            }

            tst = t_re;
            t_re = t_re * t_re - ba * ba;
            ba = tst * ba + ba * tst;
            if (u_im == 0.0) {
              u2.re = u_re / s;
              u2.im = 0.0;
            } else if (u_re == 0.0) {
              u2.re = 0.0;
              u2.im = u_im / s;
            } else {
              u2.re = u_re / s;
              u2.im = u_im / s;
            }

            y.re = t_re + (u2.re * u2.re - u2.im * u2.im);
            y.im = ba + (u2.re * u2.im + u2.im * u2.re);
            b_sqrt(&y);
            y.re *= s;
            y.im *= s;
            if (aa > 0.0) {
              if (ab == 0.0) {
                t_re = htmp1 / aa;
                ba = 0.0;
              } else if (htmp1 == 0.0) {
                t_re = 0.0;
                ba = ab / aa;
              } else {
                t_re = htmp1 / aa;
                ba = ab / aa;
              }

              if (t_re * y.re + ba * y.im < 0.0) {
                y.re = -y.re;
                y.im = -y.im;
              }
            }

            ba = htmp1 + y.re;
            aa = ab + y.im;
            if (aa == 0.0) {
              if (u_im == 0.0) {
                b_u_re = u_re / ba;
                tst = 0.0;
              } else if (u_re == 0.0) {
                b_u_re = 0.0;
                tst = u_im / ba;
              } else {
                b_u_re = u_re / ba;
                tst = u_im / ba;
              }
            } else if (ba == 0.0) {
              if (u_re == 0.0) {
                b_u_re = u_im / aa;
                tst = 0.0;
              } else if (u_im == 0.0) {
                b_u_re = 0.0;
                tst = -(u_re / aa);
              } else {
                b_u_re = u_im / aa;
                tst = -(u_re / aa);
              }
            } else {
              ab = fabs(ba);
              tst = fabs(aa);
              if (ab > tst) {
                s = aa / ba;
                tst = ba + s * aa;
                b_u_re = (u_re + s * u_im) / tst;
                tst = (u_im - s * u_re) / tst;
              } else if (tst == ab) {
                if (ba > 0.0) {
                  htmp1 = 0.5;
                } else {
                  htmp1 = -0.5;
                }

                if (aa > 0.0) {
                  tst = 0.5;
                } else {
                  tst = -0.5;
                }

                b_u_re = (u_re * htmp1 + u_im * tst) / ab;
                tst = (u_im * htmp1 - u_re * tst) / ab;
              } else {
                s = ba / aa;
                tst = aa + s * ba;
                b_u_re = (s * u_re + u_im) / tst;
                tst = (s * u_im - u_re) / tst;
              }
            }

            t_re = h[i + 6 * i].re - (u_re * b_u_re - u_im * tst);
            ba = h[i + 6 * i].im - (u_re * tst + u_im * b_u_re);
          }
        }

        goto70 = false;
        m = i;
        exitg3 = false;
        while ((!exitg3) && (m > k + 1)) {
          u2.re = h[(m + 6 * (m - 1)) - 1].re - t_re;
          u2.im = h[(m + 6 * (m - 1)) - 1].im - ba;
          tst = h[m + 6 * (m - 1)].re;
          s = (fabs(u2.re) + fabs(u2.im)) + fabs(tst);
          if (u2.im == 0.0) {
            u2.re /= s;
            u2.im = 0.0;
          } else if (u2.re == 0.0) {
            u2.re = 0.0;
            u2.im /= s;
          } else {
            u2.re /= s;
            u2.im /= s;
          }

          tst /= s;
          v[0] = u2;
          v[1].re = tst;
          v[1].im = 0.0;
          if (fabs(h[(m + 6 * (m - 2)) - 1].re) * fabs(tst) <=
              2.2204460492503131E-16 * ((fabs(u2.re) + fabs(u2.im)) * ((fabs(h
                  [(m + 6 * (m - 1)) - 1].re) + fabs(h[(m + 6 * (m - 1)) - 1].im))
                + (fabs(h[m + 6 * m].re) + fabs(h[m + 6 * m].im))))) {
            goto70 = true;
            exitg3 = true;
          } else {
            m--;
          }
        }

        if (!goto70) {
          u2.re = h[k + 6 * k].re - t_re;
          u2.im = h[k + 6 * k].im - ba;
          tst = h[(k + 6 * k) + 1].re;
          s = (fabs(u2.re) + fabs(u2.im)) + fabs(tst);
          if (u2.im == 0.0) {
            u2.re /= s;
            u2.im = 0.0;
          } else if (u2.re == 0.0) {
            u2.re = 0.0;
            u2.im /= s;
          } else {
            u2.re /= s;
            u2.im /= s;
          }

          tst /= s;
          v[0] = u2;
          v[1].re = tst;
          v[1].im = 0.0;
        }

        for (c_k = m; c_k <= i; c_k++) {
          if (c_k > m) {
            v[0] = h[(c_k + 6 * (c_k - 2)) - 1];
            v[1] = h[c_k + 6 * (c_k - 2)];
          }

          u2 = xzlarfg(&v[0], &v[1]);
          if (c_k > m) {
            h[(c_k + 6 * (c_k - 2)) - 1] = v[0];
            h[c_k + 6 * (c_k - 2)].re = 0.0;
            h[c_k + 6 * (c_k - 2)].im = 0.0;
          }

          tst = u2.re * v[1].re - u2.im * v[1].im;
          for (j = c_k - 1; j + 1 < 7; j++) {
            t_re = (u2.re * h[(c_k + 6 * j) - 1].re - -u2.im * h[(c_k + 6 * j) -
                    1].im) + tst * h[c_k + 6 * j].re;
            ba = (u2.re * h[(c_k + 6 * j) - 1].im + -u2.im * h[(c_k + 6 * j) - 1]
                  .re) + tst * h[c_k + 6 * j].im;
            h[(c_k + 6 * j) - 1].re -= t_re;
            h[(c_k + 6 * j) - 1].im -= ba;
            h[c_k + 6 * j].re -= t_re * v[1].re - ba * v[1].im;
            h[c_k + 6 * j].im -= t_re * v[1].im + ba * v[1].re;
          }

          if (c_k + 2 < i + 1) {
            b_k = c_k;
          } else {
            b_k = i - 1;
          }

          for (j = 0; j + 1 <= b_k + 2; j++) {
            t_re = (u2.re * h[j + 6 * (c_k - 1)].re - u2.im * h[j + 6 * (c_k - 1)]
                    .im) + tst * h[j + 6 * c_k].re;
            ba = (u2.re * h[j + 6 * (c_k - 1)].im + u2.im * h[j + 6 * (c_k - 1)]
                  .re) + tst * h[j + 6 * c_k].im;
            h[j + 6 * (c_k - 1)].re -= t_re;
            h[j + 6 * (c_k - 1)].im -= ba;
            h[j + 6 * c_k].re -= t_re * v[1].re - ba * -v[1].im;
            h[j + 6 * c_k].im -= t_re * -v[1].im + ba * v[1].re;
          }

          for (j = 0; j < 6; j++) {
            t_re = (u2.re * z[j + 6 * (c_k - 1)].re - u2.im * z[j + 6 * (c_k - 1)]
                    .im) + tst * z[j + 6 * c_k].re;
            ba = (u2.re * z[j + 6 * (c_k - 1)].im + u2.im * z[j + 6 * (c_k - 1)]
                  .re) + tst * z[j + 6 * c_k].im;
            z[j + 6 * (c_k - 1)].re -= t_re;
            z[j + 6 * (c_k - 1)].im -= ba;
            z[j + 6 * c_k].re -= t_re * v[1].re - ba * -v[1].im;
            z[j + 6 * c_k].im -= t_re * -v[1].im + ba * v[1].re;
          }

          if ((c_k == m) && (m > k + 1)) {
            u2.re = 1.0 - u2.re;
            u2.im = 0.0 - u2.im;
            ba = rt_hypotd_snf(u2.re, u2.im);
            if (u2.im == 0.0) {
              u2.re /= ba;
              u2.im = 0.0;
            } else if (u2.re == 0.0) {
              u2.re = 0.0;
              u2.im /= ba;
            } else {
              u2.re /= ba;
              u2.im /= ba;
            }

            tst = h[m + 6 * (m - 1)].re;
            htmp1 = h[m + 6 * (m - 1)].im;
            h[m + 6 * (m - 1)].re = tst * u2.re - htmp1 * -u2.im;
            h[m + 6 * (m - 1)].im = tst * -u2.im + htmp1 * u2.re;
            if (m + 2 <= i + 1) {
              tst = h[(m + 6 * m) + 1].re;
              htmp1 = h[(m + 6 * m) + 1].im;
              h[(m + 6 * m) + 1].re = tst * u2.re - htmp1 * u2.im;
              h[(m + 6 * m) + 1].im = tst * u2.im + htmp1 * u2.re;
            }

            for (j = m; j <= i + 1; j++) {
              if (j != m + 1) {
                if (6 > j) {
                  c = j + j * 6;
                  b_k = c + 6 * (5 - j);
                  while (c <= b_k) {
                    tst = h[c - 1].re;
                    htmp1 = h[c - 1].im;
                    h[c - 1].re = u2.re * tst - u2.im * htmp1;
                    h[c - 1].im = u2.re * htmp1 + u2.im * tst;
                    c += 6;
                  }
                }

                c = (j - 1) * 6;
                y.re = u2.re;
                y.im = -u2.im;
                b_k = (c + j) - 1;
                while (c + 1 <= b_k) {
                  tst = h[c].re;
                  htmp1 = h[c].im;
                  h[c].re = y.re * tst - y.im * htmp1;
                  h[c].im = y.re * htmp1 + y.im * tst;
                  c++;
                }

                c = (j - 1) * 6;
                y.re = u2.re;
                y.im = -u2.im;
                for (b_k = c; b_k + 1 <= c + 6; b_k++) {
                  tst = z[b_k].re;
                  htmp1 = z[b_k].im;
                  z[b_k].re = y.re * tst - y.im * htmp1;
                  z[b_k].im = y.re * htmp1 + y.im * tst;
                }
              }
            }
          }
        }

        u2 = h[i + 6 * (i - 1)];
        if (h[i + 6 * (i - 1)].im != 0.0) {
          tst = rt_hypotd_snf(h[i + 6 * (i - 1)].re, h[i + 6 * (i - 1)].im);
          h[i + 6 * (i - 1)].re = tst;
          h[i + 6 * (i - 1)].im = 0.0;
          if (u2.im == 0.0) {
            u2.re /= tst;
            u2.im = 0.0;
          } else if (u2.re == 0.0) {
            u2.re = 0.0;
            u2.im /= tst;
          } else {
            u2.re /= tst;
            u2.im /= tst;
          }

          if (6 > i + 1) {
            c = i + (i + 1) * 6;
            y.re = u2.re;
            y.im = -u2.im;
            b_k = (c + 6 * (4 - i)) + 1;
            while (c + 1 <= b_k) {
              tst = h[c].re;
              htmp1 = h[c].im;
              h[c].re = y.re * tst - y.im * htmp1;
              h[c].im = y.re * htmp1 + y.im * tst;
              c += 6;
            }
          }

          c = i * 6;
          b_k = c + i;
          while (c + 1 <= b_k) {
            tst = h[c].re;
            htmp1 = h[c].im;
            h[c].re = u2.re * tst - u2.im * htmp1;
            h[c].im = u2.re * htmp1 + u2.im * tst;
            c++;
          }

          c = i * 6;
          for (k = c; k + 1 <= c + 6; k++) {
            tst = z[k].re;
            htmp1 = z[k].im;
            z[k].re = u2.re * tst - u2.im * htmp1;
            z[k].im = u2.re * htmp1 + u2.im * tst;
          }
        }

        its++;
      }
    }

    if (!goto140) {
      info = i + 1;
      exitg1 = true;
    } else {
      i = L;
    }
  }

  return info;
}

/*
 * File trailer for xzhseqr.c
 *
 * [EOF]
 */
