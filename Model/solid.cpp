#include "solid.h"

#include <qmath.h>
#include <iostream>

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
    //double R00,R01,R02;
    //double R10,R11,R12;
    //double R20,R21,R22;
    //double dx,dy,dz;

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


void Solid::moveat(double t, double h){
    Vx = vx.valueat(t);
    Vy = vy.valueat(t);
    Vz = vz.valueat(t);

    Wx = wx.valueat(t)*h;
    Wy = wy.valueat(t)*h;
    Wz = wz.valueat(t)*h;
    x += Vx*h;
    y += Vy*h;
    z += Vz*h;
    std::cout << "t = " << t << ", h = " << h << std::endl;
    std::cout << x0 << "->" << x << "(Vx = " << Vx << ")" << std::endl;
    double W = sqrt(Wx*Wx+Wy*Wy+Wz*Wz);
    double Ca = cos(W),Sa = sin(W);
    if(W != 0){
        Wx = Wx/W;
        Wy = Wy/W;
        Wz = Wz/W;

        //      | wx^2+Ca*(1-wx^2)       wx*wy*(1-Ca)-wz*Sa     wx*wz*(1-Ca)+wy*Sa |
        //[R] = | wx*wy*(1-Ca)+wz*Sa     wy^2+Ca*(1-wy^2)       wy*wz*(1-Ca)-wx*Sa |
        //      | wx*wz*(1-Ca)-wy*Sa     wy*wz*(1-Ca)+wx*Sa     wz^2+Ca*(1-wz^2)   |

        R[0][0] = Wx*Wx+Ca*(1-Wx*Wx);
        R[0][1] = Wx*Wy*(1-Ca)-Wz*Sa;
        R[0][2] = Wx*Wz*(1-Ca)+Wy*Sa;

        R[1][0] = Wx*Wy*(1-Ca)+Wz*Sa;
        R[1][1] = Wy*Wy+Ca*(1-Wy*Wy);
        R[1][2] = Wy*Wz*(1-Ca)-Wx*Sa;

        R[2][0] = Wx*Wz*(1-Ca)-Wy*Sa;
        R[2][1] = Wy*Wz*(1-Ca)+Wx*Sa;
        R[2][2] = Wz*Wz+Ca*(1-Wz*Wz);
    }
    else{
        R[0][0] = 1;
        R[0][1] = 0;
        R[0][2] = 0;

        R[1][0] = 0;
        R[1][1] = 1;
        R[1][2] = 0;

        R[2][0] = 0;
        R[2][1] = 0;
        R[2][2] = 1;
    }

    double lx,ly,lz;

    lx = (x-orx);
    ly = (y-ory);
    lz = (z-orz);

    x = (R[0][0]*lx + R[0][1]*ly + R[0][2]*lz) + orx;
    y = (R[1][0]*lx + R[1][1]*ly + R[1][2]*lz) + ory;
    z = (R[2][0]*lx + R[2][1]*ly + R[2][2]*lz) + orz;

    lx = nx;
    ly = ny;
    lz = nz;
    nx = (R[0][0]*lx + R[0][1]*ly + R[0][2]*lz);
    ny = (R[1][0]*lx + R[1][1]*ly + R[1][2]*lz);
    nz = (R[2][0]*lx + R[2][1]*ly + R[2][2]*lz);

    lx = tx;
    ly = ty;
    lz = tz;
    tx = (R[0][0]*lx + R[0][1]*ly + R[0][2]*lz);
    ty = (R[1][0]*lx + R[1][1]*ly + R[1][2]*lz);
    tz = (R[2][0]*lx + R[2][1]*ly + R[2][2]*lz);

    lx = sx;
    ly = sy;
    lz = sz;
    sx = (R[0][0]*lx + R[0][1]*ly + R[0][2]*lz);
    sy = (R[1][0]*lx + R[1][1]*ly + R[1][2]*lz);
    sz = (R[2][0]*lx + R[2][1]*ly + R[2][2]*lz);
}


void Solid::startAnime() {
    std::cout << "startAnime => Save Solid State" << std::endl;
    isAnimated = true;
    x0 = x;
    y0 = y;
    z0 = z;
    nx0 = nx;
    ny0 = ny;
    nz0 = nz;
}

void Solid::stopAnime(){
    std::cout << "stopAnime => Reset Solid" << std::endl;
    isAnimated = false;
    x = x0;
    y = y0;
    z = z0;
    nx = nx0;
    ny = ny0;
    nz = nz0;
    base();
}


bool Solid::NonNullVelocity(){
    if(vx.A0 != 0 || vx.A1 != 0)
        return true;
    if(vy.A0 != 0 || vy.A1 != 0)
        return true;
    if(vz.A0 != 0 || vz.A1 != 0)
        return true;

    if(wx.A0 != 0 || wx.A1 != 0)
        return true;
    if(wy.A0 != 0 || wy.A1 != 0)
        return true;
    if(wz.A0 != 0 || wz.A1 != 0)
        return true;

    return false;
}
