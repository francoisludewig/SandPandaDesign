#ifndef ELBOWPRESENTER_H
#define ELBOWPRESENTER_H


#include<QTableWidgetItem>
#include<QCheckBox>

#include "Model/elbow.h"


class ElbowPresenter
{
public:
    ElbowPresenter(std::shared_ptr<Elbow>& elbow);
    void updateWidget();
    void updateModel();

    QTableWidgetItem* getWidget(std::string);
    std::shared_ptr<Elbow> elbow;

private:
    std::map<std::string, QTableWidgetItem*> widgets;
};

#endif // ELBOWPRESENTER_H
