#include "cuboidpresenter.h"

#include <QCheckBox>
#include <QHBoxLayout>

CuboidPresenter::CuboidPresenter(std::shared_ptr<Cuboid>& cuboid) : cuboid(cuboid) {
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
    widgets["Lo"] = new QTableWidgetItem();
    widgets["Lo"]->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    widgets["la"] = new QTableWidgetItem();
    widgets["la"]->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    widgets["h"] = new QTableWidgetItem();
    widgets["h"]->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

    {
        top = new QWidget();
        top_CheckBox = new QCheckBox();
        QHBoxLayout *pLayout = new QHBoxLayout(top);
        pLayout->addWidget(top_CheckBox);
        pLayout->setAlignment(Qt::AlignCenter);
        pLayout->setContentsMargins(0,0,0,0);
        top->setLayout(pLayout);
    }

    {
        bottom = new QWidget();
        bottom_CheckBox = new QCheckBox();
        QHBoxLayout *pLayout = new QHBoxLayout(bottom);
        pLayout->addWidget(bottom_CheckBox);
        pLayout->setAlignment(Qt::AlignCenter);
        pLayout->setContentsMargins(0,0,0,0);
        bottom->setLayout(pLayout);
    }

    {
        periodic = new QWidget();
        periodic_CheckBox = new QCheckBox();
        QHBoxLayout *pLayout = new QHBoxLayout(periodic);
        pLayout->addWidget(periodic_CheckBox);
        pLayout->setAlignment(Qt::AlignCenter);
        pLayout->setContentsMargins(0,0,0,0);
        periodic->setLayout(pLayout);
    }

    updateWidget();
}


void CuboidPresenter::updateWidget()
{
    widgets["x"]->setText(QString::number(cuboid->x));
    widgets["y"]->setText(QString::number(cuboid->y));
    widgets["z"]->setText(QString::number(cuboid->z));
    widgets["nx"]->setText(QString::number(cuboid->nx));
    widgets["ny"]->setText(QString::number(cuboid->ny));
    widgets["nz"]->setText(QString::number(cuboid->nz));
    widgets["Lo"]->setText(QString::number(cuboid->Lo));
    widgets["la"]->setText(QString::number(cuboid->la));
    widgets["h"]->setText(QString::number(cuboid->h));
    periodic_CheckBox->setCheckState(cuboid->ped ? Qt::CheckState::Checked : Qt::CheckState::Unchecked);
    top_CheckBox->setCheckState(cuboid->top!=nullptr ? Qt::CheckState::Checked : Qt::CheckState::Unchecked);
    bottom_CheckBox->setCheckState(cuboid->bottom!=nullptr ? Qt::CheckState::Checked : Qt::CheckState::Unchecked);
}

void CuboidPresenter::updateModel()
{
    printf("updateModel\n");
    cuboid->x = widgets["x"]->text().toDouble();
    cuboid->y = widgets["y"]->text().toDouble();
    cuboid->z = widgets["z"]->text().toDouble();
    cuboid->nx = widgets["nx"]->text().toDouble();
    cuboid->ny = widgets["ny"]->text().toDouble();
    cuboid->nz = widgets["nz"]->text().toDouble();
    cuboid->Lo = widgets["Lo"]->text().toDouble();
    cuboid->la = widgets["la"]->text().toDouble();
    cuboid->h = widgets["h"]->text().toDouble();
    cuboid->base();
    cuboid->ped = (periodic_CheckBox->checkState() == Qt::CheckState::Checked ? 1 : 0);
    cuboid->setTop(top_CheckBox->checkState() == Qt::CheckState::Checked);
    cuboid->setBottom(bottom_CheckBox->checkState() == Qt::CheckState::Checked);
    cuboid->updatePlans();
}


QTableWidgetItem *CuboidPresenter::getWidget(std::string name)
{
    return widgets[name];
}

QWidget *CuboidPresenter::getPeriodicWidget()
{
    return periodic;
}

QCheckBox *CuboidPresenter::getPeriodicCheckBox()
{
    return periodic_CheckBox;
}

QWidget* CuboidPresenter::getTopWidget()
{
    return top;
}

QWidget* CuboidPresenter::getBottomWidget()
{
    return bottom;
}

QCheckBox *CuboidPresenter::getTopCheckBox()
{
    return top_CheckBox;
}

QCheckBox *CuboidPresenter::getBottomCheckBox()
{
    return bottom_CheckBox;
}

