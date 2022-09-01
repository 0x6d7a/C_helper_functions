#include "maxus_imu.h"

int main(int argc, char const *argv[])
{
  float q[4] = {2,3,4,5};
  Maxus_IMU *imu = new Maxus_IMU((float *)q);

  float accel[3] = {11.235,-1.0647,-5.5578};
  float gyro[3] = {0.36469,-0.27855,0.97494};

  imu->normalize(imu->q, 4);
  printf("Norm Q:%f %f %f %f\n", imu->q[0],imu->q[1],imu->q[2],imu->q[3]);

  imu->attQuatUpdate(accel, gyro);
  imu->rpyCvt();
  float gz = G * cos(imu->roll) * cos(imu->pitch);
  printf("gz: %f\n", gz);
  return 0;
  return 0;
}
