#ifndef SAVELOADEXPORTWIDGET_H
#define SAVELOADEXPORTWIDGET_H

#include <QWidget>

class Setup;

class SaveLoadExportWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SaveLoadExportWidget(QWidget *parent = nullptr);

public slots:
    void on_export();
    void on_save();
    void on_load();
signals:
    void file_loaded();
};

#endif // SAVELOADEXPORTWIDGET_H
