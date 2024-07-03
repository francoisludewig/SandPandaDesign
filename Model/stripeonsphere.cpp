#include "stripeonsphere.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#include <QOpenGLFunctions>
#include<GL/GLU.h>

#include<tuple>

StripeOnSphere::StripeOnSphere(int p):precision(p) {
    computeVertex();
}

void StripeOnSphere::draw(double x, double y, double z, double r, double nx, double ny, double nz,
                          double tx, double ty, double tz, double sx, double sy, double sz) const
{
    double xl,yl,zl;
    glPushMatrix();
    glTranslated(y, z, -x);
    glScaled(r, r, r);        // Scale to the radius

    // Draw sphere
    glColor3f(0.0f, 0.0f, 1.0f);

    GLUquadric *glQ = gluNewQuadric();
    gluQuadricOrientation(glQ, GLU_OUTSIDE);
    gluSphere(glQ, 1, 12, 6);


    // Drawing Stripes
    glColor3f(0.0f, 1.0f, 1.0f);

    for(int i = 0 ; i < vertexA.size() ; i+=4){
        glBegin(GL_POLYGON);
        for(int j = 0 ; j < 4 ; j++){
            //printf("index : %d\n", i+j);
            xl = std::get<0>(vertexA[i+j])*nx + std::get<1>(vertexA[i+j])*tx + std::get<2>(vertexA[i+j])*sx;
            yl = std::get<0>(vertexA[i+j])*ny + std::get<1>(vertexA[i+j])*ty + std::get<2>(vertexA[i+j])*sy;
            zl = std::get<0>(vertexA[i+j])*nz + std::get<1>(vertexA[i+j])*tz + std::get<2>(vertexA[i+j])*sz;
            glNormal3f(yl,zl,-xl);
            glVertex3f(yl,zl,-xl);
        }
        glEnd();
    }

    for(int i = 0 ; i < vertexB.size() ; i+=4){
        glBegin(GL_POLYGON);
        for(int j = 0 ; j < 4 ; j++){
            //printf("index : %d\n", i+j);
            xl = std::get<0>(vertexB[i+j])*nx + std::get<1>(vertexB[i+j])*tx + std::get<2>(vertexB[i+j])*sx;
            yl = std::get<0>(vertexB[i+j])*ny + std::get<1>(vertexB[i+j])*ty + std::get<2>(vertexB[i+j])*sy;
            zl = std::get<0>(vertexB[i+j])*nz + std::get<1>(vertexB[i+j])*tz + std::get<2>(vertexB[i+j])*sz;
            glNormal3f(yl,zl,-xl);
            glVertex3f(yl,zl,-xl);
        }
        glEnd();
    }
    glPopMatrix();
}

void StripeOnSphere::computeVertex(){
    double rl = 1.02;
    double theta;
    double phi;
    double delta = 2.* M_PI/precision;

    for(int i = 0 ; i <= precision ; i++){
        theta = 0;
        phi = i*delta;
        vertexA.push_back(std::make_tuple(rl*sin(phi)*cos(theta), rl*sin(phi)*sin(theta), rl*cos(phi)));

        theta = delta;
        phi = i*delta;
        vertexA.push_back(std::make_tuple(rl*sin(phi)*cos(theta), rl*sin(phi)*sin(theta), rl*cos(phi)));

        theta = delta;
        phi = (i+1)*delta;
        vertexA.push_back(std::make_tuple(rl*sin(phi)*cos(theta), rl*sin(phi)*sin(theta), rl*cos(phi)));

        theta = 0;
        phi = (i+1)*delta;
        vertexA.push_back(std::make_tuple(rl*sin(phi)*cos(theta), rl*sin(phi)*sin(theta), rl*cos(phi)));



        theta = 0;
        phi = i*delta;
        vertexA.push_back(std::make_tuple(rl*sin(phi)*cos(theta), rl*sin(phi)*sin(theta), rl*cos(phi)));

        theta = -delta;
        phi = i*delta;
        vertexA.push_back(std::make_tuple(rl*sin(phi)*cos(theta), rl*sin(phi)*sin(theta), rl*cos(phi)));

        theta = -delta;
        phi = (i+1)*delta;
        vertexA.push_back(std::make_tuple(rl*sin(phi)*cos(theta), rl*sin(phi)*sin(theta), rl*cos(phi)));

        theta = 0;
        phi = (i+1)*delta;
        vertexA.push_back(std::make_tuple(rl*sin(phi)*cos(theta), rl*sin(phi)*sin(theta), rl*cos(phi)));

    }
    for(int i = 0 ; i <= 50 ; i++){
        theta = M_PI/2;
        phi = i*delta;
        vertexB.push_back(std::make_tuple(rl*sin(phi)*cos(theta), rl*sin(phi)*sin(theta), rl*cos(phi)));

        theta = M_PI/2+delta;
        phi = i*delta;
        vertexB.push_back(std::make_tuple(rl*sin(phi)*cos(theta), rl*sin(phi)*sin(theta), rl*cos(phi)));

        theta = M_PI/2+delta;
        phi = (i+1)*delta;
        vertexB.push_back(std::make_tuple(rl*sin(phi)*cos(theta), rl*sin(phi)*sin(theta), rl*cos(phi)));

        theta = M_PI/2;
        phi = (i+1)*delta;
        vertexB.push_back(std::make_tuple(rl*sin(phi)*cos(theta), rl*sin(phi)*sin(theta), rl*cos(phi)));



        theta = M_PI/2;
        phi = i*delta;
        vertexB.push_back(std::make_tuple(rl*sin(phi)*cos(theta), rl*sin(phi)*sin(theta), rl*cos(phi)));

        theta = M_PI/2-delta;
        phi = i*delta;
        vertexB.push_back(std::make_tuple(rl*sin(phi)*cos(theta), rl*sin(phi)*sin(theta), rl*cos(phi)));

        theta = M_PI/2-delta;
        phi = (i+1)*delta;
        vertexB.push_back(std::make_tuple(rl*sin(phi)*cos(theta), rl*sin(phi)*sin(theta), rl*cos(phi)));

        theta = M_PI/2;
        phi = (i+1)*delta;
        vertexB.push_back(std::make_tuple(rl*sin(phi)*cos(theta), rl*sin(phi)*sin(theta), rl*cos(phi)));
    }


    rl = 1.0;
    for(int i = 0 ; i <= precision ; i++){
        for(int j = 1 ; j <= precision ; j++) {
            theta = j*delta;
            phi = i*delta;
            vertex.push_back(std::make_tuple(rl*sin(phi)*cos(theta), rl*sin(phi)*sin(theta), rl*cos(phi)));

            theta = (j+1)*delta;
            phi = i*delta;
            vertex.push_back(std::make_tuple(rl*sin(phi)*cos(theta), rl*sin(phi)*sin(theta), rl*cos(phi)));

            theta = (j+1)*delta;
            phi = (i+1)*delta;
            vertex.push_back(std::make_tuple(rl*sin(phi)*cos(theta), rl*sin(phi)*sin(theta), rl*cos(phi)));

            theta = j*delta;
            phi = (i+1)*delta;
            vertex.push_back(std::make_tuple(rl*sin(phi)*cos(theta), rl*sin(phi)*sin(theta), rl*cos(phi)));

            theta = j*delta;
            phi = i*delta;
            vertex.push_back(std::make_tuple(rl*sin(phi)*cos(theta), rl*sin(phi)*sin(theta), rl*cos(phi)));

            theta = j*delta-delta;
            phi = i*delta;
            vertex.push_back(std::make_tuple(rl*sin(phi)*cos(theta), rl*sin(phi)*sin(theta), rl*cos(phi)));

            theta = j*delta-delta;
            phi = (i+1)*delta;
            vertex.push_back({rl*sin(phi)*cos(theta), rl*sin(phi)*sin(theta), rl*cos(phi)});

            theta = j*delta;
            phi = (i+1)*delta;
            vertex.push_back(std::make_tuple(rl*sin(phi)*cos(theta), rl*sin(phi)*sin(theta), rl*cos(phi)));
        }
    }   
}
