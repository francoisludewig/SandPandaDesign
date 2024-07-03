#include "conepresenter.h"

#include <QCheckBox>
#include <QHBoxLayout>

ConePresenter::ConePresenter(std::shared_ptr<Cone>& cone) : cone(cone) {
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
    widgets["r0"] = new QTableWidgetItem();
    widgets["r0"]->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    widgets["r1"] = new QTableWidgetItem();
    widgets["r1"]->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    widgets["h"] = new QTableWidgetItem();
    widgets["h"]->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

    {
        in_out = new QWidget();
        in_out_CheckBox = new QCheckBox();
        QHBoxLayout *pLayout = new QHBoxLayout(in_out);
        pLayout->addWidget(in_out_CheckBox);
        pLayout->setAlignment(Qt::AlignCenter);
        pLayout->setContentsMargins(0,0,0,0);
        in_out->setLayout(pLayout);
    }

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

    updateWidget();
}

void ConePresenter::updateWidget()
{
    widgets["x"]->setText(QString::number(cone->x));
    widgets["y"]->setText(QString::number(cone->y));
    widgets["z"]->setText(QString::number(cone->z));
    widgets["nx"]->setText(QString::number(cone->nx));
    widgets["ny"]->setText(QString::number(cone->ny));
    widgets["nz"]->setText(QString::number(cone->nz));
    widgets["r0"]->setText(QString::number(cone->r0));
    widgets["r1"]->setText(QString::number(cone->r1));
    widgets["h"]->setText(QString::number(cone->h));
    in_out_CheckBox->setCheckState(cone->inAndOut!=0 ? Qt::CheckState::Checked : Qt::CheckState::Unchecked);
    top_CheckBox->setCheckState(cone->top!=nullptr ? Qt::CheckState::Checked : Qt::CheckState::Unchecked);
    bottom_CheckBox->setCheckState(cone->bottom!=nullptr ? Qt::CheckState::Checked : Qt::CheckState::Unchecked);
}

void ConePresenter::updateModel()
{
    printf("updateModel\n");
    cone->x = widgets["x"]->text().toDouble();
    cone->y = widgets["y"]->text().toDouble();
    cone->z = widgets["z"]->text().toDouble();
    cone->nx = widgets["nx"]->text().toDouble();
    cone->ny = widgets["ny"]->text().toDouble();
    cone->nz = widgets["nz"]->text().toDouble();
    cone->r0 = widgets["r0"]->text().toDouble();
    cone->r1 = widgets["r1"]->text().toDouble();
    cone->h = widgets["h"]->text().toDouble();
    cone->base();
    cone->inAndOut = (in_out_CheckBox->checkState() == Qt::CheckState::Checked ? 1 : 0);
    cone->setTop(top_CheckBox->checkState() == Qt::CheckState::Checked);
    cone->setBottom(bottom_CheckBox->checkState() == Qt::CheckState::Checked);
}

QTableWidgetItem *ConePresenter::getWidget(std::string name)
{
    return widgets[name];
}

QWidget *ConePresenter::getInOutWidget()
{
    return in_out;
}

QCheckBox *ConePresenter::getInOutCheckBox()
{
    return in_out_CheckBox;
}

QWidget* ConePresenter::getTopWidget()
{
    return top;
}

QWidget* ConePresenter::getBottomWidget()
{
    return bottom;
}

QCheckBox *ConePresenter::getTopCheckBox()
{
    return top_CheckBox;
}

QCheckBox *ConePresenter::getBottomCheckBox()
{
    return bottom_CheckBox;
}
