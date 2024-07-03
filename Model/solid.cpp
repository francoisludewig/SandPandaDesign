#include "solid.h"

#include <qmath.h>

Solid::Solid() {}

void Solid::ReadFromFile(FILE *ft)
{
    double q0 = 0,q1 = 1,q2 = 0,q3 = 0;
    fscanf_s(ft, "%lf\t%lf\t%lf",&x,&y,&z);
    fscanf_s(ft, "%lf\t%lf\t%lf\t%lf",&q0,&q1,&q2,&q3);
    vx.ReadFromFile(ft);
    vy.ReadFromFile(ft);
    vz.ReadFromFile(ft);
    wx.ReadFromFile(ft);
    wy.ReadFromFile(ft);
    wz.ReadFromFile(ft);
    fscanf_s(ft, "%lf\t%lf\t%lf",&orx,&ory,&orz);

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

void Solid::base()
{
    float norme = sqrt(nx*nx+ny*ny+nz*nz);
    double R00,R01,R02;
    double R10,R11,R12;
    double R20,R21,R22;
    double dx,dy,dz;

    nx = nx/norme;
    ny = ny/norme;
    nz = nz/norme;
    if((nx == 0 && ny == 0) || (nx == 0 && nz == 0) || (ny == 0 && nz == 0)){
        tx = nz;
        ty = nx;
        tz = ny;
        norme = sqrt(tx*tx+ty*ty+tz*tz);
        tx = tx/norme;
        ty = ty/norme;
        tz = tz/norme;
        // s = n ^ t
        sx = ny*tz-nz*ty;
        sy = tx*nz-tz*nx;
        sz = nx*ty-ny*tx;
    }
    else{
        tx = ny*nz;
        ty = nx*nz;
        tz = -2*nx*ny;
        norme = sqrt(tx*tx+ty*ty+tz*tz);
        tx = tx/norme;
        ty = ty/norme;
        tz = tz/norme;
        // s = n ^ t
        sx = ny*tz-nz*ty;
        sy = tx*nz-tz*nx;
        sz = nx*ty-ny*tx;
    }

    // Rotation d'angle beta  de (t,s) autour de n
    /*
    double C = cos(beta/180*M_PI);
    double S = sin(beta/180*M_PI);
    R00 = nx*nx+(1-nx*nx)*C;
    R01 = nx*ny*(1-C)-nz*S;
    R02 = nx*nz*(1-C)+ny*S;

    R10 = nx*ny*(1-C)+nz*S;
    R11 = ny*ny+(1-ny*ny)*C;
    R12 = ny*nz*(1-C)-nx*S;

    R20 = nx*nz*(1-C)-ny*S;
    R21 = ny*nz*(1-C)+nx*S;
    R22 = nz*nz+(1-nz*nz)*C;

    dx = R00*tx + R01*ty + R02*tz;
    dy = R10*tx + R11*ty + R12*tz;
    dz = R20*tx + R21*ty + R22*tz;
    tx = dx;
    ty = dy;
    tz = dz;

    dx = R00*sx + R01*sy + R02*sz;
    dy = R10*sx + R11*sy + R12*sz;
    dz = R20*sx + R21*sy + R22*sz;
    sx = dx;
    sy = dy;
    sz = dz;
    */
}
