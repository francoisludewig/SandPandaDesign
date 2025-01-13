#ifndef SETUP_H
#define SETUP_H

class Setup
{
public:
    Setup();

    double resitutionCoefficient = 0.9;
    double normalStiffness = 100000;
    bool isTangentialDynamicModel = false;
    double staticFrictionCoefficient = 0.7;
    double dynamicFrictionCoefficient = 0.7;

    double gravityAcceleration = 9.81;
    double gravityX = 0;
    double gravityY = 0;
    double gravityZ = -1;
    double gWxA0 = 0;
    double gWxA1 = 0;
    double gWxW = 0;
    double gWxP = 0;
    double gWyA0 = 0;
    double gWyA1 = 0;
    double gWyW = 0;
    double gWyP = 0;
    double gWzA0 = 0;
    double gWzA1 = 0;
    double gWzW = 0;
    double gWzP = 0;

    double duration = 1;
    double timeStep = 0.00001;
    double captureTimeStep = 1./1000.;
    double startingTime = 0.0;
};

#endif // SETUP_H
