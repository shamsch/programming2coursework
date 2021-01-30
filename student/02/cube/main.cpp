#include <iostream>
#include <cmath>

using namespace std;

int main()
{
    int number, cube;
    long unsigned int actualCube;
    cout << "Enter a number: ";
    cin>> number;
    cube= number*number*number;
    actualCube=pow(number,3);
    if(cube==actualCube){
        cout<<"The cube of "<<number<<" is "<<cube<<".";
    }
    else{
        cout<<"Error! The cube of "<<number<<" is not "<<cube<<".";
    }

    return 0;
}