#include "animation.h"

#include<iostream>
#include<chrono>
#include"Repository/containerrepository.h"

Animation::Animation(double dt) : t(0), dt(dt), isRunning(false){}

void Animation::start() {
    if(!isRunning) {
        isRunning = true;
        ContainerRepository::getInstance().StartAnimation();
        animator = std::make_unique<std::thread>(std::thread(&Animation::play, this));
    }
}

void Animation::stop() {
    if(isRunning) {
        isRunning = false;
        animator->join();
        animator.reset();
        ContainerRepository::getInstance().StopAnimation();
    }
}

void Animation::play() {
    while(isRunning) {
        t += dt;
        std::cout << "t = " << t << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
        ContainerRepository::getInstance().Move(t, dt);
        t = 0;
    }
}

void Animation::setdt(double newValue) {
    dt = newValue;
}
