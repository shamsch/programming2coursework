#include <iostream>
#include <fstream>
#include <string>
#include <map>

using namespace std;

int main()
{
    string filename = "";
    string outputFileName = "";
    map<string, int> nameAndPoints;
    cout << "Input file: ";
    getline(cin, filename);

    ifstream file_object(filename);
    if (not file_object)
    {
        cout << "Error! The file " << filename << " cannot be opened." << endl;
        return EXIT_FAILURE;
    }
    else
    {
        string line;
       
        while (getline(file_object, line))
        {   
            string temp = "";
            string name= "";
            int point=0;
            for (string::size_type i = 0; i < line.length(); ++i)
            {
                if (line[i] == ':')
                {
                    if (nameAndPoints.find(temp) != nameAndPoints.end())
                    {
                        name= temp;
                        point=nameAndPoints.at(name);
                    }
                    else
                    {   
                        name= temp;
                        nameAndPoints.insert({name, 0});
                    }
                    temp="";

                }
                else
                {
                    temp += line[i];
                }
            }
            nameAndPoints[name]=point+stoi(temp);    
        }
        file_object.close();
        cout<<"Final scores:"<<endl;
        for ( auto data_pair : nameAndPoints ) {
        cout << data_pair.first << ": "
             << data_pair.second << endl;
    }
    }

    return EXIT_SUCCESS;
}