//reads in a geometry file, computes information as defined in class Molecule, and prints out

#include "molecule.h"
#include <cmath>

using namespace std;



int main(int argc, char *argv[]) 
{
    Molecule mol("geom.dat",0); //declar a molecule object mol that gets parameters from geom.dat
    
    //calls print_geom to print geometry
    printf("Input coordinates:\n");
    mol.print_geom();

    printf("Bonds:\n");
    for(unsigned int i=0; i < mol.natom; i++) { 
        for(unsigned int j=0; j < i; j++) {
        
            printf("%d %d %5.5f\n", i,j,mol.bond(i,j));

        }
    }

    //prints bonds that are meaningful
    printf("Selected bond angles:\n");
    for(unsigned int i=0; i < mol.natom; i++) { 
        for(unsigned int j=0; j < i; j++) {
            for(unsigned int k=0; k < j; k++) {
                if(mol.bond(i,j) < 4.0 && mol.bond(j,k)<4.0){
                    printf("%d %d %d %5.5f\n", i,j,k, mol.angle(i,j,k)*(180/acos(-1.0)));
                
                } }
        }
    }

    //prints all oop angles that are meaningful
    printf("Selected oop angles:\n");

    for(unsigned int i=0; i < mol.natom; i++) { 
        for(unsigned int j=0; j < mol.natom; j++) {
            for(unsigned int k=0; k < mol.natom; k++) {
                 for(unsigned int l=0; l < j; l++) {
                    if(i!=j && i!=k && i!=l && j!=k && k!=l && mol.bond(i,k) < 4.0 && mol.bond(k,j)<4.0 && mol.bond(k,l)<4.0){
                            printf("%d %d %d %d %5.5f\n", i,j,k,l, mol.oop(i,j,k,l)*(180/acos(-1.0)));
                    }     
                }
            }
        }
    }

    //prints all meaningful torsion angles (with sign)
    printf("Selected torsion angles:\n");

    for(unsigned int i=0; i < mol.natom; i++) { 
        for(unsigned int j=0; j < i; j++) {
            for(unsigned int k=0; k < j; k++) {
                 for(unsigned int l=0; l < k; l++) {
                    if(mol.bond(i,k) < 4.0 && mol.bond(k,j)<4.0 && mol.bond(k,l)<4.0){
                            printf("%d %d %d %d %5.5f\n", i,j,k,l, mol.torsion(i,j,k,l)*(180/acos(-1.0)));
                    }     
                }
            }
        }
    }

    //calling center of mass function to return center of mass coordinates
    double * cor = mol.com();
    printf("Center of mass coordinates: %2.6f %2.6f %2.6f\n", cor[0], cor[1], cor[2]);

    //translate molecule by center of mass to place at origin 
    mol.translate(-cor[0],-cor[1],-cor[2]);

    printf("Translated coordinates:\n");
    mol.print_geom();

    //calls moment of inertia tensor function as defined in molecule.cc
    mol.moi();


    return 0; //standard command of main functions to exit smoothly
}

