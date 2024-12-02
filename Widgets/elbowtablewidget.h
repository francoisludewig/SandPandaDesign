#ifndef ELBOWTABLEWIDGET_H
#define ELBOWTABLEWIDGET_H

#include <QTableWidget>
#include"Presenter/elbowpresenter.h"

class ElbowTableWidget : public QTableWidget
{
    Q_OBJECT
public:
    ElbowTableWidget(QWidget *parent);

public slots:
    void on_add_elbow();
    void on_remove_elbow();
    void on_new_value(QTableWidgetItem*);

signals:
    void data_updated();
    void new_elbow(std::shared_ptr<Elbow>);
    void remove_elbow(int index);

private:
    std::vector<ElbowPresenter> elbowPresenters{};
};

#endif // ELBOWTABLEWIDGET_H
