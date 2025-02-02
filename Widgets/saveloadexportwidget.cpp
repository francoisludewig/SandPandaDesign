#include "saveloadexportwidget.h"

#include <iostream>
#include <fstream>

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

void SaveLoadExportWidget::on_load() {
    auto file = QFileDialog::getOpenFileName();
    std::cout << "File : " << file.toStdString() << std::endl;
    std::ifstream ifs(file.toStdString());
    std::string fromFile( (std::istreambuf_iterator<char>(ifs) ),
                          (std::istreambuf_iterator<char>()    ) );
    JsonSerializer::DesignFromJsonValue(fromFile);
    emit file_loaded();
}

void SaveLoadExportWidget::on_save() {
    auto file = QFileDialog::getSaveFileName();
    std::cout << "File : " << file.toStdString() << std::endl;
    std::string toFile = JsonSerializer::DesignToJsonValue().toStyledString();
    std::ofstream out(file.toStdString());
    out << toFile;
    out.close();
}
