#include "book.hh"
#include <iostream>
#include<string>

using namespace std;

Book::Book(string name, string author, bool loan= false):name_(name), author_(author), loan_(loan){

}

void Book::print() const{
    if(_loan==false){
        cout<< name_ << " : " << author_ << endl;
        cout<< "- available"<<endl;
    }
}