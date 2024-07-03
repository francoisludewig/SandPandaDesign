#ifndef ELBOW_H
#define ELBOW_H

#include<cstdio>

#include "velocity.h"

class Elbow
{
public:
    Elbow();
    void ReadFromFile(FILE *ft);
    void Draw(bool isLineContainer);
    double ComputeScale() const;

    double xi,yi,zi;
    double xf,yf,zf;
    double xr,yr,zr;
    double nx,ny,nz;
    double tx,ty,tz;
    double sx,sy,sz;
    double cx,cy,cz,radius,Rc,alpha;
    double orx, ory, orz;
    int N;

    Velocity vx,vy,vz;
    Velocity wx,wy,wz;
};

#endif // ELBOW_H
