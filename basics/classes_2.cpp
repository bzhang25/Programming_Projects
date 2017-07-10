//overloading operators
#include <iostream>
using namespace std;

//can overload operators to define behavior for class types 
//i.e. for a given class, can define what + will do 
class CVector {
    public:
        int x,y;
        CVector (){};
        CVector (int a, int b) : x(a), y(b) {}//function name CVector (constructor)
        CVector operator + (const CVector&); //function that returns a CVector
};


CVector CVector::operator+ (const CVector& param) {
//defines when one class added to another class
//param is directly referenced in (&) not copied
// returns the addition of the two members added
    CVector temp;
    temp.x = x + param.x;
    temp.y = y + param.y;
    return temp;
}

//can overload with non-member functions instead
class CVector_new {
    public:
        int x,y;
        CVector_new (){};
        CVector_new (int a, int b) : x(a),y(b) {}//function name CVector (constructor)
};

CVector_new operator+ (const CVector_new& lhs, const CVector_new& rhs) {
    CVector_new temp;
    temp.x = lhs.x + rhs.x;
    temp.y = lhs.y + rhs.y;
    return temp;
}

//example on "this"
//frequently used with operator= functions that return objects by reference
//define initial class with bool variable isitme
class Dummy {
    public:
        bool isitme (Dummy& param);
};

bool Dummy::isitme (Dummy& param) {
    if (&param == this) return true;
    //this is pointer to the object whose member function is being executed
    else return false;
}

//static data is also a class variable because only one common variable for all objects of same class
//have same properties as non-member variables but have class scope
//the example shows int n which is a counter with number of objects currently allocated 
class Static {
    public:
        static int n;
        Static() {n++; };
};
//need to be initialized outside the class to avoid multiple declarations 
int Static::n=0;

int main () {
    CVector foo (3,1);
    CVector bar (1,2);
    CVector result;
    result = foo + bar;
    //equivalent to result = foo.operator+ (bar)

    CVector_new foo2 (3,1);
    CVector_new bar2 (1,2);
    CVector_new result2;
    result2 = foo2 + bar2;
    //equivalent to result2 = operator+(foo2, bar2)

    cout << result.x << ',' << result.y << '\n';
    cout << result2.x << ',' << result2.y << '\n';

    Dummy a1;
    Dummy c1;
    Dummy* b1 = &a1; //pointer b points to address of a
    if (b1->isitme(a1) )//uses isitme function with this
        cout << "yes, &a is b \n";
    else cout << "no \n";

    Static a;
    Static b[5];
    cout << a.n << '\n'; //can referr to as a member of any object
    Static *c = new Static; //allocate space to put new dummy object
    cout << Static::n<<'\n'; //can refer to directly by class name

    delete c;
    return 0;
}
