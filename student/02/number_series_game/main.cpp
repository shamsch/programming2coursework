#include <iostream>

using namespace std;

int main()
{
    cout << "How many numbers would you like to have? ";
    int number;
    cin >> number;
    for(int i=1;i<=number;i++){
        if (i%3==0 && i%7==0)
        {
            cout<<"zip boing"<<endl;
        }
        else if (i%7==0)
        {
            cout<<"boing"<<endl;
        }
         else if (i%3==0)
        {
            cout<<"zip"<<endl;
        }
        
        else{
            cout<<i<<endl;
        }
    }
}
