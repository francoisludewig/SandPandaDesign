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

    double r;
    int inAndOut;
private:
    int periodic;
};

#endif // DISK_H
