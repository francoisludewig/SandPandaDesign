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
    int diskCount() {return (top != nullptr ? 1 :0) + (bottom != nullptr ? 1 : 0);}


    void Zone(double time);

    void ExportLimits(FILE *ft);
    void Export(FILE *ft);

    double r0,r1,h,dr;
    int inAndOut;
    std::shared_ptr<Disk> top, bottom;
    double xmax, ymax, zmax, xmin, ymin, zmin;
    int id;
    static int next_id;
private:
    void updateTop();
    void updateBottom();
};

#endif // CONE_H
