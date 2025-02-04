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

    static Json::Value DesignToJsonValue();
    static void DesignFromJsonValue(std::string jsonAsString);



    static Json::Value PlansToJsonValue(std::vector< std::shared_ptr<Plan> >& plans);
    static void PlansFromJsonValue(Json::Value& jsonValue, std::vector< std::shared_ptr<Plan> >& plans);

    static Json::Value DisksToJsonValue(std::vector< std::shared_ptr<Disk> >& disks);
    static void DisksFromJsonValue(Json::Value& jsonValue, std::vector< std::shared_ptr<Disk> >& disks);

    static Json::Value ConesToJsonValue(std::vector< std::shared_ptr<Cone> >& cones);
    static void ConesFromJsonValue(Json::Value& jsonValue, std::vector< std::shared_ptr<Cone> >& cones);

    static Json::Value ElbowsToJsonValue(std::vector< std::shared_ptr<Elbow> >& elbows);
    static void ElbowsFromJsonValue(Json::Value& jsonValue, std::vector< std::shared_ptr<Elbow> >& elbows);

    static Json::Value CuboidsToJsonValue(std::vector< std::shared_ptr<Cuboid> >& cuboids);
    static void CuboidsFromJsonValue(Json::Value& jsonValue, std::vector< std::shared_ptr<Cuboid> >& cuboids);

    static Json::Value LatticesToJsonValue(std::vector< std::shared_ptr< Lattice> >&  lattices);
    static void  LatticesFromJsonValue(Json::Value& jsonValue, std::vector< std::shared_ptr< Lattice> >& lattices, std::vector< std::shared_ptr<Cuboid>> & cuboids, std::vector< std::shared_ptr<Cone>> & cones);

private:
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
    static std::shared_ptr<Lattice> LatticeFromJsonValue(Json::Value& jsonValue, std::vector< std::shared_ptr<Cuboid>> & cuboids, std::vector< std::shared_ptr<Cone>> & cones);

    static Json::Value SetupToJsonValue(std::shared_ptr<Setup>& lattice);
    static void SetupFromJsonValue(Json::Value& jsonValue, std::shared_ptr<Setup> setup);

    static Json::Value SolidToJsonValue(std::shared_ptr<Solid>& solid);
    static void SolidFromJsonValue(std::shared_ptr<Solid>& solid, Json::Value& jsonValue);
    static Json::Value VelocityToJsonValue(Velocity& solid);
    static Velocity VelocityFromJsonValue(Json::Value& jsonValue);
};

#endif // JSONSERIALIZER_H
