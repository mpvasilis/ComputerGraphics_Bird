
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

/**
 * Name: ColoredVertex
 * Desc: Vertex with RGB coloring and XYZ position
**/
typedef struct
{
   GLfloat pos[3];
   GLfloat col[3];
} ColoredVertex;

/**
 * Name: Quad
 * Desc: Collection of four verticies and the normal to the front face of those
 *       verticies.
**/
typedef struct
{
   unsigned int ver[4];
   GLfloat norm[3];
   int hasTexture;
   int textureNum;
} Quad;

/**
 * Name: QuadObject
 * Desc: High level "model" like struct.
**/
typedef struct 
{
   // Persistant values
   ColoredVertex * ver;
   int numVer;
   Quad * quad;
   int numQuad;
   short int outOfBounds;
   int numQuadAssigned;
   int numVerAssigned;

   // State machine vals
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

/**
 * Name: light_t
 * Desc: Information about game lighting.
**/
typedef struct
{
   GLfloat pos[4];
   GLfloat diffuse[4];
   GLfloat specular[4];
   GLfloat ambient[4];
}light_t;

/**
 * Name: quadobject_init(QuadObject * obj, int numVer, int numQuad)
 * Desc: Constructor for a QuadObject.
 * Para: obj, The object to operate on.
 *       numVer, The number of verticies in this object.
 *       numQuad, The number of quadrangles in this object.
**/
void quadobject_init(QuadObject * obj, int numVer, int numQuad);

/**
 * Name: quadobject_setNextColor(QuadObject * obj, GLfloat r, GLfloat g, GLfloat b)
 * Desc: Set the color of the next vertex to add to this object.
 * Para: obj, The object to operate on.
**/
void quadobject_setNextColor(QuadObject * obj, GLfloat r, GLfloat g, GLfloat b);

/**
 * Name: quadobject_setNextPos(QuadObject * obj, GLfloat x, GLfloat y, GLfloat z)
 * Desc: Set the position of the next vertex to add to this object.
 * Para: obj, The object to operate on.
 *       x, The x position of the next vertex to be added.
 *       y, The y position of the next vertex to be added.
 *       z, The z position of the next vertex to be added.
**/
void quadobject_setNextPos(QuadObject * obj, GLfloat x, GLfloat y, GLfloat z);

/**
 * Name: quadobject_setNextTexture(QuadObject * obj, int texture)
 * Desc: Indicate the next verticies should use the given textures.
 * Para: obj, The object to operate on.
 *       texture, The index / ID of the texture to use.
**/
void quadobject_setNextTexture(QuadObject * obj, int texture);

/** 
 * Name: quadobject_setNoTexture(QuadObject * obj)
 * Desc: Indicate that the next verticies should not use any texture.
**/
void quadobject_setNoTexture(QuadObject * obj);

/**
 * Name: quadobject_setNextR(QuadObject * obj, GLfloat r)
 * Desc: Set the red value of the next vertex's color
 * Para: obj, The object to operate on.
 *       r, The next red value to use.
**/
void quadobject_setNextR(QuadObject * obj, GLfloat r);

/**
 * Name: quadobject_setNextG(QuadObject * obj, GLfloat g)
 * Desc: Set the green value of the next vertex's color
 * Para: obj, The object to operate on.
 *       g, The next green value to use.
**/
void quadobject_setNextG(QuadObject * obj, GLfloat g);

/**
 * Name: quadobject_setNextB(QuadObject * obj, GLfloat b)
 * Desc: Set the blue value of the next vertex's color
 * Para: obj, The object to operate on.
 *       b, The next blue value to use.
**/
void quadobject_setNextB(QuadObject * obj, GLfloat b);

/**
 * Name: quadobject_setNextX(QuadObject * obj, GLfloat x)
 * Desc: Set the x value of the next vertex's position
 * Para: obj, The object to operate on.
 *       x, The next x position to use.
**/
void quadobject_setNextX(QuadObject * obj, GLfloat x);

/**
 * Name: quadobject_setNextY(QuadObject * obj, GLfloat y)
 * Desc: Set the y value of the next vertex's position
 * Para: obj, The object to operate on.
 *       y, The next y position to use.
**/
void quadobject_setNextY(QuadObject * obj, GLfloat y);

/**
 * Name: quadobject_setNextZ(QuadObject * obj, GLfloat z)
 * Desc: Set the z value of the next vertex's position
 * Para: obj, The object to operate on.
 *       z, The next z position to use.
**/
void quadobject_setNextZ(QuadObject * obj, GLfloat z);

/**
 * Name: quadobject_moveNextX(QuadObject * obj, GLfloat dx)
 * Desc: Adjust the x value of the next vertex's position
 * Para: obj, The object to operate on.
 *       dx, The x value (pos or neg) to add to the next X position the next
 *          vertex will get.
**/
void quadobject_moveNextX(QuadObject * obj, GLfloat dx);

/**
 * Name: quadobject_moveNextY(QuadObject * obj, GLfloat dy)
 * Desc: Adjust the y value of the next vertex's position
 * Para: obj, The object to operate on.
 *       dy, The y value (pos or neg) to add to the next Y position the next
 *          vertex will get.
**/
void quadobject_moveNextY(QuadObject * obj, GLfloat dy);

/**
 * Name: quadobject_moveNextZ(QuadObject * obj, GLfloat dz)
 * Desc: Adjust the z value of the next vertex's position
 * Para: obj, The object to operate on.
 *       dz, The z value (pos or neg) to add to the next Z position the next
 *          vertex will get.
**/
void quadobject_moveNextZ(QuadObject * obj, GLfloat dz);

/**
 * Name: quadobject_createQuadFromPrev(QuadObject * obj)
 * Desc: Create a new quadrangle in this object from the last 4 verticies added
 *       to it.
 * Para: obj, The object to operate on.
**/
void quadobject_createQuadFromPrev(QuadObject * obj);

/**
 * Name: quadobject_setVer(QuadObject * obj, int verId)
 * Desc: Create a new vertex in this object and give it the given id.
 * Para: obj, The object to operate on.
 *       verId, The id to give the new vertex.
**/
void quadobject_setVer(QuadObject * obj, int verId);

/**
 * Name: quadobject_draw(QuadObject * obj)
 * Desc: Draw this object into the current OpenGL context.
**/
void quadobject_draw(QuadObject * obj);

/**
 * Name: quadobject_drawSpecific(QuadObject * obj, int numQuads, int startQuad)
 * Desc: Draw this object into the current OpenGL context.
 * Para: numQuads, The number of quadrangles to draw.
 *       startQuad, The quadrangle ID to start drawing with.
**/
void quadobject_drawSpecific(QuadObject * obj, int numQuads, int startQuad);

/**
 * Name: quadobject_drawSpecific(QuadObject * obj, int numQuads, int startQuad)
 * Desc: Draw this object into the current OpenGL context with the normals
 *       coming out radially from the given center coordinate.
 * Para: numQuads, The number of quadrangles to draw.
 *       startQuad, The quadrangle ID to start drawing with.
 *       xCenter, The x coordinate of where the normals should start radiating.
 *       yCenter, The y coordinate of where the normals should start radiating.
 *       zCenter, The z coordinate of where the normals should start radiating.
**/
void quadobject_drawSpecificRadially(QuadObject * obj, int numQuads,
   int startQuad, float xCenter, float yCenter, float zCenter);

/**
 * Name: quadobject_addVer(QuadObject * obj)
 * Desc: Add a new vertex to this object.
 * Para: obj, The object to operate on.
 * Retr: The id given to the new vertex.
**/
int quadobject_addVer(QuadObject * obj);

/**
 * Name: quadobject_getVer(QuadObject * obj, unsigned int vertNum)
 * Desc: Gets information about a vertex.
 * Para: obj, The object to look in.
 *       vertNum, The id of the vertex to get.
 * Retr: Struct with info about the requested vertex.
**/
ColoredVertex * quadobject_getVer(QuadObject * obj, unsigned int vertNum);

/**
 * Name: quadobject_addQuad(QuadObject * obj, unsigned int v0Index,
 *                          unsigned int v1Index, unsigned int v2Index,
 *                          unsigned int v3Index)
 * Desc: Add a new quadrangle to this object (going counter-clockwise).
 * Para: obj, The object to operate on.
 *       v0Index, The id of the first vertex in the new quadrangle.
 *       v1Index, The id of the second vertex in the new quadrangle.
 *       v2Index, The id of the third vertex in the new quadrangle.
 *       v2Index, The id of the fourth vertex in the new quadrangle.
**/
int quadobject_addQuad(QuadObject * obj, unsigned int v0Index,
   unsigned int v1Index, unsigned int v2Index, unsigned int v3Index);

/**
 * Name: quadobject_addQuad(QuadObject * obj, unsigned int v0Index,
 *                          unsigned int v1Index, unsigned int v2Index,
 *                          unsigned int v3Index)
 * Desc: Add a new quadrangle to this object (going clockwise).
 * Para: obj, The object to operate on.
 *       v0Index, The id of the first vertex in the new quadrangle.
 *       v1Index, The id of the second vertex in the new quadrangle.
 *       v2Index, The id of the third vertex in the new quadrangle.
 *       v2Index, The id of the fourth vertex in the new quadrangle.
**/
int quadobject_addQuadBackwards(QuadObject * obj, unsigned int v0Index,
   unsigned int v1Index, unsigned int v2Index, unsigned int v3Index);

/**
 * Name: quadobject_del(QuadObject * obj)
 * Desc: Delete the memory used by this object.
 * Para: obj, The object to clean up after.
**/
void quadobject_del(QuadObject * obj);

/**
 * Name: quadobject_fixQuad(QuadObject * obj, int id)
 * Desc: Recalculate the normal for the given quad.
 * Para: obj, The object to recalculate a normal for.
 *       id, The integer ID of the quad whose normal should be re-calculated.
**/
void quadobject_fixQuad(QuadObject * obj, int id);

/**
 * Name: quad_init(Quad * obj, unsigned int * ver, ColoredVertex * pointa,
 *                 ColoredVertex * pointb, ColoredVertex * pointc)
 * Desc: Constructor for a record of a quadrangle in a QuadObject.
 * Para: obj, The object to operate on.
 *       ver, Array of IDs of the verticies this quadrangles contains.
 *       pointa, The first point in this quadrangle to use for finding the
 *               normal.
 *       pointb, The second point in this quadrangle to use for finding the
 *               normal.
 *       pointc, The third point in this quadrangle  to use for finding the
 *               normal.
**/
void quad_init(Quad * obj, unsigned int * ver, ColoredVertex * pointa,
    ColoredVertex * pointb, ColoredVertex * pointc);

/**
 * Name: quad_fixNormal(Quad * obj, ColoredVertex * pointa,
 *          ColoredVertex * pointb, ColoredVertex * pointc)
 * Desc: Recalculate the normal for the given quad.
 * Para: obj, The quad to recalculate normals for.
 *       pointa, The first vertex that defines the plane to calculate the normal
 *          from.
 *       pointb, The second vertex that defines the plane to calculate the
 *          normal from.
 *       pointc, The third vertex that defines the plane to calculate the normal
 *          from.
**/ 
void quad_fixNormal(Quad * obj, ColoredVertex * pointa,
    ColoredVertex * pointb, ColoredVertex * pointc);

#endif
