#ifndef CUBOIDPRESENTER_H
#define CUBOIDPRESENTER_H

#include<QTableWidgetItem>
#include<QCheckBox>

#include "Model/cuboid.h"

class CuboidPresenter
{
public:
    CuboidPresenter(std::shared_ptr<Cuboid>& cuboid);
    void updateWidget();
    void updateModel();

    QTableWidgetItem* getWidget(std::string);
    QWidget* getPeriodicWidget();
    QWidget* getTopWidget();
    QWidget* getBottomWidget();
    std::shared_ptr<Cuboid> cuboid;

    QCheckBox *getPeriodicCheckBox();
    QCheckBox *getTopCheckBox();
    QCheckBox *getBottomCheckBox();
private:
    std::map<std::string, QTableWidgetItem*> widgets;
    QWidget *periodic;
    QCheckBox *periodic_CheckBox;
    QWidget *top;
    QCheckBox *top_CheckBox;
    QWidget *bottom;
    QCheckBox *bottom_CheckBox;
};

#endif // CUBOIDPRESENTER_H
