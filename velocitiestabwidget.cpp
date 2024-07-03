#include "velocitiestabwidget.h"

VelocitiesTabWidget::VelocitiesTabWidget(QWidget *parent) : QTabWidget(parent){}

void VelocitiesTabWidget::update()
{
    auto vpIte = vp.back();
    for(auto& ite : tableWidgets)
        addVelocityWidget(ite.second, ite.first, vpIte);
}

void VelocitiesTabWidget::addVelocityWidget(QTableWidget* vw, std::string name, VelocitiesPresenter& vpIte) {
    auto currentRow = vw->rowCount();
    vw->setRowCount(currentRow + 1);
    vw->setItem(currentRow, 0, vpIte.getItem(name,"A0"));
    vw->setItem(currentRow, 1, vpIte.getItem(name,"A1"));
    vw->setItem(currentRow, 2, vpIte.getItem(name,"w"));
    vw->setItem(currentRow, 3, vpIte.getItem(name,"p"));
}

void VelocitiesTabWidget::buildConnections(QString suffix)
{
    tableWidgets["vx"] = this->widget(0)->findChild<QTableWidget*>("vxTableWidget" + suffix);
    tableWidgets["vy"] = this->widget(1)->findChild<QTableWidget*>("vyTableWidget" + suffix);
    tableWidgets["vz"] = this->widget(2)->findChild<QTableWidget*>("vzTableWidget" + suffix);
    tableWidgets["wx"] = this->widget(3)->findChild<QTableWidget*>("wxTableWidget" + suffix);
    tableWidgets["wy"] = this->widget(4)->findChild<QTableWidget*>("wyTableWidget" + suffix);
    tableWidgets["wz"] = this->widget(5)->findChild<QTableWidget*>("wzTableWidget" + suffix);

    for(auto& ite : tableWidgets)
        connect(ite.second, &QTableWidget::itemChanged, this, &VelocitiesTabWidget::on_new_value);
}

void VelocitiesTabWidget::removeRow(int row) {
    for(auto& ite : tableWidgets)
        ite.second->removeRow(row);
}

void VelocitiesTabWidget::addSolid(std::shared_ptr<Solid> s)
{
    vp.push_back(VelocitiesPresenter(s));
    update();
}

void VelocitiesTabWidget::removeSolid(int index)
{
    auto velocitiesPlanPresenterToRemove = std::next(this->vp.begin(), index);
    vp.erase(velocitiesPlanPresenterToRemove);
    this->removeRow(index);
}

void VelocitiesTabWidget::on_new_value(QTableWidgetItem *)
{
    for(auto& vpIte : vp)
        vpIte.updateModel();
}
