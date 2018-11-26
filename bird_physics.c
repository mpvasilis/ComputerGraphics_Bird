
#include "bird_physics.h"

void Bird_physics_init(Bird_physics * bird_physics, float x, float y, float z)
{
    Bird_physics_initFull(bird_physics, x, y, z, BIRD_MIN_X, BIRD_MIN_Y, BIRD_MIN_Z,
        BIRD_MAX_X, BIRD_MAX_Y, BIRD_MAX_Z);
}

void Bird_physics_initFull(Bird_physics * bird_physics, float x, float y, float z, int minX, int minY,
    int minZ, int maxX, int maxY, int maxZ)
{
    PhysicsObject_init(&(bird_physics->physicsObject), 1, x, y, z);
    bird_physics->r = START_BIRD_ANGLE;
    bird_physics->maxForce = MAX_BIRD_FORCE;
    bird_physics->maxSpeed = MAX_BIRD_SPEED;
    bird_physics->minX = minX;
    bird_physics->minY = minY;
    bird_physics->minZ = minZ;
    bird_physics->maxX = maxX;
    bird_physics->maxY = maxY;
    bird_physics->maxZ = maxZ;
 
}

void Bird_physics_setPos(Bird_physics * bird_physics, float x, float y, float z)
{
    bird_physics->physicsObject.position.x = x;
    bird_physics->physicsObject.position.y = y;
    bird_physics->physicsObject.position.z = z;
}

void Bird_physics_step(Bird_physics * bird_physics, Bird_physics * bird_physicss, int numBoids,float timestep, char ignoreSight)
{
    PhysicsVector * acceleration;

    Bird_physics_updatePosition(bird_physics, timestep);

    // Reset acceleration for next sum of forces
    acceleration = &(bird_physics->physicsObject.acceleration);
    acceleration->x = 0;
    acceleration->y = 0;
    acceleration->z = 0;

    PhysicsVector_normalize(&(bird_physics->heading), &(bird_physics->physicsObject.velocity));
}



void Bird_physics_updatePosition(Bird_physics * bird_physics, float timestep)
{
    PhysicsObject * physicsObject = &(bird_physics->physicsObject);
    PhysicsVector * velocity;

    // Apply acceleration to velocity
    PhysicsObject_updateVelocity(physicsObject, timestep);

    // Limit velocity
    velocity = &(physicsObject->velocity);
    PhysicsVector_limit(velocity, velocity, bird_physics->maxSpeed);

    // Apply velocity to position
    PhysicsObject_updatePosition(physicsObject, timestep);

    // Wrap on borders
    Bird_physics_wrapOnBorders(bird_physics);
}

void Bird_physics_wrapOnBorders(Bird_physics * bird_physics)
{
    PhysicsVector * position = &(bird_physics->physicsObject.position);
    PhysicsVector * velocity = &(bird_physics->physicsObject.velocity);
    
    if(position->x < bird_physics->minX)
    {
        position->x = bird_physics->minX;
        velocity->x = -velocity->x;
    }

    if(position->y < bird_physics->minY) 
    {
        position->y = bird_physics->minY;
        velocity->y = -velocity->y;
    }

    if(position->z < bird_physics->minZ) 
    {
        position->z = bird_physics->minZ;
        velocity->z = -velocity->z;
    }

    if(position->x > bird_physics->maxX)
    {
        position->x = bird_physics->maxX;
        velocity->x = -velocity->x;
    }

    if(position->y > bird_physics->maxY)
    {
        position->y = bird_physics->maxY;
        velocity->y = -velocity->y;
    }

    if(position->z > bird_physics->maxZ)
    {
        position->z = bird_physics->maxZ;
        velocity->z = -velocity->z;
    }
}

float Bird_physics_getX(Bird_physics * bird_physics)
{
    PhysicsVector * position = &(bird_physics->physicsObject.position);
    return position->x;
}

float Bird_physics_getY(Bird_physics * bird_physics)
{
    PhysicsVector * position = &(bird_physics->physicsObject.position);
    return position->y;
}

float Bird_physics_getZ(Bird_physics * bird_physics)
{
    PhysicsVector * position = &(bird_physics->physicsObject.position);
    return position->z;
}

void Bird_physics_setVel(Bird_physics * bird_physics, float x, float y, float z)
{
    PhysicsVector * velocity = &(bird_physics->physicsObject.velocity);
    velocity->x = x;
    velocity->y = y;
    velocity->z = z;
}
