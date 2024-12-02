#include "animationwidget.h"

#include "Repository/containerrepository.h"
#include <iostream>

AnimationWidget::AnimationWidget(QWidget *parent)
    : QWidget{parent}, dt(0.001), isRunning(false) {}

void AnimationWidget::init() {
    dt = 0.001;
    isRunning = false;
}

void AnimationWidget::start() {
    if(!isRunning) {
        isRunning = true;
        ContainerRepository::getInstance().StartAnimation();
        animator = std::make_unique<std::thread>(std::thread(&AnimationWidget::play, this));
    }
}

void AnimationWidget::stop() {
    if(isRunning) {
        isRunning = false;
        animator->join();
        animator.reset();
        ContainerRepository::getInstance().StopAnimation();
    }
}

void AnimationWidget::play() {
    while(isRunning) {
        t += dt;
        std::cout << "t = " << t << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
        ContainerRepository::getInstance().Move(t, dt);
        emit updateView();
    }
    t = 0;
}

void AnimationWidget::setdt(double newValue) {
    dt = newValue;
}
