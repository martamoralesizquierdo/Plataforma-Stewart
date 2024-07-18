// stewart_kinematics.h

#ifndef STEWART_KINEMATICS_H
#define STEWART_KINEMATICS_H

#ifdef __cplusplus
extern "C" {
#endif

void define_anchor_points(float B[3][6], float P[3][6], float r_base, float r_plat, float height_plat);
void eul2rotm(float R[3][3], float yaw, float pitch, float roll);
void stewart_inverse_kinematics(float d[6], float x, float y, float z, float roll, float pitch, float yaw, float B[3][6], float P[3][6]);

#ifdef __cplusplus
}
#endif

#endif
