#include "linkedcells.h"

LinkedCells::LinkedCells() {}


void LinkedCells::initValue() {
    xmax = -10000;
    ymax = -10000;
    zmax = -10000;
    xmin = 10000;
    ymin = 10000;
    zmin = 10000;
}



void LinkedCells::computeZoneForPlan(std::vector< std::shared_ptr<Plan> >& plans, double time) {
    for(auto& plan : plans) {
        plan->Zone(time);
        if(xmin > plan->xmin)xmin = plan->xmin;
        if(ymin > plan->ymin)ymin = plan->ymin;
        if(zmin > plan->zmin)zmin = plan->zmin;
        if(xmax < plan->xmax)xmax = plan->xmax;
        if(ymax < plan->ymax)ymax = plan->ymax;
        if(zmax < plan->zmax)zmax = plan->zmax;
    }
}

void LinkedCells::computeZoneForDisk(std::vector< std::shared_ptr<Disk> >& disks, double time) {
    for(auto& diks : disks) {
        diks->Zone(time);
        if(xmin > diks->xmin)xmin = diks->xmin;
        if(ymin > diks->ymin)ymin = diks->ymin;
        if(zmin > diks->zmin)zmin = diks->zmin;
        if(xmax < diks->xmax)xmax = diks->xmax;
        if(ymax < diks->ymax)ymax = diks->ymax;
        if(zmax < diks->zmax)zmax = diks->zmax;
    }
}

void LinkedCells::computeZoneForCone( std::vector< std::shared_ptr<Cone> >& cones, double time) {
    for(auto& cone : cones) {
        cone->Zone(time);
        if(xmin > cone->xmin)xmin = cone->xmin;
        if(ymin > cone->ymin)ymin = cone->ymin;
        if(zmin > cone->zmin)zmin = cone->zmin;
        if(xmax < cone->xmax)xmax = cone->xmax;
        if(ymax < cone->ymax)ymax = cone->ymax;
        if(zmax < cone->zmax)zmax = cone->zmax;
    }
}

void LinkedCells::computeZoneForElbow(std::vector< std::shared_ptr<Elbow> >& elbows, double time) {
    for(auto& elbow : elbows) {
        elbow->Zone(time);
        if(xmin > elbow->xmin)xmin = elbow->xmin;
        if(ymin > elbow->ymin)ymin = elbow->ymin;
        if(zmin > elbow->zmin)zmin = elbow->zmin;
        if(xmax < elbow->xmax)xmax = elbow->xmax;
        if(ymax < elbow->ymax)ymax = elbow->ymax;
        if(zmax < elbow->zmax)zmax = elbow->zmax;
    }
}

void LinkedCells::computeZoneForCuboid( std::vector< std::shared_ptr<Cuboid> >& cuboids, double time) {
    for(auto& cuboid : cuboids) {
        cuboid->Zone(time);
        if(xmin > cuboid->xmin)xmin = cuboid->xmin;
        if(ymin > cuboid->ymin)ymin = cuboid->ymin;
        if(zmin > cuboid->zmin)zmin = cuboid->zmin;
        if(xmax < cuboid->xmax)xmax = cuboid->xmax;
        if(ymax < cuboid->ymax)ymax = cuboid->ymax;
        if(zmax < cuboid->zmax)zmax = cuboid->zmax;
    }
}

double LinkedCells::computeRmax(std::vector< std::shared_ptr<Lattice> >& lattices) {
    double Rmax = 0, R;
    for(auto& lattice : lattices){
        R = lattice->RmaxSphScale();
        if(Rmax < R) Rmax = R;
    }
    return Rmax;
}


void LinkedCells::Compute(std::vector< std::shared_ptr<Plan> >& plans,
                          std::vector< std::shared_ptr<Disk> >& disks,
                          std::vector< std::shared_ptr<Cone> >& cones,
                          std::vector< std::shared_ptr<Elbow> >& elbows,
                          std::vector< std::shared_ptr<Cuboid> >& cuboids,
                          std::vector< std::shared_ptr<Lattice> >& lattices, double time) {

    initValue();
    computeZoneForPlan(plans, time);
    computeZoneForCone(cones, time);
    computeZoneForDisk(disks, time);
    computeZoneForCuboid(cuboids, time);
    computeZoneForElbow(elbows, time);
    double Rmax = computeRmax(lattices);

    xmin -= Rmax;
    ymin -= Rmax;
    zmin -= Rmax;
    xmax += Rmax;
    ymax += Rmax;
    zmax += Rmax;
    ax = 2.01*Rmax;
    ay = 2.01*Rmax;
    az = 2.01*Rmax;
    nx = (int)((xmax-xmin)/ax);
    if(nx == 0)nx = 1;
    ny = (int)((ymax-ymin)/ay);
    if(ny == 0)ny = 1;
    nz = (int)((zmax-zmin)/az);
    if(nz == 0)nz = 1;
    ax = (xmax-xmin)/nx;
    ay = (ymax-ymin)/ny;
    az = (zmax-zmin)/nz;
}

void LinkedCells::Export(FILE *ft) {
    fprintf(ft,"%e\t%e\t%e\n",xmin,ymin,zmin);
    fprintf(ft,"%e\t%e\t%e\n",xmax,ymax,zmax);
    fprintf(ft,"%e\t%e\t%e\n",ax,ay,az);
    fprintf(ft,"%d\t%d\t%d\n",nx,ny,nz);
}
