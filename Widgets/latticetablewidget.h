#ifndef LATTICETABLEWIDGET_H
#define LATTICETABLEWIDGET_H

#include <QObject>
#include <QTableWidget>
#include <QComboBox>


#include"Presenter/latticepresenter.h"

class LatticeTableWidget : public QTableWidget
{
    Q_OBJECT
public:
    LatticeTableWidget(QWidget *parent);
    QComboBox* listCone;
    QComboBox* listCuboid;

public slots:
    void on_add_lattice();
    void on_remove_lattice();
    void on_new_value(QTableWidgetItem*);
    void on_new_checkbox_value(int);

    void on_new_link_to_cone();
    void on_new_link_to_cuboid();
    void on_unlink();

    void on_update_from_container();

    void on_new_selected_row(int row, int col);
    void LoadDataFromRepository();

signals:
    void data_updated();
    void new_lattice(std::shared_ptr<Lattice>);
    void remove_lattice(int index);

private:
    void addLatticeToUI(std::shared_ptr<Lattice>& lattice);

    std::vector<LatticePresenter> latticePresenters{};
};

#endif // LATTICETABLEWIDGET_H
