#ifndef ANIMATION_H
#define ANIMATION_H

#include <thread>

class Animation
{
public:
    Animation(double dt);
    void start();
    void stop();
    void setdt(double newValue);

private:
    void play();

    double t = 0;
    double dt;
    bool isRunning;
    std::unique_ptr<std::thread> animator;
};

#endif // ANIMATION_H
