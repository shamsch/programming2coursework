#include <iostream>
#ifndef RECURSIVE_FUNC
#define RECURSIVE_FUNC
#endif

using namespace std;

void print_vertical(unsigned int num)
{
    RECURSIVE_FUNC
    // Do not remove RECURSIVE_FUNC declaration, it's necessary for automatic testing to work
    // ------------


    // Add your implementation here
    unsigned int copy;
    copy = num; //first we make a copy
    if(num/10<1){
        std::cout<<copy<<endl; // if it just one digit we print that
    }
    else{
        print_vertical(copy/10); // the first digit
        print_vertical(copy%10);
    }

}

// Do not modify rest of the code, or the automated testing won't work.
#ifndef UNIT_TESTING
int main()
{
    unsigned int number = 0;
    cout << "Enter a number: ";
    cin >> number;
    cout << "The given number (" << number << ") written vertically:" << endl;
    print_vertical(number);
    return 0;
}
#endif
