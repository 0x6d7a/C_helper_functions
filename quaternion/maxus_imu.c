/*
 * maxus_imu.cpp
 *
 *  Created on: May 7, 2019
 *  Author: ZENG Mao
 *
 */

#include "maxus_imu.h"

#define GAIN 3

void cross(float *l, float *r, float *output) {
  output[0] = l[1] * r[2] - l[2] * r[1];
  output[1] = l[2] * r[0] - l[0] * r[2];
  output[2] = l[0] * r[1] - l[1] * r[0];
}

void quadProd(float *q, float *p, float * output) {
  output[0] = q[0]*p[0] - q[1]*p[1] - q[2]*p[2] - q[3]*p[3];
  output[1] = q[0]*p[1] + q[1]*p[0] + q[2]*p[3] - q[3]*p[2];
  output[2] = q[0]*p[2] + q[2]*p[0] - q[1]*p[3] + q[3]*p[1];
  output[3] = q[0]*p[3] + q[3]*p[0] + q[1]*p[2] - q[2]*p[1];
}

float invSqrt(float x) {
  uint32_t i = 0x5F1F1412 - (*(uint32_t*)&x >> 1);
  float tmp = *(float*)&i;
  return tmp * (1.69000231f - 0.714158168f * x * tmp * tmp);
}

void normalize(float *q, uint8_t len) {
  float norm = 0;
  for (int i = 0; i < len; ++i)
  {
    norm += q[i] * q[i];
  }
  float recipnorm = invSqrt(norm);
  for (int i = 0; i < len; ++i)
  {
    q[i] *= recipnorm;
  }
}

void conjugate(float *q, float *q_hat) {
  q_hat[0] = q[0];
  q_hat[1] = q[1] * -1;
  q_hat[2] = q[2] * -1;
  q_hat[3] = q[3] * -1;
}

void rotate(float *q, float *v, float *output) {
  // qvq^
  // sum(v, cross(sum(r,r), sum(cross(r, v), mul(q[0], v))));
  float *temp = (float *)malloc(sizeof(float) * 4);
  float *q_hat = (float *)malloc(sizeof(float) * 4);
  conjugate(q, q_hat);
  quadProd(q, v, temp);
  quadProd(temp, q_hat, output);
  free(q_hat);
  free(temp);

}

void invrotate(float *q, float *v, float *output) {
  float *temp = (float *)malloc(sizeof(float) * 4);
  float *q_hat = (float *)malloc(sizeof(float) * 4);
  conjugate(q, q_hat);
  quadProd(q_hat, v, temp);
  quadProd(temp, q, output);
  free(q_hat);
  free(temp);

  // q^vq
  // sum(v, cross(sum(q,q), sum(cross(q, v), mul(q[0], v))));
}

void qsum(float *q, float *p, float *output) {
  output[0] = q[0] + p[0];
  output[1] = q[1] + p[1];
  output[2] = q[2] + p[2];
  output[3] = q[3] + p[3];
}

void v3sum(float *q, float *p, float *output) {
  output[0] = q[0] + p[0];
  output[1] = q[1] + p[1];
  output[2] = q[2] + p[2];
}

void rpyCvt(float *q, float *roll, float *pitch, float *yaw) {
  *roll = atan2(2 * (q[0] * q[1] + q[2] * q[3]), 1 - 2 * (q[1] * q[1] + q[2] * q[2]));
  *pitch = asin(2 * (q[0] * q[2] - q[1] * q[3]));
  *yaw = atan2(2 * (q[0] * q[3] + q[1] * q[2]), 1 - 2 * (q[2] * q[2] + q[3] * q[3]));
}

void initQuat(float *q) {
  q[0] = 1;
  q[1] = 0;
  q[2] = 0;
  q[3] = 0;
}

void gyroToQuat(float *gyro, float *q_gyro) {
  float alpha = 0.5 * DELTAT;
  q_gyro[1] = gyro[1] * alpha;
  q_gyro[2] = gyro[2] * alpha;
  q_gyro[3] = gyro[3] * alpha;
  q_gyro[0] = 1 - 0.5 * (q_gyro[1] * q_gyro[1] + q_gyro[2] * q_gyro[2] + q_gyro[3] * q_gyro[3]);
}

void mul(float val, float *l, float *output) {
  output[0] = val * l[0];
  output[1] = val * l[1];
  output[2] = val * l[2];
}

void fuse(float *q, float *accel, float *gyro) {
  float *tmp_1 = (float *)malloc(sizeof(float) * 4);
  memset(tmp_1, 0, sizeof(float) * 4);
  float *tmp_2 = (float *)malloc(sizeof(float) * 4);
  memset(tmp_2, 0, sizeof(float) * 4);
  float *q_gyro = (float *)malloc(sizeof(float) * 4);

  normalize(accel, 3);
  invrotate(q, (float *)GRAVITY, tmp_1);
  cross(accel, tmp_1 + 1, tmp_2 + 1);
  #ifdef GAIN
  mul(GAIN, tmp_2 + 1, tmp_2 + 1);
  #endif
  v3sum(gyro, tmp_2 + 1, tmp_1 + 1);
  gyroToQuat(tmp_1, q_gyro);
  quadProd(q, q_gyro, tmp_2);
  memcpy(q, tmp_2, 4 * sizeof(float));
  normalize(q, 4);

  free(tmp_1);
  free(tmp_2);
  free(q_gyro);
}

void eulerToQuaternion(float *q, float roll, float pitch, float yaw) {

  float cy = cos(yaw * 0.5);
  float sy = sin(yaw * 0.5);
  float cp = cos(pitch * 0.5);
  float sp = sin(pitch * 0.5);
  float cr = cos(roll * 0.5);
  float sr = sin(roll * 0.5);

  q[0] = cy * cp * cr + sy * sp * sr;
  q[1] = cy * cp * sr - sy * sp * cr;
  q[2] = sy * cp * sr + cy * sp * cr;
  q[3] = sy * cp * cr - cy * sp * sr;

}
