#include "planpresenter.h"

#include <QCheckBox>
#include <QHBoxLayout>

PlanPresenter::PlanPresenter(std::shared_ptr<Plan>& plan) : plan(plan) {
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
    widgets["dt"] = new QTableWidgetItem();
    widgets["dt"]->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    widgets["ds"] = new QTableWidgetItem();
    widgets["ds"]->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

    in_out = new QWidget();
    in_out_CheckBox = new QCheckBox();
    QHBoxLayout *pLayout = new QHBoxLayout(in_out);
    pLayout->addWidget(in_out_CheckBox);
    pLayout->setAlignment(Qt::AlignCenter);
    pLayout->setContentsMargins(0,0,0,0);
    in_out->setLayout(pLayout);

    updateWidget();
}

void PlanPresenter::updateWidget()
{
    widgets["x"]->setText(QString::number(plan->x));
    widgets["y"]->setText(QString::number(plan->y));
    widgets["z"]->setText(QString::number(plan->z));
    widgets["nx"]->setText(QString::number(plan->nx));
    widgets["ny"]->setText(QString::number(plan->ny));
    widgets["nz"]->setText(QString::number(plan->nz));
    widgets["dt"]->setText(QString::number(plan->dt));
    widgets["ds"]->setText(QString::number(plan->ds));
    widgets["ds"]->setText(QString::number(plan->ds));
    in_out_CheckBox->setCheckState(plan->inAndOut!=0 ? Qt::CheckState::Checked : Qt::CheckState::Unchecked);
}

void PlanPresenter::updateModel()
{
    printf("updateModel\n");
    plan->x = widgets["x"]->text().toDouble();
    plan->y = widgets["y"]->text().toDouble();
    plan->z = widgets["z"]->text().toDouble();
    plan->nx = widgets["nx"]->text().toDouble();
    plan->ny = widgets["ny"]->text().toDouble();
    plan->nz = widgets["nz"]->text().toDouble();
    plan->dt = widgets["dt"]->text().toDouble();
    plan->ds = widgets["ds"]->text().toDouble();
    plan->base();
    plan->inAndOut = (in_out_CheckBox->checkState() == Qt::CheckState::Checked ? 1 : 0);
    printf("plan->inAndOut = %d\n", plan->inAndOut);
}

QTableWidgetItem *PlanPresenter::getWidget(std::string name)
{
    return widgets[name];
}

QWidget *PlanPresenter::getInOutWidget()
{
    return in_out;
}

QCheckBox *PlanPresenter::getInOutCheckBox()
{
    return in_out_CheckBox;
}


