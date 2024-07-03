#include "velocity.h"

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
