#ifndef SPHERE_H
#define SPHERE_H

#include<cstdio>


class Sphere
{
public:
    Sphere();
    void ReadFromFile(FILE *ft);
    void Draw();

private:
    double x,y,z;
    double nx,ny,nz;
    double tx,ty,tz;
    double sx,sy,sz;
    double vx,vy,vz;
    double wx,wy,wz;
    int sp;
    double r;
    bool bd;
    //static StripeOnSphere sos;
    float VertexA[408][3];
    float VertexB[408][3];
};

#endif // SPHERE_H
