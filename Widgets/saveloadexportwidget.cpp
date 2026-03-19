#include "saveloadexportwidget.h"

#include <iostream>
#include <fstream>

#include "Repository/containerrepository.h"
#include "QFileDialog"

SaveLoadExportWidget::SaveLoadExportWidget(QWidget *parent)
    : QWidget{parent}
{}


void SaveLoadExportWidget::on_export() {
    if (ContainerRepository::getInstance().isImportMode())
        return;
    auto directory = QFileDialog::getExistingDirectory();
    if (directory.isEmpty()) return;
    std::cout << "Directory : " << directory.toStdString() << std::endl;
    ContainerRepository::getInstance().Export(directory.toStdString());
}

void SaveLoadExportWidget::on_load() {
    if (ContainerRepository::getInstance().isImportMode())
        return;
    auto file = QFileDialog::getOpenFileName();
    if (file.isEmpty()) return;
    std::cout << "File : " << file.toStdString() << std::endl;
    std::ifstream ifs(file.toStdString());
    std::string fromFile( (std::istreambuf_iterator<char>(ifs) ),
                          (std::istreambuf_iterator<char>()    ) );
    JsonSerializer::DesignFromJsonValue(fromFile);
    emit file_loaded();
}

void SaveLoadExportWidget::on_save() {
    if (ContainerRepository::getInstance().isImportMode())
        return;
    auto file = QFileDialog::getSaveFileName();
    if (file.isEmpty()) return;
    std::cout << "File : " << file.toStdString() << std::endl;
    std::string toFile = JsonSerializer::DesignToJsonValue().toStyledString();
    std::ofstream out(file.toStdString());
    out << toFile;
    out.close();
}

void SaveLoadExportWidget::on_import() {
    auto directory = QFileDialog::getExistingDirectory(nullptr, "Select simulation directory (containing Start_stop)");
    if (directory.isEmpty()) return;
    std::cout << "Import from: " << directory.toStdString() << std::endl;

    bool success = ContainerRepository::getInstance().ImportStartStop(directory.toStdString());
    if (success) {
        setImportMode(true);
        emit file_loaded();
    }
}

void SaveLoadExportWidget::on_export_start_stop() {
    if (!ContainerRepository::getInstance().isImportMode())
        return;
    auto directory = QFileDialog::getExistingDirectory(nullptr, "Select export directory");
    if (directory.isEmpty()) return;
    std::cout << "Export Start_stop to: " << directory.toStdString() << std::endl;
    ContainerRepository::getInstance().ExportStartStop(directory.toStdString());
}

void SaveLoadExportWidget::setImportMode(bool enabled) {
    if (exportBtn) exportBtn->setEnabled(!enabled);
    if (saveBtn) saveBtn->setEnabled(!enabled);
    if (loadBtn) loadBtn->setEnabled(!enabled);
    if (exportStartStopBtn) exportStartStopBtn->setEnabled(enabled);
}
