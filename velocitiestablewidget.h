#ifndef VELOCITIESTABLEWIDGET_H
#define VELOCITIESTABLEWIDGET_H

#include <QObject>
#include <QTableWidget>

#include "Presenter/velocitiespresenter.h"

class VelocitiesTableWidget : public QTableWidget
{
public:
    VelocitiesTableWidget(Solid* s);
    VelocitiesTableWidget(Elbow* s);


private:
    void initialize();


    VelocitiesPresenter vp;
};

#endif // VELOCITIESTABLEWIDGET_H
