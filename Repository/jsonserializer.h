#ifndef JSONSERIALIZER_H
#define JSONSERIALIZER_H

#include "json/value.h"
#include "Model/plan.h"
#include "Model/disk.h"
#include "Model/cone.h"

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

private:
    static Json::Value SolidToJsonValue(std::shared_ptr<Solid>& solid);
    static void SolidFromJsonValue(std::shared_ptr<Solid>& solid, Json::Value& jsonValue);
    static Json::Value VelocityToJsonValue(Velocity& solid);
    static Velocity VelocityFromJsonValue(Json::Value& jsonValue);
};

#endif // JSONSERIALIZER_H
