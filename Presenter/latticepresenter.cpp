#include "latticepresenter.h"

#include <QCheckBox>
#include <QHBoxLayout>

LatticePresenter::LatticePresenter(std::shared_ptr<Lattice>& lattice): lattice(lattice) {
    widgets["xmin"] = new QTableWidgetItem();
    widgets["xmin"]->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    widgets["ymin"] = new QTableWidgetItem();
    widgets["ymin"]->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    widgets["zmin"] = new QTableWidgetItem();
    widgets["zmin"]->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    widgets["xmax"] = new QTableWidgetItem();
    widgets["xmax"]->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    widgets["ymax"] = new QTableWidgetItem();
    widgets["ymax"]->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    widgets["zmax"] = new QTableWidgetItem();
    widgets["zmax"]->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    widgets["N"] = new QTableWidgetItem();
    widgets["N"]->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    widgets["r0"] = new QTableWidgetItem();
    widgets["r0"]->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    widgets["r1"] = new QTableWidgetItem();
    widgets["r1"]->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    widgets["vmax"] = new QTableWidgetItem();
    widgets["vmax"]->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    widgets["wmax"] = new QTableWidgetItem();
    widgets["wmax"]->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

    {
        rdm_position = new QWidget();
        rdm_position_CheckBox = new QCheckBox();
        QHBoxLayout *pLayout = new QHBoxLayout(rdm_position);
        pLayout->addWidget(rdm_position_CheckBox);
        pLayout->setAlignment(Qt::AlignCenter);
        pLayout->setContentsMargins(0,0,0,0);
        rdm_position->setLayout(pLayout);
    }

    updateWidget();
}

void LatticePresenter::updateWidget() {
    widgets["xmin"]->setText(QString::number(lattice->xmin));
    widgets["ymin"]->setText(QString::number(lattice->ymin));
    widgets["zmin"]->setText(QString::number(lattice->zmin));
    widgets["xmax"]->setText(QString::number(lattice->xmax));
    widgets["ymax"]->setText(QString::number(lattice->ymax));
    widgets["zmax"]->setText(QString::number(lattice->zmax));
    widgets["r0"]->setText(QString::number(lattice->r0));
    widgets["r1"]->setText(QString::number(lattice->r1));
    widgets["N"]->setText(QString::number(lattice->N));
    widgets["vmax"]->setText(QString::number(lattice->V));
    widgets["wmax"]->setText(QString::number(lattice->W));
    rdm_position_CheckBox->setCheckState(lattice->rdm!=0 ? Qt::CheckState::Checked : Qt::CheckState::Unchecked);
}

void LatticePresenter::updateModel() {
    lattice->xmin = widgets["xmin"]->text().toDouble();
    lattice->ymin = widgets["ymin"]->text().toDouble();
    lattice->zmin = widgets["zmin"]->text().toDouble();
    lattice->xmax = widgets["xmax"]->text().toDouble();
    lattice->ymax = widgets["ymax"]->text().toDouble();
    lattice->zmax = widgets["zmax"]->text().toDouble();
    lattice->r0 = widgets["r0"]->text().toDouble();
    lattice->r1 = widgets["r1"]->text().toDouble();
    lattice->N = widgets["N"]->text().toInt();
    lattice->V = widgets["vmax"]->text().toDouble();
    lattice->W = widgets["wmax"]->text().toDouble();
    lattice->rdm = (rdm_position_CheckBox->checkState() == Qt::CheckState::Checked ? 1 : 0);
    lattice->Radius();
    lattice->Position();
}



void LatticePresenter::linkToCuboid(std::shared_ptr<Cuboid> &cuboid) {
    lattice->boxes = true;
    lattice->cyd = false;
    lattice->bte = cuboid;
    lattice->Position();
}

void LatticePresenter::linkToCone(std::shared_ptr<Cone> &cone) {
    lattice->boxes = false;
    lattice->cyd = true;
    lattice->cyde = cone;
    lattice->Position();
}

void LatticePresenter::unlink() {
    lattice->cyd = false;
    lattice->boxes = false;
    lattice->Unlink();
    updateModel();
}

QTableWidgetItem* LatticePresenter::getWidget(std::string name) {
    return widgets[name];
}

QWidget* LatticePresenter::getRdmPositionWidget() {
    return rdm_position;
}

QCheckBox* LatticePresenter::getRdmPositionCheckBox() {
    return rdm_position_CheckBox;
}
