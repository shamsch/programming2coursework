/* Tramway 2
 *
 * Desc:
 * This program 
 *
 * Program author
 * Name: Shamsur Raza Chowdhury
 * Student number: 050359798
 * UserID: rvshch 
 * E-Mail: shamsurraza.chowdhury@tuni.fi
 * */

#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <map>
#include <utility>
#include <fstream>

using namespace std;
using dataStrucutre = map<string, vector<pair<string, string>>>;

// The most magnificent function in this whole program.
// Prints a RASSE
void print_rasse()
{
    cout << "=====//==================//===\n"
            "  __<<__________________<<__   \n"
            " | ____ ____ ____ ____ ____ |  \n"
            " | |  | |  | |  | |  | |  | |  \n"
            " |_|__|_|__|_|__|_|__|_|__|_|  \n"
            ".|                  RASSE   |. \n"
            ":|__________________________|: \n"
            "___(o)(o)___(o)(o)___(o)(o)____\n"
            "-------------------------------"
         << endl;
}

bool checkIfAPairExist(vector<pair<string, string>> &vec, string &name, string &dist)
{
    for (auto ele : vec)
    {
        if (ele.first == name)
        {
            return false;
        }
        if (ele.second == dist)
        {
            return false;
        }
    }
    return true;
}

vector<string> split(const string &s, const char delimiter, bool ignore_empty = false)
{
    vector<string> result;
    string tmp = s;

    while (tmp.find(delimiter) != string::npos)
    {
        string new_part = tmp.substr(0, tmp.find(delimiter));
        tmp = tmp.substr(tmp.find(delimiter) + 1, tmp.size());
        if (not(ignore_empty and new_part.empty()))
        {
            result.push_back(new_part);
        }
    }
    if (not(ignore_empty and tmp.empty()))
    {
        result.push_back(tmp);
    }
    return result;
}

bool readInputFile(dataStrucutre &cont)
{
    string filename = "";
    cout << "Give a name for input file: ";
    getline(cin, filename);
    ifstream file_object(filename);
    if (not file_object)
    {
        cout << "Error: File could not be read." << endl;
        return false;
    }
    else
    {
        string line;

        while (getline(file_object, line))
        {
            vector<string> temp;
            temp.clear();
            temp = split(line, ';');
            if (temp.size() == 3 || temp.size() == 2)
            {
                string lineName = temp.at(0);
                string nameOfStop = temp.at(1);
                if (temp.size() == 2)
                {
                    temp.push_back("0");
                }
                string distance = temp.at(2);
                // cout<<lineName << " "<<nameOfStop<<" "<< distance << endl;
                if (cont.find(lineName) == cont.end())
                {
                    // line doesn't exist
                    pair<string, string> tempPair(nameOfStop, distance);
                    vector<pair<string, string>> tempVec;
                    tempVec.clear();
                    tempVec.push_back(tempPair);
                    cont.insert({lineName, tempVec});
                }
                else
                {
                    //line exists already
                    if (checkIfAPairExist(cont[lineName], nameOfStop, distance))
                    {
                        pair<string, string> tempPair(nameOfStop, distance);
                        cont[lineName].push_back(tempPair);
                    }
                    else
                    {
                        cout << "Error: Stop/line already exists." << endl;
                        return false;
                    }
                }
            }
            else
            {
                cout << "Error: Invalid format in file." << endl;
                return false;
            }
        }
        file_object.close();
    }
    return true;
}

// Short and sweet main.
int main()
{
    dataStrucutre mainContainer;
    if (!readInputFile(mainContainer))
    {
        return EXIT_FAILURE;
    }
    print_rasse();
    return EXIT_SUCCESS;
}
