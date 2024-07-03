#ifndef VELOCITIESTABWIDGET_H
#define VELOCITIESTABWIDGET_H

#include <QObject>
#include <QTabWidget>

#include "Presenter/velocitiespresenter.h"

class VelocitiesTabWidget : public QTabWidget
{
public:
    VelocitiesTabWidget(QWidget *parent);
    VelocitiesTabWidget() = default;

    void update();
    void addElbow(std::shared_ptr<Elbow> s) {}

    void buildConnections(QString suffix);
    void addVelocityWidget(QTableWidget *vw, std::string name, VelocitiesPresenter &vpIte);
public slots:
    void addSolid(std::shared_ptr<Solid> s);
    void removeSolid(int index);
    void on_new_value(QTableWidgetItem*);

private:
    std::vector<VelocitiesPresenter> vp{};
    std::map<std::string, QTableWidget*> tableWidgets;

    void removeRow(int row);
};

#endif // VELOCITIESTABWIDGET_H
