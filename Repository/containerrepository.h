#ifndef CONTAINERREPOSITORY_H
#define CONTAINERREPOSITORY_H

#include <string>
#include<vector>
#include<memory>
#define _CRT_SECURE_NO_DEPRECATE
#include "Model/plan.h"
#include "Model/disk.h"
#include "Model/cone.h"
#include "Model/elbow.h"
#include "Model/cuboid.h"
#include "Model/lattice.h"
#include "Model/setup.h"
#include "Model/linkedcells.h"

class ContainerRepository
{
public:
    static ContainerRepository& getInstance();
    void Draw(bool isLineContainer);
    void Move(double t, double h);
    void StartAnimation();
    void StopAnimation();
    void load(std::string directory);
    std::shared_ptr<Plan> AddPlan();
    std::shared_ptr<Disk> AddDisk();
    std::shared_ptr<Cone> AddCone();
    std::shared_ptr<Elbow> AddElbow();
    std::shared_ptr<Cuboid> AddCuboid();
    std::shared_ptr<Lattice> AddLattice();

    void RemovePlan(std::shared_ptr<Plan> plan);
    void RemoveDisk(std::shared_ptr<Disk> disk);
    void RemoveCone(std::shared_ptr<Cone> cone);
    void RemoveElbow(std::shared_ptr<Elbow> elbow);
    void RemoveCuboid(std::shared_ptr<Cuboid> cuboid);
    void RemoveLattice(std::shared_ptr<Lattice> lattice);


    std::shared_ptr<Cone> GetCone(int index);
    std::shared_ptr<Cuboid> GetCuboid(int index);
    std::shared_ptr<Setup> GetSetup();
    int GetIndexOfCone(std::shared_ptr<Cone> cone);
    int GetIndexOfCuboid(std::shared_ptr<Cuboid> cuboid);

    void Export(std::string directory);

    double ComputeZoom();
private:
    ContainerRepository(); // Prevent construction
    ContainerRepository(const ContainerRepository&) = default; // Prevent construction by copying
    ContainerRepository& operator=(const ContainerRepository&) = default; // Prevent assignment
    ~ContainerRepository() = default; // Prevent unwanted destruction

    void exportContainer(std::string &directory);
    void exportGrain(std::string &directory);

    std::vector< std::shared_ptr<Plan> > plans {};
    std::vector< std::shared_ptr<Disk> > disks {};
    std::vector< std::shared_ptr<Cone> > cones {};
    std::vector< std::shared_ptr<Elbow> > elbows {};
    std::vector< std::shared_ptr<Cuboid> > cuboids {};
    std::vector< std::shared_ptr<Lattice> > lattices {};
    std::shared_ptr<Setup> setup;
    std::shared_ptr<LinkedCells> linkedCells;
};

#endif // CONTAINERREPOSITORY_H
