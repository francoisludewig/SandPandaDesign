#ifndef SPHEREREPOSITORY_H
#define SPHEREREPOSITORY_H

#include "Model/sphere.h"
#include <vector>
#include <string>

class SphereRepository
{
public:
    static SphereRepository& getInstance();
    void Draw();
    void load(std::string directory);
private:
    SphereRepository(); // Prevent construction
    SphereRepository(const SphereRepository&) = default; // Prevent construction by copying
    SphereRepository& operator=(const SphereRepository&) = default; // Prevent assignment
    ~SphereRepository() = default; // Prevent unwanted destruction

    std::vector<Sphere> spheres {};
};

#endif // SPHEREREPOSITORY_H
