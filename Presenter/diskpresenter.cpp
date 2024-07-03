#include "diskpresenter.h"

#include <QCheckBox>
#include <QHBoxLayout>

DiskPresenter::DiskPresenter(std::shared_ptr<Disk>& disk) : disk(disk) {
    widgets["x"] = new QTableWidgetItem();
    widgets["x"]->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    widgets["y"] = new QTableWidgetItem();
    widgets["y"]->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    widgets["z"] = new QTableWidgetItem();
    widgets["z"]->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    widgets["nx"] = new QTableWidgetItem();
    widgets["nx"]->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    widgets["ny"] = new QTableWidgetItem();
    widgets["ny"]->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    widgets["nz"] = new QTableWidgetItem();
    widgets["nz"]->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    widgets["r"] = new QTableWidgetItem();
    widgets["r"]->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);


    in_out = new QWidget();
    in_out_CheckBox = new QCheckBox();
    QHBoxLayout *pLayout = new QHBoxLayout(in_out);
    pLayout->addWidget(in_out_CheckBox);
    pLayout->setAlignment(Qt::AlignCenter);
    pLayout->setContentsMargins(0,0,0,0);
    in_out->setLayout(pLayout);

    updateWidget();
}

void DiskPresenter::updateWidget()
{
    widgets["x"]->setText(QString::number(disk->x));
    widgets["y"]->setText(QString::number(disk->y));
    widgets["z"]->setText(QString::number(disk->z));
    widgets["nx"]->setText(QString::number(disk->nx));
    widgets["ny"]->setText(QString::number(disk->ny));
    widgets["nz"]->setText(QString::number(disk->nz));
    widgets["r"]->setText(QString::number(disk->r));
    in_out_CheckBox->setCheckState(disk->inAndOut!=0 ? Qt::CheckState::Checked : Qt::CheckState::Unchecked);
}

void DiskPresenter::updateModel()
{
    printf("updateModel\n");
    disk->x = widgets["x"]->text().toDouble();
    disk->y = widgets["y"]->text().toDouble();
    disk->z = widgets["z"]->text().toDouble();
    disk->nx = widgets["nx"]->text().toDouble();
    disk->ny = widgets["ny"]->text().toDouble();
    disk->nz = widgets["nz"]->text().toDouble();
    disk->r = widgets["r"]->text().toDouble();
    disk->base();
    disk->inAndOut = (in_out_CheckBox->checkState() == Qt::CheckState::Checked ? 1 : 0);
}

QTableWidgetItem *DiskPresenter::getWidget(std::string name)
{
    return widgets[name];
}

QWidget *DiskPresenter::getInOutWidget()
{
    return in_out;
}

QCheckBox *DiskPresenter::getInOutCheckBox()
{
    return in_out_CheckBox;
}


