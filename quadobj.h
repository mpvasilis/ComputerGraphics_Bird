
#ifndef quad_OBJ_INC_GUARD
#define quad_OBJ_INC_GUARD

#include <stdlib.h>
#include <string.h>

#ifndef OPEN_GL_LOADED
#define OPEN_GL_LOADED
#define GL_GLEXT_PROTOTYPES
#include "GL/glut.h"
#endif
#include "math_functions.h"

#define FALSE 0
#define TRUE 1
#define NUM_VERT_PER_QUAD 4

typedef struct
{
   GLfloat pos[3];
   GLfloat col[3];
} ColoredVertex;


typedef struct
{
   unsigned int ver[4];
   GLfloat norm[3];
   int hasTexture;
   int textureNum;
} Quad;


typedef struct 
{
   ColoredVertex * ver;
   int numVer;
   Quad * quad;
   int numQuad;
   short int outOfBounds;
   int numQuadAssigned;
   int numVerAssigned;

   GLfloat r;
   GLfloat g;
   GLfloat b;
   GLfloat x;
   GLfloat y;
   GLfloat z;
   int hasTexture;
   int textureNum;

   // Translation, rotation, scale
   GLfloat curX;
   GLfloat curY;
   GLfloat curZ;
   GLfloat curRot;
   GLfloat curRoll;
   GLfloat curPitch;
   GLfloat curYaw;
   GLfloat xScale;
   GLfloat yScale;
   GLfloat zScale;

} QuadObject;

typedef struct
{
   GLfloat pos[4];
   GLfloat diffuse[4];
   GLfloat specular[4];
   GLfloat ambient[4];
}light_t;


void quadobject_init(QuadObject * obj, int numVer, int numQuad);

void quadobject_setNextColor(QuadObject * obj, GLfloat r, GLfloat g, GLfloat b);

void quadobject_setNextPos(QuadObject * obj, GLfloat x, GLfloat y, GLfloat z);

void quadobject_setNextTexture(QuadObject * obj, int texture);

void quadobject_setNoTexture(QuadObject * obj);

void quadobject_setNextR(QuadObject * obj, GLfloat r);

void quadobject_setNextG(QuadObject * obj, GLfloat g);

void quadobject_setNextB(QuadObject * obj, GLfloat b);

void quadobject_setNextX(QuadObject * obj, GLfloat x);

void quadobject_setNextY(QuadObject * obj, GLfloat y);

void quadobject_setNextZ(QuadObject * obj, GLfloat z);

void quadobject_moveNextX(QuadObject * obj, GLfloat dx);

void quadobject_moveNextY(QuadObject * obj, GLfloat dy);

void quadobject_moveNextZ(QuadObject * obj, GLfloat dz);

void quadobject_createQuadFromPrev(QuadObject * obj);

void quadobject_setVer(QuadObject * obj, int verId);

void quadobject_draw(QuadObject * obj);

void quadobject_drawSpecific(QuadObject * obj, int numQuads, int startQuad);

void quadobject_drawSpecificRadially(QuadObject * obj, int numQuads,
   int startQuad, float xCenter, float yCenter, float zCenter);

int quadobject_addVer(QuadObject * obj);

ColoredVertex * quadobject_getVer(QuadObject * obj, unsigned int vertNum);

int quadobject_addQuad(QuadObject * obj, unsigned int v0Index,
   unsigned int v1Index, unsigned int v2Index, unsigned int v3Index);

int quadobject_addQuadBackwards(QuadObject * obj, unsigned int v0Index,
   unsigned int v1Index, unsigned int v2Index, unsigned int v3Index);

void quadobject_del(QuadObject * obj);

void quadobject_fixQuad(QuadObject * obj, int id);

void quad_init(Quad * obj, unsigned int * ver, ColoredVertex * pointa,
    ColoredVertex * pointb, ColoredVertex * pointc);

void quad_fixNormal(Quad * obj, ColoredVertex * pointa,
    ColoredVertex * pointb, ColoredVertex * pointc);

#endif
