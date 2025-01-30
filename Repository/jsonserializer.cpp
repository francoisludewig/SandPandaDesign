#include "jsonserializer.h"

JsonSerializer::JsonSerializer() {}

Json::Value JsonSerializer::VelocityToJsonValue(Velocity& velocity) {
    Json::Value jsonV;
    jsonV["A0"] = velocity.A0;
    jsonV["A1"] = velocity.A1;
    jsonV["w"] = velocity.w;
    jsonV["p"] = velocity.p;
    return jsonV;
}

Velocity JsonSerializer::VelocityFromJsonValue(Json::Value& jsonValue) {
    Velocity v;
    v.A0 = jsonValue["A0"].asDouble();
    v.A1 = jsonValue["A1"].asDouble();
    v.w = jsonValue["w"].asDouble();
    v.p = jsonValue["p"].asDouble();
    return v;
}

Json::Value JsonSerializer::SolidToJsonValue(std::shared_ptr<Solid>& solid) {
    Json::Value jsonSolid;
    jsonSolid["x"] = solid->x;
    jsonSolid["y"] = solid->y;
    jsonSolid["z"] = solid->z;
    solid->computeQuaternion();
    jsonSolid["q0"] = solid->q0;
    jsonSolid["q1"] = solid->q1;
    jsonSolid["q2"] = solid->q2;
    jsonSolid["q3"] = solid->q3;
    jsonSolid["vx"] = VelocityToJsonValue(solid->vx);
    jsonSolid["vy"] = VelocityToJsonValue(solid->vy);
    jsonSolid["vz"] = VelocityToJsonValue(solid->vz);
    jsonSolid["wx"] = VelocityToJsonValue(solid->wx);
    jsonSolid["wy"] = VelocityToJsonValue(solid->wy);
    jsonSolid["wz"] = VelocityToJsonValue(solid->wz);
    return jsonSolid;
}

void JsonSerializer::SolidFromJsonValue(std::shared_ptr<Solid>& solid, Json::Value& jsonValue) {
    solid->x = jsonValue["x"].asDouble();
    solid->y = jsonValue["y"].asDouble();
    solid->z = jsonValue["z"].asDouble();
    solid->q0 = jsonValue["q0"].asDouble();
    solid->q1 = jsonValue["q1"].asDouble();
    solid->q2 = jsonValue["q2"].asDouble();
    solid->q3 = jsonValue["q3"].asDouble();
    solid->computeBaseFromQuaternion();
    solid->vx = VelocityFromJsonValue(jsonValue["vx"]);
    solid->vy = VelocityFromJsonValue(jsonValue["vy"]);
    solid->vz = VelocityFromJsonValue(jsonValue["vz"]);
    solid->wx = VelocityFromJsonValue(jsonValue["wx"]);
    solid->wy = VelocityFromJsonValue(jsonValue["wy"]);
    solid->wz = VelocityFromJsonValue(jsonValue["wz"]);
}

Json::Value JsonSerializer::PlanToJsonValue(std::shared_ptr<Plan>& plan) {
    auto asSolid = std::dynamic_pointer_cast<Solid>(plan);
    Json::Value jsonPlan = SolidToJsonValue(asSolid);
    jsonPlan["dt"] = plan->dt;
    jsonPlan["ds"] = plan->ds;
    jsonPlan["inAndOut"] = plan->inAndOut;
    return jsonPlan;
}

std::shared_ptr<Plan> JsonSerializer::PlanFromJsonValue(Json::Value& jsonValue) {
    auto plan = std::make_shared<Plan>();
    auto asSolid = std::dynamic_pointer_cast<Solid>(plan);
    SolidFromJsonValue(asSolid, jsonValue);
    plan->dt = jsonValue["dt"].asDouble();
    plan->ds = jsonValue["ds"].asDouble();
    plan->inAndOut = jsonValue["inAndOut"].asInt();
    return plan;
}

Json::Value JsonSerializer::DiskToJsonValue(std::shared_ptr<Disk>& disk) {
    auto asSolid = std::dynamic_pointer_cast<Solid>(disk);
    Json::Value jsonDisk = SolidToJsonValue(asSolid);
    jsonDisk["r"] = disk->r;
    jsonDisk["inAndOut"] = disk->inAndOut;
    return jsonDisk;
}

std::shared_ptr<Disk> JsonSerializer::DiskFromJsonValue(Json::Value& jsonValue) {
    auto disk = std::make_shared<Disk>();
    auto asSolid = std::dynamic_pointer_cast<Solid>(disk);
    SolidFromJsonValue(asSolid, jsonValue);
    disk->r = jsonValue["r"].asDouble();
    disk->inAndOut = jsonValue["inAndOut"].asInt();
    return disk;
}


Json::Value JsonSerializer::ConeToJsonValue(std::shared_ptr<Cone>& cone) {
    auto asSolid = std::dynamic_pointer_cast<Solid>(cone);
    Json::Value jsonCone = SolidToJsonValue(asSolid);
    jsonCone["r0"] = cone->r0;
    jsonCone["r1"] = cone->r1;
    jsonCone["h"] = cone->h;
    jsonCone["inAndOut"] = cone->inAndOut;
    if(cone->top != nullptr)
        jsonCone["top"] = DiskToJsonValue(cone->top);
    if(cone->bottom != nullptr)
        jsonCone["bottom"] = DiskToJsonValue(cone->bottom);

    return jsonCone;
}

std::shared_ptr<Cone> JsonSerializer::ConeFromJsonValue(Json::Value& jsonValue) {
    auto cone = std::make_shared<Cone>();
    auto asSolid = std::dynamic_pointer_cast<Solid>(cone);
    SolidFromJsonValue(asSolid, jsonValue);
    cone->r0 = jsonValue["r0"].asDouble();
    cone->r1= jsonValue["r1"].asDouble();
    cone->h = jsonValue["h"].asDouble();
    cone->dr = cone->r1 - cone->r0;
    cone->inAndOut = jsonValue["inAndOut"].asInt();

    if(jsonValue.isMember("top")) {
        cone->top = DiskFromJsonValue(jsonValue["top"]);
    }
    if(jsonValue.isMember("bottom")) {
        cone->bottom = DiskFromJsonValue(jsonValue["bottom"]);
    }
    return cone;
}
