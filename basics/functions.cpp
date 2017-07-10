//function example
#include <iostream>

//can define own namespaces
using namespace std;

int globvar; //this is a global variable with global scope
//global variables automatically initialized to zero- static storage


// declare a function multiplication 
//b has default value of 3, which is used if no a specified
//if only specifying one parameter has to be last one (i.e. b not a)
double multiplication (double a, double b=3.0)
{
    double m = a*b;// this is a local variable with block scope
                   //local variables have automatic storage- value is left uninitialized 
   return m;
}

//declaring a function without specifying what it does until later so that you can refer to it
void func (int x);

void message() //use void if no return type, in C - if no parameters put (void) as well 
{
    cout << "This function writes a message \n";
}

//function that takes reference (&) to variable 
//does not make copy of variable value - but actually changes the variables themselves
//for bigger data types- making copies can be expensive, but what if don't want to change actual variable? 
//void duplicate( const int&a, etc.) - this way, reference the variable w/o making a copy by ensures variable is not changed 
//see concatenate function below
void duplicate (int& a, int& b, int& c)
{
    a *= 2;
    b *= 2;
    c *= 2;
}

//if function is short, better to insert code of function when it is called rather than the process of formally calling a function
//most compilers already optimize code and will use inline implicitly if it sees fit
//in this case use inline: 
inline string concatenate(const string& a, const string& b)
{
    return a+b;
}

//can overload functions- same name, different parameter type or number of parameters
//generally, not goood idea to have them do vastly different things
int operate (int a, int b);
double operate (double a, double b);

//can define a function template to take in a object type 
//can also different types- ex. <class T, class U>
template <class T>
T sum (T a, T b)
{
    T result = a + b;
    return result;
}


int main()
{
    double m;
    
    m = multiplication (5.5, 2.1);
    cout << "the results is :" << m << endl;

    int x=2, y=5, z=8;
    duplicate(x,y,z);
    printf("x= %d y= %d z= %d \n", x,y,z);


    //use template defined for int and double
    int k = sum<int>(3,4);
    double h = sum<double>(3.3,4.4);
    //can also do k = sum (3,4) but then ambigious what type it is
    //can define templates with specific types inside <> but then fixed, not passed in- "non-type template arguments"


    return 0;
}
