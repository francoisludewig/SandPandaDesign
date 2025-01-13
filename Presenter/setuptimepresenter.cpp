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
