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

    double dt,ds;
    int inAndOut;
private:
    int ped;
};

#endif // PLAN_H
