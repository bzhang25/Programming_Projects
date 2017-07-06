#include <iostream>
#include "../molecule_analysis/molecule.h"
#include "../extra_files/masses.h"
#include <cmath>

//Uses Eigen package (canned library) that is used to manipulate matrix types
#include "../extra_files/Eigen/Dense" 
#include "../extra_files/Eigen/Eigenvalues"
#include "../extra_files/Eigen/Core"

#define _hartoJ 4.3597443e-18
#define _amutokg (1/1.6605389e-27)
#define _bohrtom (1/5.2917721e-11)
#define _c 2.99792458e10
#define _pi acos(-1.0)

//defines new type called matrix that's dynamically allocated and contains only doubles 
typedef Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> Matrix; 

using namespace std;


int main(int argc, char *argv[]) 
{

    FILE *hessian; //define a pointer to FILE object 
    int natom; //defines integer natom

    hessian = fopen ("hessian.dat", "r"); //returns a pointer to FILE object called hessian

    Molecule mol("geom.dat",0); //declar a molecule object mol that gets parameters from geom.dat
   // printf("%d %d %d \n", mol.zvals[0], mol.zvals[1], mol.zvals[2]);

    printf("input geom:\n");
    mol.print_geom();
    fscanf(hessian, "%d", &natom); //fscanf reads in a regex from pointer to FILE hessian and saves it to the address of natom

    //test to see if the number of atoms in the geom.dat and hessian.dat file is consistent
    if (mol.natom!=natom) printf("Warning: number of atoms inconsistent between hessian and geom input files\n");

    //allocate memory for the hessian matrix made of doubles, by defining H as ** we can call H in 2 dimensions  
    double **H = new double*[3*natom]; //the size is 3N for the x,y,z coordinates of each atom
    Matrix H_M(3*natom,3*natom); //define mass-weighted hessian matrix object

    for(int i=0; i < 3*natom; i++){ 
        H[i] = new double[3*natom];
    }
    
    //for loops will go through each line in hessian.dat in order that contains format specified 
    for(unsigned int i=0; i < 3*natom; i++) { 
        for(unsigned int j=0; j < natom; j++) {
            
            //puts hessian.dat in a square matrix 3N by 3N. First three rows read correspond to first row of square matrix, etc.
            fscanf(hessian, "%lf %lf %lf", &H[i][j*3], &H[i][j*3+1],&H[i][j*3+2]); //1st row in places j=0-2, 2nd in places j=3-5, 3rd in places j=6-8
        }
    }

    //i,j loop over the number of atoms, k, l loop over number of coordinates for each atom
    for(unsigned int i=0; i < natom; i++) { 
        for(unsigned int j=0; j < natom; j++) {
            for(unsigned int k=3*i; k < (3*i+3); k++) { 
                for(unsigned int l=3*j; l < (3*j+3); l++) {
                    //printf("value: %lf mass i: %lf mass j: %lf i: %d j: %d \n", H[k][l], mass[(int) mol.zvals[i]],  mass[(int) mol.zvals[j]],i,j);
  //                  printf("value: %lf zvals i: %d zvals j: %d i: %d j: %d \n", H[k][l], int (mol.zvals[i]),  int (mol.zvals[j]),i,j);
                        
            
                    H_M(k,l) = H[k][l]/sqrt(mass[(int) mol.zvals[i]]*mass[(int) mol.zvals[j]]);
                }
            }
        }
    }

    cout << "Weighted Hessian Matrix: \n";
    cout << H_M << endl;

    Eigen::SelfAdjointEigenSolver<Matrix> solver(H_M);
    Matrix evecs = solver.eigenvectors();
    Matrix evals = solver.eigenvalues(); //automatically puts in a sorted array smallest first

    cout << "Eigenvalues (hartree/amu-bohr^2):\n";
    cout << evals << endl;

    cout << "Frequencies(cm^-1):\n";
    //cout << pow(evals, 0.5)*8065.54446 << endl;
    for (int i=0; i<3*natom; i++) {
        cout << sqrt(evals(i)*_hartoJ*_amutokg*_bohrtom*_bohrtom)*(1/(2*_pi))*(1/_c) << endl;
    }
    //frees allocated block of memory for H and H_M
    for (int i=0; i<3*natom; i++) {
        delete[] H[i];
    }
    delete[] H;

    return 0;
}  
