#include "containerrepository.h"

#include <algorithm>
#include <filesystem>

#include "jsonserializer.h"

ContainerRepository::ContainerRepository() {
    linkedCells = std::make_shared<LinkedCells>();
    setup = std::make_shared<Setup>(&lattices, linkedCells);
}

ContainerRepository& ContainerRepository::getInstance()
{
    static ContainerRepository instance{};
    return instance;
}

void ContainerRepository::Export(std::string directory) {
    std::cout << "Export !" << std::endl;
    // Compute LinkedCell
    linkedCells->Compute(plans, disks, cones, elbows, cuboids, lattices, setup->duration);
    setup->Export(directory);
    this->exportGrain(directory);
    this->exportContainer(directory);
}

void ContainerRepository::exportContainer(std::string& directory) {

    //Demo Json Serialization
    auto jsonArray = JsonSerializer::PlansToJsonValue(this->plans);
    plans.clear();
    JsonSerializer::PlansFromJsonValue(jsonArray, this->plans);
    std::cout << "Plan : " << jsonArray.toStyledString() << std::endl;



    //Fin Demo Json Serialization


    char filename[1024];
    // Exportation du fichier container.txt
    sprintf(filename,"%s/container.txt",directory.c_str());
    printf("%s\n",filename);
    FILE *ft = fopen(filename,"w");
    int Npl = plans.size();

    for(auto cuboid : cuboids) {
        Npl += cuboid->planCount();
    }

    int Ndisk = disks.size();

    for(auto cone : cones) {
        Ndisk += cone->diskCount();
    }


    int Ncone = cones.size();
    int Nelbow = elbows.size();
    fprintf(ft,"%d\n",Npl);
    fprintf(ft,"%d\n",Ndisk);
    fprintf(ft,"%d\n",Ncone);
    fprintf(ft,"%d\n",Nelbow);

    for(auto plan : plans) {
        plan->Export(ft);
    }

    int npl = plans.size();

    for(auto cuboid : cuboids) {
        cuboid->Export(ft, npl);
        npl += cuboid->planCount();
    }

    for(auto disk : disks) {
        disk->Export(ft);
    }
    for(auto cone : cones) {
        cone->ExportLimits(ft);
    }
    for(auto cone : cones) {
        cone->Export(ft);
    }
    for(auto elbow : elbows) {
        elbow->Export(ft);
    }
    fflush(ft);
    fclose(ft);
}

void ContainerRepository::exportGrain(std::string &directory) {
    char filename[1024];
    // Exportation du fichier container.txt
    sprintf(filename,"%s/grain.txt",directory.c_str());
    printf("%s\n",filename);
    FILE *ft = fopen(filename,"w");

    setup->Nsp = 0;
    int Ngrain = 0;
    for(auto& lattice : lattices) {
        Ngrain += lattice->N;
    }
    fprintf(ft,"%d\n",Ngrain);


    for(auto& lattice : lattices) {
        lattice->Export(ft, setup->Nsp);
        setup->Nsp++;
    }

    fflush(ft);
    fclose(ft);
}


void ContainerRepository::Draw(bool isLineContainer)
{
    for(auto& plan : plans)
        plan->Draw(isLineContainer);
    for(auto& disk : disks)
        disk->Draw(isLineContainer);
    for(auto& cone : cones)
        cone->Draw(isLineContainer);
    for(auto& elbow : elbows)
        elbow->Draw(isLineContainer);
    for(auto& cuboid : cuboids)
        cuboid->Draw(isLineContainer);
    for(auto& lattice : lattices)
        lattice->draw(0);

    // Draw imported particles (read-only, from Start_stop import)
    for(auto& grain : importedGranules)
        grain.draw();
    for(auto& body : importedBodies)
        body.draw();
}

void ContainerRepository::Move(double t, double h) {
    for(auto& plan : plans)
        plan->moveat(t, h);
    for(auto& disk : disks)
        disk->moveat(t, h);
    for(auto& cone : cones)
        cone->moveat(t, h);
    for(auto elbow : elbows)
        elbow->moveat(t, h);
    for(auto& cuboid : cuboids)
        cuboid->moveat(t, h);
}



void ContainerRepository::StartAnimation() {
    for(auto& plan : plans)
        plan->startAnime();
    for(auto& disk : disks)
        disk->startAnime();
    for(auto& cone : cones)
        cone->startAnime();
    for(auto elbow : elbows)
        elbow->startAnime();
    for(auto& cuboid : cuboids)
        cuboid->startAnime();
}

void ContainerRepository::StopAnimation() {
    for(auto& plan : plans)
        plan->stopAnime();
    for(auto& disk : disks)
        disk->stopAnime();
    for(auto& cone : cones)
        cone->stopAnime();
    for(auto elbow : elbows)
        elbow->stopAnime();
    for(auto& cuboid : cuboids)
        cuboid->stopAnime();
}


void ContainerRepository::load(std::string directory)
{
    int Nplan = 0;
    int Ndisk = 0;
    int Ncone = 0;
    int Nelbow = 0;
    std::FILE *ft = nullptr;
    char filename[2048];
    plans.clear();
    disks.clear();
    cones.clear();
    elbows.clear();

    //sprintf(filename, "C:\\Users\\utilisateur\\Documents\\TestBox\\Out\\grain_%d.txt", N);
    //sprintf(filename, "C:\\Users\\utilisateur\\OneDrive - student.helmo.be\\Bureau\\Dev\\Archives\\LuGaProjects\\Test\\Sphere\\Elbow\\New\\Out\\grain_%d.txt", N);
    //sprintf(filename, "C:\\Users\\utilisateur\\OneDrive - student.helmo.be\\Bureau\\Dev\\Archives\\LuGaProjects\\Test\\Sphere\\Cone\\New\\Out\\grain_%d.txt", N);
    sprintf(filename, "%s\\Out\\container.txt", directory.data());

    printf("filename : %s\n", filename);
    ft = std::fopen(filename,"r");
    if(ft) {
        printf("Load file %s\n", filename);
        fscanf(ft,"%d",&Nplan);
        fscanf(ft,"%d",&Ndisk);
        fscanf(ft,"%d",&Ncone);
        fscanf(ft,"%d",&Nelbow);
        for(int i = 0 ; i < Nplan ; ++i) {
            Plan plan{};
            plan.ReadFromFile(ft);
            plans.push_back(std::make_shared<Plan>(plan));
        }
        for(int i = 0 ; i < Ndisk ; ++i) {
            Disk disk{};
            disk.ReadFromFile(ft);
            disks.push_back(std::make_shared<Disk>(disk));
        }
        for(int i = 0 ; i < Ncone ; ++i) {
            Cone cone{};
            cone.ReadFromFile(ft);
            cones.push_back(std::make_shared<Cone>(cone));
        }
        for(int i = 0 ; i < Nelbow ; ++i) {
            Elbow elbow{};
            elbow.ReadFromFile(ft);
            elbows.push_back(std::make_shared<Elbow>(elbow));
        }


        printf("Plan count : %d\n", Nplan);
        fclose(ft);
    }
}


std::shared_ptr<Plan> ContainerRepository::AddPlan()
{
    Plan plan{};
    auto plan_ptr = std::make_shared<Plan>(plan);
    plans.push_back(plan_ptr);
    return plan_ptr;
}

std::shared_ptr<Disk> ContainerRepository::AddDisk()
{
    Disk disk{};
    auto disk_ptr = std::make_shared<Disk>(disk);
    disks.push_back(disk_ptr);
    return disk_ptr;
}

std::shared_ptr<Cone> ContainerRepository::AddCone()
{
    Cone cone{};
    auto cone_ptr = std::make_shared<Cone>(cone);
    cones.push_back(cone_ptr);
    return cone_ptr;
}


std::shared_ptr<Elbow> ContainerRepository::AddElbow()
{
    Elbow elbow{};
    auto elbow_ptr = std::make_shared<Elbow>(elbow);
    elbows.push_back(elbow_ptr);
    return elbow_ptr;
}

std::shared_ptr<Cuboid> ContainerRepository::AddCuboid()
{
    Cuboid cuboid{};
    auto cuboid_ptr = std::make_shared<Cuboid>(cuboid);
    cuboids.push_back(cuboid_ptr);
    return cuboid_ptr;
}


std::shared_ptr<Lattice> ContainerRepository::AddLattice() {
    Lattice lattice{};
    auto lattice_ptr = std::make_shared<Lattice>(lattice);
    lattices.push_back(lattice_ptr);
    return lattice_ptr;
}

void ContainerRepository::RemovePlan(std::shared_ptr<Plan> plan)
{
    auto it = std::find(plans.begin(), plans.end(),
                        plan);

    // If element is found found, erase it
    if (it != plans.end()) {
        plans.erase(it);
    }
}

void ContainerRepository::RemoveDisk(std::shared_ptr<Disk> disk)
{
    auto it = std::find(disks.begin(), disks.end(),
                        disk);

    // If element is found found, erase it
    if (it != disks.end()) {
        disks.erase(it);
    }
}


void ContainerRepository::RemoveCone(std::shared_ptr<Cone> cone)
{
    auto it = std::find(cones.begin(), cones.end(),
                        cone);

    // If element is found found, erase it
    if (it != cones.end()) {
        cones.erase(it);
    }
}


void ContainerRepository::RemoveElbow(std::shared_ptr<Elbow> elbow) {
    auto it = std::find(elbows.begin(), elbows.end(),
                        elbow);

    // If element is found found, erase it
    if (it != elbows.end()) {
        elbows.erase(it);
    }
}

void ContainerRepository::RemoveCuboid(std::shared_ptr<Cuboid> cuboid) {
    auto it = std::find(cuboids.begin(), cuboids.end(),
                        cuboid);

    // If element is found found, erase it
    if (it != cuboids.end()) {
        cuboids.erase(it);
    }
}


void ContainerRepository::RemoveLattice(std::shared_ptr<Lattice> lattice) {
    auto it = std::find(lattices.begin(), lattices.end(),
                        lattice);

    // If element is found found, erase it
    if (it != lattices.end()) {
        lattices.erase(it);
    }
}


std::shared_ptr<Cone> ContainerRepository::GetCone(int index) {
    if(index >= 0 && index < (int)cones.size()) {
        return cones[index];
    }
    return nullptr;
}

std::shared_ptr<Cuboid> ContainerRepository::GetCuboid(int index) {
    if(index >= 0 && index < (int)cuboids.size()) {
        return cuboids[index];
    }
    return nullptr;
}

std::shared_ptr<Setup> ContainerRepository::GetSetup() {
    return setup;
}

int ContainerRepository::GetIndexOfCone(std::shared_ptr<Cone> cone) {
    for(int i = 0 ; i < (int)cones.size() ; ++i)
        if (cones[i] == cone)
            return i;
    return -1;
}

int ContainerRepository::GetIndexOfCuboid(std::shared_ptr<Cuboid> cuboid) {
    for(int i = 0 ; i < (int)cuboids.size() ; ++i)
        if (cuboids[i] == cuboid)
            return i;
    return -1;
}


double ContainerRepository::ComputeZoom() {
    double zoom0 = 1000000;
    double scale;
    for(auto& plan : plans) {
        scale = plan->ComputeScale();
        if(zoom0 > 1./scale)
            zoom0 = 1./scale;
    }
    for(auto& disk : disks) {
        scale = disk->ComputeScale();
        if(zoom0 > 1./scale)
            zoom0 = 1./scale;
    }
    for(auto& cone : cones) {
        scale = cone->ComputeScale();
        if(zoom0 > 1./scale)
            zoom0 = 1./scale;
    }
    for(auto& elbow : elbows) {
        scale = elbow->ComputeScale();
        if(zoom0 > 1./scale)
            zoom0 = 1./scale;
    }

    for(auto& lattice : lattices) {
        scale = lattice->ComputeScale();
        if(zoom0 > 1./scale)
            zoom0 = 1./scale;
    }

    if(zoom0 == 1000000)
        zoom0 = 1;

    return zoom0;
}

int ContainerRepository::planCount() {return plans.size();}
std::shared_ptr<Plan> ContainerRepository::getPlanAtIndex(int index) {return plans[index];}
int ContainerRepository::diskCount() {return disks.size();}
std::shared_ptr<Disk> ContainerRepository::getDiskAtIndex(int index) {return disks[index];}
int ContainerRepository::coneCount() {return cones.size();}
std::shared_ptr<Cone> ContainerRepository::getConeAtIndex(int index) {return cones[index];}
int ContainerRepository::elbowCount() {return elbows.size();}
std::shared_ptr<Elbow> ContainerRepository::getElbowAtIndex(int index) {return elbows[index];}
int ContainerRepository::cuboidCount() {return cuboids.size();}
std::shared_ptr<Cuboid> ContainerRepository::getCuboidAtIndex(int index) {return cuboids[index];}
int ContainerRepository::latticeCount() {return lattices.size();}
std::shared_ptr<Lattice> ContainerRepository::getLatticeAtIndex(int index) {return lattices[index];}


// ============================================================
// Import from Start_stop
// ============================================================

bool ContainerRepository::ImportStartStop(std::string directory) {
    std::cout << "Import Start_stop from: " << directory << std::endl;

    // Clear existing data
    plans.clear();
    disks.clear();
    cones.clear();
    elbows.clear();
    cuboids.clear();
    lattices.clear();
    importedGranules.clear();
    importedBodies.clear();
    importedHollowBalls.clear();

    // Reset setup to defaults
    setup = std::make_shared<Setup>(&lattices, linkedCells);

    std::string startStopDir = directory + "/Start_stop";
    if (!std::filesystem::exists(startStopDir)) {
        std::cout << "Start_stop directory not found: " << startStopDir << std::endl;
        return false;
    }

    if (!importStartStopContainer(startStopDir))
        return false;
    if (!importStartStopData(startStopDir))
        return false;
    importStartStopGrain(startStopDir);
    importStartStopBodies(startStopDir);
    importStartStopHollowBall(startStopDir);

    importMode = true;
    return true;
}


bool ContainerRepository::importStartStopContainer(std::string &directory) {
    char filename[1024];
    sprintf(filename, "%s/container.txt", directory.c_str());
    FILE *ft = fopen(filename, "r");
    if (!ft) {
        std::cout << "Cannot open: " << filename << std::endl;
        return false;
    }

    int Npl, Nplr, Nco, Nelb;
    fscanf(ft, "%d", &Npl);
    fscanf(ft, "%d", &Nplr);
    fscanf(ft, "%d", &Nco);
    fscanf(ft, "%d", &Nelb);

    std::cout << "Import container: " << Npl << " plans, " << Nplr << " disks, "
              << Nco << " cones, " << Nelb << " elbows" << std::endl;

    // Read Plans (using Solid::ReadFromFile + plan-specific + acceleration)
    for (int i = 0; i < Npl; i++) {
        Plan plan{};
        // Read Solid base: x y z, q0 q1 q2 q3, velocities + origin
        plan.Solid::ReadFromFile(ft);
        // Read Plan-specific: dn dt ds, periodic inAndOut
        double dn;
        int periodic;
        fscanf(ft, "%lf\t%lf\t%lf\n", &dn, &plan.dt, &plan.ds);
        fscanf(ft, "%d\t%d\n", &periodic, &plan.inAndOut);
        // Skip acceleration data: Mass activeGravity, Fcx Fcy Fcz, Mcx Mcy Mcz
        double dummy;
        int dummyInt;
        fscanf(ft, "%lf\t%d", &dummy, &dummyInt);
        fscanf(ft, "%lf\t%lf\t%lf", &dummy, &dummy, &dummy);
        fscanf(ft, "%lf\t%lf\t%lf", &dummy, &dummy, &dummy);
        plans.push_back(std::make_shared<Plan>(plan));
    }

    // Read Disks (PlanR in SandPanda)
    for (int i = 0; i < Nplr; i++) {
        Disk disk{};
        disk.Solid::ReadFromFile(ft);
        double dn;
        fscanf(ft, "%lf\t%lf\n", &dn, &disk.r);
        int periodic;
        fscanf(ft, "%d\n", &periodic);
        // Skip acceleration data
        double dummy;
        int dummyInt;
        fscanf(ft, "%lf\t%d", &dummy, &dummyInt);
        fscanf(ft, "%lf\t%lf\t%lf", &dummy, &dummy, &dummy);
        fscanf(ft, "%lf\t%lf\t%lf", &dummy, &dummy, &dummy);
        disks.push_back(std::make_shared<Disk>(disk));
    }

    // Read Cones
    for (int i = 0; i < Nco; i++) {
        Cone cone{};
        cone.Solid::ReadFromFile(ft);
        double dr;
        fscanf(ft, "%lf\t%lf\t%lf\t%lf\n", &cone.h, &cone.r0, &cone.r1, &dr);
        int in, numTop, numBottom;
        fscanf(ft, "%d\t%d\t%d\n", &in, &numTop, &numBottom);
        cone.inAndOut = in;
        // Skip acceleration data
        double dummy;
        int dummyInt;
        fscanf(ft, "%lf\t%d", &dummy, &dummyInt);
        fscanf(ft, "%lf\t%lf\t%lf", &dummy, &dummy, &dummy);
        fscanf(ft, "%lf\t%lf\t%lf", &dummy, &dummy, &dummy);
        cones.push_back(std::make_shared<Cone>(cone));
    }

    // Read Elbows
    for (int i = 0; i < Nelb; i++) {
        Elbow elbow{};
        elbow.ReadFromFile(ft);
        elbows.push_back(std::make_shared<Elbow>(elbow));
    }

    fclose(ft);
    return true;
}


bool ContainerRepository::importStartStopData(std::string &directory) {
    char filename[1024];
    sprintf(filename, "%s/data.txt", directory.c_str());
    FILE *ft = fopen(filename, "r");
    if (!ft) {
        std::cout << "Cannot open: " << filename << std::endl;
        return false;
    }

    // Read Gravity section
    fscanf(ft, "%lf\t%lf\t%lf", &setup->gravityX, &setup->gravityY, &setup->gravityZ);

    // Skip gravity quaternion
    double q0, q1, q2, q3;
    fscanf(ft, "%lf\t%lf\t%lf\t%lf", &q0, &q1, &q2, &q3);

    // Read gravity angular velocity sinusoids
    fscanf(ft, "%lf\t%lf\t%lf\t%lf", &setup->gWxA0, &setup->gWxA1, &setup->gWxW, &setup->gWxP);
    fscanf(ft, "%lf\t%lf\t%lf\t%lf", &setup->gWyA0, &setup->gWyA1, &setup->gWyW, &setup->gWyP);
    fscanf(ft, "%lf\t%lf\t%lf\t%lf", &setup->gWzA0, &setup->gWzA1, &setup->gWzW, &setup->gWzP);

    // Read gravity acceleration
    fscanf(ft, "%lf", &setup->gravityAcceleration);

    // Read Data section
    double TIME;
    fscanf(ft, "%lf\t%lf\t%lf", &setup->timeStep, &TIME, &setup->duration);
    setup->startingTime = TIME;

    fscanf(ft, "%d", &setup->Nsp);

    int modelTg;
    fscanf(ft, "%d", &modelTg);
    if (modelTg == 0) {
        setup->isTangentialDynamicModel = true;
        double mu;
        fscanf(ft, "%lf\t%lf\t%lf\t%lf",
               &setup->resitutionCoefficient, &mu, &mu,
               &setup->normalStiffness);
        setup->staticFrictionCoefficient = mu;
        setup->dynamicFrictionCoefficient = mu;
    } else {
        setup->isTangentialDynamicModel = false;
        fscanf(ft, "%lf\t%lf\t%lf\t%lf",
               &setup->resitutionCoefficient,
               &setup->staticFrictionCoefficient,
               &setup->dynamicFrictionCoefficient,
               &setup->normalStiffness);
    }

    double t0;
    fscanf(ft, "%lf\t%lf", &setup->captureTimeStep, &t0);

    // Skip linked cells data (xmin ymin zmin, xmax ymax zmax, ax ay az, Nx Ny Nz)
    double dummy;
    int dummyInt;
    fscanf(ft, "%lf\t%lf\t%lf", &dummy, &dummy, &dummy);
    fscanf(ft, "%lf\t%lf\t%lf", &dummy, &dummy, &dummy);
    fscanf(ft, "%lf\t%lf\t%lf", &dummy, &dummy, &dummy);
    fscanf(ft, "%d\t%d\t%d", &dummyInt, &dummyInt, &dummyInt);

    fclose(ft);
    return true;
}


bool ContainerRepository::importStartStopGrain(std::string &directory) {
    char filename[1024];
    sprintf(filename, "%s/grain.txt", directory.c_str());
    FILE *ft = fopen(filename, "r");
    if (!ft) {
        std::cout << "No grain.txt found (optional)" << std::endl;
        return false;
    }

    int Nsph;
    fscanf(ft, "%d", &Nsph);
    std::cout << "Import " << Nsph << " grains from Start_stop" << std::endl;

    for (int i = 0; i < Nsph; i++) {
        ImportedGranule grain;
        grain.readStartStopFromFile(ft);
        importedGranules.push_back(grain);
    }

    fclose(ft);
    return true;
}


bool ContainerRepository::importStartStopBodies(std::string &directory) {
    char filename[1024];
    sprintf(filename, "%s/particle.txt", directory.c_str());
    FILE *ft = fopen(filename, "r");
    if (!ft) {
        std::cout << "No particle.txt found (optional)" << std::endl;
        return false;
    }

    int Nbd;
    fscanf(ft, "%d", &Nbd);
    std::cout << "Import " << Nbd << " bodies from Start_stop" << std::endl;

    for (int i = 0; i < Nbd; i++) {
        ImportedBody body;
        body.readStartStopFromFile(ft);
        importedBodies.push_back(body);
    }

    fclose(ft);
    return true;
}


bool ContainerRepository::importStartStopHollowBall(std::string &directory) {
    char filename[1024];
    sprintf(filename, "%s/hollowBall.txt", directory.c_str());
    FILE *ft = fopen(filename, "r");
    if (!ft) {
        std::cout << "No hollowBall.txt found (optional)" << std::endl;
        return false;
    }

    int Nhbl;
    fscanf(ft, "%d", &Nhbl);
    std::cout << "Import " << Nhbl << " hollow balls from Start_stop" << std::endl;

    for (int i = 0; i < Nhbl; i++) {
        ImportedHollowBall hb;
        hb.readFromFile(ft);
        importedHollowBalls.push_back(hb);
    }

    fclose(ft);
    return true;
}


// ============================================================
// Export to Start_stop (matching SandPanda format exactly)
// ============================================================

void ContainerRepository::ExportStartStop(std::string directory) {
    std::cout << "Export Start_stop to: " << directory << std::endl;

    // Also do the normal Export to Export/ directory
    std::string exportDir = directory + "/Export";
    std::filesystem::create_directories(exportDir);
    linkedCells->Compute(plans, disks, cones, elbows, cuboids, lattices, setup->duration);
    setup->Export(exportDir);
    this->exportContainer(exportDir);
    this->exportGrain(exportDir);

    // Now export to Start_stop/ directory in SandPanda format
    std::string startStopDir = directory + "/Start_stop";
    std::filesystem::create_directories(startStopDir);

    exportStartStopContainer(startStopDir);
    exportStartStopData(startStopDir);
    exportStartStopGrain(startStopDir);
    exportStartStopBodies(startStopDir);
    exportStartStopHollowBall(startStopDir);
}


void ContainerRepository::exportStartStopContainer(std::string &directory) {
    char filename[1024];
    sprintf(filename, "%s/container.txt", directory.c_str());
    FILE *ft = fopen(filename, "w");

    int Npl = plans.size();
    for (auto& cuboid : cuboids)
        Npl += cuboid->planCount();

    int Ndisk = disks.size();
    for (auto& cone : cones)
        Ndisk += cone->diskCount();

    int Ncone = cones.size();
    int Nelbow = elbows.size();

    fprintf(ft, "%d\n", Npl);
    fprintf(ft, "%d\n", Ndisk);
    fprintf(ft, "%d\n", Ncone);
    fprintf(ft, "%d\n", Nelbow);

    // Write Plans using SandPanda Start_stop format
    for (auto& plan : plans) {
        plan->base();
        plan->computeQuaternion();
        // Solid::WriteToFile equivalent
        fprintf(ft, "%e\t%e\t%e\n", plan->x, plan->y, plan->z);
        fprintf(ft, "%e\t%e\t%e\t%e\n", plan->q0, plan->q1, plan->q2, plan->q3);
        // V.WriteToFile(ft,0) equivalent: 6 sinusoids + origin
        fprintf(ft, "%e\t%e\t%e\t%e\n", plan->vx.A0, plan->vx.A1, plan->vx.w, plan->vx.p);
        fprintf(ft, "%e\t%e\t%e\t%e\n", plan->vy.A0, plan->vy.A1, plan->vy.w, plan->vy.p);
        fprintf(ft, "%e\t%e\t%e\t%e\n", plan->vz.A0, plan->vz.A1, plan->vz.w, plan->vz.p);
        fprintf(ft, "%e\t%e\t%e\t%e\n", plan->wx.A0, plan->wx.A1, plan->wx.w, plan->wx.p);
        fprintf(ft, "%e\t%e\t%e\t%e\n", plan->wy.A0, plan->wy.A1, plan->wy.w, plan->wy.p);
        fprintf(ft, "%e\t%e\t%e\t%e\n", plan->wz.A0, plan->wz.A1, plan->wz.w, plan->wz.p);
        fprintf(ft, "%e\t%e\t%e\n", plan->orx, plan->ory, plan->orz);
        // Plan-specific
        double dn = sqrt(plan->dt * plan->dt + plan->ds * plan->ds) / 1000.;
        fprintf(ft, "%e\t%e\t%e\n", dn, plan->dt, plan->ds);
        fprintf(ft, "%d\t%d\n", -9, plan->inAndOut);
        // Acceleration data (all zeros for design)
        fprintf(ft, "%e\t%d\n", 0.0, 0);
        fprintf(ft, "%e\t%e\t%e\n", 0.0, 0.0, 0.0);
        fprintf(ft, "%e\t%e\t%e\n", 0.0, 0.0, 0.0);
    }

    // Write Cuboid sub-plans
    for (auto& cuboid : cuboids) {
        cuboid->updatePlans();
        std::vector<std::shared_ptr<Plan>> subPlans = {cuboid->p1, cuboid->p2, cuboid->p3, cuboid->p4};
        if (cuboid->top != nullptr) subPlans.push_back(cuboid->top);
        if (cuboid->bottom != nullptr) subPlans.push_back(cuboid->bottom);
        for (auto& plan : subPlans) {
            plan->base();
            plan->computeQuaternion();
            fprintf(ft, "%e\t%e\t%e\n", plan->x, plan->y, plan->z);
            fprintf(ft, "%e\t%e\t%e\t%e\n", plan->q0, plan->q1, plan->q2, plan->q3);
            fprintf(ft, "%e\t%e\t%e\t%e\n", plan->vx.A0, plan->vx.A1, plan->vx.w, plan->vx.p);
            fprintf(ft, "%e\t%e\t%e\t%e\n", plan->vy.A0, plan->vy.A1, plan->vy.w, plan->vy.p);
            fprintf(ft, "%e\t%e\t%e\t%e\n", plan->vz.A0, plan->vz.A1, plan->vz.w, plan->vz.p);
            fprintf(ft, "%e\t%e\t%e\t%e\n", plan->wx.A0, plan->wx.A1, plan->wx.w, plan->wx.p);
            fprintf(ft, "%e\t%e\t%e\t%e\n", plan->wy.A0, plan->wy.A1, plan->wy.w, plan->wy.p);
            fprintf(ft, "%e\t%e\t%e\t%e\n", plan->wz.A0, plan->wz.A1, plan->wz.w, plan->wz.p);
            fprintf(ft, "%e\t%e\t%e\n", plan->orx, plan->ory, plan->orz);
            double dn = sqrt(plan->dt * plan->dt + plan->ds * plan->ds) / 1000.;
            fprintf(ft, "%e\t%e\t%e\n", dn, plan->dt, plan->ds);
            fprintf(ft, "%d\t%d\n", -9, plan->inAndOut);
            fprintf(ft, "%e\t%d\n", 0.0, 0);
            fprintf(ft, "%e\t%e\t%e\n", 0.0, 0.0, 0.0);
            fprintf(ft, "%e\t%e\t%e\n", 0.0, 0.0, 0.0);
        }
    }

    // Write Disks using SandPanda PlanR Start_stop format
    for (auto& disk : disks) {
        disk->base();
        disk->computeQuaternion();
        fprintf(ft, "%e\t%e\t%e\n", disk->x, disk->y, disk->z);
        fprintf(ft, "%e\t%e\t%e\t%e\n", disk->q0, disk->q1, disk->q2, disk->q3);
        fprintf(ft, "%e\t%e\t%e\t%e\n", disk->vx.A0, disk->vx.A1, disk->vx.w, disk->vx.p);
        fprintf(ft, "%e\t%e\t%e\t%e\n", disk->vy.A0, disk->vy.A1, disk->vy.w, disk->vy.p);
        fprintf(ft, "%e\t%e\t%e\t%e\n", disk->vz.A0, disk->vz.A1, disk->vz.w, disk->vz.p);
        fprintf(ft, "%e\t%e\t%e\t%e\n", disk->wx.A0, disk->wx.A1, disk->wx.w, disk->wx.p);
        fprintf(ft, "%e\t%e\t%e\t%e\n", disk->wy.A0, disk->wy.A1, disk->wy.w, disk->wy.p);
        fprintf(ft, "%e\t%e\t%e\t%e\n", disk->wz.A0, disk->wz.A1, disk->wz.w, disk->wz.p);
        fprintf(ft, "%e\t%e\t%e\n", disk->orx, disk->ory, disk->orz);
        // PlanR-specific
        double dn = disk->r / 1000.;
        fprintf(ft, "%e\t%e\n", dn, disk->r);
        fprintf(ft, "%d\n", -9);
        // Acceleration
        fprintf(ft, "%e\t%d\n", 0.0, 0);
        fprintf(ft, "%e\t%e\t%e\n", 0.0, 0.0, 0.0);
        fprintf(ft, "%e\t%e\t%e\n", 0.0, 0.0, 0.0);
    }

    // Write Cone sub-disks
    for (auto& cone : cones) {
        cone->updateTop();
        cone->updateBottom();
        if (cone->top != nullptr) {
            auto& d = cone->top;
            d->base();
            d->computeQuaternion();
            fprintf(ft, "%e\t%e\t%e\n", d->x, d->y, d->z);
            fprintf(ft, "%e\t%e\t%e\t%e\n", d->q0, d->q1, d->q2, d->q3);
            fprintf(ft, "%e\t%e\t%e\t%e\n", d->vx.A0, d->vx.A1, d->vx.w, d->vx.p);
            fprintf(ft, "%e\t%e\t%e\t%e\n", d->vy.A0, d->vy.A1, d->vy.w, d->vy.p);
            fprintf(ft, "%e\t%e\t%e\t%e\n", d->vz.A0, d->vz.A1, d->vz.w, d->vz.p);
            fprintf(ft, "%e\t%e\t%e\t%e\n", d->wx.A0, d->wx.A1, d->wx.w, d->wx.p);
            fprintf(ft, "%e\t%e\t%e\t%e\n", d->wy.A0, d->wy.A1, d->wy.w, d->wy.p);
            fprintf(ft, "%e\t%e\t%e\t%e\n", d->wz.A0, d->wz.A1, d->wz.w, d->wz.p);
            fprintf(ft, "%e\t%e\t%e\n", d->orx, d->ory, d->orz);
            double dn = d->r / 1000.;
            fprintf(ft, "%e\t%e\n", dn, d->r);
            fprintf(ft, "%d\n", -9);
            fprintf(ft, "%e\t%d\n", 0.0, 0);
            fprintf(ft, "%e\t%e\t%e\n", 0.0, 0.0, 0.0);
            fprintf(ft, "%e\t%e\t%e\n", 0.0, 0.0, 0.0);
        }
        if (cone->bottom != nullptr) {
            auto& d = cone->bottom;
            d->base();
            d->computeQuaternion();
            fprintf(ft, "%e\t%e\t%e\n", d->x, d->y, d->z);
            fprintf(ft, "%e\t%e\t%e\t%e\n", d->q0, d->q1, d->q2, d->q3);
            fprintf(ft, "%e\t%e\t%e\t%e\n", d->vx.A0, d->vx.A1, d->vx.w, d->vx.p);
            fprintf(ft, "%e\t%e\t%e\t%e\n", d->vy.A0, d->vy.A1, d->vy.w, d->vy.p);
            fprintf(ft, "%e\t%e\t%e\t%e\n", d->vz.A0, d->vz.A1, d->vz.w, d->vz.p);
            fprintf(ft, "%e\t%e\t%e\t%e\n", d->wx.A0, d->wx.A1, d->wx.w, d->wx.p);
            fprintf(ft, "%e\t%e\t%e\t%e\n", d->wy.A0, d->wy.A1, d->wy.w, d->wy.p);
            fprintf(ft, "%e\t%e\t%e\t%e\n", d->wz.A0, d->wz.A1, d->wz.w, d->wz.p);
            fprintf(ft, "%e\t%e\t%e\n", d->orx, d->ory, d->orz);
            double dn = d->r / 1000.;
            fprintf(ft, "%e\t%e\n", dn, d->r);
            fprintf(ft, "%d\n", -9);
            fprintf(ft, "%e\t%d\n", 0.0, 0);
            fprintf(ft, "%e\t%e\t%e\n", 0.0, 0.0, 0.0);
            fprintf(ft, "%e\t%e\t%e\n", 0.0, 0.0, 0.0);
        }
    }

    // Write Cones using SandPanda Start_stop format
    for (auto& cone : cones) {
        cone->base();
        cone->computeQuaternion();
        fprintf(ft, "%e\t%e\t%e\n", cone->x, cone->y, cone->z);
        fprintf(ft, "%e\t%e\t%e\t%e\n", cone->q0, cone->q1, cone->q2, cone->q3);
        fprintf(ft, "%e\t%e\t%e\t%e\n", cone->vx.A0, cone->vx.A1, cone->vx.w, cone->vx.p);
        fprintf(ft, "%e\t%e\t%e\t%e\n", cone->vy.A0, cone->vy.A1, cone->vy.w, cone->vy.p);
        fprintf(ft, "%e\t%e\t%e\t%e\n", cone->vz.A0, cone->vz.A1, cone->vz.w, cone->vz.p);
        fprintf(ft, "%e\t%e\t%e\t%e\n", cone->wx.A0, cone->wx.A1, cone->wx.w, cone->wx.p);
        fprintf(ft, "%e\t%e\t%e\t%e\n", cone->wy.A0, cone->wy.A1, cone->wy.w, cone->wy.p);
        fprintf(ft, "%e\t%e\t%e\t%e\n", cone->wz.A0, cone->wz.A1, cone->wz.w, cone->wz.p);
        fprintf(ft, "%e\t%e\t%e\n", cone->orx, cone->ory, cone->orz);
        // Cone-specific
        fprintf(ft, "%e\t%e\t%e\t%e\n", cone->h, cone->r0, cone->r1, fabs(cone->r1 - cone->r0));
        fprintf(ft, "%d\t%d\t%d\n", cone->inAndOut, -9, -9);
        // Acceleration
        fprintf(ft, "%e\t%d\n", 0.0, 0);
        fprintf(ft, "%e\t%e\t%e\n", 0.0, 0.0, 0.0);
        fprintf(ft, "%e\t%e\t%e\n", 0.0, 0.0, 0.0);
    }

    // Write Elbows using SandPanda Start_stop format
    for (auto& elbow : elbows) {
        elbow->base();
        fprintf(ft, "%e\t%e\t%e\n", elbow->xi, elbow->yi, elbow->zi);
        fprintf(ft, "%e\t%e\t%e\n", elbow->xf, elbow->yf, elbow->zf);
        fprintf(ft, "%e\t%e\t%e\n", elbow->xr, elbow->yr, elbow->zr);
        fprintf(ft, "%e\t%e\t%e\n", elbow->nx, elbow->ny, elbow->nz);
        fprintf(ft, "%e\t%e\t%e\n", elbow->tx, elbow->ty, elbow->tz);
        fprintf(ft, "%e\t%e\t%e\n", elbow->sx, elbow->sy, elbow->sz);
        fprintf(ft, "%e\t%e\t%e\t%e\n", elbow->vx.A0, elbow->vx.A1, elbow->vx.w, elbow->vx.p);
        fprintf(ft, "%e\t%e\t%e\t%e\n", elbow->vy.A0, elbow->vy.A1, elbow->vy.w, elbow->vy.p);
        fprintf(ft, "%e\t%e\t%e\t%e\n", elbow->vz.A0, elbow->vz.A1, elbow->vz.w, elbow->vz.p);
        fprintf(ft, "%e\t%e\t%e\t%e\n", elbow->wx.A0, elbow->wx.A1, elbow->wx.w, elbow->wx.p);
        fprintf(ft, "%e\t%e\t%e\t%e\n", elbow->wy.A0, elbow->wy.A1, elbow->wy.w, elbow->wy.p);
        fprintf(ft, "%e\t%e\t%e\t%e\n", elbow->wz.A0, elbow->wz.A1, elbow->wz.w, elbow->wz.p);
        fprintf(ft, "%e\t%e\t%e\n", elbow->orx, elbow->ory, elbow->orz);
        fprintf(ft, "%e\t%e\t%e\n", elbow->Rc, elbow->alpha, elbow->radius);
    }

    fflush(ft);
    fclose(ft);
}


void ContainerRepository::exportStartStopData(std::string &directory) {
    char filename[1024];
    sprintf(filename, "%s/data.txt", directory.c_str());
    FILE *ft = fopen(filename, "w");

    // Gravity::WriteToFile equivalent
    fprintf(ft, "%e\t%e\t%e\n", setup->gravityX, setup->gravityY, setup->gravityZ);
    fprintf(ft, "%e\t%e\t%e\t%e\n", 0.0, 0.0, 0.0, 0.0); // quaternion
    fprintf(ft, "%e\t%e\t%e\t%e\n", setup->gWxA0, setup->gWxA1, setup->gWxW, setup->gWxP);
    fprintf(ft, "%e\t%e\t%e\t%e\n", setup->gWyA0, setup->gWyA1, setup->gWyW, setup->gWyP);
    fprintf(ft, "%e\t%e\t%e\t%e\n", setup->gWzA0, setup->gWzA1, setup->gWzW, setup->gWzP);
    fprintf(ft, "%e\n", setup->gravityAcceleration);

    // Data::WriteToFile equivalent
    fprintf(ft, "%e\t%e\t%e\n", setup->timeStep, setup->startingTime, setup->duration);

    // Compute Nsp: imported species + new lattice species
    int Nsp = setup->Nsp;
    // Count new lattice species
    int newSpecies = 0;
    for (auto& lattice : lattices) {
        if (lattice->N > 0)
            newSpecies++;
    }
    int totalNsp = Nsp + newSpecies;
    fprintf(ft, "%d\n", totalNsp);

    // Contact model
    if (setup->isTangentialDynamicModel) {
        fprintf(ft, "%d\t%e\t%e\t%e\t%e\n", 0,
                setup->resitutionCoefficient,
                setup->staticFrictionCoefficient,
                setup->staticFrictionCoefficient,
                setup->normalStiffness);
    } else {
        fprintf(ft, "%d\t%e\t%e\t%e\t%e\n", 1,
                setup->resitutionCoefficient,
                setup->staticFrictionCoefficient,
                setup->dynamicFrictionCoefficient,
                setup->normalStiffness);
    }

    fprintf(ft, "%e\t%e\n", setup->captureTimeStep, setup->startingTime);

    // LinkedCells
    linkedCells->Compute(plans, disks, cones, elbows, cuboids, lattices, setup->duration);
    linkedCells->Export(ft);

    fflush(ft);
    fclose(ft);
}


void ContainerRepository::exportStartStopGrain(std::string &directory) {
    char filename[1024];
    sprintf(filename, "%s/grain.txt", directory.c_str());
    FILE *ft = fopen(filename, "w");

    // Count total grains: imported + new from lattices
    int totalGrains = importedGranules.size();
    for (auto& lattice : lattices) {
        totalGrains += lattice->N;
    }
    fprintf(ft, "%d\n", totalGrains);

    // Write imported grains first (preserving contact data)
    for (auto& grain : importedGranules) {
        grain.writeStartStopToFile(ft);
    }

    // Write new grains from lattices (no contact data)
    int sp = setup->Nsp; // Start species numbering after imported ones
    for (auto& lattice : lattices) {
        for (auto& granule : lattice->gr) {
            fprintf(ft, "%.16e\t%.16e\t%.16e\n", granule.x, granule.y, granule.z);
            fprintf(ft, "%.16e\t%.16e\t%.16e\t%.16e\n", granule.q0, granule.q1, granule.q2, granule.q3);
            fprintf(ft, "%.16e\t%.16e\t%.16e\n", granule.vx, granule.vy, granule.vz);
            fprintf(ft, "%.16e\t%.16e\t%.16e\n", granule.wx, granule.wy, granule.wz);
            fprintf(ft, "%e\t%e\t%e\t%d\t%d\n", granule.r, granule.m, granule.I, sp, -9);
            fprintf(ft, "%d\n", 0); // No contact neighbours for new grains
        }
        sp++;
    }

    fflush(ft);
    fclose(ft);
}


void ContainerRepository::exportStartStopBodies(std::string &directory) {
    char filename[1024];
    sprintf(filename, "%s/particle.txt", directory.c_str());
    FILE *ft = fopen(filename, "w");

    int Nbd = importedBodies.size();
    fprintf(ft, "%d\n", Nbd);

    for (auto& body : importedBodies) {
        body.writeStartStopToFile(ft);
    }

    fflush(ft);
    fclose(ft);
}


void ContainerRepository::exportStartStopHollowBall(std::string &directory) {
    char filename[1024];
    sprintf(filename, "%s/hollowBall.txt", directory.c_str());
    FILE *ft = fopen(filename, "w");

    int Nhbl = importedHollowBalls.size();
    fprintf(ft, "%d\n", Nhbl);

    for (auto& hb : importedHollowBalls) {
        hb.writeToFile(ft);
    }

    fflush(ft);
    fclose(ft);
}

