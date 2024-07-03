#ifndef CONE_H
#define CONE_H

#include "solid.h"
#include "disk.h"
#include<cstdio>
#include<memory>

class Cone : public Solid
{
public:
    Cone();
    Cone(double, double, double, int);
    void ReadFromFile(FILE *ft);
    void Draw(bool isLineContainer);
    double ComputeScale() const;

    void setTop(bool activate);
    void setBottom(bool activate);


    double r0,r1,h,dr;
    int inAndOut;
    std::shared_ptr<Disk> top, bottom;

private:
    void updateTop();
    void updateBottom();
};

#endif // CONE_H
