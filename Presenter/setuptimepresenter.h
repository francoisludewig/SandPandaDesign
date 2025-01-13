#ifndef SETUPTIMEPRESENTER_H
#define SETUPTIMEPRESENTER_H


#include<memory>
#include"Model/setup.h"

class SetupTimePresenter
{
public:
    SetupTimePresenter();

    void SetStartTime(double value);
    void SetDuration(double value);
    void SetTimestep(double value);
    void SetCaptureDelay(double value);


private:
    std::shared_ptr<Setup> setup;
};

#endif // SETUPTIMEPRESENTER_H
