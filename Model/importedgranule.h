#ifndef IMPORTEDGRANULE_H
#define IMPORTEDGRANULE_H

#include <cstdio>
#include <vector>

struct ContactData {
    int numNeighbour;
    int type;
    int status;
    double x, y, z;
};

struct BodyContactData {
    int numNeighbour;
    int type;
    int selfNumFromBody;
    int numFromBody;
    double x, y, z;
};

class ImportedGranule
{
public:
    ImportedGranule();

    void readStartStopFromFile(FILE *ft);
    void writeStartStopToFile(FILE *ft) const;
    void draw() const;

    double x, y, z;
    double q0, q1, q2, q3;
    double vx, vy, vz;
    double wx, wy, wz;
    double r, m, I;
    int sp;
    int NhollowBall;

    int Nneighbour2;
    std::vector<ContactData> contacts;
};

class ImportedBody
{
public:
    ImportedBody();

    void readStartStopFromFile(FILE *ft);
    void writeStartStopToFile(FILE *ft) const;
    void draw() const;

    int sp;
    int NhollowBall;
    double x, y, z;
    double q0, q1, q2, q3;
    double vx, vy, vz;
    double wx, wy, wz;

    int Nneighbour2;
    std::vector<BodyContactData> bodyContacts;
};

class ImportedHollowBall
{
public:
    ImportedHollowBall();

    void readFromFile(FILE *ft);
    void writeToFile(FILE *ft) const;

    double x, y, z;
    double q0, q1, q2, q3;
    double vx, vy, vz;
    double wx, wy, wz;
    int lockVx, lockVy, lockVz;
    int lockWx, lockWy, lockWz;
    double r, mass, Inertia;
};

#endif // IMPORTEDGRANULE_H
