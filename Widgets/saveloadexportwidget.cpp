#include "saveloadexportwidget.h"

#include <iostream>


#include "Repository/containerrepository.h"
#include "QFileDialog"

SaveLoadExportWidget::SaveLoadExportWidget(QWidget *parent)
    : QWidget{parent}
{}


void SaveLoadExportWidget::on_export() {
    auto directory = QFileDialog::getExistingDirectory();
    std::cout << "Directory : " << directory.toStdString() << std::endl;
    ContainerRepository::getInstance().Export(directory.toStdString());
}

void SaveLoadExportWidget::on_save() {

}

void SaveLoadExportWidget::on_load() {

}
