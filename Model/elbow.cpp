#include "elbow.h"

#include <QOpenGLFunctions>
#include <GL/GLU.h>

#include "cone.h"

#define N1 15
#define N2 15

Elbow::Elbow() {
    radius = 0.1;
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
