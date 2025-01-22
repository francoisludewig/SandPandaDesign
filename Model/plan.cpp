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

void Plan::Zone(double time) {
    double h,Nh;
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
        xe = x-dt/2*tx-ds/2*sx;
        ye = y-dt/2*ty-ds/2*sy;
        ze = z-dt/2*tz-ds/2*sz;
        if(xmax < xe)xmax = xe;
        if(ymax < ye)ymax = ye;
        if(zmax < ze)zmax = ze;
        if(xmin > xe)xmin = xe;
        if(ymin > ye)ymin = ye;
        if(zmin > ze)zmin = ze;

        xe = x+dt/2*tx-ds/2*sx;
        ye = y+dt/2*ty-ds/2*sy;
        ze = z+dt/2*tz-ds/2*sz;
        if(xmax < xe)xmax = xe;
        if(ymax < ye)ymax = ye;
        if(zmax < ze)zmax = ze;
        if(xmin > xe)xmin = xe;
        if(ymin > ye)ymin = ye;
        if(zmin > ze)zmin = ze;

        xe = x-dt/2*tx+ds/2*sx;
        ye = y-dt/2*ty+ds/2*sy;
        ze = z-dt/2*tz+ds/2*sz;
        if(xmax < xe)xmax = xe;
        if(ymax < ye)ymax = ye;
        if(zmax < ze)zmax = ze;
        if(xmin > xe)xmin = xe;
        if(ymin > ye)ymin = ye;
        if(zmin > ze)zmin = ze;

        xe = x+dt/2*tx+ds/2*sx;
        ye = y+dt/2*ty+ds/2*sy;
        ze = z+dt/2*tz+ds/2*sz;
        if(xmax < xe)xmax = xe;
        if(ymax < ye)ymax = ye;
        if(zmax < ze)zmax = ze;
        if(xmin > xe)xmin = xe;
        if(ymin > ye)ymin = ye;
        if(zmin > ze)zmin = ze;
    }
    this->stopAnime();
}


void Plan::Export(FILE *ft) {
    this->base();
    ExportWithoutBaseComputing(ft);
}


void Plan::ExportWithoutBaseComputing(FILE *ft) {
    // Position
    fprintf(ft,"%lf\t%lf\t%lf\n",x,y,z);

    computeQuaternion();
    fprintf(ft,"%lf\t%lf\t%lf\t%lf\n",q0, q1, q2, q3);

    // Velocity
    vx.Export(ft);
    vy.Export(ft);
    vz.Export(ft);
    wx.Export(ft);
    wy.Export(ft);
    wz.Export(ft);
    fprintf(ft,"%lf\t%lf\t%lf\n",orx,ory,orz);

    // Dimension
    fprintf(ft,"%lf\t%lf\t%lf\n%d\t%d\n",sqrt(dt*dt+ds*ds)/1000.,dt,ds,ped,inAndOut);

    // Force & Torque
    fprintf(ft,"%lf\t%d\n",0.0,0);	// Mass, gravity
    fprintf(ft,"%lf\t%lf\t%lf\n",0.0,0.0,0.0); // Fx, Fy, Fz
    fprintf(ft,"%lf\t%lf\t%lf\n",0.0,0.0,0.0); // Mx, My, Mz
}
