#include "setuptimepresenter.h"

#include "Repository/containerrepository.h"

SetupTimePresenter::SetupTimePresenter() {
    setup = ContainerRepository::getInstance().GetSetup();
}

void SetupTimePresenter::SetStartTime(double value) {
    setup->startingTime = value;
}

void SetupTimePresenter::SetDuration(double value) {
    setup->duration = value;
}

void SetupTimePresenter::SetTimestep(double value) {
    setup->timeStep = value;
}

void SetupTimePresenter::SetCaptureDelay(double value) {
    setup->captureTimeStep = value;
}

double SetupTimePresenter::ComputeTimestep() {
    return setup->computeTimestep();
}

double SetupTimePresenter::GetStartTime() {
    return setup->startingTime;
}

double SetupTimePresenter::GetDuration() {
    return setup->duration;
}

double SetupTimePresenter::GetTimestep() {
    return setup->timeStep;
}

double SetupTimePresenter::GetCaptureDelay() {
    return setup->captureTimeStep;
}
