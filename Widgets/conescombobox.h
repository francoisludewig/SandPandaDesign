#ifndef CONESCOMBOBOX_H
#define CONESCOMBOBOX_H

#include <QComboBox>
#include <QObject>

#include "Presenter/conepresenter.h"

class ConesComboBox : public QComboBox
{
public:
    ConesComboBox(QWidget *parent = nullptr);

public slots:
    void new_cones_list(std::vector<ConePresenter> &conePresenters);
};

#endif // CONESCOMBOBOX_H
