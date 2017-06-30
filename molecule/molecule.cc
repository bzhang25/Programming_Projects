//this is the file that actually defines the functions in the Molecule class 

#include "molecule.h" //includes the initial declaration of the class 
#include <cstdio>

//these are need for reading in a file
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cassert>

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

Molecule::Molecule(const char *filename, int q) //constructor takes in constant variable point to filename mol charge as arguments
                                                //since takes two arguments here also has to take in molecule.h
                                                //we are also going to read in a file to extract geom information from file so don't have to manually do it
                                                //this allows to initialize our variable values 
{
    //initializing initial varible values
    //if do this here, don't have to do in water.cc - see water_old.cc for meaning of definitions
    charge = q;

    std::ifstream is(filename); //opens filename
    assert(is.good());

    is >> natom; //reads the number of atoms from filename

    //allocating space
    zvals = new int[natom];
    geom = new double* [natom];
    for(int i=0; i < natom; i++)
        geom[i] = new double[3];

    for(unsigned int i=0; i < natom; i++)
        is >> zvals[i] >>geom[i][0]>>geom[i][1]>>geom[i][2]; //reads zval, x,y,z line by line and assigns values

    is.close();
} 

//"overload" - same function name perform different things- here the constructor takes in natom instead of reading it from the file
//need to look into more

Molecule::~Molecule()//frees the memory allocated initially by constructor
{
    delete[] zvals;
    for(int i=0; i < natom; i++)
        delete[] geom[i];
    delete[] geom;
}
