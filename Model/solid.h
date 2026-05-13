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
    void computeBaseFromQuaternion();

    bool NonNullVelocity();

    virtual void ReadFromFile(FILE *ft);

    double x = 0,y = 0,z = 0;
    double nx = 1,ny = 0,nz = 0;
    double tx = 0,ty = 1,tz = 0;
    double sx = 0,sy = 0,sz = 1;
    Velocity vx{},vy{},vz{};
    Velocity wx{},wy{},wz{};

    double beta = 0;
    double orx = 0,ory = 0,orz = 0;
    double Vx = 0,Vy = 0,Vz = 0,Wx = 0,Wy = 0,Wz = 0;
    double R[3][3];
    double x0 = 0,y0 = 0,z0 = 0;
    double nx0 = 1,ny0 = 0,nz0 = 0;
    int Ngb = 0;
    int N = 0,Nold = 0;
    double q0 = 0, q1 = 0, q2 = 0, q3 = 0;

    bool isAnimated = false;
};

#endif // SOLID_H
