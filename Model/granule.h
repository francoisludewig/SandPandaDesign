#ifndef GRANULE_H
#define GRANULE_H

#include <iostream>

class Granule
{
public:
    Granule();

    void massInertia();
    void exportToFile(FILE *ft, int sp);


    double x,y,z,r,q0,q1,q2,q3;
    double vx,vy,vz,wx,wy,wz;
    double m,I,rho;
};

#endif // GRANULE_H
