#ifndef SAVELOADEXPORTWIDGET_H
#define SAVELOADEXPORTWIDGET_H

#include <QWidget>
#include <QPushButton>

class Setup;

class SaveLoadExportWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SaveLoadExportWidget(QWidget *parent = nullptr);

    void setExportButton(QPushButton *btn) { exportBtn = btn; }
    void setSaveButton(QPushButton *btn) { saveBtn = btn; }
    void setLoadButton(QPushButton *btn) { loadBtn = btn; }
    void setExportStartStopButton(QPushButton *btn) { exportStartStopBtn = btn; }

public slots:
    void on_export();
    void on_save();
    void on_load();
    void on_import();
    void on_export_start_stop();

signals:
    void file_loaded();

private:
    void setImportMode(bool enabled);

    QPushButton *exportBtn = nullptr;
    QPushButton *saveBtn = nullptr;
    QPushButton *loadBtn = nullptr;
    QPushButton *exportStartStopBtn = nullptr;
};

#endif // SAVELOADEXPORTWIDGET_H
