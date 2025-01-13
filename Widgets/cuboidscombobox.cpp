#include "cuboidscombobox.h"

CuboidsComboBox::CuboidsComboBox(QWidget *parent) : QComboBox(parent) { this->addItem("None"); }


void CuboidsComboBox::new_cuboids_list(std::vector<CuboidPresenter> &cuboidPresenters) {
    char cuboidName[32];
    for(int i = this->count()-1 ; i >=0 ; i--)
        this->removeItem(i);

    this->addItem("None");
    for(int i = 0 ; i < cuboidPresenters.size() ; i++) {
        sprintf(cuboidName, "Cuboid %d", i+1);
        this->addItem(cuboidName);
    }
}
