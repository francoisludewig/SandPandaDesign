#include "setupcontactmodelpresenter.h"

#include "Repository/containerrepository.h"

SetupContactModelPresenter::SetupContactModelPresenter() {
    setup = ContainerRepository::getInstance().GetSetup();
}

void SetupContactModelPresenter::setResitutionCoefficient(double value) {
    setup->resitutionCoefficient = value;
}

void SetupContactModelPresenter::setNormalStiffness(double value) {
    setup->normalStiffness = value;
}

void SetupContactModelPresenter::setIsTangentialDynamicModel(bool value) {
    setup->isTangentialDynamicModel = value;
}

void SetupContactModelPresenter::setStaticFrictionCoefficient(double value) {
    setup->staticFrictionCoefficient = value;
}

void SetupContactModelPresenter::setDynamicFrictionCoefficient(double value){
    setup->dynamicFrictionCoefficient = value;
}
