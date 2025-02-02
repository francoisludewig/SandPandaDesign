#include "plantablewidget.h"

#include "Repository/containerrepository.h"

#include<QTableWidgetItem>
#include <QApplication>

PlanTableWidget::PlanTableWidget(QWidget *parent) : QTableWidget(parent) {}


void PlanTableWidget::LoadDataFromRepository() {
    for(int i = 0 ; i < ContainerRepository::getInstance().planCount() ; i++) {
        auto item = ContainerRepository::getInstance().getPlanAtIndex(i);
        addPlanToUI(item);
    }
}

void PlanTableWidget::on_add_plan()
{
    auto plan = ContainerRepository::getInstance().AddPlan();
    addPlanToUI(plan);
}

void PlanTableWidget::addPlanToUI(std::shared_ptr<Plan>& plan) {
    PlanPresenter planPresenter(plan);
    this->planPresenters.push_back(planPresenter);

    int currentRow = this->rowCount();
    this->setRowCount(this->rowCount()+1);

    this->setItem(currentRow, 0, planPresenter.getWidget("x"));
    this->setItem(currentRow, 1, planPresenter.getWidget("y"));
    this->setItem(currentRow, 2, planPresenter.getWidget("z"));
    this->setItem(currentRow, 3, planPresenter.getWidget("nx"));
    this->setItem(currentRow, 4, planPresenter.getWidget("ny"));
    this->setItem(currentRow, 5, planPresenter.getWidget("nz"));
    this->setItem(currentRow, 6, planPresenter.getWidget("dt"));
    this->setItem(currentRow, 7, planPresenter.getWidget("ds"));
    this->setCellWidget(currentRow, 8, planPresenter.getInOutWidget());

    connect(planPresenter.getInOutCheckBox(), &QCheckBox::stateChanged, this, &PlanTableWidget::on_new_checkbox_value);

    printf("New Plan !\n");
    emit new_plan(plan);
    emit data_updated();
}

void PlanTableWidget::on_remove_plan()
{
    if(!this->selectedIndexes().empty()) {
        int row = this->selectedIndexes().begin()->row();
        auto planPrToRemove = std::next(this->planPresenters.begin(), row);
        ContainerRepository::getInstance().RemovePlan(planPrToRemove->plan);
        this->planPresenters.erase(planPrToRemove);
        this->removeRow(row);
        emit remove_plan(row);
        emit data_updated();
    }
}

void PlanTableWidget::on_new_value(QTableWidgetItem* item)
{
    for(auto ppr : planPresenters) {
        ppr.updateModel();
    }
    emit data_updated();
}

void PlanTableWidget::on_new_checkbox_value(int value)
{
    for(auto ppr : planPresenters) {
        ppr.updateModel();
    }
    emit data_updated();
}
