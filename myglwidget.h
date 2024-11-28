#ifndef MYGLWIDGET_H
#define MYGLWIDGET_H

#include <QPushButton>

#include <QOpenGLWidget>
#include <QOpenGLFunctions>

class MyGLWidget : public QOpenGLWidget, public QOpenGLFunctions
{
    Q_OBJECT
public:
    MyGLWidget(QWidget *parent);

    /*
    void incrementCurrentfile();
    void decrementCurrentfile();
    void play();
    void stop();
    */
    void reset();

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
signals:
    void updateCurrentfile(int currentfile);

public slots:
    //void loadDirectory(std::string directory);
    void on_new_container_visual_parameter(int index);
    void on_new_data();
    void on_new_drawBase_state(int);
};

#endif // MYGLWIDGET_H
