#include "containerrepository.h"

#include <algorithm>

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
    Json::Value jsonValuePlans;
    int index = 0;
    for(auto& plan : plans) {
        auto jvalue = JsonSerializer::PlanToJsonValue(plan);
        jsonValuePlans[index] = jvalue;
        auto new_plan = JsonSerializer::PlanFromJsonValue(jsonValuePlans[index]);
        auto jvalue2 = JsonSerializer::PlanToJsonValue(new_plan);
        std::cout << jvalue2.toStyledString() << std::endl;
        index++;
    }
    std::cout << "Plan : " << jsonValuePlans.toStyledString() << std::endl;
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
        fscanf_s(ft,"%d",&Nplan);
        fscanf_s(ft,"%d",&Ndisk);
        fscanf_s(ft,"%d",&Ncone);
        fscanf_s(ft,"%d",&Nelbow);
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
    if(index >= 0 && index < cones.size()) {
        return cones[index];
    }
    return nullptr;
}

std::shared_ptr<Cuboid> ContainerRepository::GetCuboid(int index) {
    if(index >= 0 && index < cuboids.size()) {
        return cuboids[index];
    }
    return nullptr;
}

std::shared_ptr<Setup> ContainerRepository::GetSetup() {
    return setup;
}

int ContainerRepository::GetIndexOfCone(std::shared_ptr<Cone> cone) {
    for(int i = 0 ; i < cones.size() ; ++i)
        if (cones[i] == cone)
            return i;
    return -1;
}

int ContainerRepository::GetIndexOfCuboid(std::shared_ptr<Cuboid> cuboid) {
    for(int i = 0 ; i < cuboids.size() ; ++i)
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







