#ifndef SETUPGRAVITYWIDGET_H
#define SETUPGRAVITYWIDGET_H

#include <QWidget>
#include <QLineEdit>
#include "Presenter/setupgraviptypresenter.h"

class SetupGravityWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SetupGravityWidget(QWidget *parent = nullptr);
    void setComponant(std::string name, QLineEdit* componant) {componants[name] = componant;}

public slots:
    void on_new_gravityAcceleration(const QString& newText);
    void on_new_gravity_x_direction(const QString& newText);
    void on_new_gravity_y_direction(const QString& newText);
    void on_new_gravity_z_direction(const QString& newText);

    void on_new_gravity_vx_A0(const QString& newText);
    void on_new_gravity_vx_A1(const QString& newText);
    void on_new_gravity_vx_w(const QString& newText);
    void on_new_gravity_vx_p(const QString& newText);

    void on_new_gravity_vy_A0(const QString& newText);
    void on_new_gravity_vy_A1(const QString& newText);
    void on_new_gravity_vy_w(const QString& newText);
    void on_new_gravity_vy_p(const QString& newText);

    void on_new_gravity_vz_A0(const QString& newText);
    void on_new_gravity_vz_A1(const QString& newText);
    void on_new_gravity_vz_w(const QString& newText);
    void on_new_gravity_vz_p(const QString& newText);
    void LoadDataFromRepository();


private:
    std::unique_ptr<SetupGraviptyPresenter> setupGraviptyPresenter;
    std::map<std::string, QLineEdit*> componants {};
};

#endif // SETUPGRAVITYWIDGET_H
