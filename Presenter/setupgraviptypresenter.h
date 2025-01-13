#ifndef SETUPGRAVIPTYPRESENTER_H
#define SETUPGRAVIPTYPRESENTER_H

#include<memory>
#include"Model/setup.h"

class SetupGraviptyPresenter
{
public:
    SetupGraviptyPresenter();

    void setAcceleration(double intensity);
    void setXdirection(double x);
    void setYdirection(double y);
    void setZdirection(double z);

    void setWxA0(double value);
    void setWxA1(double value);
    void setWxW(double value);
    void setWxP(double value);
    void setWyA0(double value);
    void setWyA1(double value);
    void setWyW(double value);
    void setWyP(double value);
    void setWzA0(double value);
    void setWzA1(double value);
    void setWzW(double value);
    void setWzP(double value);


private:
    std::shared_ptr<Setup> setup;
};

#endif // SETUPGRAVIPTYPRESENTER_H
