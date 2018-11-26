
#ifndef FINAL_PHYSICS_HEADER
#define FINAL_PHYSICS_HEADER

#define GL_GLEXT_PROTOTYPES
#include "../GL/glut.h"
#include <math.h>
#include <stdlib.h>

typedef struct
{
    GLfloat x;
    GLfloat y;
    GLfloat z;
} PhysicsVector;

typedef struct
{
    float mass;
    PhysicsVector position;
    PhysicsVector acceleration;
    PhysicsVector velocity;
} PhysicsObject;

void PhysicsVector_init(PhysicsVector * vector, GLfloat x, GLfloat y, GLfloat z);

void PhysicsVector_add(PhysicsVector * dest, PhysicsVector * op1, PhysicsVector * op2);

void PhysicsVector_sub(PhysicsVector * dest, PhysicsVector * op1, PhysicsVector * op2);

int PhysicsVector_eq(PhysicsVector * op1, PhysicsVector * op2, float tollerance);

void PhysicsVector_mult(PhysicsVector * dest, PhysicsVector * op1, PhysicsVector * op2);

void PhysicsVector_multScalar(PhysicsVector * dest, PhysicsVector * op1, float op2);

void PhysicsVector_div(PhysicsVector * dest, PhysicsVector * op1, PhysicsVector * op2);

void PhysicsVector_divScalar(PhysicsVector * dest, PhysicsVector * op1,float op2);

float PhysicsVector_length(PhysicsVector * target);

void PhysicsVector_distVector(PhysicsVector * dest, PhysicsVector * op1, PhysicsVector * op2);

float PhysicsVector_dist(PhysicsVector * op1, PhysicsVector * op2);

void PhysicsVector_normalize(PhysicsVector * target, PhysicsVector * op);

void PhysicsVector_limit(PhysicsVector * target, PhysicsVector * op, float limit);

void PhysicsObject_init(PhysicsObject * obj, float mass, GLfloat x, GLfloat y, GLfloat z);

void PhysicsObject_addForce(PhysicsObject * physicsObject, PhysicsVector * force);

void PhysicsObject_updateVelocity(PhysicsObject * physicsObject, float time);

void PhysicsObject_updatePosition(PhysicsObject * physicsObject, float time);

float PhysicsVector_dot(PhysicsVector * op1, PhysicsVector * op2);

float PhysicsVector_angle(PhysicsVector * op1, PhysicsVector * op2);

#endif