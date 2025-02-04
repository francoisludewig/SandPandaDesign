#include "setuptimewidget.h"

#include<iostream>

SetupTimeWidget::SetupTimeWidget(QWidget *parent)
    : QWidget{parent}
{
    setupTimePresenter = std::make_unique<SetupTimePresenter>(SetupTimePresenter());
}

void SetupTimeWidget::on_compute_timestep(bool checked) {
    std::cout << "Compute time step !" << std::endl;
    this->timestepField->setText(QString::number(setupTimePresenter->ComputeTimestep()));
}

void SetupTimeWidget::on_new_start_time(const QString& newText) {
    std::cout << "New start_time : " << newText.toStdString() << std::endl;
    setupTimePresenter->SetStartTime(newText.toDouble());
}

void SetupTimeWidget::on_new_time_step(const QString& newText) {
    std::cout << "New time_step : " << newText.toStdString() << std::endl;
    setupTimePresenter->SetTimestep(newText.toDouble());
}
void SetupTimeWidget::on_new_capture_delay(const QString& newText) {
    std::cout << "New capture_delay : " << newText.toStdString() << std::endl;
    setupTimePresenter->SetCaptureDelay(newText.toDouble());
}
void SetupTimeWidget::on_new_duration(const QString& newText) {
    std::cout << "New duration : " << newText.toStdString() << std::endl;
    setupTimePresenter->SetDuration(newText.toDouble());
}

void SetupTimeWidget::setTimesetpField(QLineEdit* timestepField) {
    this->timestepField = timestepField;
}

void SetupTimeWidget::setStartingTimeField(QLineEdit* startingTimeField) {
    this->startingTimeField = startingTimeField;
}

void SetupTimeWidget::setCaptureDelayField(QLineEdit* captureDelayField) {
    this->captureDelayField = captureDelayField;
}

void SetupTimeWidget::setDurationField(QLineEdit* durationField) {
    this->durationField = durationField;
}

void SetupTimeWidget::LoadDataFromRepository() {
    this->timestepField->setText(QString::number(setupTimePresenter->GetTimestep()));
    this->startingTimeField->setText(QString::number(setupTimePresenter->GetStartTime()));
    this->captureDelayField->setText(QString::number(setupTimePresenter->GetCaptureDelay()));
    this->durationField->setText(QString::number(setupTimePresenter->GetDuration()));
}
