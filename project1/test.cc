//reads in a geometry file and calculates bond lengths, angles, and oop angles

#include "molecule.h"
#include <cmath>

using namespace std;



int main(int argc, char *argv[]) 
{
    Molecule mol("geom.dat",0); //declar a molecule object mol that gets parameters from geom.dat
    
    printf("Bonds:\n");
    for(unsigned int i=0; i < mol.natom; i++) { 
        for(unsigned int j=0; j < i; j++) {
        
            printf("%d %d %5.5f\n", i,j,mol.bond(i,j));

        }
    }

    printf("Selected bond angles:\n");
    for(unsigned int i=0; i < mol.natom; i++) { 
        for(unsigned int j=0; j < i; j++) {
            for(unsigned int k=0; k < j; k++) {
                if(mol.bond(i,j) < 4.0 && mol.bond(j,k)<4.0){
                    printf("%d %d %d %5.5f\n", i,j,k, mol.angle(i,j,k)*(180/acos(-1.0)));
                
                }
            }
        }
    }

    printf("Selected oop angles:\n");

    for(unsigned int i=0; i < mol.natom; i++) { 
        for(unsigned int j=0; j < mol.natom; j++) {
            for(unsigned int k=0; k < mol.natom; k++) {
                 for(unsigned int l=0; l < mol.natom; l++) {
                    if(i!=j && i!=k && i!=l && j!=k && j!=l && k!=l && mol.bond(i,k) < 4.0 && mol.bond(k,j)<4.0 && mol.bond(k,l)<4.0){
                            printf("%d %d %d %d %5.5f\n", i,j,k,l, mol.oop(i,j,k,l)*(180/acos(-1.0)));
                    }     
                }
            }
        }
    }
    return 0; //standard command of main functions to exit smoothly
}

