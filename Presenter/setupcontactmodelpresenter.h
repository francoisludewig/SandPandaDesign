#ifndef SETUPCONTACTMODELPRESENTER_H
#define SETUPCONTACTMODELPRESENTER_H

#include<memory>
#include"Model/setup.h"

class SetupContactModelPresenter
{
public:
    SetupContactModelPresenter();

    void setResitutionCoefficient(double value);
    void setNormalStiffness(double value);
    void setIsTangentialDynamicModel(bool value);
    void setStaticFrictionCoefficient(double value);
    void setDynamicFrictionCoefficient(double value);


    double GetResitutionCoefficient();
    double GetNormalStiffness();
    bool GetIsTangentialDynamicModel();
    double GetStaticFrictionCoefficient();
    double GetDynamicFrictionCoefficient();



private:
    std::shared_ptr<Setup> setup;
};

#endif // SETUPCONTACTMODELPRESENTER_H
