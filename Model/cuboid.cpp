#include "cuboid.h"

#include <iostream>

Cuboid::Cuboid():Solid() {
    la = 0.25;
    Lo = 0.25;
    h= 0.5;
    ped = 0;
    bottom = nullptr;
    top = nullptr;
    Plan plan1;
    p1 = std::make_shared<Plan>(plan1);
    Plan plan2;
    p2 = std::make_shared<Plan>(plan2);
    Plan plan3;
    p3 = std::make_shared<Plan>(plan3);
    Plan plan4;
    p4 = std::make_shared<Plan>(plan4);

    nx = 0;
    ny = 0;
    nz = 1;
    this->base();
    this->updatePlans();

}

void Cuboid::Draw(bool isLineContainer) {
    updatePlans();
    p1->Draw(isLineContainer);
    p2->Draw(isLineContainer);
    p3->Draw(isLineContainer);
    p4->Draw(isLineContainer);
    if(bottom != nullptr) bottom->Draw(isLineContainer);
    if(top != nullptr) top->Draw(isLineContainer);
}

double Cuboid::ComputeScale() {
    double px,py,pz,zoom;
    this->base();
    px = x+h/2*nx+Lo/2*tx+la/2*sx;
    py = y+h/2*ny+Lo/2*ty+la/2*sy;
    pz = z+h/2*nz+Lo/2*tz+la/2*sz;
    zoom = sqrt(px*px+py*py+pz*pz);

    px = x-h/2*nx-Lo/2*tx-la/2*sx;
    py = y-h/2*ny-Lo/2*ty-la/2*sy;
    pz = z-h/2*nz-Lo/2*tz-la/2*sz;
    if(zoom < sqrt(px*px+py*py+pz*pz))
        zoom = sqrt(px*px+py*py+pz*pz);
    return zoom;
}


void Cuboid::setTop(bool activate) {
    std::cout << "SetTop " << activate << std::endl;
    if(activate) {
        Plan plan{};
        this->top = std::make_shared<Plan>(plan);
        this->updatePlans();
    } else {
        this->top.reset();
    }
}

void Cuboid::setBottom(bool activate){
    std::cout << "SetBottom " << activate << std::endl;
    if(activate) {
        Plan plan{};
        this->bottom = std::make_shared<Plan>(plan);
        this->updatePlans();
    }else {
        this->bottom.reset();
    }
}


void Cuboid::updateVelocityPlans(std::shared_ptr<Plan> p) {
    p->vx = vx;
    p->vy = vy;
    p->vz = vz;
    p->wx = wx;
    p->wy = wy;
    p->wz = wz;
    p->orx = orx;
    p->ory = ory;
    p->orz = orz;
}

void Cuboid::updatePlans() {
    updateVelocityPlans(p1);
    updateVelocityPlans(p2);
    updateVelocityPlans(p3);
    updateVelocityPlans(p4);
    if(top != nullptr) updateVelocityPlans(top);
    if(bottom != nullptr) updateVelocityPlans(bottom);

    p1->nx = sx;
    p1->ny = sy;
    p1->nz = sz;
    p1->tx = tx;
    p1->ty = ty;
    p1->tz = tz;
    p1->sx = -nx;
    p1->sy = -ny;
    p1->sz = -nz;
    p1->dt = la;
    p1->ds = h;
    p1->x = (x-sx*Lo/2.);
    p1->y = (y-sy*Lo/2.);
    p1->z = (z-sz*Lo/2.);

    p2->nx = -sx;
    p2->ny = -sy;
    p2->nz = -sz;
    p2->tx = tx;
    p2->ty = ty;
    p2->tz = tz;
    p2->sx = nx;
    p2->sy = ny;
    p2->sz = nz;
    p2->dt = la;
    p2->ds = h;
    p2->x = (x+sx*Lo/2.);
    p2->y = (y+sy*Lo/2.);
    p2->z = (z+sz*Lo/2.);

    p3->nx = tx;
    p3->ny = ty;
    p3->nz = tz;
    p3->tx = sx;
    p3->ty = sy;
    p3->tz = sz;
    p3->sx = nx;
    p3->sy = ny;
    p3->sz = nz;
    p3->dt = Lo;
    p3->ds = h;
    p3->x = (x-tx*la/2.);
    p3->y = (y-ty*la/2.);
    p3->z = (z-tz*la/2.);

    p4->nx = -tx;
    p4->ny = -ty;
    p4->nz = -tz;
    p4->tx = sx;
    p4->ty = sy;
    p4->tz = sz;
    p4->sx = -nx;
    p4->sy = -ny;
    p4->sz = -nz;
    p4->dt = Lo;
    p4->ds = h;
    p4->x = (x+tx*la/2.);
    p4->y = (y+ty*la/2.);
    p4->z = (z+tz*la/2.);

    if(bottom != nullptr){
        bottom->nx = nx;
        bottom->ny = ny;
        bottom->nz = nz;
        bottom->tx = sx;
        bottom->ty = sy;
        bottom->tz = sz;
        bottom->sx = -tx;
        bottom->sy = -ty;
        bottom->sz = -tz;
        bottom->dt = Lo;
        bottom->ds = la;
        bottom->x = x-nx*h/2.;
        bottom->y = y-ny*h/2.;
        bottom->z = z-nz*h/2.;
    }
    if(top != nullptr){
        top->nx = -nx;
        top->ny = -ny;
        top->nz = -nz;
        top->tx = sx;
        top->ty = sy;
        top->tz = sz;
        top->sx = tx;
        top->sy = ty;
        top->sz = tz;
        top->dt = Lo;
        top->ds = la;
        top->x = x+nx*h/2.;
        top->y = y+ny*h/2.;
        top->z = z+nz*h/2.;
    }
}

void Cuboid::Zone(double time) {
    double xe,ye,ze;
    p1->Zone(time);
    p2->Zone(time);
    xmax = -10000;
    ymax = -10000;
    zmax = -10000;
    xmin = 10000;
    ymin = 10000;
    zmin = 10000;
    xe = p1->xmin;
    ye = p1->ymin;
    ze = p1->zmin;
    if(xmax < xe)xmax = xe;
    if(ymax < ye)ymax = ye;
    if(zmax < ze)zmax = ze;
    if(xmin > xe)xmin = xe;
    if(ymin > ye)ymin = ye;
    if(zmin > ze)zmin = ze;
    xe = p1->xmax;
    ye = p1->ymax;
    ze = p1->zmax;
    if(xmax < xe)xmax = xe;
    if(ymax < ye)ymax = ye;
    if(zmax < ze)zmax = ze;
    if(xmin > xe)xmin = xe;
    if(ymin > ye)ymin = ye;
    if(zmin > ze)zmin = ze;

    xe = p2->xmin;
    ye = p2->ymin;
    ze = p2->zmin;
    if(xmax < xe)xmax = xe;
    if(ymax < ye)ymax = ye;
    if(zmax < ze)zmax = ze;
    if(xmin > xe)xmin = xe;
    if(ymin > ye)ymin = ye;
    if(zmin > ze)zmin = ze;
    xe = p2->xmax;
    ye = p2->ymax;
    ze = p2->zmax;
    if(xmax < xe)xmax = xe;
    if(ymax < ye)ymax = ye;
    if(zmax < ze)zmax = ze;
    if(xmin > xe)xmin = xe;
    if(ymin > ye)ymin = ye;
    if(zmin > ze)zmin = ze;
}


void Cuboid::Export(FILE *ft, int npl) {
    this->base();
    this->updatePlans();

    //TODO add associated periodic plans by number ;-)

    p1->ExportWithoutBaseComputing(ft);
    p2->ExportWithoutBaseComputing(ft);
    p3->ExportWithoutBaseComputing(ft);
    p4->ExportWithoutBaseComputing(ft);

    if(top != nullptr) top->ExportWithoutBaseComputing(ft);
    if(bottom != nullptr) bottom->ExportWithoutBaseComputing(ft);
}
