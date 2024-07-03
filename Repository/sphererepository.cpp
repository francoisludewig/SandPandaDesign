#include "Repository/sphererepository.h"

#include <cstdio>

SphereRepository::SphereRepository() {}


SphereRepository &SphereRepository::getInstance()
{
    static SphereRepository instance{};
    return instance;
}

void SphereRepository::load(std::string directory)
{
    int count = 0;
    std::FILE *ft = nullptr;
    char filename[2048];
    spheres.clear();

    //sprintf(filename, "C:\\Users\\utilisateur\\Documents\\TestBox\\Out\\grain_%d.txt", N);
    //sprintf(filename, "C:\\Users\\utilisateur\\OneDrive - student.helmo.be\\Bureau\\Dev\\Archives\\LuGaProjects\\Test\\Sphere\\Elbow\\New\\Out\\grain_%d.txt", N);
    //sprintf(filename, "C:\\Users\\utilisateur\\OneDrive - student.helmo.be\\Bureau\\Dev\\Archives\\LuGaProjects\\Test\\Sphere\\Cone\\New\\Out\\grain_%d.txt", N);
    sprintf(filename, "%s\\Out\\grain.txt", directory.data());
    printf("filename : %s\n", filename);
    ft = std::fopen(filename,"r");
    if(ft) {
        printf("Load file %s\n", filename);
        fscanf_s(ft,"%d",&count);
        for(int i = 0 ; i < count ; ++i) {
            Sphere sph{};
            sph.ReadFromFile(ft);
            spheres.push_back(sph);
        }

        printf("Sphere count : %d\n", count);
        fclose(ft);
    }
}


void SphereRepository::Draw() {
    for(auto sph : spheres)
        sph.Draw();

}


