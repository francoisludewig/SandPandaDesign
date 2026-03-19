#include "importedgranule.h"

#include <QOpenGLFunctions>
#include <GL/glu.h>

// ---- ImportedGranule ----

ImportedGranule::ImportedGranule()
    : x(0), y(0), z(0),
      q0(1), q1(0), q2(0), q3(0),
      vx(0), vy(0), vz(0),
      wx(0), wy(0), wz(0),
      r(0.01), m(0), I(0),
      sp(0), NhollowBall(-9),
      Nneighbour2(0) {}

void ImportedGranule::readStartStopFromFile(FILE *ft) {
    fscanf(ft, "%lf\t%lf\t%lf\n", &x, &y, &z);
    fscanf(ft, "%lf\t%lf\t%lf\t%lf\n", &q0, &q1, &q2, &q3);
    fscanf(ft, "%lf\t%lf\t%lf\n", &vx, &vy, &vz);
    fscanf(ft, "%lf\t%lf\t%lf\n", &wx, &wy, &wz);
    fscanf(ft, "%lf\t%lf\t%lf\t%d\t%d\n", &r, &m, &I, &sp, &NhollowBall);
    fscanf(ft, "%d\n", &Nneighbour2);
    contacts.resize(Nneighbour2);
    for (int i = 0; i < Nneighbour2; i++) {
        fscanf(ft, "%d\t%d\t%d\t%lf\t%lf\t%lf\n",
               &contacts[i].numNeighbour, &contacts[i].type,
               &contacts[i].status,
               &contacts[i].x, &contacts[i].y, &contacts[i].z);
    }
}

void ImportedGranule::writeStartStopToFile(FILE *ft) const {
    fprintf(ft, "%.16e\t%.16e\t%.16e\n", x, y, z);
    fprintf(ft, "%.16e\t%.16e\t%.16e\t%.16e\n", q0, q1, q2, q3);
    fprintf(ft, "%.16e\t%.16e\t%.16e\n", vx, vy, vz);
    fprintf(ft, "%.16e\t%.16e\t%.16e\n", wx, wy, wz);
    fprintf(ft, "%e\t%e\t%e\t%d\t%d\n", r, m, I, sp, NhollowBall);
    fprintf(ft, "%d\n", Nneighbour2);
    for (int i = 0; i < Nneighbour2; i++) {
        fprintf(ft, "%d\t%d\t%d\t%.16e\t%.16e\t%.16e\n",
                contacts[i].numNeighbour, contacts[i].type,
                contacts[i].status,
                contacts[i].x, contacts[i].y, contacts[i].z);
    }
}

void ImportedGranule::draw() const {
    glColor3f(0.5, 0.5, 0.0);
    glPushMatrix();
    glTranslated(y, z, -x);
    glScaled(r, r, r);
    GLUquadric *glQ = gluNewQuadric();
    gluQuadricOrientation(glQ, GLU_OUTSIDE);
    gluSphere(glQ, 1, 20, 10);
    gluDeleteQuadric(glQ);
    glPopMatrix();
}

// ---- ImportedBody ----

ImportedBody::ImportedBody()
    : sp(0), NhollowBall(-9),
      x(0), y(0), z(0),
      q0(1), q1(0), q2(0), q3(0),
      vx(0), vy(0), vz(0),
      wx(0), wy(0), wz(0),
      Nneighbour2(0) {}

void ImportedBody::readStartStopFromFile(FILE *ft) {
    fscanf(ft, "%d\t%d\t", &sp, &NhollowBall);
    fscanf(ft, "%lf\t%lf\t%lf\t", &x, &y, &z);
    fscanf(ft, "%lf\t%lf\t%lf\t%lf\t", &q0, &q1, &q2, &q3);
    fscanf(ft, "%lf\t%lf\t%lf\t", &vx, &vy, &vz);
    fscanf(ft, "%lf\t%lf\t%lf\n", &wx, &wy, &wz);
    fscanf(ft, "%d\n", &Nneighbour2);
    bodyContacts.resize(Nneighbour2);
    for (int i = 0; i < Nneighbour2; i++) {
        fscanf(ft, "%d\t%d\t%d\t%d\t%lf\t%lf\t%lf\n",
               &bodyContacts[i].numNeighbour, &bodyContacts[i].type,
               &bodyContacts[i].selfNumFromBody, &bodyContacts[i].numFromBody,
               &bodyContacts[i].x, &bodyContacts[i].y, &bodyContacts[i].z);
    }
}

void ImportedBody::writeStartStopToFile(FILE *ft) const {
    fprintf(ft, "%d\t%d\t", sp, NhollowBall);
    fprintf(ft, "%.15f\t%.15f\t%.15f\t", x, y, z);
    fprintf(ft, "%e\t%e\t%e\t%e\t", q0, q1, q2, q3);
    fprintf(ft, "%e\t%e\t%e\t", vx, vy, vz);
    fprintf(ft, "%e\t%e\t%e\n", wx, wy, wz);
    fprintf(ft, "%d\n", Nneighbour2);
    for (int i = 0; i < Nneighbour2; i++) {
        fprintf(ft, "%d\t%d\t%d\t%d\t%e\t%e\t%e\n",
                bodyContacts[i].numNeighbour, bodyContacts[i].type,
                bodyContacts[i].selfNumFromBody, bodyContacts[i].numFromBody,
                bodyContacts[i].x, bodyContacts[i].y, bodyContacts[i].z);
    }
}

void ImportedBody::draw() const {
    // Bodies are composite - draw as a point marker
    glColor3f(0.5, 0.0, 0.5);
    glPushMatrix();
    glTranslated(y, z, -x);
    glScaled(0.005, 0.005, 0.005);
    GLUquadric *glQ = gluNewQuadric();
    gluQuadricOrientation(glQ, GLU_OUTSIDE);
    gluSphere(glQ, 1, 10, 5);
    gluDeleteQuadric(glQ);
    glPopMatrix();
}

// ---- ImportedHollowBall ----

ImportedHollowBall::ImportedHollowBall()
    : x(0), y(0), z(0),
      q0(1), q1(0), q2(0), q3(0),
      vx(0), vy(0), vz(0),
      wx(0), wy(0), wz(0),
      lockVx(0), lockVy(0), lockVz(0),
      lockWx(0), lockWy(0), lockWz(0),
      r(0.1), mass(1), Inertia(1) {}

void ImportedHollowBall::readFromFile(FILE *ft) {
    int b1, b2, b3, b4, b5, b6;
    fscanf(ft, "%lf\t%lf\t%lf\t%lf\t%lf\t%lf\t%lf\t%lf\t%lf\t%lf\t%lf\t%lf\t%lf\t%d\t%d\t%d\t%d\t%d\t%d\t%lf\t%lf\t%lf",
           &x, &y, &z, &q0, &q1, &q2, &q3, &vx, &vy, &vz, &wx, &wy, &wz,
           &b1, &b2, &b3, &b4, &b5, &b6, &r, &mass, &Inertia);
    lockVx = b1; lockVy = b2; lockVz = b3;
    lockWx = b4; lockWy = b5; lockWz = b6;
}

void ImportedHollowBall::writeToFile(FILE *ft) const {
    fprintf(ft, "%e\t%e\t%e\t%e\t%e\t%e\t%e\t%e\t%e\t%e\t%e\t%e\t%e\t%d\t%d\t%d\t%d\t%d\t%d\t%e\t%e\t%e\n",
            x, y, z, q0, q1, q2, q3, vx, vy, vz, wx, wy, wz,
            lockVx, lockVy, lockVz, lockWx, lockWy, lockWz, r, mass, Inertia);
}
