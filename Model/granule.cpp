#include "granule.h"

#include <cmath>

Granule::Granule() {
    x = 0;
    y = 0;
    z = 0;
    r = 0.1;
    vx = 0;
    vy = 0;
    vz = 0;
    wx = 0;
    wy = 0;
    wz = 0;
    q0 = 1;
    q1 = 0;
    q2 = 0;
    q3 = 0;
    rho = 2500.;
}

void Granule::massInertia(){
    const double PI = 3.141592;
    m = 4./3.*PI*pow(r,3)*rho;
    I = 2./5.*m*r*r;
}

void Granule::exportToFile(FILE *ft, int sp){
    fprintf(ft,"%e\t%e\t%e\n",x,y,z);
    fprintf(ft,"%e\t%e\t%e\t%e\n",0.0,0.0,0.0,0.0);
    fprintf(ft,"%e\t%e\t%e\n",vx,vy,vz);
    fprintf(ft,"%e\t%e\t%e\n",wx,wy,wz);
    fprintf(ft,"%e\t%e\t%e\t%d\t%d\n",r,m,I,sp,-9);
}
