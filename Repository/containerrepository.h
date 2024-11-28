#ifndef CONTAINERREPOSITORY_H
#define CONTAINERREPOSITORY_H

#include <string>
#include<vector>
#include<memory>

#include "Model/plan.h"
#include "Model/disk.h"
#include "Model/cone.h"
#include "Model/elbow.h"
#include "Model/box.h"

class ContainerRepository
{
public:
    static ContainerRepository& getInstance();
    void Draw(bool isLineContainer);
    void load(std::string directory);
    std::shared_ptr<Plan> AddPlan();
    std::shared_ptr<Disk> AddDisk();
    std::shared_ptr<Cone> AddCone();
    std::shared_ptr<Elbow> AddElbow();
    std::shared_ptr<Box> AddBox();

    void RemovePlan(std::shared_ptr<Plan> plan);
    void RemoveDisk(std::shared_ptr<Disk> disk);
    void RemoveCone(std::shared_ptr<Cone> cone);
    void RemoveElbow(std::shared_ptr<Elbow> elbow);
    void RemoveBox(std::shared_ptr<Box> box);
    double ComputeZoom();
private:
    ContainerRepository(); // Prevent construction
    ContainerRepository(const ContainerRepository&) = default; // Prevent construction by copying
    ContainerRepository& operator=(const ContainerRepository&) = default; // Prevent assignment
    ~ContainerRepository() = default; // Prevent unwanted destruction

    std::vector<std::shared_ptr<Plan> > plans {};
    std::vector<std::shared_ptr<Disk> > disks {};
    std::vector<std::shared_ptr<Cone> > cones {};
    std::vector<std::shared_ptr<Elbow> > elbows {};
    std::vector<std::shared_ptr<Box> > boxes {};
};

#endif // CONTAINERREPOSITORY_H
