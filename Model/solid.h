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

    virtual void ReadFromFile(FILE *ft);

    double x = 0,y = 0,z = 0;
    double nx = 1,ny = 0,nz = 0;
    double tx = 0,ty = 1,tz = 0;
    double sx = 0,sy = 0,sz = 1;
    Velocity vx,vy,vz;
    Velocity wx,wy,wz;

    double beta;
    double orx,ory,orz;
    double Vx,Vy,Vz,Wx,Wy,Wz;
    int Ngb;
    int N,Nold;
};

#endif // SOLID_H
