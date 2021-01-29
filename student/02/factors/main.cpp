#include <iostream>
#include <cmath>

using namespace std;

int main()
{
    int number;
    cout << "Enter a positive number: ";
    cin>> number;
    if (number>=0){
        int squareRoot = sqrt(number);
        while(number%squareRoot!=0){
            squareRoot--;
        }
        cout<<number<<" = "<<squareRoot<<" * "<<number/squareRoot;
    }
    else{
        cout << "Only positive numbers accepted";
    }

    return 0;
}
