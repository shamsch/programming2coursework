#include <iostream>
#include <cmath>

using namespace std;

unsigned long long int factorial(int n){
     return (n==0) || (n==1) ? 1 : n* factorial(n-1);
}


int main()
{
    int totalBalls, balls, diff;
    cout<<"Enter the total number of lottery balls: ";
    cin>>totalBalls;
    cout<<"Enter the number of drawn balls: ";
    cin>>balls;
    if(balls>totalBalls){
        cout<< "The maximum number of drawn balls is the total amount of balls."<<endl;
    }
    else if(totalBalls>0 and balls>0){
         diff= totalBalls-balls;
        unsigned long long int prob = factorial(totalBalls)/(factorial(diff)*factorial(balls));
        cout << "The probability of guessing all "<<balls<< " balls correctly is 1/" << prob ;
    }
    else{
        cout<<"The number of balls must be a positive number."<<endl;
    }
   

    return 0;
}