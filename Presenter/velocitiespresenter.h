#ifndef VELOCITIESPRESENTER_H
#define VELOCITIESPRESENTER_H

#include<map>
#include<string>

#include "Presenter/velocitypresenter.h"
#include "Model/solid.h"
#include "Model/elbow.h"

class VelocitiesPresenter
{
public:
    VelocitiesPresenter(std::shared_ptr<Solid> s);
    VelocitiesPresenter(std::shared_ptr<Elbow> s);

    QTableWidgetItem* getItem(std::string presenterName, std::string itemName);

    bool isSolid();
    bool isElbow();
    bool isSolid(std::shared_ptr<Solid> s);
    bool isElbow(std::shared_ptr<Elbow> e);
    void updateModel();

private:
    void updateWidget();

    std::shared_ptr<Solid> solid;
    std::shared_ptr<Elbow> elbow;
    std::map<std::string, VelocityPresenter> presenters;
};

#endif // VELOCITIESPRESENTER_H
