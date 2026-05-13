#ifndef DISK_H
#define DISK_H

#include "solid.h"
#include<cstdio>

class Disk : public Solid
{
public:
    Disk();
    void ReadFromFile(FILE *ft);
    void Draw(bool isLineContainer);
    double ComputeScale() const;
    void Export(FILE *ft);


    void Zone(double time);
    double r = 0;
    int inAndOut = -1;
    double xmax = 0, ymax = 0, zmax = 0, xmin = 0, ymin = 0, zmin = 0;

private:
    int periodic = -9;
};

#endif // DISK_H
