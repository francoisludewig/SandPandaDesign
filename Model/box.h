#ifndef BOX_H
#define BOX_H

#include<memory>

#include "solid.h"
#include "plan.h"

class Box : public Solid
{
public:
    Box();
    void Draw(bool isLineContainer);
    double ComputeScale();

    void setTop(bool activate);
    void setBottom(bool activate);

    void updateVelocityPlans(std::shared_ptr<Plan> p);
    void updatePlans();

    double la,Lo,h;
    std::shared_ptr<Plan> top, bottom;
    std::shared_ptr<Plan> p1, p2, p3, p4;
    bool inte;
    bool ped;
    double xmin,ymin,zmin;
    double xmax,ymax,zmax;
};

#endif // BOX_H
