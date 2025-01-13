#ifndef CUBOIDTABLEWIDGET_H
#define CUBOIDTABLEWIDGET_H

#include <QTableWidget>
#include"Presenter/cuboidpresenter.h"
#include "Model/cuboid.h"

class CuboidTableWidget : public QTableWidget
{
    Q_OBJECT
public:
    CuboidTableWidget(QWidget *parent);

public slots:
    void on_add_cuboid();
    void on_remove_cuboid();
    void on_new_value(QTableWidgetItem*);
    void on_new_checkbox_value(int);

signals:
    void data_updated();
    void new_cuboid(std::shared_ptr<Cuboid>);
    void remove_cuboid(int index);
    void cuboids_updated(std::vector<CuboidPresenter> &cuboidPresenters);

private:
    std::vector<CuboidPresenter> cuboidPresenters{};
};

#endif // CUBOIDTABLEWIDGET_H
