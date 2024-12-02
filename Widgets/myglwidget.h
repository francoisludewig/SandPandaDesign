#ifndef MYGLWIDGET_H
#define MYGLWIDGET_H

#include <QPushButton>
#include <QObject>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include "animationwidget.h"

class MyGLWidget : public QOpenGLWidget, public QOpenGLFunctions
{
    Q_OBJECT
public:
    MyGLWidget(QWidget *parent);
    /*
    void incrementCurrentfile();
    void decrementCurrentfile();

    */
    void reset();
    void setAnimator(AnimationWidget* animationWidget);
protected:
    void initializeGL() override;
    void paintGL() override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseDoubleClickEvent(QMouseEvent *event) override;
    void wheelEvent(QWheelEvent* event) override;

private:
    int mousePosX, mousePosY;
    bool isMouseDragged;
    bool isDoubleClickMouseDragged;
    int currentFile = 0;
    bool animation = false;
    bool drawContainer = true;
    bool isLineContainer = false;
    bool draw_base = true;

    double posX = 0, posY = 0;
    double zoom;
    double anglex;
    double angley;

    void prepare();
    void drawCylinder(double r);
    void drawBase();
    void computeDefaultZoom();
    double zoom0;

    AnimationWidget* animator;
signals:
    void updateCurrentfile(int currentfile);

public slots:
    //void loadDirectory(std::string directory);
    void on_new_container_visual_parameter(int index);
    void on_new_data();
    void on_new_drawBase_state(int);
    void play();
    void stop();
    void on_new_timestep(const QString&);
};

#endif // MYGLWIDGET_H
