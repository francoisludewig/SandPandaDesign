#ifndef STRIPEONSPHERE_H
#define STRIPEONSPHERE_H

#include<vector>

#include <QOpenGLFunctions>
#include<GL/GLU.h>

class StripeOnSphere
{
public:
    StripeOnSphere(int p);

    void draw(double x, double y, double z, double r, double nx, double ny, double nz,
              double tx, double ty, double tz, double sx, double sy, double sz) const;
private:
    void computeVertex();

    int precision;
    std::vector<std::tuple<double, double, double>> vertexA;
    std::vector<std::tuple<double, double, double>> vertexB;
    std::vector<std::tuple<double, double, double>> vertex;
};

#endif // STRIPEONSPHERE_H
