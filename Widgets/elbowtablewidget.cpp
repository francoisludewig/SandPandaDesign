#include "elbowtablewidget.h"

#include "Repository/containerrepository.h"

#include<QTableWidgetItem>
#include <QApplication>

ElbowTableWidget::ElbowTableWidget(QWidget *parent) : QTableWidget(parent) {}

void ElbowTableWidget::LoadDataFromRepository() {
    for(int i = 0 ; i < ContainerRepository::getInstance().elbowCount() ; i++) {
        auto item = ContainerRepository::getInstance().getElbowAtIndex(i);
        addElbowToUI(item);
    }
}

void ElbowTableWidget::on_add_elbow()
{
    auto elbow = ContainerRepository::getInstance().AddElbow();
    addElbowToUI(elbow);
}

void ElbowTableWidget::addElbowToUI(std::shared_ptr<Elbow>& elbow) {
    ElbowPresenter elbowPresenter(elbow);
    this->elbowPresenters.push_back(elbowPresenter);

    int currentRow = this->rowCount();
    this->setRowCount(this->rowCount()+1);

    this->setItem(currentRow, 0, elbowPresenter.getWidget("xi"));
    this->setItem(currentRow, 1, elbowPresenter.getWidget("yi"));
    this->setItem(currentRow, 2, elbowPresenter.getWidget("zi"));
    this->setItem(currentRow, 3, elbowPresenter.getWidget("xf"));
    this->setItem(currentRow, 4, elbowPresenter.getWidget("yf"));
    this->setItem(currentRow, 5, elbowPresenter.getWidget("zf"));
    this->setItem(currentRow, 6, elbowPresenter.getWidget("nx"));
    this->setItem(currentRow, 7, elbowPresenter.getWidget("ny"));
    this->setItem(currentRow, 8, elbowPresenter.getWidget("nz"));
    this->setItem(currentRow, 9, elbowPresenter.getWidget("r"));
    this->setItem(currentRow, 10, elbowPresenter.getWidget("orx"));
    this->setItem(currentRow, 11, elbowPresenter.getWidget("ory"));
    this->setItem(currentRow, 12, elbowPresenter.getWidget("orz"));

    printf("New Elbow !\n");
    emit new_elbow(elbow);
    emit data_updated();
}


void ElbowTableWidget::on_remove_elbow()
{
    if(!this->selectedIndexes().empty()) {
        int row = this->selectedIndexes().begin()->row();
        auto elbowPrToRemove = std::next(this->elbowPresenters.begin(), row);
        ContainerRepository::getInstance().RemoveElbow(elbowPrToRemove->elbow);
        this->elbowPresenters.erase(elbowPrToRemove);
        this->removeRow(row);
        emit remove_elbow(row);
        emit data_updated();
    }
}

void ElbowTableWidget::on_new_value(QTableWidgetItem* item)
{
    for(auto ppr : elbowPresenters) {
        ppr.updateModel();
    }
    emit data_updated();
}

