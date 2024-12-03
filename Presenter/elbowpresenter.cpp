#include "elbowpresenter.h"

ElbowPresenter::ElbowPresenter(std::shared_ptr<Elbow>& elbow) : elbow(elbow) {
    widgets["xi"] = new QTableWidgetItem();
    widgets["xi"]->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    widgets["yi"] = new QTableWidgetItem();
    widgets["yi"]->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    widgets["zi"] = new QTableWidgetItem();
    widgets["zi"]->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    widgets["xf"] = new QTableWidgetItem();
    widgets["xf"]->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    widgets["yf"] = new QTableWidgetItem();
    widgets["yf"]->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    widgets["zf"] = new QTableWidgetItem();
    widgets["zf"]->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    widgets["nx"] = new QTableWidgetItem();
    widgets["nx"]->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    widgets["ny"] = new QTableWidgetItem();
    widgets["ny"]->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    widgets["nz"] = new QTableWidgetItem();
    widgets["nz"]->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    widgets["r"] = new QTableWidgetItem();
    widgets["r"]->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    widgets["orx"] = new QTableWidgetItem();
    widgets["orx"]->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    widgets["ory"] = new QTableWidgetItem();
    widgets["ory"]->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    widgets["orz"] = new QTableWidgetItem();
    widgets["orz"]->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

    updateWidget();
}

void ElbowPresenter::updateWidget()
{
    widgets["xi"]->setText(QString::number(elbow->xi));
    widgets["yi"]->setText(QString::number(elbow->yi));
    widgets["zi"]->setText(QString::number(elbow->zi));
    widgets["xf"]->setText(QString::number(elbow->xf));
    widgets["yf"]->setText(QString::number(elbow->yf));
    widgets["zf"]->setText(QString::number(elbow->zf));
    widgets["nx"]->setText(QString::number(elbow->nx));
    widgets["ny"]->setText(QString::number(elbow->ny));
    widgets["nz"]->setText(QString::number(elbow->nz));
    widgets["r"]->setText(QString::number(elbow->radius));
    widgets["orx"]->setText(QString::number(elbow->orx));
    widgets["ory"]->setText(QString::number(elbow->ory));
    widgets["orz"]->setText(QString::number(elbow->orz));
}

void ElbowPresenter::updateModel()
{
    printf("updateModel\n");
    elbow->xi = widgets["xi"]->text().toDouble();
    elbow->yi = widgets["yi"]->text().toDouble();
    elbow->zi = widgets["zi"]->text().toDouble();
    elbow->xf = widgets["xf"]->text().toDouble();
    elbow->yf = widgets["yf"]->text().toDouble();
    elbow->zf = widgets["zf"]->text().toDouble();
    elbow->cx = widgets["nx"]->text().toDouble();
    elbow->cy = widgets["ny"]->text().toDouble();
    elbow->cz = widgets["nz"]->text().toDouble();
    elbow->orx = widgets["orx"]->text().toDouble();
    elbow->ory = widgets["ory"]->text().toDouble();
    elbow->orz = widgets["orz"]->text().toDouble();
    elbow->radius = widgets["r"]->text().toDouble();
    elbow->base();
}

QTableWidgetItem *ElbowPresenter::getWidget(std::string name)
{
    return widgets[name];
}
