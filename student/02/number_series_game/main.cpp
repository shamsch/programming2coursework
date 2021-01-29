#include <iostream>

using namespace std;

int main()
{
    cout << "How many numbers would you like to have? ";
    int number;
    cin >> number;
    for(int i=1;i<=number;i++){
        cout<<i<<endl;
    }
}
