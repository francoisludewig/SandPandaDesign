#include "setup.h"

const double PI  =3.141592653589793238463;

Setup::Setup(std::vector< std::shared_ptr<Lattice> > *lattices) : lattices(lattices) {}

double Setup::computeTimestep() {
    double meff = 1000000;
    for(auto& lattice : *lattices) {
        if(lattice->massMin() < meff)
            meff = lattice->massMin();
    }
    timeStep = sqrt(PI*PI*meff/normalStiffness+meff*log(resitutionCoefficient)*log(resitutionCoefficient)/normalStiffness) / 100.0;
    return timeStep;
}
