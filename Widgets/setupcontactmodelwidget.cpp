#include "setupcontactmodelwidget.h"

#include<iostream>

SetupContactModelWidget::SetupContactModelWidget(QWidget *parent)
    : QWidget{parent}
{
    setupContactModelPresenter = std::make_unique<SetupContactModelPresenter>(SetupContactModelPresenter());
}

void SetupContactModelWidget::setStaticFrictionCoefficient(QLineEdit* staticFrictionCoefficient) {
    this->staticFrictionCoefficient = staticFrictionCoefficient;
}

void SetupContactModelWidget::setStaticFrictionCoefficientLabel(QLabel* staticFrictionCoefficientLabel) {
    this->staticFrictionCoefficientLabel = staticFrictionCoefficientLabel;
}

void SetupContactModelWidget::on_new_restitution_coefficient(const QString& newText) {
    setupContactModelPresenter->setResitutionCoefficient(newText.toDouble());
    std::cout << "New resitution coefficient : " << newText.toStdString() << std::endl;
}

void SetupContactModelWidget::on_new_stiffness_coefficient(const QString& newText) {
    setupContactModelPresenter->setNormalStiffness(newText.toDouble());
    std::cout << "New stiffness coefficient : " << newText.toStdString() << std::endl;
}

void SetupContactModelWidget::on_new_static_friction_coefficient(const QString& newText) {
    setupContactModelPresenter->setStaticFrictionCoefficient(newText.toDouble());
    std::cout << "New static friction coefficient : " << newText.toStdString() << std::endl;
}

void SetupContactModelWidget::on_new_dynamic_friction_coefficient(const QString& newText) {
    setupContactModelPresenter->setDynamicFrictionCoefficient(newText.toDouble());
    std::cout << "New dynamic friction coefficient : " << newText.toStdString() << std::endl;
}

void SetupContactModelWidget::on_new_tangential_model(int index) {
    setupContactModelPresenter->setIsTangentialDynamicModel(index!=1);
    std::cout << "New Model : " << (index == 1 ? "Dynamic " : "Static ") << "model" << std::endl;
    staticFrictionCoefficient->setReadOnly(index == 1);
    {
        QPalette *palette = new QPalette();
        palette->setColor(QPalette::Text,(index == 1 ? Qt::darkGray : Qt::white));
        staticFrictionCoefficient->setPalette(*palette);
    }
    {
        QPalette *palette = new QPalette();
        palette->setColor(QPalette::WindowText,(index == 1 ? Qt::darkGray : Qt::white));
        staticFrictionCoefficientLabel->setPalette(*palette);
    }
}
