//reads in a geometry file and calculates bond lengths, angles, and oop angles

#include "molecule.h"
#include <cmath>

using namespace std;



int main(int argc, char *argv[]) 
{
    Molecule mol("geom.dat",0); //declar a molecule object mol that gets parameters from geom.dat

    double bond = mol.bond(0,1);

    printf("bond: %5.5f\n",bond);

    return 0; //standard command of main functions to exit smoothly
}

