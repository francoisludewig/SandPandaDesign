#include "plan.h"

#include <QOpenGLFunctions>
#include <GL/GLU.h>

Plan::Plan() : Solid() {
    dt = 0.5;
    ds = 0.5;
    ped = -9;
    inAndOut = 0;
    nx = 0;
    ny = 0;
    nz = 1;
    base();
}

void Plan::ReadFromFile(FILE *ft)
{
    double a;
    Solid::ReadFromFile(ft);
    fscanf_s(ft,"%lf\t%lf\t%lf\n%d\t%d\t%d\n",&a,&dt,&ds,&ped,&Ngb,&inAndOut);
}

void Plan::Draw(bool isLineContainer) const
{
    printf("Plan::Draw = (%f, %f, %f)\n\tn (%f, %f, %f)\n\tt (%f, %f, %f)\n\ts (%f, %f, %f)\n", x, y, z, nx, ny, nz, tx, ty, tz, sx, sy, sz);
    double nl;
    nl = sqrt(dt*dt+ds*ds)/1000.;

    if(inAndOut == 0){
        glColor3f(0, 0, 1);
    }
    else{
        glColor3f(0.5, 0.5, 1);
    }
    glPushMatrix();
    glTranslated(y, z, -x);
    if(isLineContainer)
        glBegin(GL_LINE_LOOP);
    else
        glBegin(GL_POLYGON);


    glNormal3f(-ny, -nz, nx);
    printf("\t(%f, %f, %f)\n",-ny*nl-dt/2*ty-ds/2*sy, -nz*nl-dt/2*tz-ds/2*sz,-(-nx*nl-dt/2*tx-ds/2*sx));
    printf("\t(%f, %f, %f)\n",-ny*nl-dt/2*ty+ds/2*sy, -nz*nl-dt/2*tz+ds/2*sz,-(-nx*nl-dt/2*tx+ds/2*sx));
    printf("\t(%f, %f, %f)\n",-ny*nl+dt/2*ty+ds/2*sy, -nz*nl+dt/2*tz+ds/2*sz,-(-nx*nl+dt/2*tx+ds/2*sx));
    printf("\t(%f, %f, %f)\n",-ny*nl+dt/2*ty-ds/2*sy, -nz*nl+dt/2*tz-ds/2*sz,-(-nx*nl+dt/2*tx-ds/2*sx));

    glVertex3f(-ny*nl-dt/2*ty-ds/2*sy, -nz*nl-dt/2*tz-ds/2*sz,-(-nx*nl-dt/2*tx-ds/2*sx));
    glVertex3f(-ny*nl-dt/2*ty+ds/2*sy, -nz*nl-dt/2*tz+ds/2*sz,-(-nx*nl-dt/2*tx+ds/2*sx));
    glVertex3f(-ny*nl+dt/2*ty+ds/2*sy, -nz*nl+dt/2*tz+ds/2*sz,-(-nx*nl+dt/2*tx+ds/2*sx));
    glVertex3f(-ny*nl+dt/2*ty-ds/2*sy, -nz*nl+dt/2*tz-ds/2*sz,-(-nx*nl+dt/2*tx-ds/2*sx));
    glEnd();
    glPopMatrix();

    glColor3f(0.5, 0.5, 1);

    glPushMatrix();
    glTranslated(y, z, -x);
    if(isLineContainer)
        glBegin(GL_LINE_LOOP);
    else
        glBegin(GL_POLYGON);
    glNormal3f(ny, nz, -nx);
    glVertex3f(-dt/2*ty-ds/2*sy, -dt/2*tz-ds/2*sz,-(-dt/2*tx-ds/2*sx));
    glVertex3f(-dt/2*ty+ds/2*sy, -dt/2*tz+ds/2*sz,-(-dt/2*tx+ds/2*sx));
    glVertex3f(+dt/2*ty+ds/2*sy, +dt/2*tz+ds/2*sz,-(+dt/2*tx+ds/2*sx));
    glVertex3f(+dt/2*ty-ds/2*sy, +dt/2*tz-ds/2*sz,-(+dt/2*tx-ds/2*sx));
    glEnd();
    glPopMatrix();
}

double Plan::ComputeScale() const
{
    double px,py,pz,zoom;
    px = x-dt/2*tx-ds/2*sx;
    py = y-dt/2*ty-ds/2*sy;
    pz = z-dt/2*tz-ds/2*sz;
    zoom = sqrt(px*px+py*py+pz*pz);
    px = x-dt/2*tx+ds/2*sx;
    py = y-dt/2*ty+ds/2*sy;
    pz = z-dt/2*tz+ds/2*sz;
    if(zoom <  sqrt(px*px+py*py+pz*pz))
        zoom =  sqrt(px*px+py*py+pz*pz);
    px = x+dt/2*tx+ds/2*sx;
    py = y+dt/2*ty+ds/2*sy;
    pz = z+dt/2*tz+ds/2*sz;
    if(zoom <  sqrt(px*px+py*py+pz*pz))
        zoom =  sqrt(px*px+py*py+pz*pz);
    px = x+dt/2*tx-ds/2*sx;
    py = y+dt/2*ty-ds/2*sy;
    pz = z+dt/2*tz-ds/2*sz;
    if(zoom <  sqrt(px*px+py*py+pz*pz))
        zoom =  sqrt(px*px+py*py+pz*pz);
    return zoom;
}
