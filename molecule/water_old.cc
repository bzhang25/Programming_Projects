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
    Molecule h2o; //declar a molecule object h2o

    h2o.natom = 3; //defines natom to be 3 
    h2o.charge = 0; //defines charge to be 0
    h2o.zvals = new int[h2o.natom]; //new is dynamically allocating natom integers of memory to address pointed to by zvals
                                    //later on need to free this allocated block of memory with delet[]
    h2o.geom = new double* [h2o.natom]; //allocating the outmost pointer to pointer
                                        //like how many addresses needed - natoms
    for(int i=0; i < h2o.natom; i++)
        h2o.geom[i] = new double[3]; //since h2o.geom is a pointer, it allocates three blocks of double memory to the address pointed to by pointer geom[i]

    h2o.zvals[0] = 8; //defines the value at address pointed to by zvals offset by 0 
    h2o.zvals[1] = 1; //defines the value at address pointed to by zvals offset by 1
    h2o.zvals[2] = 1; //defines the value at address pointed to by zvals offset by 2 
    h2o.geom[0][0] =  0.000000000000; //geom[0] points to the pointer of geom[0][0], geom[0][0] is the
                                    //value of the pointer to pointer, and the pointer, both offset by 0
    h2o.geom[0][2] = -0.122368916506;
    h2o.geom[1][0] =  0.000000000000;
    h2o.geom[1][1] =  1.414995841403;
    h2o.geom[1][2] =  0.971041753535;
    h2o.geom[2][0] =  0.000000000000;
    h2o.geom[2][1] = -1.414995841403;
    h2o.geom[2][2] =  0.971041753535;

    printf("your geometry is:\n");
    h2o.print_geom(); //calls function from Molecule class defined in molecule.cc
    h2o.translate(5,0,0); //calls function that moves x by 5, y by 0, z by 0
    printf("after translation,your geometry is:\n");
    h2o.print_geom(); //prints geom again

    delete[] h2o.zvals; //frees this allocated block of memory
    for (int i=0; i < h2o.natom; i++)
        delete[] h2o.geom[i]; //frees allocated block of memory pointed to by pointer geom[i]
    delete[] h2o.geom; //frees allocated block of pointer to pointer

    return 0; //standard command of main functions to exit smoothly
}

/* 
to compile this program, 
c++ -c molecule.cc -> compiles molecule.cc into machine code molecule.o
c++ -c water.cc -> compiles water.cc into machine code water.o
c++ water.o molecule.o -o water, makes a final  executable water from linking object (machine codes)
*/
