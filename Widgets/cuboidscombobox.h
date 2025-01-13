#ifndef CUBOIDSCOMBOBOX_H
#define CUBOIDSCOMBOBOX_H

#include <QComboBox>
#include <QObject>

#include "Presenter/cuboidpresenter.h"

class CuboidsComboBox : public QComboBox
{
public:
    CuboidsComboBox(QWidget *parent = nullptr);

public slots:
    void new_cuboids_list(std::vector<CuboidPresenter> &conePresenters);
};

#endif // CUBOIDSCOMBOBOX_H
