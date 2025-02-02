#include "jsonserializer.h"

#include "containerrepository.h"

#include <json/reader.h>

JsonSerializer::JsonSerializer() {}

Json::Value JsonSerializer::DesignToJsonValue() {
    Json::Value jsonValue;
    jsonValue["plans"] = PlansToJsonValue(ContainerRepository::getInstance().plans);
    jsonValue["disks"] = DisksToJsonValue(ContainerRepository::getInstance().disks);
    jsonValue["elbows"] = ElbowsToJsonValue(ContainerRepository::getInstance().elbows);
    jsonValue["cones"] = ConesToJsonValue(ContainerRepository::getInstance().cones);
    jsonValue["cuboids"] = CuboidsToJsonValue(ContainerRepository::getInstance().cuboids);
    jsonValue["lattices"] = LatticesToJsonValue(ContainerRepository::getInstance().lattices);
    jsonValue["setup"] = SetupToJsonValue(ContainerRepository::getInstance().setup);
    return jsonValue;
}

void JsonSerializer::DesignFromJsonValue(std::string jsonAsString) {
    Json::Value jsonValue;
    Json::Reader reader;
    if (!reader.parse(jsonAsString.c_str(), jsonValue)){
        std::cout  << "Failed to parse"
                  << reader.getFormattedErrorMessages();
    } else {
        if(jsonValue["plans"].isNull())
            PlansFromJsonValue(jsonValue["plans"] , ContainerRepository::getInstance().plans);
        if(!jsonValue["disks"].isNull())
            DisksFromJsonValue(jsonValue["disks"], ContainerRepository::getInstance().disks);
        if(!jsonValue["elbows"].isNull())
            ElbowsFromJsonValue(jsonValue["elbows"], ContainerRepository::getInstance().elbows);
        if(!jsonValue["cones"].isNull())
            ConesFromJsonValue(jsonValue["cones"], ContainerRepository::getInstance().cones);
        if(!jsonValue["cuboids"].isNull())
            CuboidsFromJsonValue(jsonValue["cuboids"], ContainerRepository::getInstance().cuboids);
        if(!jsonValue["lattices"].isNull())
            LatticesFromJsonValue(jsonValue["lattices"], ContainerRepository::getInstance().lattices);
        ContainerRepository::getInstance().setup = SetupFromJsonValue(jsonValue["setup"], &ContainerRepository::getInstance().lattices,  ContainerRepository::getInstance().linkedCells);
    }
}

Json::Value JsonSerializer::PlansToJsonValue(std::vector< std::shared_ptr<Plan> >& plans) {
    Json::Value jsonArray;
    int index = 0;
    for(auto& item : plans) {
        jsonArray[index] = PlanToJsonValue(item);
        index++;
    }
    return jsonArray;
}

void JsonSerializer::PlansFromJsonValue(Json::Value& jsonArray, std::vector< std::shared_ptr<Plan> >& plans) {
    for(auto& jsonValue : jsonArray) {
        plans.push_back(PlanFromJsonValue(jsonValue));
    }
}

Json::Value JsonSerializer::DisksToJsonValue(std::vector< std::shared_ptr<Disk> >& disks) {
    Json::Value jsonArray;
    int index = 0;
    for(auto& item : disks) {
        jsonArray[index] = DiskToJsonValue(item);
        index++;
    }
    return jsonArray;
}

void JsonSerializer::DisksFromJsonValue(Json::Value& jsonArray, std::vector< std::shared_ptr<Disk> >& disks) {
    for(auto& jsonValue : jsonArray) {
        disks.push_back(DiskFromJsonValue(jsonValue));
    }
}

Json::Value JsonSerializer::ConesToJsonValue(std::vector< std::shared_ptr<Cone> >& cones) {
    Json::Value jsonArray;
    int index = 0;
    for(auto& item : cones) {
        jsonArray[index] = ConeToJsonValue(item);
        index++;
    }
    return jsonArray;
}

void JsonSerializer::ConesFromJsonValue(Json::Value& jsonArray, std::vector< std::shared_ptr<Cone> >& cones) {
    for(auto& jsonValue : jsonArray) {
        cones.push_back(ConeFromJsonValue(jsonValue));
    }
}


Json::Value JsonSerializer::ElbowsToJsonValue(std::vector< std::shared_ptr<Elbow> >& elbows) {
    Json::Value jsonArray;
    int index = 0;
    for(auto& item : elbows) {
        jsonArray[index] = ElbowToJsonValue(item);
        index++;
    }
    return jsonArray;
}

void JsonSerializer::ElbowsFromJsonValue(Json::Value& jsonArray, std::vector< std::shared_ptr<Elbow> >& elbows) {
    for(auto& jsonValue : jsonArray) {
        elbows.push_back(ElbowFromJsonValue(jsonValue));
    }
}

Json::Value JsonSerializer::CuboidsToJsonValue(std::vector< std::shared_ptr<Cuboid> >& cuboids) {
    Json::Value jsonArray;
    int index = 0;
    for(auto& item : cuboids) {
        jsonArray[index] = CuboidToJsonValue(item);
        index++;
    }
    return jsonArray;
}

void JsonSerializer::CuboidsFromJsonValue(Json::Value& jsonArray, std::vector< std::shared_ptr<Cuboid> >& cuboids) {
    for(auto& jsonValue : jsonArray) {
        cuboids.push_back(CuboidFromJsonValue(jsonValue));
    }
}

Json::Value JsonSerializer::LatticesToJsonValue(std::vector< std::shared_ptr< Lattice> >&  lattices) {
    Json::Value jsonArray;
    int index = 0;
    for(auto& item : lattices) {
        jsonArray[index] = LatticeToJsonValue(item);
        index++;
    }
    return jsonArray;
}

void  JsonSerializer::LatticesFromJsonValue(Json::Value& jsonArray, std::vector< std::shared_ptr< Lattice> >& lattices) {
    for(auto& jsonValue : jsonArray) {
        lattices.push_back(LatticeFromJsonValue(jsonValue));
    }
}

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


Json::Value JsonSerializer::ElbowToJsonValue(std::shared_ptr<Elbow>& elbow) {
    Json::Value jsonElbow;
    jsonElbow["xi"] = elbow->xi;
    jsonElbow["yi"] = elbow->yi;
    jsonElbow["zi"] = elbow->zi;
    jsonElbow["xf"] = elbow->xf;
    jsonElbow["yf"] = elbow->yf;
    jsonElbow["zf"] = elbow->zf;
    jsonElbow["cx"] = elbow->cx;
    jsonElbow["cy"] = elbow->cy;
    jsonElbow["cz"] = elbow->cz;
    jsonElbow["vx"] = VelocityToJsonValue(elbow->vx);
    jsonElbow["vy"] = VelocityToJsonValue(elbow->vy);
    jsonElbow["vz"] = VelocityToJsonValue(elbow->vz);
    jsonElbow["wx"] = VelocityToJsonValue(elbow->wx);
    jsonElbow["wy"] = VelocityToJsonValue(elbow->wy);
    jsonElbow["wz"] = VelocityToJsonValue(elbow->wz);
    jsonElbow["radius"] = elbow->radius;
    jsonElbow["Rc"] = elbow->Rc;
    jsonElbow["alpha"] = elbow->alpha;
    return jsonElbow;
}

std::shared_ptr<Elbow> JsonSerializer::ElbowFromJsonValue(Json::Value& jsonValue) {
    auto elbow = std::make_shared<Elbow>();

    elbow->xi = jsonValue["xi"].asDouble();
    elbow->yi = jsonValue["yi"].asDouble();
    elbow->zi = jsonValue["zi"].asDouble();
    elbow->xf = jsonValue["xf"].asDouble();
    elbow->yf = jsonValue["yf"].asDouble();
    elbow->zf = jsonValue["zf"].asDouble();
    elbow->cx = jsonValue["cx"].asDouble();
    elbow->cy = jsonValue["cy"].asDouble();
    elbow->cz = jsonValue["cz"].asDouble();

    elbow->vx = VelocityFromJsonValue(jsonValue["vx"]);
    elbow->vy = VelocityFromJsonValue(jsonValue["vy"]);
    elbow->vz = VelocityFromJsonValue(jsonValue["vz"]);
    elbow->wx = VelocityFromJsonValue(jsonValue["wx"]);
    elbow->wy = VelocityFromJsonValue(jsonValue["wy"]);
    elbow->wz = VelocityFromJsonValue(jsonValue["wz"]);

    elbow->radius = jsonValue["radius"].asDouble();
    elbow->Rc = jsonValue["Rc"].asDouble();
    elbow->alpha = jsonValue["alpha"].asDouble();

    elbow->base();

    return elbow;
}

Json::Value JsonSerializer::CuboidToJsonValue(std::shared_ptr<Cuboid>& cuboid) {
    auto asSolid = std::dynamic_pointer_cast<Solid>(cuboid);
    Json::Value jsonCuboid = SolidToJsonValue(asSolid);
    jsonCuboid["Lo"] = cuboid->Lo;
    jsonCuboid["la"] = cuboid->la;
    jsonCuboid["h"] = cuboid->h;
    jsonCuboid["top"] = cuboid->top != nullptr;
    jsonCuboid["bottom"] = cuboid->bottom != nullptr;
    jsonCuboid["inte"] = cuboid->inte;
    jsonCuboid["ped"] = cuboid->ped;
    return jsonCuboid;
}

std::shared_ptr<Cuboid> JsonSerializer::CuboidFromJsonValue(Json::Value& jsonValue) {
    auto cuboid = std::make_shared<Cuboid>();
    auto asSolid = std::dynamic_pointer_cast<Solid>(cuboid);
    cuboid->Lo = jsonValue["Lo"].asDouble();
    cuboid->la = jsonValue["la"].asDouble();
    cuboid->h = jsonValue["h"].asDouble();
    cuboid->setTop(jsonValue["top"].asBool());
    cuboid->setBottom(jsonValue["bottom"].asBool());
    cuboid->inte = jsonValue["inte"].asBool();
    cuboid->ped = jsonValue["ped"].asBool();
    cuboid->updatePlans();
    return cuboid;
}

Json::Value JsonSerializer::LatticeToJsonValue(std::shared_ptr<Lattice>& lattice) {
    Json::Value jsonLattice;
    jsonLattice["xmin"] = lattice->xmin;
    jsonLattice["ymin"] = lattice->ymin;
    jsonLattice["zmin"] = lattice->zmin;
    jsonLattice["xmax"] = lattice->xmax;
    jsonLattice["ymax"] = lattice->ymax;
    jsonLattice["zmax"] = lattice->zmax;
    jsonLattice["r0"] = lattice->r0;
    jsonLattice["r1"] = lattice->r1;
    jsonLattice["rho"] = lattice->rho;
    jsonLattice["rdm"] = lattice->rdm;
    jsonLattice["V"] = lattice->V;
    jsonLattice["W"] = lattice->W;
    jsonLattice["N"] = lattice->N;
    return jsonLattice;
}

std::shared_ptr<Lattice> JsonSerializer::LatticeFromJsonValue(Json::Value& jsonValue) {
    auto lattice = std::make_shared<Lattice>();
    lattice->xmin = jsonValue["xmin"].asDouble();
    lattice->ymin = jsonValue["ymin"].asDouble();
    lattice->zmin = jsonValue["zmin"].asDouble();
    lattice->xmax = jsonValue["xmax"].asDouble();
    lattice->ymax = jsonValue["ymax"].asDouble();
    lattice->zmax = jsonValue["zmax"].asDouble();

    lattice->r0 = jsonValue["r0"].asDouble();
    lattice->r1 = jsonValue["r1"].asDouble();
    lattice->rho = jsonValue["rho"].asDouble();
    lattice->V = jsonValue["V"].asDouble();
    lattice->W = jsonValue["W"].asDouble();
    lattice->N = jsonValue["N"].asInt();
    lattice->rdm = jsonValue["rdm"].asBool();
    lattice->Radius();
    lattice->Position();
    return lattice;
}


Json::Value JsonSerializer::SetupToJsonValue(std::shared_ptr<Setup>& setup) {
    Json::Value jsonSetup;
    jsonSetup["resitutionCoefficient"] = setup->resitutionCoefficient;
    jsonSetup["normalStiffness"] = setup->normalStiffness;
    jsonSetup["isTangentialDynamicModel"] = setup->isTangentialDynamicModel;
    jsonSetup["staticFrictionCoefficient"] = setup->staticFrictionCoefficient;
    jsonSetup["dynamicFrictionCoefficient"] = setup->dynamicFrictionCoefficient;

    jsonSetup["gravityAcceleration"] = setup->gravityAcceleration;
    jsonSetup["gravityX"] = setup->gravityX;
    jsonSetup["gravityY"] = setup->gravityY;
    jsonSetup["gravityZ"] = setup->gravityZ;

    jsonSetup["gWxA0"] = setup->gWxA0;
    jsonSetup["gWxA1"] = setup->gWxA1;
    jsonSetup["gWxP"] = setup->gWxP;
    jsonSetup["gWxW"] = setup->gWxW;
    jsonSetup["gWyA0"] = setup->gWyA0;
    jsonSetup["gWyA1"] = setup->gWyA1;
    jsonSetup["gWyP"] = setup->gWyP;
    jsonSetup["gWyW"] = setup->gWyW;
    jsonSetup["gWzA0"] = setup->gWzA0;
    jsonSetup["gWzA1"] = setup->gWzA1;
    jsonSetup["gWzP"] = setup->gWzP;
    jsonSetup["gWzW"] = setup->gWzW;

    jsonSetup["duration"] = setup->duration;
    jsonSetup["timeStep"] = setup->timeStep;
    jsonSetup["captureTimeStep"] = setup->captureTimeStep;
    jsonSetup["startingTime"] = setup->startingTime;

    jsonSetup["Nsp"] = setup->Nsp;

    return jsonSetup;
}

std::shared_ptr<Setup> JsonSerializer::SetupFromJsonValue(Json::Value& jsonValue, std::vector< std::shared_ptr<Lattice> > *lattices, std::shared_ptr<LinkedCells> linkedCells) {
    auto setup = std::make_shared<Setup>(lattices, linkedCells);
    setup->resitutionCoefficient = jsonValue["resitutionCoefficient"].asDouble();
    setup->normalStiffness = jsonValue["normalStiffness"].asDouble();
    setup->staticFrictionCoefficient = jsonValue["staticFrictionCoefficient"].asDouble();
    setup->dynamicFrictionCoefficient = jsonValue["dynamicFrictionCoefficient"].asDouble();
    setup->isTangentialDynamicModel = jsonValue["isTangentialDynamicModel"].asBool();

    setup->gravityAcceleration = jsonValue["gravityAcceleration"].asDouble();
    setup->gravityX = jsonValue["gravityX"].asDouble();
    setup->gravityY = jsonValue["gravityY"].asDouble();
    setup->gravityZ = jsonValue["gravityZ"].asDouble();

    setup->gWxA0 = jsonValue["gWxA0"].asDouble();
    setup->gWxA1 = jsonValue["gWxA1"].asDouble();
    setup->gWxP = jsonValue["gWxP"].asDouble();
    setup->gWxW = jsonValue["gWxW"].asDouble();
    setup->gWyA0 = jsonValue["gWyA0"].asDouble();
    setup->gWyA1 = jsonValue["gWyA1"].asDouble();
    setup->gWyP = jsonValue["gWyP"].asDouble();
    setup->gWyW = jsonValue["gWyW"].asDouble();
    setup->gWzA0 = jsonValue["gWzA0"].asDouble();
    setup->gWzA1 = jsonValue["gWzA1"].asDouble();
    setup->gWzP = jsonValue["gWzP"].asDouble();
    setup->gWzW = jsonValue["gWzW"].asDouble();

    setup->duration = jsonValue["duration"].asDouble();
    setup->timeStep = jsonValue["timeStep"].asDouble();
    setup->captureTimeStep = jsonValue["captureTimeStep"].asDouble();
    setup->startingTime = jsonValue["startingTime"].asDouble();

    setup->Nsp = jsonValue["Nsp"].asDouble();

    // TODO Link ??
    return setup;
}
