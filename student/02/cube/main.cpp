#include <iostream>
#include <cmath>

using namespace std;

int main()
{
    int number, cube;
    long unsigned int actualCube, testInt;
    cout << "Enter a number: ";
    cin>> number;
    cube= number*number*number;
    testInt=cube;
    actualCube=pow(number,3);
    if(testInt==actualCube){
        cout<<"The cube of "<<number<<" is "<<cube<<".";
    }
    else{
        cout<<"Error! The cube of "<<number<<" is not "<<cube<<".";
    }

    return 0;
}