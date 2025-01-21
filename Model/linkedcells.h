#ifndef LINKEDCELLS_H
#define LINKEDCELLS_H

#include <vector>

#include "plan.h"
#include "disk.h"
#include "cone.h"
#include "elbow.h"
#include "cuboid.h"
#include "lattice.h"


class LinkedCells
{
public:
    LinkedCells();

    void Compute(std::vector< std::shared_ptr<Plan> >& plans,
                 std::vector< std::shared_ptr<Disk> >& disks,
                 std::vector< std::shared_ptr<Cone> >& cones,
                 std::vector< std::shared_ptr<Elbow> >& elbows,
                 std::vector< std::shared_ptr<Cuboid> >& cuboids,
                 std::vector< std::shared_ptr<Lattice> >& lattices, double time);
    void Export(FILE *ft);

private:
    void initValue();
    void computeZoneForPlan(std::vector< std::shared_ptr<Plan> >& plans, double time);
    void computeZoneForDisk(std::vector< std::shared_ptr<Disk> >& disks, double time);
    void computeZoneForCone( std::vector< std::shared_ptr<Cone> >& cones, double time);
    void computeZoneForElbow(std::vector< std::shared_ptr<Elbow> >& elbows, double time);
    void computeZoneForCuboid( std::vector< std::shared_ptr<Cuboid> >& cuboids, double time);

    double computeRmax(std::vector< std::shared_ptr<Lattice> >& lattices);

    double xmin, ymin, zmin;
    double xmax, ymax, zmax;
    double ax, ay, az;
    int nx, ny, nz;
};

#endif // LINKEDCELLS_H
