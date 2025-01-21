#include "velocity.h"
#include<cmath>

Velocity::Velocity() {
    A0 = 0;
    A1 = 0;
    w = 0;
    p = 0;
}

void Velocity::ReadFromFile(FILE *ft)
{
    fscanf_s(ft,"%lf\t%lf\t%lf\t%lf\n",&A0,&A1,&w,&p);
}

void Velocity::Export(FILE *ft) {
    fprintf(ft,"%lf\t%lf\t%lf\t%lf\n",A0,A1,w,p);
}


double Velocity::valueat(double t) {
    return(A0+A1*w*sin(w*t+p));
}
