#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "Widgets/setuptimewidget.h"
#include "Widgets/setupcontactmodelwidget.h"
#include "Widgets/setupgravitywidget.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}

class MyGLWidget;

QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    void InitPlanTab(MyGLWidget* myGLWidget);
    void InitDiskTab(MyGLWidget* myGLWidget);
    void InitConeTab(MyGLWidget* myGLWidget);
    void InitElbowTab(MyGLWidget* myGLWidget);
    void InitCuboidTab(MyGLWidget* myGLWidget);
    void InitLatticeTab(MyGLWidget* myGLWidget);
    void InitSetupTimeWidget(SetupTimeWidget* setupTimeWidget );
    void InitSetupContactModelWidget(SetupContactModelWidget* setupContactModelWidget );
    void InitSetupGravityWidget(SetupGravityWidget* setupGravityWidget);
public slots:


};
#endif // MAINWINDOW_H
