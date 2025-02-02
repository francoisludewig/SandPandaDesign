#ifndef DISKTABLEWIDGET_H
#define DISKTABLEWIDGET_H

#include <QTableWidget>
#include"Presenter/diskpresenter.h"

class DiskTableWidget : public QTableWidget
{
    Q_OBJECT
public:
    DiskTableWidget(QWidget *parent);

public slots:
    void on_add_disk();
    void on_remove_disk();
    void on_new_value(QTableWidgetItem*);
    void on_new_checkbox_value(int);
    void LoadDataFromRepository();

signals:
    void data_updated();
    void new_disk(std::shared_ptr<Disk>);
    void remove_disk(int index);

private:
    void addDiskToUI(std::shared_ptr<Disk>& disk);

    std::vector<DiskPresenter> diskPresenters{};
};

#endif // DISKTABLEWIDGET_H
