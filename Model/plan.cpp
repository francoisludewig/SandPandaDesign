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

void Plan::computeQuaternion() {
    /*float T = nx + ty + sz;
    float s;
    if (T > 0) {
        float s = sqrt(T + 1) * 2.f;
        q1 = (tz - sy) / s;
        q2 = (sx - nz) / s;
        q3 = (ny - tx) / s;
        q0 = 0.25f * s;
    } else if ( nx > ty && nx > sz) {
        s = sqrt(1 + nx - ty - sz) * 2;
        q1 = 0.25f * s;
        q2 = (ny + tx) / s;
        q3 = (sx + nz) / s;
        q0 = (tz - sy) / s;
    } else if (ty > sz) {
        s = sqrt(1 + ty - nx - sz) * 2;
        q1 = (ny + tx) / s;
        q2 = 0.25f * s;
        q3 = (tz + sy) / s;
        q0 = (sx - nz) / s;
    } else {
        s = sqrt(1 + sz - nx - ty) * 2;
        q1 = (sx + nz) / s;
        q2 = (tz + sy) / s;
        q3 = 0.25f * s;
        q0 = (ny - tx) / s;
    }*/

    /*
    double r = 0.5*sqrt(nx*nx+ty*ty+sz*sz);
    if(r < pow(10,-14)) {
        q0 = 0;
        if(nx != 1) {
            q1 = 0;
            q2 = nz;
            q3 = -ny;
        } else {
            q1 = -ty;
            q2 = 0;
            q3 = tx;
        }

    }
    else {
        q0 = r;
        q1 = 1/(4*r)*(tz-sy);
        q2 = 1/(4*r)*(sx-nz);
        q3 = 1/(4*r)*(ny-tx);
    }*/

    //double q0,q1,q2,q3;
    q1 = sqrt(-(ty+sz-nx-1)/4.);
    if(-(ty+sz-nx-1) < 0)
        q1 = 0.;

    q2 = sqrt(-(-ty+sz+nx-1)/4.);
    if(-(-ty+sz+nx-1) < 0)
        q2 = 0.;

    q3 = sqrt(-(ty-sz+nx-1)/4.);
    if(-(ty-sz+nx-1) < 0)
        q3 = 0.;

    q0 = sqrt(1.-q1*q1-q2*q2-q3*q3);
    if(q0 != q0)
        q0 = 0.;
    double maxq = q0;
    if(q1 > maxq)maxq = q1;
    if(q2 > maxq)maxq = q2;
    if(q3 > maxq)maxq = q3;
    maxq *= pow(10,-14);

    if(fabs(q0) < maxq)q0 = 0.;
    if(fabs(q1) < maxq)q1 = 0.;
    if(fabs(q2) < maxq)q2 = 0.;
    if(fabs(q3) < maxq)q3 = 0.;

    if(tz-sy < 0) q1*=-1;
    if(sx-nz < 0) q2*=-1;
    if(ny-tx < 0) q3*=-1;
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
