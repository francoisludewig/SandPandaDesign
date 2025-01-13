#include "setupgraviptypresenter.h"

#include "Repository/containerrepository.h"

SetupGraviptyPresenter::SetupGraviptyPresenter() {
    setup = ContainerRepository::getInstance().GetSetup();
}

void SetupGraviptyPresenter::setAcceleration(double intensity) {
    setup->gravityAcceleration = intensity;
}

void SetupGraviptyPresenter::setXdirection(double x) {
    setup->gravityX = x;
}

void SetupGraviptyPresenter::setYdirection(double y) {
    setup->gravityY = y;
}

void SetupGraviptyPresenter::setZdirection(double z) {
    setup->gravityZ = z;
}

void SetupGraviptyPresenter::setWxA0(double value) {
    setup->gWxA0 = value;
}

void SetupGraviptyPresenter::setWxA1(double value) {
    setup->gWxA1 = value;
}
void SetupGraviptyPresenter::setWxW(double value) {
    setup->gWxW = value;
}
void SetupGraviptyPresenter::setWxP(double value) {
    setup->gWxP = value;
}
void SetupGraviptyPresenter::setWyA0(double value) {
    setup->gWyA0 = value;
}

void SetupGraviptyPresenter::setWyA1(double value) {
    setup->gWyA1 = value;
}

void SetupGraviptyPresenter::setWyW(double value) {
    setup->gWyW = value;
}

void SetupGraviptyPresenter::setWyP(double value) {
    setup->gWyP = value;
}

void SetupGraviptyPresenter::setWzA0(double value) {
    setup->gWzA0 = value;
}

void SetupGraviptyPresenter::setWzA1(double value) {
    setup->gWzA1 = value;
}

void SetupGraviptyPresenter::setWzW(double value) {
    setup->gWzW = value;
}

void SetupGraviptyPresenter::setWzP(double value) {
    setup->gWzP = value;
}
