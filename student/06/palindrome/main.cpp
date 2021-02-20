#include <iostream>
#include <string>
#ifndef RECURSIVE_FUNC
#define RECURSIVE_FUNC
#endif

bool palindrome_recursive(std::string inputString)
{
    RECURSIVE_FUNC
    // Do not remove RECURSIVE_FUNC declaration, it's necessary for automatic testing to work
    // ------------

    // Add your implementation here
    std::string s="";
    s+=inputString;
    int len = s.length() - 1;
    if (0>=len)
    {
        return true;
    }
    if (s[0] != s[len])
    {
        return false;
    }
    s.pop_back();
    s.erase(s.begin());
    return palindrome_recursive(s);
}

// Do not modify rest of the code, or the automated testing won't work.
#ifndef UNIT_TESTING
int main()
{
    std::cout << "Enter a word: ";
    std::string word;
    std::cin >> word;

    if (palindrome_recursive(word))
    {
        std::cout << word << " is a palindrome" << std::endl;
    }
    else
    {
        std::cout << word << " is not a palindrome" << std::endl;
    }
}
#endif
