
#include "math_functions.h"

void linalg_getFaceNormal(float *norm, float * pointa, float * pointb,
    float * pointc)
{
    float vect[2][3];
    int a,b;
    float point[3][3];

    // copies points into point[][]
    for (a=0;a<3;++a)
    {
        point[0][a]=pointa[a];
        point[1][a]=pointb[a];
        point[2][a]=pointc[a];
    }

    // Calculate vectors from point[0] to point[1]
    for (a=0;a<2;++a)
    {
        //Calculate vectors from point[0] to point[2]
        for (b=0;b<3;++b)
        {
            vect[a][b]=point[2-a][b]-point[0][b];        
        }
    }

    // Calculates vector at 90 deg to 2 vectors
    linalg_crossProduct(norm,vect[0],vect[1]);
    linalg_normalize(norm);
}

void linalg_normalize(float * vect)
{
    float length;
    int a;

    length = sqrt(pow(vect[0],2) + pow(vect[1],2) + pow(vect[2],2));

    for (a=0;a<3;++a)
    {
        vect[a]/=length;
    }
}

void linalg_crossProduct(float *c,float a[3], float b[3])
{                                            
    c[0]=a[1]*b[2] - b[1]*a[2];
    c[1]=a[2]*b[0] - b[2]*a[0];
    c[2]=a[0]*b[1] - b[0]*a[1];
}

float linalg_calcPitch(PhysicsVector * from, PhysicsVector * to)
{
    return atan2f(to->x - from->x, to->z - from->z) + PI;
}

float linalg_calcYaw(PhysicsVector * from, PhysicsVector * to)
{
    return atan2f(to->x - from->x, to->y - from->y);
}

float linalg_calcPitchDeg(PhysicsVector * from, PhysicsVector * to)
{
    return linalg_calcPitch(from, to) / PI * 180;
}

float linalg_calcYawDeg(PhysicsVector * from, PhysicsVector * to)
{
    return linalg_calcYaw(from, to) / PI * 180;
}
