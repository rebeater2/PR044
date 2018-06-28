/*
 * File: fft.h
 *
 * MATLAB Coder version            : 3.3
 * C/C++ source code generated on  : 31-May-2018 13:39:01
 */

#ifndef FFT_H
#define FFT_H

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
extern void fft(const double x[8192], creal_T y[16384]);

#endif

/*
 * File trailer for fft.h
 *
 * [EOF]
 */
