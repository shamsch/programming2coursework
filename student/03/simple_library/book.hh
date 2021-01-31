#ifndef BOOK_HH
#define BOOK_HH

#include <string>
using namespace std;

class Book
{
public:
    Book(string name, string author, bool loan= false);
    void print() const;

private:
    string name_,author_;
    bool loan_;
};

#endif 
