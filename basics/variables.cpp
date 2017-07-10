//operating with variables

#include <iostream>
#include <string>

using namespace std;

int main()
{
    //declaring variables
    int a, b;
    int result;
    
    //processing 
    a = 5;
    b = 2;  
    a = a + 1;
    result = a - b;

    int c = 5; //c-like initialization
    int d (3); //constructor initialization
    int f {2}; //uniform initialization

    //only use if increases readability 
    auto bar = f; //bar has same type as the value used to initialize it(int)
    decltype(f) foo; //no initial value but foo same type as f


    //print out result
    printf("result:\n");
    cout << result << endl;

    string mystring;
    mystring = "This is a string";
    cout << mystring << endl; 
    
    //use of conditional: g is result of evaluation a > b - if true g = a, if false g = b
    int g = (a>b) ? a : b;
    cout << g << endl;

    //casting
    
    int integer;
    double fp = 3.000;
    integer = (int) fp; //or int (fp) 
    cout << fp << endl;



    //terminate program
    return 0;
}

