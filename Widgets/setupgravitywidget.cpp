#include "setupgravitywidget.h"
#include<iostream>


SetupGravityWidget::SetupGravityWidget(QWidget *parent)
    : QWidget{parent}
{
    setupGraviptyPresenter = std::make_unique<SetupGraviptyPresenter>(SetupGraviptyPresenter());
}

void SetupGravityWidget::on_new_gravityAcceleration(const QString& newText) {
    setupGraviptyPresenter->setAcceleration(newText.toDouble());
    std::cout << "New gravity acceleration : " << newText.toStdString() << std::endl;
}

void SetupGravityWidget::on_new_gravity_x_direction(const QString& newText) {
    setupGraviptyPresenter->setXdirection(newText.toDouble());
    std::cout << "New gravity x direction : " << newText.toStdString() << std::endl;
}

void SetupGravityWidget::on_new_gravity_y_direction(const QString& newText) {
    setupGraviptyPresenter->setYdirection(newText.toDouble());
    std::cout << "New gravity y direction : " << newText.toStdString() << std::endl;
}

void SetupGravityWidget::on_new_gravity_z_direction(const QString& newText) {
    setupGraviptyPresenter->setZdirection(newText.toDouble());
    std::cout << "New gravity z direction : " << newText.toStdString() << std::endl;
}

void SetupGravityWidget::on_new_gravity_vx_A0(const QString& newText){
    setupGraviptyPresenter->setWxA0(newText.toDouble());
    std::cout << "New gravity vx const A0 : " << newText.toStdString() << std::endl;
}

void SetupGravityWidget::on_new_gravity_vx_A1(const QString& newText) {
    setupGraviptyPresenter->setWxA1(newText.toDouble());
    std::cout << "New gravity vx amplitude A1 : " << newText.toStdString() << std::endl;
}
void SetupGravityWidget::on_new_gravity_vx_w(const QString& newText) {
    setupGraviptyPresenter->setWxW(newText.toDouble());
    std::cout << "New gravity vx angular frequency w : " << newText.toStdString() << std::endl;
}
void SetupGravityWidget::on_new_gravity_vx_p(const QString& newText) {
    setupGraviptyPresenter->setWxP(newText.toDouble());
    std::cout << "New gravity vx phase p : " << newText.toStdString() << std::endl;
}

void SetupGravityWidget:: on_new_gravity_vy_A0(const QString& newText){
    setupGraviptyPresenter->setWyA0(newText.toDouble());
    std::cout << "New gravity vy const A0 : " << newText.toStdString() << std::endl;
}
void SetupGravityWidget::on_new_gravity_vy_A1(const QString& newText){
    setupGraviptyPresenter->setWyA1(newText.toDouble());
    std::cout << "New gravity vy amplitude A1 : " << newText.toStdString() << std::endl;
}
void SetupGravityWidget::on_new_gravity_vy_w(const QString& newText){
    setupGraviptyPresenter->setWyW(newText.toDouble());
    std::cout << "New gravity vy angular frequency w : " << newText.toStdString() << std::endl;
}
void SetupGravityWidget::on_new_gravity_vy_p(const QString& newText) {
    setupGraviptyPresenter->setWyP(newText.toDouble());
    std::cout << "New gravity vy phase p : " << newText.toStdString() << std::endl;
}

void SetupGravityWidget::on_new_gravity_vz_A0(const QString& newText){
    setupGraviptyPresenter->setWzA0(newText.toDouble());
    std::cout << "New gravity vz const A0 : " << newText.toStdString() << std::endl;
}
void SetupGravityWidget::on_new_gravity_vz_A1(const QString& newText){
    setupGraviptyPresenter->setWzA1(newText.toDouble());
    std::cout << "New gravity vz amplitude A1 : " << newText.toStdString() << std::endl;
}
void SetupGravityWidget::on_new_gravity_vz_w(const QString& newText){
    setupGraviptyPresenter->setWzW(newText.toDouble());
    std::cout << "New gravity vz angular frequency w : " << newText.toStdString() << std::endl;
}
void SetupGravityWidget::on_new_gravity_vz_p(const QString& newText) {
    setupGraviptyPresenter->setWzP(newText.toDouble());
    std::cout << "New gravity vz phase p : " << newText.toStdString() << std::endl;
}

void SetupGravityWidget::LoadDataFromRepository() {
    componants["gravity_acceleration_field"]->setText(QString::number(setupGraviptyPresenter->getAcceleration()));

    componants["gravity_x_direction_field"]->setText(QString::number(setupGraviptyPresenter->getXdirection()));
    componants["gravity_y_direction_field"]->setText(QString::number(setupGraviptyPresenter->getYdirection()));
    componants["gravity_z_direction_field"]->setText(QString::number(setupGraviptyPresenter->getZdirection()));

    componants["gravity_vx_a0_field"]->setText(QString::number(setupGraviptyPresenter->getWxA0()));
    componants["gravity_vx_a1_field"]->setText(QString::number(setupGraviptyPresenter->getWxA1()));
    componants["gravity_vx_w_field"]->setText(QString::number(setupGraviptyPresenter->getWxW()));
    componants["gravity_vx_p_field"]->setText(QString::number(setupGraviptyPresenter->getWxP()));

    componants["gravity_vy_a0_field"]->setText(QString::number(setupGraviptyPresenter->getWyA0()));
    componants["gravity_vy_a1_field"]->setText(QString::number(setupGraviptyPresenter->getWyA1()));
    componants["gravity_vy_w_field"]->setText(QString::number(setupGraviptyPresenter->getWyW()));
    componants["gravity_vy_p_field"]->setText(QString::number(setupGraviptyPresenter->getWyP()));

    componants["gravity_vz_a0_field"]->setText(QString::number(setupGraviptyPresenter->getWzA0()));
    componants["gravity_vz_a1_field"]->setText(QString::number(setupGraviptyPresenter->getWzA1()));
    componants["gravity_vz_w_field"]->setText(QString::number(setupGraviptyPresenter->getWzW()));
    componants["gravity_vz_p_field"]->setText(QString::number(setupGraviptyPresenter->getWzP()));
}



