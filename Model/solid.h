#ifndef SOLID_H
#define SOLID_H

#include<cstdio>
#include "velocity.h"

class Solid
{
public:
    Solid(); // Prevent construction
    Solid(const Solid&) = default;
    Solid(Solid&&) = default;
    Solid& operator=(const Solid&) = default;
    ~Solid() = default;

    void base();
    void moveat(double t, double h);
    void startAnime();
    void stopAnime();
    void computeQuaternion();

    bool NonNullVelocity();

    virtual void ReadFromFile(FILE *ft);

    double x = 0,y = 0,z = 0;
    double nx = 1,ny = 0,nz = 0;
    double tx = 0,ty = 1,tz = 0;
    double sx = 0,sy = 0,sz = 1;
    Velocity vx,vy,vz;
    Velocity wx,wy,wz;

    double beta;
    double orx = 0,ory = 0,orz = 0;
    double Vx,Vy,Vz,Wx,Wy,Wz;
    double R[3][3];
    double x0 = 0,y0 = 0,z0 = 0;
    double nx0 = 1,ny0 = 0,nz0 = 0;
    int Ngb;
    int N,Nold;
    double q0, q1, q2, q3;

    bool isAnimated = false;
};

#endif // SOLID_H
