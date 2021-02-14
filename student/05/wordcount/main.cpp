#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    string filename = "";
    map<string, vector<int>> wordAndLine;
    vector<int> uniqueOccurenceCounter;
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
        int lineCounter = 1;

        while (getline(file_object, line))
        {
            string temp = "";
            vector<int> occurenceInLine;
            for (string::size_type i = 0; i < line.length(); ++i)
            {
                if (line[i] == ' ')
                {
                    if (wordAndLine.find(temp) != wordAndLine.end())
                    {
                        wordAndLine[temp].push_back(lineCounter);
                    }
                    else
                    {
                        occurenceInLine.push_back(lineCounter);
                        wordAndLine.insert({temp, occurenceInLine});
                    }
                    temp = "";
                    occurenceInLine.clear();
                }
                else
                {
                    temp += line[i];
                }
            }
            if (temp != "")
            {
                if (wordAndLine.find(temp) != wordAndLine.end())
                {
                    wordAndLine[temp].push_back(lineCounter);
                }
                else
                {
                    occurenceInLine.push_back(lineCounter);
                    wordAndLine.insert({temp, occurenceInLine});
                }
                temp = "";
                occurenceInLine.clear();
            }
            lineCounter += 1;
        }

        // for(auto ele:wordAndLine){
        //     cout<<endl;
        //     cout<< ele.first;
        //     for (auto x : ele.second){
        //         cout<<x;
        //     }
        // }

        for (auto ele : wordAndLine)
        {
            cout << ele.first << " " << ele.second.size() << ": ";
            uniqueOccurenceCounter.clear();
            for (auto i : ele.second)
            {
                if (find(uniqueOccurenceCounter.begin(), uniqueOccurenceCounter.end(), i) != uniqueOccurenceCounter.end())
                {
                    continue;
                }
                else
                {
                    uniqueOccurenceCounter.push_back(i);
                }
            }
            if (uniqueOccurenceCounter.size() > 1)
            {
                for (auto k : uniqueOccurenceCounter)
                {
                    if (k == uniqueOccurenceCounter.back())
                    {
                        cout << k << endl;
                    }
                    else
                    {
                        cout << k << ", ";
                    }
                }
            }
            else
            {
                cout << uniqueOccurenceCounter.at(0) << endl;
            }
        }
        file_object.close();
    }

    return EXIT_SUCCESS;
}