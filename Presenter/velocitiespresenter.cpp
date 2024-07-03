#include "velocitiespresenter.h"

VelocitiesPresenter::VelocitiesPresenter(std::shared_ptr<Solid> s) : solid(s), elbow(nullptr){
    presenters["vx"] = VelocityPresenter(&s->vx);
    presenters["vy"] = VelocityPresenter(&s->vy);
    presenters["vz"] = VelocityPresenter(&s->vz);
    presenters["wx"] = VelocityPresenter(&s->wx);
    presenters["wy"] = VelocityPresenter(&s->wy);
    presenters["wz"] = VelocityPresenter(&s->wz);
    updateWidget();
}

VelocitiesPresenter::VelocitiesPresenter(std::shared_ptr<Elbow> s) : solid(nullptr), elbow(s) {
    presenters["vx"] = VelocityPresenter(&s->vx);
    presenters["vy"] = VelocityPresenter(&s->vy);
    presenters["vz"] = VelocityPresenter(&s->vz);
    presenters["wx"] = VelocityPresenter(&s->wx);
    presenters["wy"] = VelocityPresenter(&s->wy);
    presenters["wz"] = VelocityPresenter(&s->wz);
}

QTableWidgetItem* VelocitiesPresenter::getItem(std::string presenterName, std::string itemName)
{
    return presenters[presenterName].getItem(itemName);
}

void VelocitiesPresenter::updateWidget()
{
    presenters["vx"].updateWidget();
    presenters["vy"].updateWidget();
    presenters["vz"].updateWidget();
    presenters["wx"].updateWidget();
    presenters["wy"].updateWidget();
    presenters["wz"].updateWidget();
}

void VelocitiesPresenter::updateModel()
{
    presenters["vx"].updateModel();
    presenters["vy"].updateModel();
    presenters["vz"].updateModel();
    presenters["wx"].updateModel();
    presenters["wy"].updateModel();
    presenters["wz"].updateModel();
}

bool VelocitiesPresenter::isSolid() {
    return solid != nullptr;
}

bool VelocitiesPresenter::isElbow() {
    return elbow != nullptr;
}

bool VelocitiesPresenter::isSolid(std::shared_ptr<Solid> s) {
    return solid == s;
}

bool VelocitiesPresenter::isElbow(std::shared_ptr<Elbow> e) {
    return elbow == e;
}



