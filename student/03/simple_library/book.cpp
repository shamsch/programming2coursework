#include "book.hh"
#include <iostream>
#include<string>

using namespace std;

Book::Book(string name, string author, bool loan):name_(name), author_(author), loan_(loan){

}

void Book::print() const{
    if(loan_==false){
        cout<< name_ << " : " << author_ << endl;
        cout<< "- available"<<endl;
    }
    else{
        cout<< name_ << " : " << author_ << endl;
        cout<< "- loaned: ";
        loanDate_.print();
        cout<< "- to be returned: ";
        returnDate_.print();
    }
}

void Book::loan(Date x){
    if(loan_==true){
        cout<<"Already loaned: cannot be loaned"<<endl;
    }
    else{
        loanDate_=x;
        x.advance(28);
        returnDate_=x;
        loan_= true;
    }
   
}

void Book::renew(){
    if(loan_==true){
        returnDate_.advance(28);
}
    }
   

void Book::give_back(){
    loan_= false;
}