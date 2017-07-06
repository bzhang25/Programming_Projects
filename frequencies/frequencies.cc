#include <iostream>
#include "../molecule_analysis/molecule.h"
#include "../molecule_analysis/masses.h"
#include <cmath>

using namespace std;


int main(int argc, char *argv[]) 
{

    FILE *hessian; //define a pointer to FILE object 
    int natom; //defines integer natom

    hessian = fopen ("hessian.dat", "r"); //returns a pointer to FILE object called hessian

    Molecule mol("geom.dat",0); //declar a molecule object mol that gets parameters from geom.dat

    fscanf(hessian, "%d", &natom); //fscanf reads in a regex from pointer to FILE hessian and saves it to the address of natom

    //test to see if the number of atoms in the geom.dat and hessian.dat file is consistent
    if (mol.natom!=natom) printf("Warning: number of atoms inconsistent between hessian and input files\n");

    //allocate memory for the hessian matrix made of doubles, by defining H as ** we can call H in 2 dimensions  
    double **H = new double*[3*natom]; //the size is 3N for the x,y,z coordinates of each atom
    double **H_M = new double*[3*natom]; //mass weighted hessian matrix
    for(int i=0; i < 3*natom; i++){ 
        H[i] = new double[3*natom];
        H_M[i] = new double[3*natom];
    }
    
    //for loops will go through each line in hessian.dat in order that contains format specified 
    for(unsigned int i=0; i < 3*natom; i++) { 
        for(unsigned int j=0; j < 3; j++) {
            
            //puts hessian.dat in a square matrix 3N by 3N. First three rows read correspond to first row of square matrix, etc.
            fscanf(hessian, "%lf %lf %lf", &H[i][j*3], &H[i][j*3+1],&H[i][j*3+2]); //1st row in places j=0-2, 2nd in places j=3-5, 3rd in places j=6-8
        }
    }

    //first two loops loop over the number of atoms
    for(unsigned int i=0; i < natom; i++) { 
        for(unsigned int j=0; j < natom; j++) {
           //second two loops loop over x,y,z coordinates of each atom 
            for(unsigned int k=3*i; k < 3*i+3; k++) { 
                for(unsigned int l=3*j; l < 3*l+3; l++) {
                    
                    H_M[k][l] = H[k][l]/(mass[(int) mol.zvals[i]]*mass[(int) mol.zvals[j]]);
                }
            }
        }
    }

    
    for(unsigned int i=0; i < 3*natom; i++) { 
        printf("%lf %lf %lf %lf %lf %lf %lf %lf %lf \n", H_M[i][0], H_M[i][1], H_M[i][2], H_M[i][3], H_M[i][4], H_M[i][5], H_M[i][6], H_M[i][7], H_M[i][8]);
    }



    //frees allocated block of memory for H and H_M
    for (int i=0; i<3*natom; i++) {
        delete[] H[i];
        delete[] H_M[i];
    }
    delete[] H;
    delete[] H_M;

    return 0;
}  
