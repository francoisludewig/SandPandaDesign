#ifndef VELOCITYPRESENTER_H
#define VELOCITYPRESENTER_H

#include "Model/velocity.h"

#include<string>
#include<QTableWidgetItem>

class VelocityPresenter
{
public:
    VelocityPresenter(Velocity *v);

    VelocityPresenter() = default;
    VelocityPresenter(const VelocityPresenter&) = default;
    VelocityPresenter(VelocityPresenter&&) = default;
    VelocityPresenter& operator=(const VelocityPresenter&) = default;
    ~VelocityPresenter() = default;

    QTableWidgetItem* getItem(std::string name);


    void updateWidget();
    void updateModel();
private:
    Velocity *v;
    std::map<std::string, QTableWidgetItem*> widgets;
};

#endif // VELOCITYPRESENTER_H
