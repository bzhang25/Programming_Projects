//this is the file that actually defines the functions in the Molecule class 

#include "molecule.h" //includes the initial declaration of the class 
#include "masses.h"
#include <cstdio>

//these are need for reading in a file
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cassert>

//for math functions
#include <cmath>

//Uses Eigen package (canned library) that is used to manipulate matrix types
#include "Eigen/Dense" 
#include "Eigen/Eigenvalues"
#include "Eigen/Core"

#define bohrtoang 0.52917721067
#define bohrtocm  5.2917721067e-9
#define amutogram 1.660539040e-24
#define _h 6.62607004e-27 //(cm^2 g s^-1)
#define _c 2.99792458e10 //(cm/s)
#define _pi acos(-1.0) 

//defines new type called matrix that's dynamically allocated and contains only doubles 
typedef Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> Matrix; 

void Molecule::print_geom() //use prefix Molecule to explicitly define print_geom function for the Molecule class 
{
    for(int i=0; i < natom; i++)
        printf("%lf %8.5f %8.5f %8.5f\n", zvals[i], geom[i][0], geom[i][1],geom[i][2]);
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

double * Molecule::com()
{

    double x = 0.0;
    double y = 0.0;
    double z = 0.0;
    double m = 0.0;
    
    
    for(int i=0; i < natom; i++){
        m += mass[(int) zvals[i]];
        x += mass[(int) zvals[i]]*geom[i][0];
        y += mass[(int) zvals[i]]*geom[i][1];
        z += mass[(int) zvals[i]]*geom[i][2];
    } 

    double X = x/m;
    double Y = y/m;
    double Z = z/m;
    
    double *cor = new double[3];

    cor[0] = X; 
    cor[1] = Y; 
    cor[2] = Z; 
    
    return cor;
}

void Molecule::moi()
{

    Matrix I(3,3);

    for(int k=0; k < natom; k++)
    {
        I(0,0) += mass[(int) zvals[k]]*(geom[k][1]*geom[k][1]+geom[k][2]*geom[k][2]);
        I(1,1) += mass[(int) zvals[k]]*(geom[k][0]*geom[k][0]+geom[k][2]*geom[k][2]);
        I(2,2) += mass[(int) zvals[k]]*(geom[k][1]*geom[k][1]+geom[k][0]*geom[k][0]);

        I(0,1) += mass[(int) zvals[k]]*geom[k][0]*geom[k][1];  
        I(0,2) += mass[(int) zvals[k]]*geom[k][0]*geom[k][2];  
        I(1,2) += mass[(int) zvals[k]]*geom[k][2]*geom[k][1];  
    
    }
    
    I(1,0) = I(0,1);
    I(2,0) = I(0,2);
    I(2,1) = I(1,2);

    printf("Moment of Inertia Tensor in amu bohr^2):\n");

    cout << I << endl;

    //compute eigenvalues and eigenvectors of moment of inertia tensor
    Eigen::SelfAdjointEigenSolver<Matrix> solver(I);
    Matrix evecs = solver.eigenvectors();
    Matrix evals = solver.eigenvalues(); //automatically puts in a sorted array smallest first

    printf("Moments of inertia(amu bohr^2):\n");
    cout << evals << endl;

    printf("Moments of inertia(amu AA^2):\n");
    cout << evals*bohrtoang*bohrtoang <<endl;

    printf("Moments of inertia(g cm^2):\n");
    cout << evals*bohrtocm*bohrtocm*amutogram << endl;
    
    if (natom==0) printf("Molecule is diatomic\n");
    else if (evals(0) < 1.0e-4) printf("Molecule is linear\n");
    else if ((evals(1) - evals(0)) < 1.0e-4 && (evals(2) - evals(0)) < 1.0e-4) printf("Molecule is a spherical top\n");
    else if ((evals(1) - evals(0)) < 1.0e-4 && (evals(2)-evals(0)) > 1.0e-4) printf("Molecule is an oblate top\n");
    else if ((evals(2) - evals(1)) < 1.0e-4 && (evals(2)-evals(0)) > 1.0e-4) printf("Molecule is a prolate top\n");
    else printf("Molecule is an asymmetric top\n");

    Matrix evals_gcm = evals*bohrtocm*bohrtocm*amutogram;

    double A = _h/(8*_pi*_pi*_c*evals_gcm(0));
    double B = _h/(8*_pi*_pi*_c*evals_gcm(1));
    double C = _h/(8*_pi*_pi*_c*evals_gcm(2));
    
    printf("Rotational constants in cm^-1\n");
    printf("A: %5.5f \n", A); 
    printf("B: %5.5f \n", B); 
    printf("C: %5.5f \n", C); 

    printf("Rotational constants in MHz\n");
    printf("A: %5.5f \n", A*_c*1.0e-6); 
    printf("B: %5.5f \n", B*_c*1.0e-6); 
    printf("C: %5.5f \n", C*_c*1.0e-6); 
}


Molecule::Molecule(const char *filename, int q) //constructor takes in constant variable point to filename and charge as arguments
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
    zvals = new double[natom];
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
