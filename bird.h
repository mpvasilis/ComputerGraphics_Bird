
#ifndef BIRD_INC_GUARD
#define BIRD_INC_GUARD

#define BEAK_INNER_SIDE_LEN 1.0
#define BEAK_SHIFT 0.5
#define BEAK_OUTER_SIDE_LEN 2.0
#define BIRD_LENGTH 10.0
#define BIRD_HEIGHT 4.0
#define BEAK_LENGTH 4.0
#define NUM_HEAD_RADI 5

#define HEAD_END_RAD 4.0
#define HEAD_END_SHIFT 1
#define HEAD_END_LENGTH 2.0

#define HEAD_INNER_RAD 4.5
#define HEAD_INNER_X_SHIFT 2.1
#define HEAD_INNER_SHIFT 0.25
#define HEAD_INNER_LENGTH 2.0

#define HEAD_START_RAD 3.0
#define HEAD_START_SHIFT 1.25
#define HEAD_START_X_SHIFT 2.20
#define HEAD_START_LENGTH 2.0

#define BODY_FRONT_RAD 3.5
#define BODY_FRONT_SHIFT 0.25
#define BODY_FRONT_X_SHIFT 1.5
#define BODY_FRONT_LENGTH 2.5

#define BODY_MID_RAD 4
#define BODY_MID_LENGTH 4
#define BODY_MID_X_SHIFT 1.75
#define BODY_MID_SHIFT 1

#define BODY_BACK_RAD 4
#define BODY_BACK_LENGTH 15
#define BODY_BACK_X_SHIFT 2
#define BODY_BACK_SHIFT 0

#define BODY_REAR_RAD 1
#define BODY_REAR_LENGTH 2
#define BODY_REAR_X_SHIFT 2.5
#define BODY_REAR_SHIFT 0

#define NOT_FLAPPING 0
#define FLAPPING_DOWN 1
#define FLAPPING_UP 2
#define RETURNING 3

#define BEAK_R 0.94902
#define BEAK_G 0.623529
#define BEAK_B 0.121569

#define HEAD_R 153
#define HEAD_G 42
#define HEAD_B 89

#define BACK_HEAD_R 153
#define BACK_HEAD_G 42
#define BACK_HEAD_B 42

#define BODY_R 153
#define BODY_G 42
#define BODY_B 42

#define WING_R 70
#define WING_G 83
#define WING_B 14

#define NUM_WING_GUIDE_POINTS 5

#define BIRD_SCALE 7


#include <stdio.h>
#include <stdlib.h>

#include "bird_physics.h"

#include "quadobj.h"

typedef struct
{
    QuadObject quadObject;
    int flapping; 
    float flappingAmount;

    int * frontTopLeftWing;
    int * backTopLeftWing;
    int * frontBottomLeftWing;
    int * backBottomLeftWing;

    int * frontTopRightWing;
    int * backTopRightWing;
    int * frontBottomRightWing;
    int * backBottomRightWing;

    ColoredVertex * origFrontTopLeftWing;
    ColoredVertex * origBackTopLeftWing;
    ColoredVertex * origFrontBottomLeftWing;
    ColoredVertex * origBackBottomLeftWing;

    ColoredVertex * origFrontTopRightWing;
    ColoredVertex * origBackTopRightWing;
    ColoredVertex * origFrontBottomRightWing;
    ColoredVertex * origBackBottomRightWing;

    int startWingQuadIndex;
    int endWingQuadIndex;

    Bird_physics * bird_physics;

} Bird;

void bird_initBird(Bird * birdPtr, Bird_physics * bird_physics_ptr);

void bird_initBirdModel(Bird * birdModelPtr);

void bird_draw(Bird * birdPtr);

void bird_flap(Bird * birdPtr);

void bird_animate(Bird * birdPtr);

void bird_step(Bird * birdPtr, Bird_physics * bird_physics, float timestep);

void bird_setParams(Bird * birdPtr);

#endif

