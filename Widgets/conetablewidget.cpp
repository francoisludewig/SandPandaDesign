#include "conetablewidget.h"

#include "Repository/containerrepository.h"

#include<QTableWidgetItem>
#include <QApplication>

ConeTableWidget::ConeTableWidget(QWidget *parent) : QTableWidget(parent) {}

void ConeTableWidget::on_add_cone()
{
    auto cone = ContainerRepository::getInstance().AddCone();
    ConePresenter conePresenter(cone);
    this->conePresenters.push_back(conePresenter);

    int currentRow = this->rowCount();
    this->setRowCount(this->rowCount()+1);

    this->setItem(currentRow, 0, conePresenter.getWidget("x"));
    this->setItem(currentRow, 1, conePresenter.getWidget("y"));
    this->setItem(currentRow, 2, conePresenter.getWidget("z"));
    this->setItem(currentRow, 3, conePresenter.getWidget("nx"));
    this->setItem(currentRow, 4, conePresenter.getWidget("ny"));
    this->setItem(currentRow, 5, conePresenter.getWidget("nz"));
    this->setItem(currentRow, 6, conePresenter.getWidget("r0"));
    this->setItem(currentRow, 7, conePresenter.getWidget("r1"));
    this->setItem(currentRow, 8, conePresenter.getWidget("h"));
    this->setCellWidget(currentRow, 9, conePresenter.getInOutWidget());
    this->setCellWidget(currentRow, 10, conePresenter.getTopWidget());
    this->setCellWidget(currentRow, 11, conePresenter.getBottomWidget());

    connect(conePresenter.getInOutCheckBox(), &QCheckBox::stateChanged, this, &ConeTableWidget::on_new_checkbox_value);
    connect(conePresenter.getTopCheckBox(), &QCheckBox::stateChanged, this, &ConeTableWidget::on_new_checkbox_value);
    connect(conePresenter.getBottomCheckBox(), &QCheckBox::stateChanged, this, &ConeTableWidget::on_new_checkbox_value);
    printf("New Cone !\n");
    emit new_cone(cone);
    emit cones_updated(this->conePresenters);
    emit data_updated();
}

void ConeTableWidget::on_remove_cone()
{
    if(!this->selectedIndexes().empty()) {
        int row = this->selectedIndexes().begin()->row();
        auto conePrToRemove = std::next(this->conePresenters.begin(), row);
        ContainerRepository::getInstance().RemoveCone(conePrToRemove->cone);
        this->conePresenters.erase(conePrToRemove);
        this->removeRow(row);
        emit remove_cone(row);
        emit cones_updated(this->conePresenters);
        emit data_updated();
    }
}

void ConeTableWidget::on_new_value(QTableWidgetItem* item)
{
    for(auto ppr : conePresenters) {
        ppr.updateModel();
    }
    emit data_updated();
}

void ConeTableWidget::on_new_checkbox_value(int value)
{
    for(auto ppr : conePresenters) {
        ppr.updateModel();
    }
    emit data_updated();
}
