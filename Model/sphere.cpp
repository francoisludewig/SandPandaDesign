#include "sphere.h"

#include <QOpenGLFunctions>
#include <GL/GLU.h>
#include "stripeonsphere.h"

static const StripeOnSphere sos{25};

Sphere::Sphere() {}

void Sphere::ReadFromFile(FILE *ft)
{
    int b = 0,b1 = 0;
    double q0 = 0,q1 = 1,q2 = 0,q3 = 0;

    fscanf_s(ft,"%d\t%d\t%lf\t%lf\t%lf\t%lf\t%lf\t%lf\t%lf\t%lf\t%lf\t%lf\t%lf\t%lf\t%lf\t%lf\t%d\t%d\n",
             &b,&sp,&r,
             &x,&y,&z,
             &q0,&q1,&q2,&q3,
             &vx,&vy,&vz,
             &wx,&wy,&wz,
             &b,&b1);

    // Quaternion -> axe de rotation et angle
    if(q0 != 0){
        nx = (1 - 2*q2*q2 - 2*q3*q3);
        ny = (2*q1*q2 + 2*q3*q0);
        nz = (2*q1*q3 - 2*q2*q0);

        tx = (2*q1*q2 - 2*q3*q0);
        ty = (1 - 2*q1*q1 - 2*q3*q3);
        tz = (2*q2*q3 + 2*q1*q0);

        sx = (2*q1*q3 + 2*q2*q0);
        sy = (2*q2*q3 - 2*q1*q0);
        sz = (1 - 2*q1*q1 - 2*q2*q2);
    }
    else{
        nx = (1);
        ny = (0);
        nz = (0);
        tx = (0);
        ty = (1);
        tz = (0);
        sx = (0);
        sy = (0);
        sz = (1);
    }
    if(b1 != -9)bd = true;
}


void Sphere::Draw(){
    sos.draw(x, y, z, r,
             nx, ny, nz,
             tx, ty, tz,
             sx, sy, sz);
}
