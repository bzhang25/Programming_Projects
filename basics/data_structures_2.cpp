//pointers to structures
#include <iostream>
#include <string>
#include <sstream>
using namespace std;

struct movies_t {//defining structure
    string title;
    int year;
};

//example of nesting a structure within another structure 
struct friends_t {
    string name;
    string email;
    movies_t favorite movie; //refers to previously defined structure 
} charlie, maria; //some initial objects 

int main()
{
    string mystr;
    
    movies_t amovie; //declare variable amovie with object type movies_t
    movies_t * pmovie;//declare pointer to movies_t object pmovie
    pmovie = &amovie; //pointer pmovie points to address of amovie
    //how does c++ know how much to allocate for struct types? based on variables? 
    cout << "enter title: ";
    //arrow operator is dereference operator used exclusively with pointers to objects with members 
    //accesses the member of object directly from address
    //pmovie->title is like (*pmovie).title
    getline (cin, pmovie ->title);
    cout << "enter year: ";
    getline (cin, mystr);
    (stringstream) mystr >> pmovie->year;

    cout << "\nyou have entered:\n";
    cout <<pmovie->title;
    cout << "("<<pmovie->year<<")\n";
 
    friends_t * pfriends = &charlie;
    //define a pointer to structure pfriends which points to address of charlie object
    //can access member variables in charlie like:  
    //charlie.name
    //charlie.favorite_movie.year
    //pfriends->favorite_movie.year 
   
    return 0;
}

// a.b member b of object a
// a->b member b of object pointed to by a (*a).b
//*a.b value pointed to by member b of object a *(a.b) - I guess only makes sense if b is a pointer
