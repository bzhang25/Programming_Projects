//reads in a geometry file and calculates bond lengths, angles, and oop angles

#include "molecule.h"
#include <cmath>
#define PI 3.14159265
using namespace std;



int main(int argc, char *argv[]) 
{
    Molecule mol("geom.dat",0); //declar a molecule object mol that gets parameters from geom.dat

    //calculate all bond lengths between all atoms

    //allocate memory for matrix R that stores all bond lengths
    double **R = new double* [mol.natom];
    for(unsigned int i=0; i < mol.natom; i++){
        R[i] = new double[mol.natom];
    }

    //calculate bond lengths with formula R_ij = sqrt((x_i-x_j)^2 + (y_i - y_j)^2 + (z_i - z_j)^2)
    //loops over all i and j
    for(unsigned int i=0; i < mol.natom; i++) { 
        for(unsigned int j=0; j < mol.natom; j++) {
            R[i][j] = sqrt(pow((mol.geom[i][0]-mol.geom[j][0]),2.0) 
                          +pow((mol.geom[i][1]-mol.geom[j][1]),2.0) 
                          +pow((mol.geom[i][2]-mol.geom[j][2]),2.0));
        }
    }
    //prints results 
    printf("Bond lengths:\n");
    for(unsigned int i=0; i < mol.natom; i++) { 
        for(unsigned int j=0; j < i; j++) {
        
            printf("%d %d %5.5f\n", i,j, R[i][j]);

        }
    }


    //calculate all angles between all atoms 

    //allocate memory for matrices E_X, E_Y, E_Z that stores all unit vectors
    double **E_X = new double* [mol.natom];
    double **E_Y = new double* [mol.natom];
    double **E_Z = new double* [mol.natom];
    for(unsigned int i=0; i < mol.natom; i++){
        E_X[i] = new double[mol.natom];
        E_Y[i] = new double[mol.natom];
        E_Z[i] = new double[mol.natom];
    }
    //form the unit vector matrices, only calculate half of matrices to avoid dividing by zero
    for(unsigned int i=0; i < mol.natom; i++) { 
        for(unsigned int j=0; j < i; j++) {
            E_X[i][j] = E_X[j][i] =(-mol.geom[i][0]+mol.geom[j][0])/R[i][j]; 
            E_Y[i][j] = E_Y[j][i] =(-mol.geom[i][1]+mol.geom[j][1])/R[i][j]; 
            E_Z[i][j] = E_Z[j][i] =(-mol.geom[i][2]+mol.geom[j][2])/R[i][j]; 
        }
    }

    //if wanted to store, would use a 3D array
    
    //Printing selected bond angles 
    printf("Selected bond angles:\n");
    for(unsigned int k=0; k < mol.natom; k++) { 
        for(unsigned int j=0; j < k; j++) {
            for(unsigned int i=0; i < j; i++) {
                if(R[i][j] < 4.0 && R[j][k]<4.0){
                    double angle = acos((E_X[j][i]*E_X[j][k] + E_Y[j][i]*E_Y[j][k] + E_Z[j][i]*E_Z[j][k])) * (180.0 / acos(-1.0));
                    // for some reason gives 180 -right angle...figure out at some point
                    printf("%d %d %d %5.5f\n", i,j,k, angle);
                
                }
            }
        }
    }

    for(int i=0; i < mol.natom; i++){
    //deletes memory allocated for bond lengths
        delete[] R[i];
    //deletes memory allocated for angles
        delete[] E_X[i];
        delete[] E_Y[i];
        delete[] E_Z[i];
    }
    delete[] R;
    delete[] E_X;
    delete[] E_Y;
    delete[] E_Z;


    return 0; //standard command of main functions to exit smoothly
}

