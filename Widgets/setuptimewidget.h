#ifndef SETUPTIMEWIDGET_H
#define SETUPTIMEWIDGET_H

#include <QWidget>
#include <QLineEdit>
#include "Presenter/setuptimepresenter.h"

class SetupTimeWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SetupTimeWidget(QWidget *parent = nullptr);
    void setTimesetpField(QLineEdit* timestepField);


public slots:
    void on_compute_timestep(bool checked);
    void on_new_start_time(const QString& newText);
    void on_new_time_step(const QString& newText);
    void on_new_capture_delay(const QString& newText);
    void on_new_duration(const QString& newText);

private:
    QLineEdit* timestepField = nullptr;
    std::unique_ptr<SetupTimePresenter> setupTimePresenter;
};

#endif // SETUPTIMEWIDGET_H
