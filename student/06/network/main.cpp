#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

const std::string HELP_TEXT = "S = store id1 i2\nP = print id\n"
                              "C = count id\nD = depth id\n";

std::vector<std::string> split(const std::string &s, const char delimiter, bool ignore_empty = false)
{
    std::vector<std::string> result;
    std::string tmp = s;

    while (tmp.find(delimiter) != std::string::npos)
    {
        std::string new_part = tmp.substr(0, tmp.find(delimiter));
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

void addToNetwork(map<string, vector<string>> &net, string &recruiter, string &adding)
{
    if (net.find(recruiter) != net.end())
    {
        net[recruiter].push_back(adding);
    }
    else
    {
        vector<string> recruit;
        recruit.push_back(adding);
        net.insert({recruiter, recruit});
    }
    vector<string> vect;
    // vect.clear();
    net.insert({adding, vect});
}

void printNetwork(map<string, vector<string>> &net, string &id, string &dot)
{
    cout << dot << id << endl;
    if (net[id].size() > 0)
    {
        for (auto x : net[id])
        {
            string dots = dot + "..";
            printNetwork(net, x, dots);
        }
    }
}

unsigned int count(map<string, vector<string>> &net, string &id, unsigned int &counter)
{
    
    unsigned int newCounter = counter + net[id].size();
    if (net[id].size()>0)
    {
        for (auto ele : net[id])
        {
            return count(net, ele, newCounter);
        }
    }
    else
    {
        return counter;
    }

    return 0;
}

int main()
{
    // TODO: Implement the datastructure here

    map<string, vector<string>> netowrk;

    while (true)
    {
        std::string line;
        std::cout << "> ";
        getline(std::cin, line);
        std::vector<std::string> parts = split(line, ' ', true);

        std::string command = parts.at(0);

        if (command == "S" or command == "s")
        {
            if (parts.size() != 3)
            {
                std::cout << "Erroneous parameters!" << std::endl
                          << HELP_TEXT;
                continue;
            }
            std::string id1 = parts.at(1);
            std::string id2 = parts.at(2);

            // TODO: Implement the command here!
            addToNetwork(netowrk, id1, id2);
        }
        else if (command == "P" or command == "p")
        {
            if (parts.size() != 2)
            {
                std::cout << "Erroneous parameters!" << std::endl
                          << HELP_TEXT;
                continue;
            }
            std::string id = parts.at(1);

            // TODO: Implement the command here!
            string emptyToBeDots = "";
            printNetwork(netowrk, id, emptyToBeDots);
        }
        else if (command == "C" or command == "c")
        {
            if (parts.size() != 2)
            {
                std::cout << "Erroneous parameters!" << std::endl
                          << HELP_TEXT;
                continue;
            }
            std::string id = parts.at(1);

            // TODO: Implement the command here!
            unsigned int counter = 0;
            cout << count(netowrk, id, counter) << endl;
        }
        else if (command == "D" or command == "d")
        {
            if (parts.size() != 2)
            {
                std::cout << "Erroneous parameters!" << std::endl
                          << HELP_TEXT;
                continue;
            }
            std::string id = parts.at(1);

            // TODO: Implement the command here!
        }
        else if (command == "Q" or command == "q")
        {
            return EXIT_SUCCESS;
        }
        else
        {
            std::cout << "Erroneous command!" << std::endl
                      << HELP_TEXT;
        }
    }
}
