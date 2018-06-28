/*
 * File: xscal.h
 *
 * MATLAB Coder version            : 3.3
 * C/C++ source code generated on  : 31-May-2018 13:39:01
 */

#ifndef XSCAL_H
#define XSCAL_H

/* Include Files */
#include <float.h>
#include <math.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "rt_defines.h"
#include "rt_nonfinite.h"
#include "rtwtypes.h"
#include "music_angle_types.h"

/* Function Declarations */
extern void b_xscal(int n, const creal_T a, creal_T x[36], int ix0);
extern void c_xscal(const creal_T a, creal_T x[36], int ix0);
extern void xscal(int n, const creal_T a, creal_T x[36], int ix0);

#endif

/*
 * File trailer for xscal.h
 *
 * [EOF]
 */
