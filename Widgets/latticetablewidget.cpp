#include "latticetablewidget.h"

#include "Repository/containerrepository.h"

LatticeTableWidget::LatticeTableWidget(QWidget *parent) : QTableWidget(parent) {}


void LatticeTableWidget::LoadDataFromRepository() {
    for(int i = 0 ; i < ContainerRepository::getInstance().latticeCount() ; i++) {
        auto item = ContainerRepository::getInstance().getLatticeAtIndex(i);
        addLatticeToUI(item);
    }
}

void LatticeTableWidget::on_add_lattice()
{
    auto lattice = ContainerRepository::getInstance().AddLattice();
    addLatticeToUI(lattice);
}

void LatticeTableWidget::addLatticeToUI(std::shared_ptr<Lattice>& lattice) {
    LatticePresenter latticePresenter(lattice);
    this->latticePresenters.push_back(latticePresenter);

    int currentRow = this->rowCount();
    this->setRowCount(this->rowCount()+1);

    this->setItem(currentRow, 0, latticePresenter.getWidget("xmin"));
    this->setItem(currentRow, 1, latticePresenter.getWidget("ymin"));
    this->setItem(currentRow, 2, latticePresenter.getWidget("zmin"));
    this->setItem(currentRow, 3, latticePresenter.getWidget("xmax"));
    this->setItem(currentRow, 4, latticePresenter.getWidget("ymax"));
    this->setItem(currentRow, 5, latticePresenter.getWidget("zmax"));
    this->setItem(currentRow, 6, latticePresenter.getWidget("r0"));
    this->setItem(currentRow, 7, latticePresenter.getWidget("r1"));
    this->setItem(currentRow, 8, latticePresenter.getWidget("N"));
    this->setItem(currentRow, 9, latticePresenter.getWidget("vmax"));
    this->setItem(currentRow, 10, latticePresenter.getWidget("wmax"));
    this->setCellWidget(currentRow, 11, latticePresenter.getRdmPositionWidget());
    connect(latticePresenter.getRdmPositionCheckBox(), &QCheckBox::stateChanged, this, &LatticeTableWidget::on_new_checkbox_value);
    connect(this, &LatticeTableWidget::cellClicked, this, &LatticeTableWidget::on_new_selected_row);

    printf("New lattice !\n");
    emit new_lattice(lattice);
    emit data_updated();
}


void LatticeTableWidget::on_remove_lattice()
{
    if(!this->selectedIndexes().empty()) {
        int row = this->selectedIndexes().begin()->row();
        auto latticePrToRemove = std::next(this->latticePresenters.begin(), row);
        ContainerRepository::getInstance().RemoveLattice(latticePrToRemove->lattice);
        this->latticePresenters.erase(latticePrToRemove);
        this->removeRow(row);
        emit remove_lattice(row);
        emit data_updated();
    }
}

void LatticeTableWidget::on_new_value(QTableWidgetItem* item)
{
    for(auto ppr : latticePresenters) {
        ppr.updateModel();
    }
    emit data_updated();
}

void LatticeTableWidget::on_new_checkbox_value(int value)
{
    for(auto ppr : latticePresenters) {
        ppr.updateModel();
    }
    emit data_updated();
}


void LatticeTableWidget::on_update_from_container() {
    for(auto ppr : latticePresenters) {
        ppr.updateModel();
    }
    emit data_updated();
}

void LatticeTableWidget::on_new_selected_row(int row, int col) {
    int selectedLatticeIndex = this->currentRow();
    if(selectedLatticeIndex == -1) return;
    if(latticePresenters[selectedLatticeIndex].lattice->boxes) {
        listCone->setCurrentIndex(0);
        listCuboid->setCurrentIndex(ContainerRepository::getInstance().GetIndexOfCuboid(latticePresenters[selectedLatticeIndex].lattice->bte) + 1);

    } else if (latticePresenters[selectedLatticeIndex].lattice->cyd) {
        listCuboid->setCurrentIndex(0);
        listCone->setCurrentIndex(ContainerRepository::getInstance().GetIndexOfCone(latticePresenters[selectedLatticeIndex].lattice->cyde) + 1);
    } else {
        listCone->setCurrentIndex(0);
        listCuboid->setCurrentIndex(0);
    }

}

void LatticeTableWidget::on_new_link_to_cone() {
    int selectedConeIndex = listCone->currentIndex();
    int selectedLatticeIndex = this->currentRow();

    if(selectedConeIndex > 0) {
        // Cone exist => link
        auto cone = ContainerRepository::getInstance().GetCone(selectedConeIndex-1);
        latticePresenters[selectedLatticeIndex].linkToCone(cone);
    } else {
        // None => unlink ?
        latticePresenters[selectedLatticeIndex].unlink();
    }
    emit data_updated();
    std::cout << "Cone selectionné : " << selectedConeIndex << " (lattice " << selectedLatticeIndex << ")" << std::endl;
}

void LatticeTableWidget::on_new_link_to_cuboid() {
    int selectedCuboidIndex = listCuboid->currentIndex();
    int selectedLatticeIndex = this->currentRow();
    if(selectedCuboidIndex > 0) {
        // Cone exist => link
        auto cuboid = ContainerRepository::getInstance().GetCuboid(selectedCuboidIndex-1);
        latticePresenters[selectedLatticeIndex].linkToCuboid(cuboid);
    } else {
        // None => unlink ?
        latticePresenters[selectedLatticeIndex].unlink();
    }
    emit data_updated();

    std::cout << "Cuboid selectionné : " << selectedCuboidIndex << " (lattice " << selectedLatticeIndex << ")" << std::endl;
}

void LatticeTableWidget::on_unlink() {
    int selectedLatticeIndex = this->currentRow();
    std::cout << "Release Lattice :" << selectedLatticeIndex << ")" << std::endl;
    latticePresenters[selectedLatticeIndex].unlink();
    emit data_updated();
}
