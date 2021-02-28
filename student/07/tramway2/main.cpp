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
#include <cmath>

using namespace std;
using dataStrucutre = map<string, vector<pair<string, float>>>;
const string ERROR = "Error: Invalid input.";

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

bool checkIfAPairExist(vector<pair<string, float>> &vec, string &name, float &dist, bool avoidDistance = false)
{
    for (auto ele : vec)
    {
        if (ele.first == name)
        {
            return false;
        }
        if (ele.second == dist && !(avoidDistance))
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
            temp = split(line, ';', true);
            if (temp.size() == 3 || temp.size() == 2)
            {
                string lineName = temp.at(0);
                string nameOfStop = temp.at(1);
                if (temp.size() == 2)
                {
                    temp.push_back("0");
                }
                float distance = stof(temp.at(2));
                //cout<<lineName << " "<<nameOfStop<<" "<< distance << endl;
                if (cont.find(lineName) == cont.end())
                {
                    // line doesn't exist
                    pair<string, float> tempPair(nameOfStop, distance);
                    vector<pair<string, float>> tempVec;
                    tempVec.clear();
                    tempVec.push_back(tempPair);
                    cont.insert({lineName, tempVec});
                }
                else
                {
                    //line exists already
                    if (checkIfAPairExist(cont[lineName], nameOfStop, distance))
                    {
                        pair<string, float> tempPair(nameOfStop, distance);
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

void printLines(dataStrucutre &cont)
{
    cout << "All tramlines in alphabetical order:" << endl;
    vector<string> allLines;
    allLines.clear();
    for (auto element : cont)
    {
        allLines.push_back(element.first);
    }
    sort(allLines.begin(),allLines.end());
    for(auto line: allLines){
        cout<<line<<endl;
    }
}

bool sortbysec(const pair<string, float> &a, const pair<string, float> &b)
{
    return b.second > a.second;
}

void printStopsOfOneLine(dataStrucutre &cont, string &line)
{
    cout << "Line " << line << " goes through these stops in the order they are listed:" << endl;
    sort(cont[line].begin(), cont[line].end(), sortbysec);
    for (auto element : cont[line])
    {
        cout << " - " << element.first << " : " << element.second << endl;
    }
}

bool doesThisLineExist(dataStrucutre &cont, string &line)
{
    if (cont.find(line) == cont.end())
    {
        //not found
        return false;
    }
    else
    {
        return true;
    }
}

void printAllStops(dataStrucutre &cont)
{
    vector<string> stops;
    stops.clear();
    for (auto vectors : cont)
    {
        for (auto pairs : vectors.second)
        {
            if (find(stops.begin(), stops.end(), pairs.first) == stops.end())
            {
                stops.push_back(pairs.first);
            }
        }
    }
    sort(stops.begin(), stops.end());
    cout << "All stops in alphabetical order:" << endl;
    for (auto name : stops)
    {
        if(name!=""){
            cout << name << endl;
        }
    }
}

void findAllLinesWithAStop(dataStrucutre &cont, string &stop)
{
    vector<string> lines;
    for (auto vectors : cont)
    {
        for (auto pairs : vectors.second)
        {
            if (pairs.first == stop)
            {
                lines.push_back(vectors.first);
            }
        }
    }
    if (lines.size())
    {
        cout << "Stop " << stop << " can be found on the following lines:" << endl;
        for (auto element : lines)
        {
            cout << " - " << element << endl;
        }
    }
    else
    {
        cout << "Error: Stop could not be found." << endl;
    }
}

void calculateDistance(dataStrucutre &cont, string &line, string &firstStation, string &secondStation)
{
    float none = 0.0;
    float firstDist = 0.0;
    float secondDist = 0.0;
    if (cont.find(line) != cont.end())
    {
        if (!(checkIfAPairExist(cont[line], firstStation, none, true) && checkIfAPairExist(cont[line], secondStation, none, true)))
        {
            for (auto ele : cont[line])
            {
                if (ele.first == firstStation)
                {
                    firstDist = ele.second;
                }
                if (ele.first == secondStation)
                {
                    secondDist = ele.second;
                }
            }
            cout << "Distance between " << firstStation << " and " << secondStation << " is " << abs(firstDist - secondDist) << endl;
        }
        else
        {
            cout << "Error: Stop could not be found." << endl;
        }
    }
    else
    {
        cout << "Error: Line could not be found." << endl;
    }
}

string trimTheQuotationMark(vector<string> &listOfName)
{
    string result = "";
    string firstElement = listOfName.at(0);
    int count = 0;
    for (auto &element : listOfName)
    {
        string temp = element;
        if (temp[0] == '"' || temp[temp.length() - 1] == '"')
        {
            vector<string> tempVec;
            tempVec = split(temp, '"', true);
            result += tempVec.at(0) + " ";
        }
        else
        {
            result += temp + " ";
        }
        count++;
        //last quotation mark found
        if (temp[temp.length() - 1] == '"')
        {
            break;
        }
        //no quotation mark in first element
        if (temp[0] != '"' && temp == firstElement)
        {
            break;
        }
    }
    listOfName.erase(listOfName.begin(), listOfName.begin() + count);
    result.pop_back();
    return result;
}

void addNewLine(dataStrucutre &cont, string &lineName)
{
    if (cont.find(lineName) != cont.end())
    {
        //line already exists
        cout << "Error: Stop/line already exists." << endl;
    }
    else
    {
        //line does NOT exist
        vector<pair<string, float>> tempVec;
        tempVec.clear();
        cont.insert({lineName, tempVec});
        cout << "Line was added." << endl;
    }
}

void addStopToALine(dataStrucutre &cont, string &line, string &stopName, float &dist)
{
    if (cont.find(line) != cont.end())
    {
        if (checkIfAPairExist(cont[line], stopName, dist))
        {
            pair<string, float> tempPair(stopName, dist);
            cont[line].push_back(tempPair);
            cout << "Stop was added." << endl;
        }
        else
        {
            cout << "Error: Stop/line already exists." << endl;
        }
    }
    else
    {
        cout << "Error: Line could not be found." << endl;
    }
}

void removeAStopFromAllLine(dataStrucutre &cont, string &stopName)
{
    bool removedAtLeastOnce= false;
    bool removeCondition= false;
    pair<string, float> temp;
    for (auto &map : cont)
    {
        for(auto &vec: map.second){
            if(vec.first==stopName){
                temp= vec;
                removeCondition=true;
                removedAtLeastOnce=true;
            }
        }
        if(removeCondition){
            remove(map.second.begin(),map.second.end(), temp);
            removeCondition=false;
        }
    }
    if(removedAtLeastOnce){
        cout<<"Stop was removed from all lines."<<endl;
    }
    else{
        cout<<"Error: Invalid input"<<endl;
    }
}

int main()
{
    print_rasse();
    dataStrucutre mainContainer;
    if (!readInputFile(mainContainer))
    {
        return EXIT_FAILURE;
    }

    while (true)
    {
        string line;
        cout << "tramway> ";
        getline(cin, line);
        vector<string> parts = split(line, ' ', true);

        string command = parts.at(0);

        if (command == "LINES")
        {
            printLines(mainContainer);
        }
        else if (command == "LINE")
        {

            if (parts.size() >= 2)
            {
                parts.erase(parts.begin());
                string nameOfLine;
                nameOfLine = trimTheQuotationMark(parts);
                if (!doesThisLineExist(mainContainer, nameOfLine))
                {
                    cout << "Error: Line could not be found." << endl;
                }
                else
                {
                    printStopsOfOneLine(mainContainer, nameOfLine);
                }
            }
            else
            {
                cout << ERROR << endl;
            }
        }
        else if (command == "STOPS")
        {
            printAllStops(mainContainer);
        }
        else if (command == "STOP")
        {
            if (parts.size() >= 2)
            {
                parts.erase(parts.begin());
                string stop = trimTheQuotationMark(parts);
                // cout<<stop<<endl;
                findAllLinesWithAStop(mainContainer, stop);
            }
            else
            {
                cout << ERROR << endl;
            }
        }
        else if (command == "DISTANCE")
        {
            parts.erase(parts.begin());
            if (parts.size() >= 3)
            {
                string line = trimTheQuotationMark(parts);
                string firstStation = trimTheQuotationMark(parts);
                string secondStation = trimTheQuotationMark(parts);
                // cout<<line<< " "<< firstStation << " " << secondStation << endl;
                calculateDistance(mainContainer, line, firstStation, secondStation);
            }
            else
            {
                cout << ERROR << endl;
            }
        }
        else if (command == "ADDLINE")
        {
            if (parts.size() >= 2)
            {
                parts.erase(parts.begin());
                string nameOfTheLine = trimTheQuotationMark(parts);
                addNewLine(mainContainer, nameOfTheLine);
            }
            else
            {
                cout << ERROR << endl;
            }
        }
        else if (command == "ADDSTOP")
        {
            if (parts.size() >= 4)
            {
                parts.erase(parts.begin());
                string line = trimTheQuotationMark(parts);
                string station = trimTheQuotationMark(parts);
                float dist = stof(trimTheQuotationMark(parts));
                addStopToALine(mainContainer, line, station, dist);
            }
            else
            {
                cout << ERROR << endl;
            }
        }
        else if (command == "REMOVE")
        {
            if (parts.size() >= 2)
            {
                parts.erase(parts.begin());
                string station = trimTheQuotationMark(parts);
                removeAStopFromAllLine(mainContainer, station);
            }
            else
            {
                cout << ERROR << endl;
            }
        }
        else if (command == "QUIT")
        {
            break;
        }
        else
        {
            cout << ERROR << endl;
        }
    }

    return EXIT_SUCCESS;
}
