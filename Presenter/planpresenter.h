#ifndef PLANPRESENTER_H
#define PLANPRESENTER_H

#include<map>
#include<string>
#include<QTableWidgetItem>
#include<QCheckBox>

#include "Model/plan.h"

class PlanPresenter
{
public:
    PlanPresenter(std::shared_ptr<Plan>& plan);
    void updateWidget();
    void updateModel();

    QTableWidgetItem* getWidget(std::string);
    QWidget* getInOutWidget();
    std::shared_ptr<Plan> plan;

    QCheckBox *getInOutCheckBox();
private:
    std::map<std::string, QTableWidgetItem*> widgets;
    QWidget *in_out;
    QCheckBox *in_out_CheckBox;
};

#endif // PLANPRESENTER_H
