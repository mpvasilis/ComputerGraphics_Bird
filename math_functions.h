

#ifndef LINALG_INC_GUARD
#define LINALG_INC_GUARD

#include <math.h>

#include "physics.h"

#define PI 3.14159265

void linalg_normalize(float * vect);

void linalg_crossProduct(float *c, float a[3], float b[3]);

float linalg_calcPitch(PhysicsVector * from, PhysicsVector * to);

float linalg_calcYaw(PhysicsVector * from, PhysicsVector * to);

float linalg_calcPitchDeg(PhysicsVector * from, PhysicsVector * to);

float linalg_calcYawDeg(PhysicsVector * from, PhysicsVector * to);

#endif