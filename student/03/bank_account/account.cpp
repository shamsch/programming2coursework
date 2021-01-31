#include "account.hh"
#include <iostream>

using namespace std;

Account::Account(const std::string& owner, bool has_credit):  creditStatus_(has_credit),owner_(owner)
{
    generate_iban();
}

// Setting initial value for the static attribute running_number_
int Account::running_number_ = 0;

void Account::generate_iban()
{
    ++running_number_;
    std::string suffix = "";
    if(running_number_ < 10)
    {
        suffix.append("0");
    }
    else if(running_number_ > 99)
    {
        std::cout << "Too many accounts" << std::endl;
    }
    suffix.append(std::to_string(running_number_));

    iban_ = "FI00 1234 ";
    iban_.append(suffix);
}

 void Account::set_credit_limit(int amount){
        if (creditStatus_==true){
            creditLimit_=amount;
            
        }
        else{
            cout<<"Cannot set credit limit: the account has no credit card"<<endl;
        }
    }

void Account::save_money(int money){
    money_=money;
}

void Account::transfer_to(Account& x, int amount){
     if(money_>=amount){
         money_=money_-amount;
         x.money_=x.money_+amount;
         cout<<amount<<" euros taken: new balance of "<< iban_<<" is "<< money_ <<" euros"<<endl;
     }
     else if (creditStatus_==true)
     {
        if ((amount-money_)<=creditLimit_)
        {
            money_=money_-amount;
            x.money_=x.money_+amount;
            cout<<amount<<" euros taken: new balance of "<< iban_<<" is "<< money_ <<" euros"<<endl;
        }
        else{
            cout<<"Cannot take money: credit limit overflow"<<endl;
            cout<<"Transfer from "<< iban_ <<" failed"<<endl;
        }
     }
     
     else{
        cout<<"Cannot take money: balance underflow"<<endl;
        cout<<"Transfer from "<< iban_ <<" failed"<<endl;
     }
 }
 
void Account::take_money(int amount){
    if (amount<=money_){
        money_=money_-amount;
        cout<<amount<<" euros taken: new balance of "<< iban_<<" is "<< money_ <<" euros"<<endl;
    }
    else if (creditStatus_==true)
    {
        if ((amount-money_)<=creditLimit_)
        {
            money_=money_-amount;
            cout<<amount<<" euros taken: new balance of "<< iban_<<" is "<< money_ <<" euros"<<endl;
        }
        else{
            cout<<"Cannot take money: credit limit overflow"<<endl;
        }
        
    }
    
    else{
        cout<<"Cannot take money: balance underflow"<<endl;
    }
}

 void Account::print() const{
     cout<< owner_ <<" : "<< iban_ <<" : "<< money_<<" euros"<<endl;
 } 