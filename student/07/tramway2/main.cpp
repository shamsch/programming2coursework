/* Tramway 2
 *
 * Desc:
 * This program is done as part of a project for programming 2 course. 
 * It reads input which will contain the lines, stops, and distance of tramway network.
 * It ask for a set of command from the user like: priniting all lines, all stops in a line, adding new line and stop, among other things.
 * This program is implemented with just functional programming. No class or such has been used. 
 * The data strucutre used is a nested one, which could've been made simpler with a struct or something else.
 * I prefered to use this datastructure as I am very comfortable with them. 
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

//This function takes a vector of pairs and check if there exist a simmilar pair in the vector already, uponn which it returns false.
//Otherwise, it returns true. The last parameter is given solely to use this function in other functions than just readInputFile().
bool checkIfAPairExist(vector<pair<string, float>> &vec, string &name, float &dist, bool avoidDistance = false)
{
    for (auto ele : vec)
    {
        //If the name exist, return false
        if (ele.first == name)
        {
            return false;
        }
        //If avoid distance is false and there exist a same distance return false
        if (ele.second == dist && !(avoidDistance))
        {
            return false;
        }
    }
    //Otherwise, true
    return true;
}
// This function is directly copied from previous assigment as advised in the description of this project.
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

//This function takes input and checks for all sorts of error that can arise. It also intitalizes the dataStructure used for this project.
bool readInputFile(dataStrucutre &cont)
{
    // Reading the file
    string filename = "";
    cout << "Give a name for input file: ";
    getline(cin, filename);
    ifstream file_object(filename);
    //Error handeling
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
                //When the distance is not explicitly given 
                if (temp.size() == 2)
                {
                    temp.push_back("0");
                }
                float distance = stof(temp.at(2));
                //Next line was used for testing, kept for debugging.
                //cout<<lineName << " "<<nameOfStop<<" "<< distance << endl;
                if (cont.find(lineName) == cont.end())
                {
                    // Line doesn't exist already
                    pair<string, float> tempPair(nameOfStop, distance);
                    vector<pair<string, float>> tempVec;
                    tempVec.clear();
                    tempVec.push_back(tempPair);
                    cont.insert({lineName, tempVec});
                }
                else
                {
                    // Line exists already
                    // Using a function defined by me to check if the stop or distance exists in the vector of the line 
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
            // Error handeling 
            else
            {
                cout << "Error: Invalid format in file." << endl;
                return false;
            }
        }
        file_object.close();
    }
    //Sucessful reading 
    return true;
}
//This function prints all the line or the key of the map in an alph order
void printLines(dataStrucutre &cont)
{
    cout << "All tramlines in alphabetical order:" << endl;
    vector<string> allLines;
    allLines.clear();
    for (auto element : cont)
    {
        allLines.push_back(element.first);
    }
    //sorting (although, it might work otherwise)
    sort(allLines.begin(),allLines.end());
    for(auto line: allLines){
        cout<<line<<endl;
    }
}

//This function is driver for the sort function in printStopsOfOneLine() and allows to sort by the second value
bool sortbysec(const pair<string, float> &a, const pair<string, float> &b)
{
    return b.second > a.second;
}

//This function prints all the stops in order which belong to a particular line
void printStopsOfOneLine(dataStrucutre &cont, string &line)
{
    cout << "Line " << line << " goes through these stops in the order they are listed:" << endl;
    sort(cont[line].begin(), cont[line].end(), sortbysec);
    for (auto element : cont[line])
    {
        cout << " - " << element.first << " : " << element.second << endl;
    }
}

//This function checks if a line exist or not in the datastructure. Used in main() for error handeling.
bool doesThisLineExist(dataStrucutre &cont, string &line)
{
    if (cont.find(line) == cont.end())
    {
        //not found
        return false;
    }
    else
    {
        //found
        return true;
    }
}

//This function prints all the unique stops/station across all lines.
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
                //does not exist alrady so push it in
                stops.push_back(pairs.first);
            }
        }
    }
    //sorting
    sort(stops.begin(), stops.end());
    cout << "All stops in alphabetical order:" << endl;
    for (auto name : stops)
    {
        //ignore the if here (doesn't change anything if removed)
        if(name!=""){
            cout << name << endl;
        }
    }
}

//prints out which lines contain a particular stop/or station
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
    //if it truly exists in any line
    if (lines.size())
    {
        cout << "Stop " << stop << " can be found on the following lines:" << endl;
        for (auto element : lines)
        {
            cout << " - " << element << endl;
        }
    }
    // otherwise
    else
    {
        cout << "Error: Stop could not be found." << endl;
    }
}

//calculates the distance between two stops/staion in a line
void calculateDistance(dataStrucutre &cont, string &line, string &firstStation, string &secondStation)
{
    float none = 0.0;
    float firstDist = 0.0;
    float secondDist = 0.0;
    if (cont.find(line) != cont.end())
    {
        //this is the other use of checkIfAPairExist() to find if the station exist in that line
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

// trims the quotation mark off a vector element(s) if it has one and continues until it finds the ending quotation mark and then return a concatation of elements 
// if the element of doesn't have any quotation mark returns it as it is 
// also erases the element which was trimmed, so it can be used repeatedly to catch the next parameter from the user input
string trimTheQuotationMark(vector<string> &listOfName)
{
    string result = "";
    string firstElement = listOfName.at(0);
    int count = 0;
    for (auto &element : listOfName)
    {
        string temp = element;
        //first quotation mark or last
        if (temp[0] == '"' || temp[temp.length() - 1] == '"')
        {
            vector<string> tempVec;
            //using the split function
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
        //no quotation mark in first element, so no point in continuing
        if (temp[0] != '"' && temp == firstElement)
        {
            break;
        }
    }
    //erasing for repeated use
    listOfName.erase(listOfName.begin(), listOfName.begin() + count);
    //removing the last space 
    result.pop_back(); 
    return result;
}
//adds new line in the data structure 
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
// adds a stop to a pre-exisiting line and a valid distance 
void addStopToALine(dataStrucutre &cont, string &line, string &stopName, float &dist)
{
    if (cont.find(line) != cont.end())
    {
        // using the function to check the validity of the given distance and stop/station name
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
// removes a stop from the data structure 
void removeAStopFromAllLine(dataStrucutre &cont, string &stopName)
{
    bool removedAtLeastOnce= false;
    bool removeCondition= false;
    auto index=0;
    for (auto &map : cont)
    {
        for(auto &vec: map.second){
            // found the stop
            if(vec.first==stopName){
                //gets the index
                auto temp=find(map.second.begin(),map.second.end(),vec);
                index=temp-map.second.begin();
                //remove condition is set to true
                removeCondition=true;
                //at least once removed, hence the stop existed in at least once in somme line
                removedAtLeastOnce=true;
            }
        }
        if(removeCondition){
            //erases the index position
            map.second.erase(map.second.begin()+index);
            //remove condition is set to false until a match is found again
            removeCondition=false;
        }
    }
    if(removedAtLeastOnce){
        cout<<"Stop was removed from all lines."<<endl;
    }
    else{
        cout<<"Error: Stop could not be found."<<endl;
    }
}

int main()
{
    print_rasse();
    dataStrucutre mainContainer;
    //if there's an error
    if (!readInputFile(mainContainer))
    {
        return EXIT_FAILURE;
    }

    while (true)
    {
        //user interface
        string line;
        cout << "tramway> ";
        getline(cin, line);
        vector<string> parts = split(line, ' ', true);

        string command = parts.at(0);
        //make command uppercase 
        transform(command.begin(),command.end(), command.begin(), ::toupper);

        if (command == "LINES")
        {
            printLines(mainContainer);
        }
        else if (command == "LINE")
        {

            if (parts.size() >= 2)
            {
                //if sufficent parameter is given, erases the command 
                parts.erase(parts.begin());
                string nameOfLine;
                //gets the name of the line
                nameOfLine = trimTheQuotationMark(parts);
                //if this line exist or not
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
                //if sufficent parameter is given, erases the command 
                parts.erase(parts.begin());
                string stop = trimTheQuotationMark(parts);
                //next line of code was used in debugging
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
                //if sufficent parameter is given, erases the command 
                //given the nature of the trimTheQuotationMark() it allows to methodically get all three parameters by repeated use
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
                //if sufficent parameter is given, erases the command
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
                //if sufficent parameter is given, erases the command 
                //given the nature of the trimTheQuotationMark() it allows to methodically get all three parameters by repeated use
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
                //if sufficent parameter is given, erases the command 
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
    // succesful run
    return EXIT_SUCCESS;
}
