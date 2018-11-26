
#include "quadobj.h"

light_t light={
      {6,10,15,1},   //position 
      {1,1,1,1},     //diffuse
      {0,0,0,1},     //specular
      {0.1,0.1,0.1,1}      //ambient
}; 

void quadobject_init(QuadObject * obj, int numVer, int numQuad)
{
    obj->ver = malloc(sizeof(ColoredVertex) * numVer);
    obj->quad = malloc(sizeof(Quad) * numQuad);
    obj->numVer = numVer;
    obj->numQuad = numQuad;
    obj->outOfBounds = FALSE;
    obj->numQuadAssigned = 0;
    obj->numVerAssigned = 0;

    obj->r = 0;
    obj->g = 0;
    obj->b = 0;
    obj->x = 0;
    obj->y = 0;
    obj->z = 0;

    obj->hasTexture = 0;
    obj->textureNum = -1;

    obj->curX = 0;
    obj->curY = 0;
    obj->curZ = 0;
    obj->curRot = 0;
    obj->curRoll = 0;
    obj->curPitch = 0;
    obj->curYaw = 0;
    obj->xScale = 1;
    obj->yScale = 1;
    obj->zScale = 1;
}

void quadobject_setNextTexture(QuadObject * obj, int texture)
{
    obj->hasTexture = 1;
    obj->textureNum = texture;
}

void quadobject_setNoTexture(QuadObject * obj)
{
    obj->hasTexture = 0;
}

void quadobject_setNextColor(QuadObject * obj, GLfloat r, GLfloat g, GLfloat b)
{
    obj->r = r;
    obj->g = g;
    obj->b = b;
}

void quadobject_setNextPos(QuadObject * obj, GLfloat x, GLfloat y, GLfloat z)
{
    obj->x = x;
    obj->y = y;
    obj->z = z;
}

void quadobject_setNextR(QuadObject * obj, GLfloat r)
{
    obj->r = r;
}

void quadobject_setNextG(QuadObject * obj, GLfloat g)
{
    obj->g = g;
}

void quadobject_setNextB(QuadObject * obj, GLfloat b)
{
    obj->b = b;
}

void quadobject_setNextX(QuadObject * obj, GLfloat x)
{
    obj->x = x;
}

void quadobject_setNextY(QuadObject * obj, GLfloat y)
{
    obj->y = y;
}

void quadobject_setNextZ(QuadObject * obj, GLfloat z)
{
    obj->z = z;
}

void quadobject_moveNextX(QuadObject * obj, GLfloat dx)
{
    obj->x += dx;
}

void quadobject_moveNextY(QuadObject * obj, GLfloat dy)
{
    obj->y += dy;
}

void quadobject_moveNextZ(QuadObject * obj, GLfloat dz)
{
    obj->z += dz;
}

void quadobject_createQuadFromPrev(QuadObject * obj)
{
    int i = obj->numVerAssigned - 1;
    quadobject_addQuad(obj, i-3, i-2, i-1, i);
}

void quadobject_setVer(QuadObject * obj, int verId)
{
    ColoredVertex * vertex;

    // Check bounds
    if(obj->numVer <= verId)
    {
        obj->outOfBounds = TRUE;
        return;
    }

    // Set vertex
    vertex = &(obj->ver[verId]);
    vertex->pos[0] = obj->x;
    vertex->pos[1] = obj->y;
    vertex->pos[2] = obj->z;
    vertex->col[0] = obj->r;
    vertex->col[1] = obj->g;
    vertex->col[2] = obj->b;
}

int quadobject_addVer(QuadObject * obj)
{
    int index = obj->numVerAssigned;
    quadobject_setVer(obj, index);
    obj->numVerAssigned++;

    return index;
}

ColoredVertex * quadobject_getVer(QuadObject * obj, unsigned int vertId)
{
    // Check bounds
    if(obj->numVer <= vertId)
    {
        obj->outOfBounds = TRUE;
        return NULL;
    }

    return &(obj->ver[vertId]);
}

void quadobject_fixQuad(QuadObject * obj, int id)
{
    Quad * targetQuad = &(obj->quad[id]);
    ColoredVertex * pointa = quadobject_getVer(obj, targetQuad->ver[2]);
    ColoredVertex * pointb = quadobject_getVer(obj, targetQuad->ver[1]);
    ColoredVertex * pointc = quadobject_getVer(obj, targetQuad->ver[0]);
    quad_fixNormal(targetQuad, pointa, pointb, pointc);
}

int quadobject_addQuadBackwards(QuadObject * obj, unsigned int v0Index,
    unsigned int v1Index, unsigned int v2Index, unsigned int v3Index)
{
    return quadobject_addQuad(obj, v3Index, v2Index, v1Index, v0Index);
}

int quadobject_addQuad(QuadObject * obj, unsigned int v0Index,
    unsigned int v1Index, unsigned int v2Index, unsigned int v3Index)
{
    int index;
    Quad * quad;
    ColoredVertex * v0;
    ColoredVertex * v1;
    ColoredVertex * v2;

    unsigned int vertexIndicies [4] = {v0Index, v1Index, v2Index, v3Index}; 

    // Check bounds
    if(obj->numQuad <= obj->numQuadAssigned)
    {
        obj->outOfBounds = TRUE;
        return -1;
    }

    // Get verticies
    v0 = quadobject_getVer(obj, v0Index);
    v1 = quadobject_getVer(obj, v1Index);
    v2 = quadobject_getVer(obj, v2Index);

    if(obj->outOfBounds)
        return -1;

    // Set object
    index = obj->numQuadAssigned;
    quad = &(obj->quad[index]);
    quad_init(
        quad,
        vertexIndicies,
        v2,
        v1,
        v0
    );
    quad->hasTexture = obj->hasTexture;
    quad->textureNum = obj->textureNum;

    obj->numQuadAssigned++;

    return index;
}

void quadobject_del(QuadObject * obj)
{
    free(obj->ver);
    free(obj->quad);
}

void quadobject_draw(QuadObject * obj)
{
    quadobject_drawSpecific(obj, obj->numQuad, 0);
}

void quadobject_drawSpecific(QuadObject * obj, int numQuad, int startQuad)
{
    int a;
    unsigned int currentVer;

    glPushMatrix();
      glTranslatef(obj->curX,obj->curY,obj->curZ);
      glRotatef(obj->curRoll,1,0,0);
      glRotatef(obj->curPitch,0,1,0);
      glRotatef(obj->curYaw,0,0,1);
      glRotatef(obj->curRot,obj->curRoll,obj->curPitch,obj->curYaw);
      glScalef(obj->xScale,obj->yScale,obj->zScale);

      for (a=startQuad;a<numQuad;++a)
      {
        if(obj->quad[a].hasTexture)
        {
            glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D,obj->quad[a].textureNum);
        }

        glBegin(GL_QUADS);

        //sets the current normal to this quad's normal
        glNormal3fv(obj->quad[ a ].norm);

        // Draw verticies
        currentVer=obj->quad[a].ver[0];
        glColor3fv(obj->ver[ currentVer ].col);
        glTexCoord2f(0,0);
        glVertex3fv(obj->ver[ currentVer ].pos);

        currentVer=obj->quad[a].ver[1];
        glColor3fv(obj->ver[ currentVer ].col);
        glTexCoord2f(1,0);
        glVertex3fv(obj->ver[ currentVer ].pos);
        
        currentVer=obj->quad[a].ver[2];
        glColor3fv(obj->ver[ currentVer ].col);
        glTexCoord2f(1,1);
        glVertex3fv(obj->ver[ currentVer ].pos);
        
        currentVer=obj->quad[a].ver[3];
        glColor3fv(obj->ver[ currentVer ].col);
        glTexCoord2f(0,1);
        glVertex3fv(obj->ver[ currentVer ].pos);

        glEnd();

        if(obj->quad[a].hasTexture)
            glDisable(GL_TEXTURE_2D);
      }

   glPopMatrix();
}

void quadobject_drawSpecificRadially(QuadObject * obj, int numQuads,
   int startQuad, float xCenter, float yCenter, float zCenter)
{
    int a;
    int b;
    GLfloat effectiveX;
    GLfloat effectiveY;
    GLfloat effectiveZ;
    GLfloat normX;
    GLfloat normY;
    GLfloat normZ;
    unsigned int currentVer;

    glPushMatrix();
      glTranslatef(obj->curX,obj->curY,obj->curZ);
      glTranslatef(xCenter, yCenter, zCenter);
      glRotatef(obj->curRot,obj->curRoll,obj->curPitch,obj->curYaw);
      glScalef(obj->xScale,obj->yScale,obj->zScale);

      glBegin(GL_QUADS);
      
      for (a=startQuad;a<numQuads;++a)
      {
         for (b=0;b<4;++b)
         {
            currentVer=obj->quad[a].ver[b];

            normX = obj->ver[ currentVer ].pos[0] - xCenter;
            normY = obj->ver[ currentVer ].pos[1] - yCenter;
            normZ = obj->ver[ currentVer ].pos[2] - zCenter;
            effectiveX = obj->ver[ currentVer ].pos[0] - xCenter / obj->xScale;
            effectiveY = obj->ver[ currentVer ].pos[1] - yCenter / obj->yScale;
            effectiveZ = obj->ver[ currentVer ].pos[2] - zCenter / obj->zScale;

            glNormal3f(normX, normY, normZ);
            glColor3fv(obj->ver[ currentVer ].col);
            glVertex3f(effectiveX, effectiveY, effectiveZ);
         }
      }
      
      glEnd();
   glPopMatrix();
}

void quad_init(Quad * obj, unsigned int * ver, ColoredVertex * pointa,
    ColoredVertex * pointb, ColoredVertex * pointc)
{
    memcpy(obj->ver, ver, sizeof(unsigned int) * NUM_VERT_PER_QUAD);
    linalg_getFaceNormal(obj->norm, pointa->pos, pointb->pos, pointc->pos);
}

void quad_fixNormal(Quad * obj, ColoredVertex * pointa, ColoredVertex * pointb,
    ColoredVertex * pointc)
{
    linalg_getFaceNormal(obj->norm, pointa->pos, pointb->pos, pointc->pos);
}
