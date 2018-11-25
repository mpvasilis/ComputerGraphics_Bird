#include <stdlib.h>
#include <stdio.h>

#include <stdarg.h>
#include <math.h>

#include "flocking/physics.h"

#ifndef OPEN_GL_LOADED
#define OPEN_GL_LOADED
#define GL_GLEXT_PROTOTYPES
#include "GL/glut.h"
#endif

#ifndef GRAPHICS_CONSTANTS
#define GRAPHICS_CONSTANTS


#define MAX_X 300
#define MAX_Y 300
#define MAX_Z 300
#define MIN_X -300
#define MIN_Y 0
#define MIN_Z -300

// OpenGL Window Settings
#define WINDOW_TITLE "Computer Graphics: Assign 1: OpenGL Bird"
#define WIDTH 600
#define HEIGHT 500
#define UPDATE_FREQUENCY 25


// Cameras
#define CAM_C_PERSPECTIVE 1
#define ORTHOGRAPHIC 2
#define CAM_A_SIDE 3
#define CAM_B_FRONT 4


// Logical
#define TRUE 1
#define FALSE 0


// Menu
#define START_ANIMATION 1
#define STOP_ANIMATION 2
#define CHANGE_CAMERA 3
#define EXIT 4


// Camera Settings
#define THIRD_PERSON_CAMERA_Y_OFFEST -20
#define THIRD_PERSON_CAMERA_Z_OFFEST -50

#endif

#include "bird.h"

// trignometric functions
#define trig_rad_cos(th) cos(3.1415926/180*(th))
#define trig_rad_sin(th) sin(3.1415926/180*(th))

Boid *boids;
Bird *bird;


void MenuSelect(int choice);