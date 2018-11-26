

#ifndef FINAL_BIRD_HEADER
#define FINAL_BIRD_HEADER

#include <stdlib.h> 

#ifndef BIRD_FLOCKING_CONSTANTS
#define BIRD_FLOCKING_CONSTANTS

#define MAX_BIRD_SPEED 3
#define MAX_BIRD_FORCE 0.05
#define START_BIRD_ANGLE 3


#define BIRD_MIN_X -400
#define BIRD_MAX_X 400
#define BIRD_MIN_Y 50
#define BIRD_MAX_Y 300
#define BIRD_MIN_Z -400
#define BIRD_MAX_Z 400

#define MATH_PI 3.1415926535897

#define FALSE 0
#define TRUE 1

#endif

#include "physics.h"


typedef struct
{
    PhysicsObject physicsObject;
    PhysicsVector heading;
    float r;
    float maxForce;
    float maxSpeed;
    int minX;
    int minY;
    int minZ;
    int maxX;
    int maxY;
    int maxZ;

} Bird_physics;

void Bird_physics_init(Bird_physics * bird_physics, float x, float y, float z);

void Bird_physics_setPos(Bird_physics * bird_physics, float x, float y, float z);

void Bird_physics_initFull(Bird_physics * bird_physics, float x, float y, float z, int minX, int minY,
    int minZ, int maxX, int maxY, int maxZ);

void Bird_physics_step(Bird_physics * bird_physics, Bird_physics * bird_physicss, int numBoids,
     float timestep,
    char ignoreSight);

void Bird_physics_updatePosition(Bird_physics * bird_physics, float timestep);

void Bird_physics_wrapOnBorders(Bird_physics * bird_physics);

float Bird_physics_getX(Bird_physics * bird_physics);

float Bird_physics_getY(Bird_physics * bird_physics);

float Bird_physics_getZ(Bird_physics * bird_physics);

void Bird_physics_setVel(Bird_physics * bird_physics, float x, float y, float z);

#endif