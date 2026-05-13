#ifndef GRANULE_H
#define GRANULE_H


#include <cstdio>
#include <vector>

struct ContactData {
    int id;
    int status;
    double x, y, z;
};

class Granule
{
public:
    Granule();

    void massInertia();
    void exportToFile(FILE *ft, int sp);
    void readStartStopFromFile(FILE *ft);
    void writeStartStopToFile(FILE *ft) const;

    double x,y,z,r,q0,q1,q2,q3;
    double vx,vy,vz,wx,wy,wz;
    double m,I,rho;
    int sp;
    int NhollowBall;

    int Nneighbour2;
    std::vector<ContactData> contacts{};
};

#endif // GRANULE_H
