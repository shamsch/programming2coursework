#include <iostream>

using namespace std;

int main()
{
    float temperature, farenheit, celsius;
    cout << "Enter a temperature: ";
    cin>>  temperature;
    farenheit= (temperature*1.8)+32;
    celsius= (temperature-32)/1.8;
    cout<<temperature<<" degrees Celsius is "<<farenheit<<" degrees Fahrenheit"<<endl;
    cout<<temperature<<" degrees Fahrenheit is "<<celsius<<" degrees Celsius";
    return 0;
}
