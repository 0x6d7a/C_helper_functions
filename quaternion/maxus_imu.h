/*
 * maxus_imu.h
 *
 *  Created on: May 7, 2019
 *  Author: ZENG Mao
 *
 */

#ifndef MAXUS_IMU_H
#define MAXUS_IMU_H

// #include "maxus_math_util.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>

#define GRAVITY (const float[4]){0,0,0,1}
#define DELTAT  0.02
#define G       9.81

extern void sum(float *l, float *r, float *output);
extern void mul(float val, float *l, float *output);
extern void cross(float *l, float *r, float *output);
extern void quadProd(float *q, float *p, float *output);
extern float invSqrt(float val);
extern void normalize(float *q, uint8_t len);
extern void rotate(float *q, float *v, float *output);
extern void invrotate(float *q, float *v, float *output);
extern void conjugate(float *q, float *q_hat);
extern void rpyCvt(float *q, float *roll, float *pitch, float *yaw);
extern void qsum(float *q, float *v, float *output);
extern void v3sum(float *q, float *p, float *output);
extern void qmul(float val, float *v, float *output);
extern void fuse(float *q, float *accel, float *gyro);
extern void initQuat(float *q);
extern void gyroToQuat(float *gyro, float *q);
extern void eulerToQuaternion(float *q, float roll, float pitch, float yaw);

#endif
