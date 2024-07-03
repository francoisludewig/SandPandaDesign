#include "disk.h"

#include <QOpenGLFunctions>
#include <GL/GLU.h>

Disk::Disk() : Solid() {
    r = 0.5;
    periodic = -9;
    inAndOut = 0;
    nx = 0;
    ny = 0;
    nz = 1;
    base();
}

void Disk::ReadFromFile(FILE *ft)
{
    double a;
    Solid::ReadFromFile(ft);
    fscanf_s(ft,"%lf\t%lf",&a,&r);
    fscanf_s(ft,"%d\t%d",&periodic,&Ngb);
}

void Disk::Draw(bool isLineContainer)
{
    double dn = r/1000;
    double theta,dtheta = 6.28318531/50.;



    glColor3f(0.5, 0.5, 1);

    glPushMatrix();
    glTranslated(y, z, -x);
    if(isLineContainer)
        glBegin(GL_LINE_LOOP);
    else
        glBegin(GL_POLYGON);
    glNormal3f(ny, nz, -nx);
    for(int i = 0 ; i <= 50 ; i++){
        theta = i*dtheta;
        glVertex3f(r*cos(theta)*ty+r*sin(theta)*sy,r*cos(theta)*tz+r*sin(theta)*sz,-(r*cos(theta)*tx+r*sin(theta)*sx));
    }
    glEnd();
    glPopMatrix();

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
    for(int i = 0 ; i <= 50 ; i++){
        theta = i*dtheta;
        glVertex3f(-ny*dn+r*cos(theta)*ty+r*sin(theta)*sy,-nz*dn+r*cos(theta)*tz+r*sin(theta)*sz,-(-nx*dn+r*cos(theta)*tx+r*sin(theta)*sx));

    }
    glEnd();
    glPopMatrix();
}

double Disk::ComputeScale() const
{
    double theta,dtheta = 6.28318531/50.;
    double px,py,pz,zoom;
    theta = 0;
    px = x+r*cos(theta)*tx+r*sin(theta)*sx;
    py = y+r*cos(theta)*ty+r*sin(theta)*sy;
    pz = z+r*cos(theta)*tz+r*sin(theta)*sz;
    zoom = sqrt(px*px+py*py+pz*pz);
    for(int i = 1 ; i < 50 ; i++){
        theta = i*dtheta;
        px = x+r*cos(theta)*tx+r*sin(theta)*sx;
        py = y+r*cos(theta)*ty+r*sin(theta)*sy;
        pz = z+r*cos(theta)*tz+r*sin(theta)*sz;
        if(zoom < sqrt(px*px+py*py+pz*pz))
            zoom = sqrt(px*px+py*py+pz*pz);
    }
    return zoom;
}
