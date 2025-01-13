#include "lattice.h"

#include <QOpenGLFunctions>
#include <GL/GLU.h>

Lattice::Lattice() {
    N = 0;
    r0 = 0.01;
    r1 = 0.01;
    rmax = 0.01;
    dist = false;
    rdm = false;
    rho = 2500;
    xmin = -0.5;
    ymin = -0.5;
    zmin = -0.5;
    xmax = 0.5;
    ymax = 0.5;
    zmax = 0.5;
    V = 0;
    W = 0;
    boxes = false;
    cyd = false;
    solid = true;
    nx = 1;ny = 0;nz = 0;
    tx = 0;ty = 1;tz = 0;
    sx = 0;sy = 0;sz = 1;
    x0 = 0;y0 = 0;z0 = 0;
    bte = nullptr;
    cyde = nullptr;
}

void Lattice::LinkedToBoxe(std::shared_ptr<Cuboid> &cuboid) {
    boxes = true;
    cyd = false;
    solid = false;
    bte = cuboid;
}

void Lattice::UpDateFromBoxe(){
    nx = bte->tx;ny = bte->ty;nz = bte->tz;
    tx = bte->sx;ty = bte->sy;tz = bte->sz;
    sx = bte->nx;sy = bte->ny;sz = bte->nz;
    x0 = bte->x;y0 = bte->y;z0 = bte->z;

    xmin = -bte->la/2;
    xmax = +bte->la/2;
    ymin = -bte->Lo/2;
    ymax = +bte->Lo/2;
    zmin = -bte->h/2;
    zmax = +bte->h/2;
}

void Lattice::Unlink() {
    // Reset base to default value
    nx = 1;ny = 0;nz = 0;
    tx = 0;ty = 1;tz = 0;
    sx = 0;sy = 0;sz = 1;
    x0 = 0;y0 = 0;z0 = 0;
}


void Lattice::LinkedToCone(std::shared_ptr<Cone> & co){
    cyd = true;
    cyde = co;
    solid = false;
}

void Lattice::UpDateFromCone(){
    double r;
    nx = cyde->tx;ny = cyde->ty ;nz = cyde->tz ;
    tx = cyde->sx;ty = cyde->sy ;tz = cyde->sz ;
    sx = cyde->nx;sy = cyde->ny ;sz = cyde->nz ;
    x0 = cyde->x;y0 = cyde->y ;z0 = cyde->z ;

    zmin = -cyde->h /2;
    zmax = +cyde->h /2;

    r = cyde->r0 ;
    if(r > cyde->r1 ) r = cyde->r1 ;
    xmin = -r/sqrt(2);
    ymin = -r/sqrt(2);
    xmax = +r/sqrt(2);
    ymax = +r/sqrt(2);
}

void Lattice::Radius(){
    gr.clear();
    rmax = 0.;
    const double PI = 3.141592;
    if(dist){
        for(int i = 0 ; i < N ; i++){
            Granule g;
            if(r1 != 0){
                do{
                    g.r = r0 + r1*(cos(2*PI*(((double)(rand()%10000))/10000.)))*sqrt(-2*log((((double)(rand()%10000))/10000.)));
                }while(g.r > r0+3*r1 || g.r < r0-3*r1);
            }
            else
                g.r= r0;

            if(rmax < g.r)rmax=g.r;
            g.rho = rho;
            g.massInertia();
            gr.push_back(g);
        }
    }
    else{
        for(int i = 0 ; i < N ; i++){
            Granule g;
            g.r = r0+((double)(rand()%10000)/10000.)*(r1-r0);
            if(rmax < g.r)rmax=g.r;
            g.rho = rho;
            g.massInertia();
            gr.push_back(g);
        }
    }
}


void Lattice::Position(int fluid){
    if(boxes)
        this->UpDateFromBoxe();
    if(cyd)
        this->UpDateFromCone();

    double dila = 1+fluid;
    double xl,yl,zl;
    Granule *g;
    Granule *h;
    if(!rdm){
        int Nx = (int)((xmax-xmin)/2./(rmax*dila));
        int Ny = (int)((ymax-ymin)/2./(rmax*dila));
        int Nz = (int)((zmax-zmin)/2./(rmax*dila));
        if(Nx*Ny*Nz > N){
            for(int i = 0 ; i < Nz ; i++){
                for(int j = 0 ; j < Ny ; j++){
                    for(int k = 0 ; k < Nx ; k++){
                        if(k+j*Nx+i*Nx*Ny < N){
                            g = &gr[k+j*Nx+i*Nx*Ny];
                            xl = xmin + (rmax*dila)+k*2*(rmax*dila);
                            yl = ymin + (rmax*dila)+j*2*(rmax*dila);
                            zl = zmin + (rmax*dila)+i*2*(rmax*dila);
                            g->x = x0 + xl*nx+yl*tx+zl*sx;
                            g->y = y0 + xl*ny+yl*ty+zl*sy;
                            g->z = z0 + xl*nz+yl*tz+zl*sz;
                        }
                        else{
                            i = Nz+1;
                            j = Ny+1;
                            k = Nx+1;
                        }
                    }
                }
            }
        }
        else{
            if(N != 0){
                //int choice = NSRunAlertPanel(@"PreLuGa Alert", @"The Volume cannot contains the particules", @"OK", nil, nil);
                //NSLog(@"Error : the defined volume is too small to place all granule (Lattice Mode %d)",choice);
            }
        }
    }
    else{
        double Vt = (xmax-xmin)*(ymax-ymin)*(zmax-zmin);
        double Vg = 0;
        for(int i = 0 ; i < N ; i++){
            g = &gr[i];
            Vg += g->m/g->rho*pow(dila,3);
        }
        if(Vg/Vt < 0.4){
            double x,y,z;
            int ok;
            for(int i = 0 ; i < N ; i++){
                g = &gr[i];
                do{
                    ok = 0;
                    //NSLog(@"Generation for %d",i);
                    xl = xmin + (double)(rand()%10000)/10000.*(xmax-xmin - 2*g->r) + g->r;
                    yl = ymin + (double)(rand()%10000)/10000.*(ymax-ymin - 2*g->r) + g->r;
                    zl = zmin + (double)(rand()%10000)/10000.*(zmax-zmin - 2*g->r) + g->r;
                    x = x0 + xl*nx+yl*tx+zl*sx;
                    y = y0 + xl*ny+yl*ty+zl*sy;
                    z = z0 + xl*nz+yl*tz+zl*sz;
                    for(int j = 0 ; j < i ; j++){
                        h = &gr[j];
                        if(sqrt((x-h->x)*(x-h->x)+(y-h->y)*(y-h->y)+(z-h->z)*(z-h->z)) < (g->r+h->r)*(dila)){
                            ok = 1;
                            j = N+1;
                        }
                    }
                }while(ok != 0);
                g->x = x;
                g->y = y;
                g->z = z;
            }
        }
        else{
            if(N != 0){
                //int choice = NSRunAlertPanel(@"PreLuGa Alert", @"The Volume cannot contains the particules", @"OK", nil, nil);
                //NSLog(@"Error : the defined volume is too small to place all granule (Lattice Mode %d)",choice);
            }
        }
    }
}

void Lattice::Velocity(){
    Granule *g;
    double norme,x,y,z;
    for(int i = 0 ; i < N ; i++){
        g = &gr[i];
        x = (double)(rand()%10000)/10000. -0.5;
        y = (double)(rand()%10000)/10000. -0.5;
        z = (double)(rand()%10000)/10000. -0.5;
        norme = sqrt(x*x+y*y+z*z);
        g->vx = x/norme*V;
        g->vy = y/norme*V;
        g->vz = z/norme*V;
        x = (double)(rand()%10000)/10000. -0.5;
        y = (double)(rand()%10000)/10000. -0.5;
        z = (double)(rand()%10000)/10000. -0.5;
        norme = sqrt(x*x+y*y+z*z);
        g->wx = x/norme*W;
        g->wy = y/norme*W;
        g->wz = z/norme*W;
    }
}

void Lattice::draw(int color) {
    Granule *g;
    if(color == 0)
        glColor3f(0, 0, 1);
    else
        glColor3f(1,0.25,0);

    for(int i = 0 ; i < N ; i++){
        g = &gr[i];
        glPushMatrix();
        glTranslated(g->y, g->z ,-g->x);
        glScaled(g->r, g->r, g->r);
        GLUquadric *glQ = gluNewQuadric();
        gluQuadricOrientation(glQ, GLU_OUTSIDE);
        gluSphere(glQ, 1, 20, 10);
        glPopMatrix();
    }
}

double Lattice::ComputeScale(){
    double zoom;
    double x,y,z;
    x = x0 + xmin*nx + ymin*tx + zmin*sx;
    y = y0 + xmin*ny + ymin*ty + zmin*sy;
    z = z0 + xmin*nz + ymin*tz + zmin*sz;
    zoom = sqrt(x*x+y*y+z*z);

    x = x0 + xmax*nx + ymax*tx + zmax*sx;
    y = y0 + xmax*ny + ymax*ty + zmax*sy;
    z = z0 + xmax*nz + ymax*tz + zmax*sz;

    if(zoom <  sqrt(x*x+y*y+z*z))
        zoom =   sqrt(x*x+y*y+z*z);
    /*
    zoom = sqrt(xmin*xmin+ymin*ymin+zmin*zmin);
    if(zoom <  sqrt(xmax*xmax+ymax*ymax+zmax*zmax))
        zoom =   sqrt(xmax*xmax+ymax*ymax+zmax*zmax);
     */
    return zoom;
}
