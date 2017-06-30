//this is the file that actually defines the functions in the Molecule class 

#include "molecule.h" //includes the initial declaration of the class 
#include <cstdio>

//these are need for reading in a file
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cassert>

//for math functions
#include <cmath>

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

double Molecule::bond(int atom1, int atom2) //defines a function to calculate bond distances between atoms
{
    
    double bond =  sqrt(pow((geom[atom1][0]-geom[atom2][0]),2.0) 
                       +pow((geom[atom1][1]-geom[atom2][1]),2.0) 
                       +pow((geom[atom1][2]-geom[atom2][2]),2.0));

    return bond;
}

double Molecule::unit(int cart, int atom1, int atom2) //function that computes components of unit vectors, where cart = 0 for x, 1 for y, and 2 for z
{

    return -(geom[atom1][cart]-geom[atom2][cart])/bond(atom1,atom2);
}

double Molecule::angle(int atom1, int atom2, int atom3)//function that returns angles between three atoms
{

    return acos(unit(0,atom2,atom1)*unit(0,atom2,atom3) + unit(1,atom2,atom1)*unit(1,atom2,atom3) + unit(2,atom2,atom1)*unit(2,atom2,atom3));
}

double * Molecule::crossproduct(int a, int b, int c)
{

    double *e = new double[3];

    //cross product of two vectors
    e[0] = unit(1,b,a)*unit(2,b,c) - unit(2,b,a)*unit(1,b,c);
    e[1] = unit(2,b,a)*unit(0,b,c) - unit(0,b,a)*unit(2,b,c);
    e[2] = unit(0,b,a)*unit(1,b,c) - unit(1,b,a)*unit(0,b,c);
    
    return e;

}

double Molecule::oop(int i, int j, int k, int l)//function that returns the oop angles between 4 atoms
{

    double * e = crossproduct(j,k,l);
    double ejkl_x=e[0], ejkl_y=e[1], ejkl_z = e[2]; 
    double theta = (ejkl_x*unit(0,k,i) + ejkl_y*unit(1,k,i) + ejkl_z*unit(2,k,i))/sin(angle(j,k,l));

    //if statements due to numerical percision needs for asin()
    if (theta > 1.0) theta = asin(1.0);
    else if (theta < -1.0) theta = asin (-1.0);
    else theta = asin(theta);
    
    return theta;
}

double Molecule::torsion(int i, int j, int k, int l)//function that returns the oop angles between 4 atoms
{

    double * eijk = crossproduct(i,j,k);
    double * ejkl = crossproduct(j,k,l);
    double eijk_x=eijk[0], eijk_y=eijk[1], eijk_z = eijk[2]; 
    double ejkl_x=ejkl[0], ejkl_y=ejkl[1], ejkl_z = ejkl[2]; 
    
    double tau = (ejkl_x*eijk_x + ejkl_y*eijk_y + ejkl_z*eijk_z)/(sin(angle(j,k,l))*sin(angle(i,j,k)));

    //if statements due to numerical percision needs for asin()
    if (tau > 1.0) tau = acos(1.0);
    else if (tau < -1.0) tau = acos(-1.0);
    else tau = acos(tau);

    //compute the sign of the torsion angle
    double cross_x = eijk_y*ejkl_z - eijk_z*ejkl_y;
    double cross_y = eijk_z*ejkl_x - eijk_x*ejkl_z;
    double cross_z = eijk_x*ejkl_y - eijk_y*ejkl_x;
    double norm = cross_x*cross_x + cross_y*cross_y + cross_z*cross_z;
    
    cross_x /= norm;
    cross_y /= norm;
    cross_z /= norm;
    
    double sign = 1.0;
    double dot = cross_x*unit(0,j,k)+cross_y*unit(1,j,k)+cross_z*unit(2,j,k);
    if(dot < 0.0) sign = -1.0;
    
    return tau*sign;
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
