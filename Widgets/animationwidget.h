#ifndef ANIMATIONWIDGET_H
#define ANIMATIONWIDGET_H

#include <QObject>
#include <QWidget>
#include <thread>

class AnimationWidget : public QWidget
{
    Q_OBJECT
public:
    explicit AnimationWidget(QWidget *parent = nullptr);
    void start();
    void stop();
    void setdt(double newValue);
    void init();

private:
    void play();

    double t = 0;
    double dt;
    bool isRunning;
    std::unique_ptr<std::thread> animator;
signals:
    void updateView();
};

#endif // ANIMATIONWIDGET_H
