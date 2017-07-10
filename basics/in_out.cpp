//io example

#include <iostream>
#include <string>
#include <sstream>

using namespace std;

#define newline "\n" 

int main()
{
    
    //most basic example 
    //this is a poorly designed thing because it does not account
    //for times where user enters something other than an integer
    //int i;
    //cout << "enter integer value:" << newline;
    //cin >> i; //user enters i 
    //cout << "the value entered is: " << i << newline;

    //string example
    //just cin will terminate when encountering spaces, so use function getline to get whole string
    string mystr;
    cout << "enter a string: " << newline;
    //note: when the previous example is also run, the tab saved from cin << i interferes with the getline you can't enter a string
    getline (cin, mystr);
    cout << "you entered: " << mystr << newline;

    for (char c : mystr)// : is in range - for char c in range of mystr
    {
        cout << c << newline;
    }
    
    //using stringstream - which can convert input strings to numerical values 
    double price;
    int quantity;
    cout << "enter price: ";
    getline (cin, mystr);
    stringstream(mystr) >> price;
    cout << "enter quantity: ";
    getline (cin, mystr);
    stringstream(mystr) >> quantity;
    cout << "Total price: " << price*quantity << endl;

    return 0;
}
