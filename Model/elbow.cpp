#include "elbow.h"

#include <QOpenGLFunctions>
#include <GL/GLU.h>

#include "cone.h"

#include<iostream>

#define N1 15
#define N2 15

Elbow::Elbow() {
    xi = 0.0;
    yi = -0.25;
    zi = 0.0;
    xf = 0.0;
    yf = 0.0;
    zf = 0.25;
    cx = 0.0;
    cy = 0.0;
    cz = 1.0;
    radius = 0.1;
    base();
}

void Elbow::ReadFromFile(FILE *ft)
{
    fscanf_s(ft,"%lf\t%lf\t%lf\n",&xi,&yi,&zi);
    fscanf_s(ft,"%lf\t%lf\t%lf\n",&xf,&yf,&zf);
    fscanf_s(ft,"%lf\t%lf\t%lf\n",&xr,&yr,&zr);
    fscanf_s(ft,"%lf\t%lf\t%lf\n",&nx,&ny,&nz);
    fscanf_s(ft,"%lf\t%lf\t%lf\n",&tx,&ty,&tz);
    fscanf_s(ft,"%lf\t%lf\t%lf\n",&sx,&sy,&sz);
    vx.ReadFromFile(ft);
    vy.ReadFromFile(ft);
    vz.ReadFromFile(ft);
    wx.ReadFromFile(ft);
    wy.ReadFromFile(ft);
    wz.ReadFromFile(ft);
    fscanf_s(ft,"%lf\t%lf\t%lf\n",&orx,&ory,&orz);
    fscanf_s(ft,"%lf\t%lf\t%lf\n",&Rc,&alpha,&radius);
}



void Elbow::moveat(double t, double h){
    Vx = vx.valueat(t);
    Vy = vy.valueat(t);
    Vz = vz.valueat(t);

    Wx = wx.valueat(t)*h;
    Wy = wy.valueat(t)*h;
    Wz = wz.valueat(t)*h;
    xi += Vx*h;
    yi += Vy*h;
    zi += Vz*h;
    xf += Vx*h;
    yf += Vy*h;
    zf += Vz*h;

    double W = sqrt(Wx*Wx+Wy*Wy+Wz*Wz);
    double Ca = cos(W),Sa = sin(W);
    if(W != 0){
        Wx = Wx/W;
        Wy = Wy/W;
        Wz = Wz/W;

        //      | wx^2+Ca*(1-wx^2)       wx*wy*(1-Ca)-wz*Sa     wx*wz*(1-Ca)+wy*Sa |
        //[R] = | wx*wy*(1-Ca)+wz*Sa     wy^2+Ca*(1-wy^2)       wy*wz*(1-Ca)-wx*Sa |
        //      | wx*wz*(1-Ca)-wy*Sa     wy*wz*(1-Ca)+wx*Sa     wz^2+Ca*(1-wz^2)   |

        Rot[0][0] = Wx*Wx+Ca*(1-Wx*Wx) ;
        Rot[0][1] = Wx*Wy*(1-Ca)-Wz*Sa;
        Rot[0][2] = Wx*Wz*(1-Ca)+Wy*Sa;

        Rot[1][0] = Wx*Wy*(1-Ca)+Wz*Sa;
        Rot[1][1] = Wy*Wy+Ca*(1-Wy*Wy);
        Rot[1][2] = Wy*Wz*(1-Ca)-Wx*Sa;

        Rot[2][0] = Wx*Wz*(1-Ca)-Wy*Sa;
        Rot[2][1] = Wy*Wz*(1-Ca)+Wx*Sa;
        Rot[2][2] = Wz*Wz+Ca*(1-Wz*Wz);
    }
    else{
        Rot[0][0] = 1;
        Rot[0][1] = 0;
        Rot[0][2] = 0;

        Rot[1][0] = 0;
        Rot[1][1] = 1;
        Rot[1][2] = 0;

        Rot[2][0] = 0;
        Rot[2][1] = 0;
        Rot[2][2] = 1;
    }
    double lx,ly,lz;

    lx = (xi-orx);
    ly = (yi-ory);
    lz = (zi-orz);

    xi = (Rot[0][0]*lx + Rot[0][1]*ly + Rot[0][2]*lz) + orx;
    yi = (Rot[1][0]*lx + Rot[1][1]*ly + Rot[1][2]*lz) + ory;
    zi = (Rot[2][0]*lx + Rot[2][1]*ly + Rot[2][2]*lz) + orz;

    lx = (xf-orx);
    ly = (yf-ory);
    lz = (zf-orz);

    xf = (Rot[0][0]*lx + Rot[0][1]*ly + Rot[0][2]*lz) + orx;
    yf = (Rot[1][0]*lx + Rot[1][1]*ly + Rot[1][2]*lz) + ory;
    zf = (Rot[2][0]*lx + Rot[2][1]*ly + Rot[2][2]*lz) + orz;

    lx = cx;
    ly = cy;
    lz = cz;
    cx = (Rot[0][0]*lx + Rot[0][1]*ly + Rot[0][2]*lz);
    cy = (Rot[1][0]*lx + Rot[1][1]*ly + Rot[1][2]*lz);
    cz = (Rot[2][0]*lx + Rot[2][1]*ly + Rot[2][2]*lz);
    base();
}


void Elbow::startAnime() {
    std::cout << "startAnime => Save Solid State" << std::endl;
    isAnimated = true;
    xi0 = xi;
    yi0 = yi;
    zi0 = zi;

    xf0 = xf;
    yf0 = yf;
    zf0 = zf;

    cx0 = cx;
    cy0 = cy;
    cz0 = cz;
}

void Elbow::stopAnime(){
    std::cout << "stopAnime => Reset Solid" << std::endl;
    isAnimated = false;
    xi = xi0;
    yi = yi0;
    zi = zi0;
    xf = xf0;
    yf = yf0;
    zf = zf0;
    cx = cx0;
    cy = cy0;
    cz = cz0;
    base();
}


void Elbow::Draw(bool isLineContainer)
{
    double nrx,nry,nrz;
    double tr_x,tr_y,tr_z;
    double r,A;

    double xc[N1],yc[N1],zc[N1];
    double nxc[N1],nyc[N1],nzc[N1];
    double txc[N1],tyc[N1],tzc[N1];
    double sxc,syc,szc;

    // Memorisation des données du coude
    nrx = nx;
    nry = ny;
    nrz = nz;
    tr_x = tx;
    tr_y = ty;
    tr_z = tz;
    r = radius;
    A = alpha;

    for(int j = 0 ; j <= N1 ; j++){
        xc[j] = xr + Rc * (nrx * sin(j*A/N1) + tr_x * cos(j*A/N1));
        yc[j] = yr + Rc * (nry * sin(j*A/N1) + tr_y * cos(j*A/N1));
        zc[j] = zr + Rc * (nrz * sin(j*A/N1) + tr_z * cos(j*A/N1));
        nxc[j] = (nrx * sin(j*A/N1) + tr_x * cos(j*A/N1));
        nyc[j] = (nry * sin(j*A/N1) + tr_y * cos(j*A/N1));
        nzc[j] = (nrz * sin(j*A/N1) + tr_z * cos(j*A/N1));
        sxc = (nrx * cos(j*A/N1) - tr_x * sin(j*A/N1));
        syc = (nry * cos(j*A/N1) - tr_y * sin(j*A/N1));
        szc = (nrz * cos(j*A/N1) - tr_z * sin(j*A/N1));
        txc[j] = nyc[j]*szc - nzc[j]*syc;
        tyc[j] = nzc[j]*sxc - nxc[j]*szc;
        tzc[j] = nxc[j]*syc - nyc[j]*sxc;
    }

    // Dessin du coude
    double a = 2*3.141592/N2;

    glColor3f(0.5, 0.5, 1);

    for(int j = 0 ; j < N1 ; j++){
        for(int k = 0 ; k < N2 ; k++){
            if(isLineContainer)
                glBegin(GL_LINE_LOOP);
            else
                glBegin(GL_POLYGON);
            glNormal3f(-(nyc[j] * cos(a*k) + tyc[j] * sin(a*k)),
                       -(nzc[j] * cos(a*k) + tzc[j] * sin(a*k)),
                       (nxc[j] * cos(a*k) + txc[j] * sin(a*k)));
            glVertex3f(yc[j] + r * nyc[j] * cos(a*k) + r * tyc[j] * sin(a*k),
                       zc[j] + r * nzc[j] * cos(a*k) + r * tzc[j] * sin(a*k),
                       -(xc[j] + r * nxc[j] * cos(a*k) + r * txc[j] * sin(a*k)));

            glNormal3f(-(nyc[j] * cos(a*(k+1)) + tyc[j] * sin(a*(k+1))),
                       -(nzc[j] * cos(a*(k+1)) + tzc[j] * sin(a*(k+1))),
                       (nxc[j] * cos(a*(k+1)) + txc[j] * sin(a*(k+1))));
            glVertex3f(yc[j] + r * nyc[j] * cos(a*(k+1)) + r * tyc[j] * sin(a*(k+1)),
                       zc[j] + r * nzc[j] * cos(a*(k+1)) + r * tzc[j] * sin(a*(k+1)),
                       -(xc[j] + r * nxc[j] * cos(a*(k+1)) + r * txc[j] * sin(a*(k+1))));

            glNormal3f(-(nyc[(j+1)] * cos(a*(k+1)) + tyc[(j+1)] * sin(a*(k+1))),
                       -(nzc[(j+1)] * cos(a*(k+1)) + tzc[(j+1)] * sin(a*(k+1))),
                       (nxc[(j+1)] * cos(a*(k+1)) + txc[(j+1)] * sin(a*(k+1))));
            glVertex3f(yc[(j+1)] + r * nyc[(j+1)] * cos(a*(k+1)) + r * tyc[(j+1)] * sin(a*(k+1)),
                       zc[(j+1)] + r * nzc[(j+1)] * cos(a*(k+1)) + r * tzc[(j+1)] * sin(a*(k+1)),
                       -(xc[(j+1)] + r * nxc[(j+1)] * cos(a*(k+1)) + r * txc[(j+1)] * sin(a*(k+1))));

            glNormal3f(-(nyc[(j+1)] * cos(a*k) + tyc[(j+1)] * sin(a*k)),
                       -(nzc[(j+1)] * cos(a*k) + tzc[(j+1)] * sin(a*k)),
                       (nxc[(j+1)] * cos(a*k) + txc[(j+1)] * sin(a*k)));
            glVertex3f(yc[(j+1)] + r * nyc[(j+1)] * cos(a*k) + r * tyc[(j+1)] * sin(a*k),
                       zc[(j+1)] + r * nzc[(j+1)] * cos(a*k) + r * tzc[(j+1)] * sin(a*k),
                       -(xc[(j+1)] + r * nxc[(j+1)] * cos(a*k) + r * txc[(j+1)] * sin(a*k)));
            glEnd();
        }
    }
    glColor3f(0, 0, 1);
    // Dessin du coude
    for(int j = 0 ; j < N1 ; j++){
        for(int k = 0 ; k < N2 ; k++){
            if(isLineContainer)
                glBegin(GL_LINE_LOOP);
            else
                glBegin(GL_POLYGON);
            glNormal3f((nyc[j] * cos(a*k) + tyc[j] * sin(a*k)),
                       (nzc[j] * cos(a*k) + tzc[j] * sin(a*k)),
                       -(nxc[j] * cos(a*k) + txc[j] * sin(a*k)));
            glVertex3f(yc[j] + (r*1.001) * nyc[j] * cos(a*k) + (r*1.001) * tyc[j] * sin(a*k),
                       zc[j] + (r*1.001) * nzc[j] * cos(a*k) + (r*1.001) * tzc[j] * sin(a*k),
                       -(xc[j] + (r*1.001) * nxc[j] * cos(a*k) + (r*1.001) * txc[j] * sin(a*k)));

            glNormal3f((nyc[j] * cos(a*(k+1)) + tyc[j] * sin(a*(k+1))),
                       (nzc[j] * cos(a*(k+1)) + tzc[j] * sin(a*(k+1))),
                       -(nxc[j] * cos(a*(k+1)) + txc[j] * sin(a*(k+1))));
            glVertex3f(yc[j] + (r*1.001) * nyc[j] * cos(a*(k+1)) + (r*1.001) * tyc[j] * sin(a*(k+1)),
                       zc[j] + (r*1.001) * nzc[j] * cos(a*(k+1)) + (r*1.001) * tzc[j] * sin(a*(k+1)),
                       -(xc[j] + (r*1.001) * nxc[j] * cos(a*(k+1)) + (r*1.001) * txc[j] * sin(a*(k+1))));

            glNormal3f((nyc[(j+1)] * cos(a*(k+1)) + tyc[(j+1)] * sin(a*(k+1))),
                       (nzc[(j+1)] * cos(a*(k+1)) + tzc[(j+1)] * sin(a*(k+1))),
                       -(nxc[(j+1)] * cos(a*(k+1)) + txc[(j+1)] * sin(a*(k+1))));
            glVertex3f(yc[(j+1)] + (r*1.001) * nyc[(j+1)] * cos(a*(k+1)) + (r*1.001) * tyc[(j+1)] * sin(a*(k+1)),
                       zc[(j+1)] + (r*1.001) * nzc[(j+1)] * cos(a*(k+1)) + (r*1.001) * tzc[(j+1)] * sin(a*(k+1)),
                       -(xc[(j+1)] + (r*1.001) * nxc[(j+1)] * cos(a*(k+1)) + (r*1.001) * txc[(j+1)] * sin(a*(k+1))));

            glNormal3f((nyc[(j+1)] * cos(a*k) + tyc[(j+1)] * sin(a*k)),
                       (nzc[(j+1)] * cos(a*k) + tzc[(j+1)] * sin(a*k)),
                       -(nxc[(j+1)] * cos(a*k) + txc[(j+1)] * sin(a*k)));
            glVertex3f(yc[(j+1)] + (r*1.001) * nyc[(j+1)] * cos(a*k) + (r*1.001) * tyc[(j+1)] * sin(a*k),
                       zc[(j+1)] + (r*1.001) * nzc[(j+1)] * cos(a*k) + (r*1.001) * tzc[(j+1)] * sin(a*k),
                       -(xc[(j+1)] + (r*1.001) * nxc[(j+1)] * cos(a*k) + (r*1.001) * txc[(j+1)] * sin(a*k)));
            glEnd();
        }
    }
}

double Elbow::ComputeScale() const
{
    double zoom0 = -1000;
    int N = 50;
    double dalpha = alpha/N;
    for(int i = 0 ; i < N ; i++){
        Cone c(radius, radius, dalpha*(Rc+radius), 0);
        c.x = Rc*cos(i*dalpha)*tx+Rc*sin(i*dalpha)*nx+xr;
        c.y = Rc*cos(i*dalpha)*ty+Rc*sin(i*dalpha)*ny+yr;
        c.z = Rc*cos(i*dalpha)*tz+Rc*sin(i*dalpha)*nz+zr;
        c.nx = sin(i*dalpha)*tx-cos(i*dalpha)*nx;
        c.ny = sin(i*dalpha)*ty-cos(i*dalpha)*ny;
        c.nz = sin(i*dalpha)*tz-cos(i*dalpha)*nz;
        c.base();
        if(zoom0 < c.ComputeScale())
            zoom0 = c.ComputeScale();
    }
    return zoom0;
}

void Elbow::base()
{
    double norme = sqrt(cx*cx+cy*cy+cz*cz);
    cx = cx/norme;
    cy = cy/norme;
    cz = cz/norme;
    double lx = xf-xi;
    double ly = yf-yi;
    double lz = zf-zi;
    double l = sqrt(lx*lx+ly*ly+lz*lz);
    double theta = acos((lx*cx+ly*cy+lz*cz)/l);
    alpha = 2*theta;
    if(alpha > pow(10,-3) && fabs(3.141592-alpha) > pow(10,-3))
        Rc = fabs(sin(3.141592/2.-theta)/sin(alpha)*l);
    else
        Rc = l/2;

    double cpx,cpy,cpz;
    double c2 = (cx*lx+cy*ly+cz*lz)/l;
    double b = 1./(sqrt(1+c2*c2));
    cpx = -b*(cx*lx+cy*ly+cz*lz)*cx+b*lx;
    cpy = -b*(cx*lx+cy*ly+cz*lz)*cy+b*ly;
    cpz = -b*(cx*lx+cy*ly+cz*lz)*cz+b*lz;
    norme = sqrt(cpx*cpx+cpy*cpy+cpz*cpz);
    cpx = cpx/norme;
    cpy = cpy/norme;
    cpz = cpz/norme;

    xr = xi - Rc*cpx;
    yr = yi - Rc*cpy;
    zr = zi - Rc*cpz;

    double d = sqrt((xr-xf)*(xr-xf)+(yr-yf)*(yr-yf)+(zr-zf)*(zr-zf));
    if(fabs(d-Rc) > pow(10,-5)){
        cpx = -cpx;
        cpy = -cpy;
        cpz = -cpz;
        xr = xi - Rc*cpx;
        yr = yi - Rc*cpy;
        zr = zi - Rc*cpz;
    }

    // Définition de la base
    nx = cx;
    ny = cy;
    nz = cz;
    tx = cpx;
    ty = cpy;
    tz = cpz;
    sx = ny*tz-nz*ty;
    sy = tx*nz-tz*nx;
    sz = nx*ty-ny*tx;
}



bool Elbow::NonNullVelocity(){
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

void Elbow::Zone(double time) {
    double h,Nh,dalpha;
    double xe,ye,ze;
    xmax = -10000;
    ymax = -10000;
    zmax = -10000;
    xmin = 10000;
    ymin = 10000;
    zmin = 10000;

    h = 0.0001;
    if(this->NonNullVelocity())
        Nh = (int)(time/h);
    else
        Nh = 1;

    this->startAnime();
    for(int i = 0 ; i < Nh ; i++){
        this->moveat(i*h, h);
        dalpha = 0;
        xe = Rc*cos(dalpha)*tx+Rc*sin(dalpha)*nx+xr;
        ye = Rc*cos(dalpha)*ty+Rc*sin(dalpha)*ny+yr;
        ze = Rc*cos(dalpha)*tz+Rc*sin(dalpha)*nz+zr;

        xe += radius;
        ye += radius;
        ze += radius;
        if(xmax < xe)xmax = xe;
        if(ymax < ye)ymax = ye;
        if(zmax < ze)zmax = ze;
        if(xmin > xe)xmin = xe;
        if(ymin > ye)ymin = ye;
        if(zmin > ze)zmin = ze;
        xe -= 2*radius;
        ye -= 2*radius;
        ze -= 2*radius;
        if(xmax < xe)xmax = xe;
        if(ymax < ye)ymax = ye;
        if(zmax < ze)zmax = ze;
        if(xmin > xe)xmin = xe;
        if(ymin > ye)ymin = ye;
        if(zmin > ze)zmin = ze;

        dalpha = alpha/2;
        xe = Rc*cos(dalpha)*tx+Rc*sin(dalpha)*nx+xr;
        ye = Rc*cos(dalpha)*ty+Rc*sin(dalpha)*ny+yr;
        ze = Rc*cos(dalpha)*tz+Rc*sin(dalpha)*nz+zr;

        xe += radius;
        ye += radius;
        ze += radius;
        if(xmax < xe)xmax = xe;
        if(ymax < ye)ymax = ye;
        if(zmax < ze)zmax = ze;
        if(xmin > xe)xmin = xe;
        if(ymin > ye)ymin = ye;
        if(zmin > ze)zmin = ze;
        xe -= 2*radius;
        ye -= 2*radius;
        ze -= 2*radius;
        if(xmax < xe)xmax = xe;
        if(ymax < ye)ymax = ye;
        if(zmax < ze)zmax = ze;
        if(xmin > xe)xmin = xe;
        if(ymin > ye)ymin = ye;
        if(zmin > ze)zmin = ze;

        dalpha = alpha;
        xe = Rc*cos(dalpha)*tx+Rc*sin(dalpha)*nx+xr;
        ye = Rc*cos(dalpha)*ty+Rc*sin(dalpha)*ny+yr;
        ze = Rc*cos(dalpha)*tz+Rc*sin(dalpha)*nz+zr;

        xe += radius;
        ye += radius;
        ze += radius;
        if(xmax < xe)xmax = xe;
        if(ymax < ye)ymax = ye;
        if(zmax < ze)zmax = ze;
        if(xmin > xe)xmin = xe;
        if(ymin > ye)ymin = ye;
        if(zmin > ze)zmin = ze;
        xe -= 2*radius;
        ye -= 2*radius;
        ze -= 2*radius;
        if(xmax < xe)xmax = xe;
        if(ymax < ye)ymax = ye;
        if(zmax < ze)zmax = ze;
        if(xmin > xe)xmin = xe;
        if(ymin > ye)ymin = ye;
        if(zmin > ze)zmin = ze;
    }
    this->stopAnime();
}



void Elbow::Export(FILE *ft) {
    this->base();
    fprintf(ft,"%lf\t%lf\t%lf\n",xi,yi,zi);
    fprintf(ft,"%lf\t%lf\t%lf\n",xf,yf,zf);
    fprintf(ft,"%lf\t%lf\t%lf\n",xr,yr,zr);
    fprintf(ft,"%lf\t%lf\t%lf\n",nx,ny,nz);
    fprintf(ft,"%lf\t%lf\t%lf\n",tx,ty,tz);
    fprintf(ft,"%lf\t%lf\t%lf\n",sx,sy,sz);
    vx.Export(ft);
    vy.Export(ft);
    vz.Export(ft);
    wx.Export(ft);
    wy.Export(ft);
    wz.Export(ft);
    fprintf(ft,"%lf\t%lf\t%lf\n",orx,ory,orz);
    fprintf(ft,"%lf\t%lf\t%lf\n",Rc,alpha,radius);
}
