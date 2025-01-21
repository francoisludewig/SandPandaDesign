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
    double r;
    int inAndOut;
    double xmax, ymax, zmax, xmin, ymin, zmin;

private:
    int periodic;
};

#endif // DISK_H
