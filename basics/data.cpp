//intro to different data types

#include <iostream>

//can define aliases by which type is identified
//option 1: typedef existing_type new_type_name
//ex: typedef char C;
//ex: typedef char * pChar;
//option 2: using new_type_name = existing_type
//ex: using C = char;
//ex: using pChar = char *;
//useful if need to change every instance of a type of object
//does not create distinct data types 




using namespace std;






//passing an array as a parameter- use void, don't specify length
//you always lose a dimension because when array passed it is actually passing a pointer
//passing a multidimensional array - leave first dimension empty
void printarray (int arg[], int length){
    for (int n=0; n < length; ++n)
    cout << arg[n] << " \n";
}

int main() {
    //an array is a series of elememts of same type placed in contiguous memory locations

    //can use library #include <array> 

    //declaring an array of integers containing 5 elements - the number of elements must be constant 
    //the values are left uninitalized;
    int array [5];

    //you can initialize an array:
    int array2 [5] = {1,2,3,4,5};

    //you can initialize with zero by defining empty brackets
    int array3 [5] = {};

    //can leave number of elements empty if initializing with specific values, can also leave out =
    int array4[] {1,2,3,4};

    //can access members of an array with
    int x = array2[3];
    //difference between access and declaration is declaration preceded by types of elements 
    
    //can define multi-dimensional arrays:
    int matrix[3][5];
    //which is equal to 
    int mat[15];
    //with multi-dimensional- compiler remembers depth of each imaginary dimension
    // for matrix[i][j] to access the jth term in memory cmopute does i*constant + j
    printarray(array4, 4);

    //can have array of characters of a string, which has a null-terminated sequences of characters
    //these are called c-strings, you could also have strings from libraries- can interconvert 

    //pointers
    //since a pointer can directly refer to the value it points to, declaration of pointer needs 
    //to specify the type of data the pointer points to
    int * foo;
    int myvar;

    foo = &myvar; //we are declaring foo to have the address of myvar 
    *foo = 20; //the value pointed to by foo is 20, which canges myvar to 20 
    int baz = *foo; //we are declaring baz to have the the value pointed to by foo: *foo==myvar

    //an example
    int firstvalue = 5,secondvalue = 15;
    int * p1, * p2;

    p1 = &firstvalue; //p1 = address of first value
    p2 = &secondvalue; //p2 = address of second value 
    *p1 = 10; //value pointed to by p1 is 10
    *p2 = *p1; //value pointed to by p2 is value pointed to by p1
    p1 = p2; //p1 now also points to the address of p2
    *p1 = 20; //value pointed to by p1 (second value) is now 20

    //pointers and arrays
    
    //arrays and pointers are related- array represent a block of elements 
    int numbers[5]; //declare an array numbers of 5 elements of type int
    int * p; //declare pointer p
    
    p = numbers; //this operation is valid- pointer points to the address of first element of this array
                 // numbers = p is not valid because the array is a block of elements and can't be assigned anything 
    *p = 10; //this assigns the value of the thing pointed to by p, which we defined to be the first element of numbers (numbers[0])

    //the following represent the different ways that p can be used to change various elements of numbers
    p++; *p = 20; //2nd element
    p = &numbers[2]; *p = 30; //3rd element
    p = numbers + 3; *p = 40; //4th element
    p = numbers; *(p+4) = 50; //5th element
    // p[3] - bracket acts like a dereference operator- like a offset of 3
    for (int n=0; n<5; n++)
        cout << numbers[n] << " , ";
    cout << endl;

    //when incrementing pointers increment by size of bytes their type of value is

    *p++; //same as *(p++_): increment pointer, dereference the unincremented address
    *++p; //same as *(++p) : increment pointer, dereference incremented address
    ++*p //same as ++(*p): dereference pointer, increment the value it points to
    (*p)++ //dereference pointer, and post-increment value it points to

    // *p++ = *q++: value assigned to *p is *q, then both are incremented 
    
    //constants and pointers:
    int example;
    int * p1 = &x; //non-const pointer to non-const int
    const int * p2 = &x; //this means that the pointer is pointing to a constant that can't be changed although the pointer can
    int * const p3 = &x; //const pointer to non-const int
    const int * const p4 = &x; //const pointer to const int
    //if const anywhere before *, refers to the int
    
    //pointers to pointers - asterisk for each level of indirection 
    char a; //a is char
    char * b = &a; //b is pointer to a
    char ** c = &b //c is pointer to pointer b

    //void* pointer points to any data type
    //defining pointers are nullptr or 0 makes it point to explicitly nowhere
    //defining pointers to functions: int (*pointer)(function parameter types) = function

    //dynamic memory - uses new and delete

    //dynamic memory - uses new and delete
    //array allocates size before running(constant expression)  while dynamic memory is allocated during runtime
    int * foo;
    foo = new int [5];

    int i, n; //declare int i and n
    int * p; //declare pointer p 
    cout << "how many numbers would you like to type? ";
    cin >> i; //user input
    p = new (nothrow) int[i]; //allocate block of memory size of i(which is not constant but value enter by user, don't throw exception if failed
    if (p == nullptr)
        cout > "Error: memory could not be allocated";
    else
    {
        for (n=o; n<i; n++)
        {
            cout << "enter number : ";
            cin >> p[n]; //this assigns the number to the nth block of memory of p
        }
        cout << "you have entered: ";
        for (n=0; n<i; n++)
            cout << p[n] << " , "; //print out values
        delete[] p; //delete block of memory allocated for p
    
    
    return 0;

    //other data types:
    




   }
