#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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
};
#endif // MAINWINDOW_H
