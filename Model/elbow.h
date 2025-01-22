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
    void base();

    void moveat(double t, double h);
    void startAnime();
    void stopAnime();
    void Export(FILE *ft);

    bool NonNullVelocity();
    void Zone(double time);

    double xi,yi,zi;
    double xf,yf,zf;
    double xr,yr,zr;
    double nx,ny,nz;
    double tx,ty,tz;
    double sx,sy,sz;
    double cx,cy,cz,radius,Rc,alpha;
    double orx = 0, ory = 0, orz = 0;

    int N;

    double xi0 = 0,yi0 = 0,zi0 = 0;
    double xf0 = 0,yf0 = 0,zf0 = 0;
    double cx0 = 0,cy0 = 0,cz0 = 0;
    bool isAnimated = false;
    double Rot[3][3];

    Velocity vx,vy,vz;
    Velocity wx,wy,wz;
    double Vx,Vy,Vz,Wx,Wy,Wz;
    double xmax, ymax, zmax, xmin, ymin, zmin;
};

#endif // ELBOW_H
