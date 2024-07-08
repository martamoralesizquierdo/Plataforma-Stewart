// stewart_kinematics.c

#include "stewart_kinematics.h"
#include <math.h>

void define_anchor_points(float B[3][6], float P[3][6], float r_base, float r_plat, float height_plat) {
  float theta_base[6];
  float theta_plat[6];
  for (int i = 0; i < 6; i++) {
    theta_base[i] = 2 * M_PI / 6 * i;
    theta_plat[i] = 2 * M_PI / 6 * i + M_PI / 6;
  }

  for (int i = 0; i < 6; i++) {
    B[0][i] = r_base * cos(theta_base[i]);
    B[1][i] = r_base * sin(theta_base[i]);
    B[2][i] = 0;

    P[0][i] = r_plat * cos(theta_plat[i]);
    P[1][i] = r_plat * sin(theta_plat[i]);
    P[2][i] = height_plat;
  }
}

void eul2rotm(float R[3][3], float yaw, float pitch, float roll) {
  float cy = cos(yaw);
  float sy = sin(yaw);
  float cp = cos(pitch);
  float sp = sin(pitch);
  float cr = cos(roll);
  float sr = sin(roll);

  R[0][0] = cy * cp;
  R[0][1] = cy * sp * sr - sy * cr;
  R[0][2] = cy * sp * cr + sy * sr;
  R[1][0] = sy * cp;
  R[1][1] = sy * sp * sr + cy * cr;
  R[1][2] = sy * sp * cr - cy * sr;
  R[2][0] = -sp;
  R[2][1] = cp * sr;
  R[2][2] = cp * cr;
}

void stewart_inverse_kinematics(float d[6], float x, float y, float z, float roll, float pitch, float yaw, float B[3][6], float P[3][6]) {
  float R[3][3];
  eul2rotm(R, yaw, pitch, roll);

  float pos[3] = {x, y, z};
  float plat_positions[3][6];

  for (int i = 0; i < 6; i++) {
    for (int j = 0; j < 3; j++) {
      plat_positions[j][i] = R[j][0] * P[0][i] + R[j][1] * P[1][i] + R[j][2] * P[2][i] + pos[j];
    }
  }

  for (int i = 0; i < 6; i++) {
    float dx = plat_positions[0][i] - B[0][i];
    float dy = plat_positions[1][i] - B[1][i];
    float dz = plat_positions[2][i] - B[2][i];
    d[i] = sqrt(dx * dx + dy * dy + dz * dz);
  }
}
