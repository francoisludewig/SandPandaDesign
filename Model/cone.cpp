#include "cone.h"

#include <QOpenGLFunctions>
#include <GL/GLU.h>

int Cone::next_id = 0;

Cone::Cone():Solid() {
    id = (Cone::next_id++);
    r0 = 0.25;
    r1 = 0.5;
    h = 0.75;
    dr = 0.25;
    top = nullptr;
    bottom = nullptr;
    inAndOut = 0;
    nx = 0;
    ny = 0;
    nz = 1;
    base();
}

Cone::Cone(double r0, double r1, double h, int inAndOut):r0(r0), r1(r1), h(h), dr(r1-r0),inAndOut(inAndOut) {}

void Cone::ReadFromFile(FILE *ft)
{
    int b;
    Solid::ReadFromFile(ft);
    fscanf_s(ft,"%lf\t%lf\t%lf\t%lf",&h,&r0,&r1,&dr);
    fscanf_s(ft,"%d\t%d\t%d",&inAndOut,&b,&Ngb);
}

void Cone::Draw(bool isLineContainer)
{
    double PI = 3.1415926;
    double nlx,nly,nlz;
    nlx = ny;
    nly = nz;
    nlz = -nx;
    double theta;
    double cost = nlz;
    double sint = sqrt(nlx*nlx+nly*nly);
    /*if(isAnimated) {
        updateBottom();
        updateTop();
    }*/
    if(sint >= 0)
        theta = acos(cost);
    else
        theta = 2*PI-acos(cost);
    //NSLog(@"theta = %e",theta);
    glPushMatrix();
    glTranslatef(y-h/2*nlx,z-h/2*nly,-x-h/2*nlz);
    glPushMatrix();
    glRotatef(-theta/2/PI*360,nly,-nlx,0);
    GLUquadric* quad = gluNewQuadric();
    glColor3f(0.5, 0.5, 1);

    if(isLineContainer)
        gluQuadricDrawStyle(quad, GLU_LINE);

    gluQuadricOrientation(quad, GLU_INSIDE);
    gluCylinder(quad, r0, r1, h, 50, 5);

    if(inAndOut == 0)
        glColor3f(0, 0, 1);
    else
        glColor3f(0.5, 0.5, 1);
    if(isLineContainer)
        gluQuadricDrawStyle(quad, GLU_LINE);

    gluQuadricOrientation(quad, GLU_OUTSIDE);
    gluCylinder(quad, r0*1.001, r1+(r0*0.001), h, 50, 5);

    glPopMatrix();
    glPopMatrix();

    if(top != nullptr) {
        updateTop();
        top->Draw(isLineContainer);
    }
    if(bottom != nullptr) {
        updateBottom();
        bottom->Draw(isLineContainer);
    }
}

double Cone::ComputeScale() const
{
    double px,py,pz,zoom;
    px = x+nx*h/2+r1*tx;
    py = y+ny*h/2+r1*ty;
    pz = z+nz*h/2+r1*tz;
    zoom = sqrt(px*px+py*py+pz*pz);
    px = x+nx*h/2+r1*sx;
    py = y+ny*h/2+r1*sy;
    pz = z+nz*h/2+r1*sz;
    if(zoom <  sqrt(px*px+py*py+pz*pz))
        zoom =  sqrt(px*px+py*py+pz*pz);

    px = x-nx*h/2+r0*sx;
    py = y-ny*h/2+r0*sy;
    pz = z-nz*h/2+r0*sz;
    if(zoom <  sqrt(px*px+py*py+pz*pz))
        zoom =  sqrt(px*px+py*py+pz*pz);
    px = x-nx*h/2+r0*tx;
    py = y-ny*h/2+r0*ty;
    pz = z-nz*h/2+r0*tz;
    if(zoom <  sqrt(px*px+py*py+pz*pz))
        zoom =  sqrt(px*px+py*py+pz*pz);
    return(zoom);
}

void Cone::setTop(bool activate)
{
    if(activate) {
        Disk disk{};
        this->top = std::make_shared<Disk>(disk);
        updateTop();
    } else {
        this->top.reset();
    }
}

void Cone::setBottom(bool activate)
{
    if(activate) {
        Disk disk{};
        this->bottom = std::make_shared<Disk>(disk);
        updateBottom();
    }else {
        this->bottom.reset();
    }
}

void Cone::updateTop()
{
    if(top != nullptr) {
        top->x = x+nx*h/2;
        top->y = y+ny*h/2;
        top->z = z+nz*h/2;
        top->nx = -nx;
        top->ny = -ny;
        top->nz = -nz;
        top->base();
        top->r = r1;
        top->inAndOut = inAndOut;
    }
}

void Cone::updateBottom()
{
    if(bottom != nullptr) {
        bottom->x = x-nx*h/2;
        bottom->y = y-ny*h/2;
        bottom->z = z-nz*h/2;
        bottom->nx = nx;
        bottom->ny = ny;
        bottom->nz = nz;
        bottom->base();
        bottom->r = r0;
        bottom->inAndOut = inAndOut;
    }
}


void Cone::Zone(double time) {
    double dh,Nh;
    double xe,ye,ze;
    xmax = -10000;
    ymax = -10000;
    zmax = -10000;
    xmin = 10000;
    ymin = 10000;
    zmin = 10000;

    dh = 0.0001;
    if(this->NonNullVelocity())
        Nh = (int)(time/dh);
    else
        Nh = 1;

    this->startAnime();
    for(int i = 0 ; i < Nh ; i++){
        this->moveat(i*dh, dh);
        for(int j = 0 ; j < 20 ; j++){
            xe = x-h/2*nx + r0*cos(0.3141592*j)*tx + r0*sin(0.3141592*j)*sx;
            ye = y-h/2*ny + r0*cos(0.3141592*j)*ty + r0*sin(0.3141592*j)*sy;
            ze = z-h/2*nz + r0*cos(0.3141592*j)*tz + r0*sin(0.3141592*j)*sz;
            if(xmax < xe)xmax = xe;
            if(ymax < ye)ymax = ye;
            if(zmax < ze)zmax = ze;
            if(xmin > xe)xmin = xe;
            if(ymin > ye)ymin = ye;
            if(zmin > ze)zmin = ze;
        }

        for(int j = 0 ; j < 20 ; j++){
            xe = x+h/2*nx + r1*cos(0.3141592*j)*tx + r1*sin(0.3141592*j)*sx;
            ye = y+h/2*ny + r1*cos(0.3141592*j)*ty + r1*sin(0.3141592*j)*sy;
            ze = z+h/2*nz + r1*cos(0.3141592*j)*tz + r1*sin(0.3141592*j)*sz;
            if(xmax < xe)xmax = xe;
            if(ymax < ye)ymax = ye;
            if(zmax < ze)zmax = ze;
            if(xmin > xe)xmin = xe;
            if(ymin > ye)ymin = ye;
            if(zmin > ze)zmin = ze;

        }
    }
    this->stopAnime();
}

void Cone::ExportLimits(FILE *ft) {
    if(top != nullptr) top->Export(ft);
    if(bottom != nullptr) bottom->Export(ft);
}

void Cone::Export(FILE *ft) {
    this->base();
    this->updateBottom();
    this->updateTop();
    fprintf(ft,"%lf\t%lf\t%lf\n",x,y,z);
    computeQuaternion();
    fprintf(ft,"%lf\t%lf\t%lf\t%lf\n",q0, q1, q2, q3);
    vx.Export(ft);
    vy.Export(ft);
    vz.Export(ft);
    wx.Export(ft);
    wy.Export(ft);
    wz.Export(ft);
    fprintf(ft,"%lf\t%lf\t%lf\n",orx,ory,orz);
    //fprintf(ft,"%d\n",0);
    fprintf(ft,"%lf\t%lf\t%lf\t%lf\n",h,r0,r1,fabs(r1-r0));
    fprintf(ft,"%d\t-9\t-9\n",inAndOut);
    fprintf(ft,"%lf\t%d\n",0.0,0);	// Mass, gravity
    fprintf(ft,"%lf\t%lf\t%lf\n",0.0,0.0,0.0); // Fx, Fy, Fz
    fprintf(ft,"%lf\t%lf\t%lf\n",0.0,0.0,0.0); // Mx, My, Mz
}
