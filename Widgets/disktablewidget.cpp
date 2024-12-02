#include "disktablewidget.h"

#include "Repository/containerrepository.h"

#include<QTableWidgetItem>
#include <QApplication>

DiskTableWidget::DiskTableWidget(QWidget *parent) : QTableWidget(parent) {}

void DiskTableWidget::on_add_disk()
{
    auto disk = ContainerRepository::getInstance().AddDisk();
    DiskPresenter diskPresenter(disk);
    this->diskPresenters.push_back(diskPresenter);

    int currentRow = this->rowCount();
    this->setRowCount(this->rowCount()+1);

    this->setItem(currentRow, 0, diskPresenter.getWidget("x"));
    this->setItem(currentRow, 1, diskPresenter.getWidget("y"));
    this->setItem(currentRow, 2, diskPresenter.getWidget("z"));
    this->setItem(currentRow, 3, diskPresenter.getWidget("nx"));
    this->setItem(currentRow, 4, diskPresenter.getWidget("ny"));
    this->setItem(currentRow, 5, diskPresenter.getWidget("nz"));
    this->setItem(currentRow, 6, diskPresenter.getWidget("r"));
    this->setCellWidget(currentRow, 7, diskPresenter.getInOutWidget());

    connect(diskPresenter.getInOutCheckBox(), &QCheckBox::stateChanged, this, &DiskTableWidget::on_new_checkbox_value);

    printf("New Disk !\n");
    emit new_disk(disk);
    emit data_updated();
}

void DiskTableWidget::on_remove_disk()
{
    if(!this->selectedIndexes().empty()) {
        int row = this->selectedIndexes().begin()->row();
        auto planPrToRemove = std::next(this->diskPresenters.begin(), row);
        ContainerRepository::getInstance().RemoveDisk(planPrToRemove->disk);
        this->diskPresenters.erase(planPrToRemove);
        this->removeRow(row);
        emit remove_disk(row);
        emit data_updated();
    }
}

void DiskTableWidget::on_new_value(QTableWidgetItem* item)
{
    for(auto ppr : diskPresenters) {
        ppr.updateModel();
    }
    emit data_updated();
}

void DiskTableWidget::on_new_checkbox_value(int value)
{
    for(auto ppr : diskPresenters) {
        ppr.updateModel();
    }
    emit data_updated();
}
