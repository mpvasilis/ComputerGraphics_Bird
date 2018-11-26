

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
    float seperationWeight;
    float alignWeight;
    float cohesionWeight;
} Bird_physics;

/**
 * Name: Bird_physics_init(Bird_physics * boid, float x, float y, float z)
 * Desc: Contructor for a Bird_physics
 * Para: boid, The Bird_physics object to initalize
 *       x, The starting x position of the boid.
 *       y, The starting y position of the boid.
 *       z, The starting z position of the boid.
**/
void Bird_physics_init(Bird_physics * boid, float x, float y, float z);


/**
 * Name: Bird_physics_setPos
 * Desc: Set the current position of the given Bird_physics object.
 * Para: boid, The boid to set the position of.
 *       x, The boid's new x position.
 *       y, The boid's new y position.
 *       z, The boid's new z position.
**/
void Bird_physics_setPos(Bird_physics * boid, float x, float y, float z);

/**
 * Name: Bird_physics_initFull
 * Desc: Full constructor for a Bird_physics with custom position bounds
 * Para: boid, The Bird_physics object to initalize
 *       x, The starting x position of the boid.
 *       y, The starting y position of the boid.
 *       z, The starting z position of the boid.
 *       minX, The minimum allowable x position of a boid.
 *       minY, The minimum allowable y position of a boid.
 *       minZ, The minimum allowable z position of a boid.
 *       maxX, The minimum allowable x position of a boid.
 *       maxY, The minimum allowable y position of a boid.
 *       maxZ, The minimum allowable z position of a boid.
**/
void Bird_physics_initFull(Bird_physics * boid, float x, float y, float z, int minX, int minY,
    int minZ, int maxX, int maxY, int maxZ);

/**
 * Name: Bird_physics_step
 * Desc: Update the position of a boid in relation to all other boids.
 * Para: boid, The Bird_physics to update.
 *       boids, The other Boids in the simulation.
 *       numBoids, The number of boids in boids.
 *       timestep, The time to apply the resulting force for.
 *       ignoreSight, If TRUE the angle field of view for this boid will not be
 *          checked in calculations.
**/
void Bird_physics_step(Bird_physics * boid, Bird_physics * boids, int numBoids,
     float timestep,
    char ignoreSight);

/**
 * Name: Bird_physics_updatePosition
 * Desc: Update the position of a boid given a timestep and its currently
 *       applied forces.
 * Para: boid, The Bird_physics to update.
 *       timestep, The amount of time to apply current forces for.
**/
void Bird_physics_updatePosition(Bird_physics * boid, float timestep);

/**
 * Name: Bird_physics_wrapOnBorders
 * Desc: If the current boid is outside of its physics bounds, will wrap around.
 * Para: boid, The Bird_physics to wrap.
**/
void Bird_physics_wrapOnBorders(Bird_physics * boid);

/**
 * Name: Bird_physics_getX(Bird_physics * boid)
 * Desc: Get the current global x position of this boid.
 * Para: boid, The boid to get the current x position for.
**/
float Bird_physics_getX(Bird_physics * boid);

/**
 * Name: Bird_physics_getY(Bird_physics * boid)
 * Desc: Get the current global y position of this boid.
 * Para: boid, The boid to get the current y position for.
**/
float Bird_physics_getY(Bird_physics * boid);

/**
 * Name: Bird_physics_getZ(Bird_physics * boid)
 * Desc: Get the current global z position of this boid.
**/
float Bird_physics_getZ(Bird_physics * boid);

/**
 * Name: Bird_physics_setVel(Bird_physics * boid, float x, float y, float z)
 * Desc: Artifically set the current velocity for this boid.
 * Para: boid, The boid to set the velocity.
 *       x, The new x component of this boid's velocity.
 *       y, The new y component of this boid's velocity.
 *       z, The new z component of this boid's velocity.
**/
void Bird_physics_setVel(Bird_physics * boid, float x, float y, float z);

#endif