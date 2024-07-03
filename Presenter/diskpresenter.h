#ifndef DISKPRESENTER_H
#define DISKPRESENTER_H

#include<map>
#include<string>
#include<QTableWidgetItem>
#include<QCheckBox>

#include "Model/disk.h"

class DiskPresenter
{
public:
    DiskPresenter(std::shared_ptr<Disk>& disk);
    void updateWidget();
    void updateModel();

    QTableWidgetItem* getWidget(std::string);
    QWidget* getInOutWidget();
    std::shared_ptr<Disk> disk;

    QCheckBox *getInOutCheckBox();
private:
    std::map<std::string, QTableWidgetItem*> widgets;
    QWidget *in_out;
    QCheckBox *in_out_CheckBox;
};

#endif // DISKPRESENTER_H
