//this is the file that actually defines the functions in the Molecule class 

#include "molecule.h" //includes the initial declaration of the class 
#include <cstdio>

void Molecule::print_geom() //use prefix Molecule to explicitly define print_geom function for the Molecule class 
{
    for(int i=0; i < natom; i++)
        printf("%d %8.5f %8.5f %8.5f\n", zvals[i], geom[i][0], geom[i][1],geom[i][2]);
        //iterate over number of atoms, print the zval, x, y, z coordinates 
}

void Molecule::translate(double x, double y, double z) //takes the x,y,z double precision floats as input
{
    for(int i=0; i < natom; i++) {
        geom[i][0] += x;
        geom[i][1] += y;
        geom[i][2] += z;
        // for every atom, move each x,y,z coordinate by amount indicated in the input
    }
}

Molecule::Molecule(){} //defines empty constructor
Molecule::~Molecule(){} //defines empty deconstructor
