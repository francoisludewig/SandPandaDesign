#ifndef SETUPCONTACTMODELWIDGET_H
#define SETUPCONTACTMODELWIDGET_H

#include <QWidget>
#include <QLineEdit>
#include <QLabel>

#include "Presenter/setupcontactmodelpresenter.h"

class SetupContactModelWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SetupContactModelWidget(QWidget *parent = nullptr);
    void setStaticFrictionCoefficient(QLineEdit* staticFrictionCoefficient);
    void setStaticFrictionCoefficientLabel(QLabel* staticFrictionCoefficientLabel);

public slots:

    void on_new_restitution_coefficient(const QString& newText);
    void on_new_stiffness_coefficient(const QString& newText);
    void on_new_static_friction_coefficient(const QString& newText);
    void on_new_dynamic_friction_coefficient(const QString& newText);
    void on_new_tangential_model(int index);

private:
    QLineEdit* staticFrictionCoefficient;
    QLabel* staticFrictionCoefficientLabel;
    std::unique_ptr<SetupContactModelPresenter> setupContactModelPresenter;
};

#endif // SETUPCONTACTMODELWIDGET_H
