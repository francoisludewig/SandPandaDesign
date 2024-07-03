#ifndef VELOCITY_H
#define VELOCITY_H

#include<cstdio>

class Velocity
{
public:
    Velocity();
    void ReadFromFile(FILE *ft);

    double A0,A1,w,p;
};

#endif // VELOCITY_H
