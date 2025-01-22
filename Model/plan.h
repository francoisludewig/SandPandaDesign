#ifndef PLAN_H
#define PLAN_H

#include "solid.h"
#include<cstdio>

class Plan : public Solid
{
public:
    Plan();
    Plan(const Plan&) = default;
    Plan(Plan&&) = default;
    Plan& operator=(const Plan&) = default;
    ~Plan() = default;

    void ReadFromFile(FILE *ft) override;
    void Draw(bool isLineContainer) const;
    double ComputeScale() const;

    void Zone(double time);
    void Export(FILE *ft);
    void ExportWithoutBaseComputing(FILE *ft);

    double dt,ds;
    int inAndOut;
    double xmax, ymax, zmax, xmin, ymin, zmin;
private:
    int ped;
};

#endif // PLAN_H
