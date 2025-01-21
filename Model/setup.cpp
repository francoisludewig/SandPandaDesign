#include "setup.h"

const double PI  =3.141592653589793238463;

Setup::Setup(std::vector< std::shared_ptr<Lattice> > *lattices, std::shared_ptr<LinkedCells> linkedCells) : lattices(lattices), linkedCells(linkedCells) {}

double Setup::computeTimestep() {
    double meff = 1000000;
    for(auto& lattice : *lattices) {
        if(lattice->massMin() < meff)
            meff = lattice->massMin();
    }
    timeStep = sqrt(PI*PI*meff/normalStiffness+meff*log(resitutionCoefficient)*log(resitutionCoefficient)/normalStiffness) / 100.0;
    return timeStep;
}

void Setup::Export(std::string &directory) {
    char filename[1024];
    // Exportation du fichier container.txt
    sprintf(filename,"%s/data.txt",directory.c_str());
    printf("%s\n",filename);
    FILE *ft = fopen(filename,"w");

    // Gravity
    fprintf(ft,"%e\t%e\t%e\n",gravityX,gravityY,gravityZ);
    fprintf(ft,"%e\t%e\t%e\t%e\n",0.0,0.0,0.0,0.0);
    fprintf(ft,"%e\t%e\t%e\t%e\n",gWxA0,gWxA1,gWxW,gWxP);
    fprintf(ft,"%e\t%e\t%e\t%e\n",gWyA0,gWyA1,gWyW,gWyP);
    fprintf(ft,"%e\t%e\t%e\t%e\n",gWzA0,gWzA1,gWzW,gWzP);
    fprintf(ft,"%e\n",gravityAcceleration);


    // Data Setup

    fprintf(ft,"%e\t%e\t%e\n",timeStep,0.0,duration);
    fprintf(ft,"%d\n",Nsp);
    fprintf(ft,"%d\n",isTangentialDynamicModel ? 0 : 1);
    if(isTangentialDynamicModel != 0)
        fprintf(ft,"%e\t%e\t%e\n",resitutionCoefficient,dynamicFrictionCoefficient, dynamicFrictionCoefficient, normalStiffness);
    else
        fprintf(ft,"%e\t%e\t%e\t%e\n",resitutionCoefficient,staticFrictionCoefficient,dynamicFrictionCoefficient,normalStiffness);
    fprintf(ft,"%e\t%e\n",captureTimeStep, startingTime);
    //Export Linked Cells !
    linkedCells->Export(ft);



    fflush(ft);
    fclose(ft);
}
