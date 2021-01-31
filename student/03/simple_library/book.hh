#ifndef BOOK_HH
#define BOOK_HH

#include <string>
#include"date.hh"
using namespace std;

class Book
{
public:
    Book(string name, string author, bool loan= false);
    void print() const;
    void loan(Date x);
    void renew();
    void give_back();

private:
    string name_,author_;
    bool loan_;
    Date loanDate_,returnDate_;
};

#endif 
