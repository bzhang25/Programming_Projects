//this is a molecule.h file, which has defined the type of class 

#include <string>

using namespace std; //using standard namespace 

class Molecule  //defining a molecule class
{ 
    public:     //directive indicates that all variables are functions are available to any code with object Molecule
        int natom; //define an integer variable natom
        int charge; //define an integer variable charge
        double *zvals; //define a point-to-integer variable zvals, which defines an address not the actual variable 
        double **geom; //pointer to a pointer of a double precision float 

        /* The following are declarations but not yet definitions  of member functions*/
        // see molecule.cc for definitions and explanations on what they do
        void print_geom(); //void is for functions that might not have a predefined return type or doesn't return anything
        void rotate(double phi);
        void translate(double x, double y, double z);
        double bond(int atom1, int atom2);
        double angle(int atom1, int atom2, int atom3);
        double * crossproduct(int , int b, int c);
        double torsion(int i, int j, int k, int l);
        double unit(int cart, int atom1, int atom2);
        double oop(int i, int j, int k, int l);
        double * com();
        void moi();

        Molecule(const char *filename, int q); //constructor, automatically called, or instantiated, when object type Molecule declared
                                //takes initial arguments, see molecule.cc for definition
        ~Molecule(); //deconstructor, automatically called when object goes out of scope 
};
        


