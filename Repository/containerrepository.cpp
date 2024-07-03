#include "containerrepository.h"

ContainerRepository::ContainerRepository() {}

ContainerRepository& ContainerRepository::getInstance()
{
    static ContainerRepository instance{};
    return instance;
}

void ContainerRepository::Draw(bool isLineContainer)
{
    for(auto plan : plans)
        plan->Draw(isLineContainer);
    for(auto disk : disks)
        disk->Draw(isLineContainer);
    for(auto cone : cones)
        cone->Draw(isLineContainer);
    for(auto elbow : elbows)
        elbow->Draw(isLineContainer);

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

    if(zoom0 == 1000000)
        zoom0 = 1;

    return zoom0;
}







