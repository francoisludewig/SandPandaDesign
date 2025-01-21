#ifndef LATTICE_H
#define LATTICE_H

#include "cuboid.h"
#include "cone.h"
#include "granule.h"

#include <vector>

class Lattice
{
public:
    Lattice();

    void LinkedToBoxe(std::shared_ptr<Cuboid> &cuboid);
    void UpDateFromBoxe();
    void LinkedToCone(std::shared_ptr<Cone> & co);
    void UpDateFromCone();
    void Unlink();
    void Radius();
    void Position(int fluid = 0);
    void Velocity();
    double ComputeScale();
    void draw(int color);
    double massMin();

    double RmaxSphScale();
    void Export(FILE *ft, int sp);

    int N;
    double r0,r1,rho,rmax;
    bool dist,rdm,solid;
    std::vector<Granule> gr;
    double xmin,ymin,zmin,xmax,ymax,zmax;
    double V,W;
    bool boxes,cyd;
    double nx,ny,nz;
    double tx,ty,tz;
    double sx,sy,sz;
    double x0,y0,z0;
    std::shared_ptr<Cuboid> bte;
    std::shared_ptr<Cone> cyde;
    int Nbte,Nco;
};

#endif // LATTICE_H
