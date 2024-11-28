#include "cuboidtablewidget.h"

#include "Repository/containerrepository.h"

CuboidTableWidget::CuboidTableWidget(QWidget *parent) : QTableWidget(parent) {}


void CuboidTableWidget::on_add_cuboid()
{
    auto cuboid = ContainerRepository::getInstance().AddCuboid();
    CuboidPresenter cuboidPresenter(cuboid);
    this->cuboidPresenters.push_back(cuboidPresenter);

    int currentRow = this->rowCount();
    this->setRowCount(this->rowCount()+1);

    this->setItem(currentRow, 0, cuboidPresenter.getWidget("x"));
    this->setItem(currentRow, 1, cuboidPresenter.getWidget("y"));
    this->setItem(currentRow, 2, cuboidPresenter.getWidget("z"));
    this->setItem(currentRow, 3, cuboidPresenter.getWidget("nx"));
    this->setItem(currentRow, 4, cuboidPresenter.getWidget("ny"));
    this->setItem(currentRow, 5, cuboidPresenter.getWidget("nz"));
    this->setItem(currentRow, 6, cuboidPresenter.getWidget("Lo"));
    this->setItem(currentRow, 7, cuboidPresenter.getWidget("la"));
    this->setItem(currentRow, 8, cuboidPresenter.getWidget("h"));
    this->setCellWidget(currentRow, 9, cuboidPresenter.getTopWidget());
    this->setCellWidget(currentRow, 10, cuboidPresenter.getBottomWidget());
    this->setCellWidget(currentRow, 11, cuboidPresenter.getPeriodicWidget());

    connect(cuboidPresenter.getPeriodicCheckBox(), &QCheckBox::stateChanged, this, &CuboidTableWidget::on_new_checkbox_value);
    connect(cuboidPresenter.getTopCheckBox(), &QCheckBox::stateChanged, this, &CuboidTableWidget::on_new_checkbox_value);
    connect(cuboidPresenter.getBottomCheckBox(), &QCheckBox::stateChanged, this, &CuboidTableWidget::on_new_checkbox_value);

    printf("New Box !\n");
    emit new_cuboid(cuboid);
    emit data_updated();
}

void CuboidTableWidget::on_remove_cuboid()
{
    if(!this->selectedIndexes().empty()) {
        int row = this->selectedIndexes().begin()->row();
        auto cuboidPrToRemove = std::next(this->cuboidPresenters.begin(), row);
        ContainerRepository::getInstance().RemoveCuboid(cuboidPrToRemove->cuboid);
        this->cuboidPresenters.erase(cuboidPrToRemove);
        this->removeRow(row);
        emit remove_cuboid(row);
        emit data_updated();
    }
}

void CuboidTableWidget::on_new_value(QTableWidgetItem* item)
{
    for(auto ppr : cuboidPresenters) {
        ppr.updateModel();
    }
    emit data_updated();
}

void CuboidTableWidget::on_new_checkbox_value(int value)
{
    for(auto ppr : cuboidPresenters) {
        ppr.updateModel();
    }
    emit data_updated();
}
