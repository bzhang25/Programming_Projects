//since molecule already initializes initial variables no need to do here
//A script that prepares a water molecule, print coorginates, translate along x-axis 
// and prints coordinates again

#include "molecule.h"

using namespace std;

int main(int argc, char *argv[]) 
//argc (argument count) is number of arguments passed to program, if no parameters still is one from program
//argv points to string array (argument vector)- 1D of function arguments
//argc is number of strings pointed to by argv
//needed if passing arguments to program, if program doesn't need arguments passes, can leave blank  
{
    Molecule h2o("geom.dat",0); //declar a molecule object h2o

    printf("your geometry is:\n");
    h2o.print_geom(); //calls function from Molecule class defined in molecule.cc
    h2o.translate(5,0,0); //calls function that moves x by 5, y by 0, z by 0
    printf("after translation,your geometry is:\n");
    h2o.print_geom(); //prints geom again

    return 0; //standard command of main functions to exit smoothly
}

/* 
to compile this program, 
c++ -c molecule.cc -> compiles molecule.cc into machine code molecule.o
c++ -c water.cc -> compiles water.cc into machine code water.o
c++ water.o molecule.o -o water, makes a final  executable water from linking object (machine codes)
*/
