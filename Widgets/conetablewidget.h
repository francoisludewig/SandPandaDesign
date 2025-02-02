#ifndef CONETABLEWIDGET_H
#define CONETABLEWIDGET_H

#include <QTableWidget>
#include"Presenter/conepresenter.h"

class ConeTableWidget : public QTableWidget
{
    Q_OBJECT
public:
    ConeTableWidget(QWidget *parent);


public slots:
    void on_add_cone();
    void on_remove_cone();
    void on_new_value(QTableWidgetItem*);
    void on_new_checkbox_value(int);
    void LoadDataFromRepository();

signals:
    void data_updated();
    void new_cone(std::shared_ptr<Cone>);
    void remove_cone(int index);
    void cones_updated(std::vector<ConePresenter> &conePresenters);

private:
    void addConeToUI(std::shared_ptr<Cone>& cone);


    std::vector<ConePresenter> conePresenters{};
};

#endif // CONETABLEWIDGET_H
