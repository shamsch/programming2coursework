#include <iostream>
#include <string>
#include <vector>

// TODO: Implement split function here
// Do not change main function

std::vector<std::string> split(std::string line, char sep, bool ignore = false)
{
    std::string temp = "";
    std::vector<std::string> vectorResult;
    int count = 0;
    if (ignore)
    {
        for (std::string::size_type i = 0; i < line.length(); i++)
        {
            if (line[i] == sep)
            {
                if (temp != "")
                {
                    vectorResult.push_back(temp);
                    temp = "";
                }
            }
            else
            {
                temp = temp + line[i];
            }
        }
        if (temp != "")
        {
            vectorResult.push_back(temp);
        }
    }
    else
    {
        for (std::string::size_type i = 0; i < line.length(); i++)
        {
            if (line[i] == sep)
            {
                if (temp != "")
                {
                    vectorResult.push_back(temp);
                    temp = "";
                }
                count += 1;
                if (count > 1)
                {
                    vectorResult.push_back(" ");
                    if (count==3){
                        vectorResult.push_back(" ");
                    }
                }
            }
            else
            {
                temp += line[i];
                count = 0;
            }
        }
        if (temp != "")
        {
            vectorResult.push_back(temp);
        }
    }

    return vectorResult;
}

int main()
{
    std::string line = "";
    std::cout << "Enter a string: ";
    getline(std::cin, line);
    std::cout << "Enter the separator character: ";
    char separator = getchar();

    std::vector<std::string> parts = split(line, separator);
    std::cout << "Splitted string including empty parts: " << std::endl;
    for (auto part : parts)
    {
        std::cout << part << std::endl;
    }

    std::vector<std::string> parts_no_empty = split(line, separator, true);
    std::cout << "Splitted string ignoring empty parts: " << std::endl;
    for (auto part : parts_no_empty)
    {
        std::cout << part << std::endl;
    }
}
