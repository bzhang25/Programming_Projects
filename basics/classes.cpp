//learning about classes 
//a class expands the concept of data structure- contains both members and functions 
//an object is an instantiation of class (like class is type, object is variable) 
//classes can have access specifiers - private, public, or protected
//members are set to private by default- only accessed within members of class

//classes can also be defined with struct and union - for these public is the default access

//example:
#include <iostream>
using namespace std;

//declare class rectangle 
class Rectangle {
        int width, height;//these are private members only can access within class
    public: //these are members that can be accessed whenever class is called 
        
        int area() {return width*height;}//function that returns width*height 
       // void set_values (int, int); //function that has be declared but not defined 
        //instead of putting set_values as a function can put in constructor
        //constructor initializes members or allocate storage when class is called
        //cannot be called explicitly, only executed once
        //the name matches the class, no return type because don't return any things, only initialize
        Rectangle();//this declares the default constructor
        Rectangle(int, int);
};


////define function set_values, which sets input values as width and height
//void Rectangle::set_values (int x, int y) { //:: lets us know that we are talking about the set_values function in the rectangle class
//    width = x;
//    height = y;
//}

//define what constructor for Rectangle class does
//can be overloaded with different versions  that take different parameters

//this is the default constructor -> if want to use, don't use parenthese to call
Rectangle::Rectangle () {
    width = 5;
    height = 5;
}

Rectangle::Rectangle (int a, int b) {
    width = a;
    height = b;
}

class Circle {
    double radius;
    public:
        Circle(double r) : radius(r){} //constructor where members initialized directly without putting in both 
        double area() {return radius*radius*3.14159265;}
};

class Cylinder {
    Circle base; //instantiate circle object base 
    double height; 
    public:
        Cylinder(double r, double h) : base (r), height(h) {}
        //since objects of circle can only be constructed with parameter, base's constructor needs to be called
        //can only do through member initializer list as above
        double volume() {return base.area() * height;}
};

int main () {
    //Rectangle rect; //define an instantiation of class rectangle called rex
    //Rectangle rectb; //define another instantiation rectb
    //rect.set_values(3,4);//calls public function set_values 
    //rectb.set_values(5,6);
    
    //with constructor, can do:
    Rectangle rect (3,4);
    Rectangle rectb (5,6);
    
    //can also call values like
    Rectangle foo1 {3,4}; //width and height are 3 and 4, brackets - uniform initialization 
    Rectangle bar; //calls default constructor
    Rectangle baz{};//another way to call default constructor
    //Rectangle rectc(); is a function declaration, default constructor not called
    
    cout << "rect area: " << rect.area() <<endl;
    cout << "rectb area: " << rectb.area() <<endl;

    Cylinder foo (10,20);

    cout << "foo's volume: " << foo.volume() << '\n';

    //example of using pointers to classes
    Rectangle obj (3,4);
    Rectangle * a, * b, * c; //define pointers to class rectangle 
    a = &obj; //a is the address of rectangle object obj
    b = new Rectangle (5,6); //allocated space for a rectangle with initial parameters 5,6
    c = new Rectangle[2] { {2,5}, {3,6}}; //allocated space for 2 rectangle objects which are then defined
    cout << "obj's area: " << obj.area() << '\n'; 
    cout << "*a's area: " << a->area() << '\n'; //should be the same as ojb's area
    cout << "*b's area: " << b->area() << '\n'; 
    cout << "c[0]'s area: " << c[0].area() << '\n'; //c[n] (n+1)tj object pointed to by x
    cout << "c[1]'s area: " << c[1].area() << '\n';
    
    //deleting allocated memory
    delete b;
    delete[] c;

    return 0;
}
