#ifndef JSONSERIALIZER_H
#define JSONSERIALIZER_H

#include "json/value.h"
#include "Model/plan.h"
#include "Model/disk.h"
#include "Model/cone.h"
#include "Model/elbow.h"
#include "Model/cuboid.h"
#include "Model/lattice.h"
#include "Model/setup.h"

class JsonSerializer
{
public:
    JsonSerializer();
    static Json::Value PlanToJsonValue(std::shared_ptr<Plan>& plan);
    static std::shared_ptr<Plan> PlanFromJsonValue(Json::Value& jsonValue);


    static Json::Value DiskToJsonValue(std::shared_ptr<Disk>& disk);
    static std::shared_ptr<Disk> DiskFromJsonValue(Json::Value& jsonValue);

    static Json::Value ConeToJsonValue(std::shared_ptr<Cone>& cone);
    static std::shared_ptr<Cone> ConeFromJsonValue(Json::Value& jsonValue);

    static Json::Value ElbowToJsonValue(std::shared_ptr<Elbow>& elbow);
    static std::shared_ptr<Elbow> ElbowFromJsonValue(Json::Value& jsonValue);

    static Json::Value CuboidToJsonValue(std::shared_ptr<Cuboid>& cuboid);
    static std::shared_ptr<Cuboid> CuboidFromJsonValue(Json::Value& jsonValue);

    static Json::Value LatticeToJsonValue(std::shared_ptr<Lattice>& lattice);
    static std::shared_ptr<Lattice> LatticeFromJsonValue(Json::Value& jsonValue);

    static Json::Value SetupToJsonValue(std::shared_ptr<Setup>& lattice);
    static std::shared_ptr<Setup> SetupFromJsonValue(Json::Value& jsonValue, std::vector< std::shared_ptr<Lattice> > *lattices, std::shared_ptr<LinkedCells> linkedCells);

private:
    static Json::Value SolidToJsonValue(std::shared_ptr<Solid>& solid);
    static void SolidFromJsonValue(std::shared_ptr<Solid>& solid, Json::Value& jsonValue);
    static Json::Value VelocityToJsonValue(Velocity& solid);
    static Velocity VelocityFromJsonValue(Json::Value& jsonValue);
};

#endif // JSONSERIALIZER_H
