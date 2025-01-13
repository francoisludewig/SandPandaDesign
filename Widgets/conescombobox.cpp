#include "conescombobox.h"

ConesComboBox::ConesComboBox(QWidget *parent) : QComboBox(parent) { this->addItem("None"); }

void ConesComboBox::new_cones_list(std::vector<ConePresenter> &conePresenters) {
    char coneName[32];
    for(int i = this->count()-1 ; i >=0 ; i--)
        this->removeItem(i);

    this->addItem("None");
    for(int i = 0 ; i < conePresenters.size() ; i++) {
        sprintf(coneName, "Cone %d", i+1);
        this->addItem(coneName);
    }
}
