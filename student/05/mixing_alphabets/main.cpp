#include <iostream>
#include <string>
#include <algorithm>
#include <random>

int main()
{
    // This is a random number generator that should be given as parameter to the
    // function of the algorithm library to shuffle letters
    std::minstd_rand generator;

    std::cout << "Enter some text. Quit by entering the word \"END\"." << std::endl;
    std::string word = "";
    std::vector<char> interim;
    std::vector<std::string> wordShuffled;

    while (std::cin >> word)
    {
        if (word == "END")
        {   
            for (auto ele: wordShuffled){
                std::cout<<ele<<std::endl;
            }
            return EXIT_SUCCESS;
        }

        // TODO: implement your solution here
        if (word.length() > 1)
        {
            interim.clear();
            for (std::string::size_type i = 0; i < word.length(); i++)
            {
                interim.push_back(word[i]);
            }
            std::shuffle(interim.begin() + 1, interim.end() - 1, generator);
            std::vector<char>::iterator iter;
            iter = interim.begin();

            for (std::string::size_type j = 0; j < word.length(); j++)
            {
                word[j] = *iter;
                ++iter;
            }
        }
        wordShuffled.push_back(word);

    }
}
