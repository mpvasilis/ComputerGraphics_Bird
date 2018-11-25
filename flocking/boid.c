
#include "boid.h"

void Boid_init(Boid * boid, float x, float y, float z)
{
    Boid_initFull(boid, x, y, z, BOID_MIN_X, BOID_MIN_Y, BOID_MIN_Z,
        BOID_MAX_X, BOID_MAX_Y, BOID_MAX_Z);
}

void Boid_initFull(Boid * boid, float x, float y, float z, int minX, int minY,
    int minZ, int maxX, int maxY, int maxZ)
{
    PhysicsObject_init(&(boid->physicsObject), 1, x, y, z);
    boid->r = START_BOID_ANGLE;
    boid->maxForce = MAX_BOID_FORCE;
    boid->maxSpeed = MAX_BOID_SPEED;
    boid->minX = minX;
    boid->minY = minY;
    boid->minZ = minZ;
    boid->maxX = maxX;
    boid->maxY = maxY;
    boid->maxZ = maxZ;
 
}


void Boid_setPos(Boid * boid, float x, float y, float z)
{
    boid->physicsObject.position.x = x;
    boid->physicsObject.position.y = y;
    boid->physicsObject.position.z = z;
}

void Boid_step(Boid * boid, Boid * boids, int numBoids,float timestep, char ignoreSight)
{
    PhysicsVector * acceleration;

    Boid_updatePosition(boid, timestep);

    // Reset acceleration for next sum of forces
    acceleration = &(boid->physicsObject.acceleration);
    acceleration->x = 0;
    acceleration->y = 0;
    acceleration->z = 0;

    PhysicsVector_normalize(&(boid->heading), &(boid->physicsObject.velocity));
}



void Boid_updatePosition(Boid * boid, float timestep)
{
    PhysicsObject * physicsObject = &(boid->physicsObject);
    PhysicsVector * velocity;

    // Apply acceleration to velocity
    PhysicsObject_updateVelocity(physicsObject, timestep);

    // Limit velocity
    velocity = &(physicsObject->velocity);
    PhysicsVector_limit(velocity, velocity, boid->maxSpeed);

    // Apply velocity to position
    PhysicsObject_updatePosition(physicsObject, timestep);

    // Wrap on borders
    Boid_wrapOnBorders(boid);
}

void Boid_wrapOnBorders(Boid * boid)
{
    PhysicsVector * position = &(boid->physicsObject.position);
    PhysicsVector * velocity = &(boid->physicsObject.velocity);
    
    if(position->x < boid->minX)
    {
        position->x = boid->minX;
        velocity->x = -velocity->x;
    }

    if(position->y < boid->minY) 
    {
        position->y = boid->minY;
        velocity->y = -velocity->y;
    }

    if(position->z < boid->minZ) 
    {
        position->z = boid->minZ;
        velocity->z = -velocity->z;
    }

    if(position->x > boid->maxX)
    {
        position->x = boid->maxX;
        velocity->x = -velocity->x;
    }

    if(position->y > boid->maxY)
    {
        position->y = boid->maxY;
        velocity->y = -velocity->y;
    }

    if(position->z > boid->maxZ)
    {
        position->z = boid->maxZ;
        velocity->z = -velocity->z;
    }
}

float Boid_getX(Boid * boid)
{
    PhysicsVector * position = &(boid->physicsObject.position);
    return position->x;
}

float Boid_getY(Boid * boid)
{
    PhysicsVector * position = &(boid->physicsObject.position);
    return position->y;
}

float Boid_getZ(Boid * boid)
{
    PhysicsVector * position = &(boid->physicsObject.position);
    return position->z;
}

void Boid_setVel(Boid * boid, float x, float y, float z)
{
    PhysicsVector * velocity = &(boid->physicsObject.velocity);
    velocity->x = x;
    velocity->y = y;
    velocity->z = z;
}
