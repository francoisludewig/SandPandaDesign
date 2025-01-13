#ifndef LATTICEPRESENTER_H
#define LATTICEPRESENTER_H

#include<QTableWidgetItem>
#include<QCheckBox>

#include "Model/lattice.h"

class LatticePresenter
{
public:
    LatticePresenter(std::shared_ptr<Lattice>& lattice);
    void updateWidget();
    void updateModel();

    void linkToCuboid(std::shared_ptr<Cuboid> &cuboid);
    void linkToCone(std::shared_ptr<Cone> &cone);
    void unlink();

    QTableWidgetItem* getWidget(std::string);
    QWidget* getRdmPositionWidget();
    QCheckBox *getRdmPositionCheckBox();

    std::shared_ptr<Lattice> lattice;
private:
    std::map<std::string, QTableWidgetItem*> widgets;
    QWidget *rdm_position;
    QCheckBox *rdm_position_CheckBox;

};

#endif // LATTICEPRESENTER_H
