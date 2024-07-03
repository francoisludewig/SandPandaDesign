#include "velocitypresenter.h"

VelocityPresenter::VelocityPresenter(Velocity *velocity) : v(velocity) {
    widgets["A0"] = new QTableWidgetItem();
    widgets["A0"]->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    widgets["A1"] = new QTableWidgetItem();
    widgets["A1"]->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    widgets["w"] = new QTableWidgetItem();
    widgets["w"]->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    widgets["p"] = new QTableWidgetItem();
    widgets["p"]->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
}

QTableWidgetItem* VelocityPresenter::getItem(std::string name)
{
    return widgets[name];
}

void VelocityPresenter::updateWidget()
{
    widgets["A0"]->setText(QString::number(v->A0));
    widgets["A1"]->setText(QString::number(v->A1));
    widgets["w"]->setText(QString::number(v->w));
    widgets["p"]->setText(QString::number(v->p));
}

void VelocityPresenter::updateModel()
{
    v->A0 = widgets["A0"]->text().toDouble();
    v->A1 = widgets["A1"]->text().toDouble();
    v->w = widgets["w"]->text().toDouble();
    v->p = widgets["p"]->text().toDouble();
    printf("V = %f + %f sin(%f t + %f)\n",v->A0, v->A1, v->w, v->p);
}
