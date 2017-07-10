//structures example - array of structures 
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

//defines structure movies_t with member variables title and year
// then define an array of 3 films made of movies_t objects 
struct movies_t {
    string title;
    int year;
} films [3];

//union types- all members occupy same physical space in memory
//size is the one of the largest member element
//changing one will change all the ones -not independent 
//one use: access a value in entirely or as an array, or structure of smaller elements
//ex: 
union mix_t {
    int l;
    struct{
        short hi;
        short lo;
        } s;
    char c[4];
} mix;
//here the largest element is long - 4 bytes
//all these data types will be within these 4 bytes 


//regular union
struct book1_t {
    char title[50];
    char author[50];
    union {
        float dollars;
        int yen;    
    } price; //define union with an initial object, so don't have to have type name
} book1;
//access object by book1.price.dollars, book1.price.yen


//anonymous union
struct book2_t {
    char title[50];
    char author[50];
    union {
        float dollars;
        int yen;
    };
} book2;
//access object by book2.dollars, book2.yen 

//since union, dollars and yen share memory location, so can't both be stored simultaneously 

//enumerated types- types with custom identifiers (enumerators)
//objects of enumerated types can take any enumerator as value
//creates whole new data type from scratch without basing on existing type
//elements are automatically/internally assigned an integer numerical equivalent, starting from 0
//can specify specific integer value if wanted 
//ex:

enum months_t { january=1, february, march, april, 
                may, june, july, august,
                september, october, november, december} y2k;
//variable y2k can contain 12 possible values- equivalent to 1 to 12 since specified start at 1 for jan. 
//implicit two way conversion between value and integer equivalent

//enum class NAME {}
//preserve type safety because don't implicitly convert
//need to scoped into type"
//enum class Colors {black, blue, etc};
//Colors mycolor;
//mycolor = Colors::blue;
//can be an integral data type, specify by:
//enum class EyeColor : char {blue, green, brown}; 
    




void printmovie (movies_t movie); //declare a function that takes movies_t object movie as parameter

int main()
{
    string mystr; //define string
    int n;
    
    for (n=0; n<3; n++)
    {
        cout << "enter title: ";
        getline (cin, films[n].title); //puts user input of title into the corresponding element of films array
                                        //in member variable title
        cout << "eneter year: ";
        getline (cin, mystr);
        stringstream(mystr) >> films[n].year; //uses stringstream to convert to an int for the year
    }

    cout << "\n you have entered these movies: \n";
    for (n=0; n<3; n++)
        printmovie (films[n]);
    return 0;
}

void printmovie (movies_t movie) //defines what function does
{
    cout << movie.title;
    cout << " (" << movie.year << ")\n";
}
