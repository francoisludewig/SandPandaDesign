#ifndef PLANTABLEWIDGET_H
#define PLANTABLEWIDGET_H

#include <QTableWidget>
#include"Presenter/planpresenter.h"

class PlanTableWidget : public QTableWidget
{
    Q_OBJECT
public:
    PlanTableWidget(QWidget *parent);

public slots:
    void on_add_plan();
    void on_remove_plan();
    void on_new_value(QTableWidgetItem*);
    void on_new_checkbox_value(int);
    void LoadDataFromRepository();

signals:
    void data_updated();
    void new_plan(std::shared_ptr<Plan>);
    void remove_plan(int index);

private:
    void addPlanToUI(std::shared_ptr<Plan>& plan);

    std::vector<PlanPresenter> planPresenters{};
};

#endif // PLANTABLEWIDGET_H
