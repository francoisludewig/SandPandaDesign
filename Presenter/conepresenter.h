#ifndef CONEPRESENTER_H
#define CONEPRESENTER_H

#include<map>
#include<string>
#include<QTableWidgetItem>
#include<QCheckBox>

#include "Model/cone.h"

class ConePresenter
{
public:
    ConePresenter(std::shared_ptr<Cone>& cone);
    void updateWidget();
    void updateModel();

    QTableWidgetItem* getWidget(std::string);
    QWidget* getInOutWidget();
    QWidget* getTopWidget();
    QWidget* getBottomWidget();
    std::shared_ptr<Cone> cone;

    QCheckBox *getInOutCheckBox();
    QCheckBox *getTopCheckBox();
    QCheckBox *getBottomCheckBox();
private:
    std::map<std::string, QTableWidgetItem*> widgets;
    QWidget *in_out;
    QCheckBox *in_out_CheckBox;
    QWidget *top;
    QCheckBox *top_CheckBox;
    QWidget *bottom;
    QCheckBox *bottom_CheckBox;
};

#endif // CONEPRESENTER_H
