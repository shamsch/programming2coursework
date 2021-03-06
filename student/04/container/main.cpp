#include <cstdlib>
#include <iostream>
#include <vector>

void read_integers(std::vector<int> &ints, int count)
{
    int new_integer = 0;
    for (int i = 0; i < count; ++i)
    {
        std::cin >> new_integer;
        ints.push_back(new_integer);
    }
}

// TODO: Implement your solution here

bool same_values(const std::vector<int> ints)
{
    if (ints.front() == ints.back())
    {
        return true;
    }
    else
    {
        return false;
    }
}
bool is_ordered_non_strict_ascending(const std::vector<int> ints)
{
    bool order = true;
    std::vector<int>::size_type x = ints.size();
    int sizeOfTheVector = x;
    for (int i = 0; i < sizeOfTheVector; i++)
    {
        if (i != sizeOfTheVector - 1)
        {
            if (ints.at(i) <= ints.at(i + 1))
            {
                continue;
            }
            else
            {
                order = false;
                return order;
            }
        }
    }
    return order;
}
bool is_arithmetic_series(const std::vector<int> ints)
{
    bool arith = true;
    int diff = 0;
    diff = ints.at(1) - ints.at(0);
    std::vector<int>::size_type x = ints.size();
    int sizeOfTheVector = x;
    for (int i = 0; i < sizeOfTheVector - 1; i++)
    {
        int running_diff = ints.at(i + 1) - ints.at(i);
        if (running_diff != diff)
        {
            arith = false;
            break;
        }
    }
    return arith;
}
bool is_geometric_series(const std::vector<int> ints)
{
    bool geo = true;
    int rat = 0;
    if (ints.at(1) != 0 && ints.at(0) != 0)
    {
        rat = (ints.at(1)) / (ints.at(0));
        std::vector<int>::size_type x = ints.size();
        int sizeOfTheVector = x;
        for (int i = 0; i < sizeOfTheVector - 1; i++)
        {
            if (ints.at(i) != 0 && ints.at(i + 1) != 0)
            {
                int running_rat = (ints.at(i + 1)) / (ints.at(i));
                if (running_rat != rat)
                {
                    geo = false;
                    break;
                }
            }
            else{
                return false;
            }
        }
    }
    else{
        return false;
    }

    return geo;
}

int main()
{
    std::cout << "How many integers are there? ";
    int how_many = 0;
    std::cin >> how_many;

    std::cout << "Enter the integers: ";
    std::vector<int> integers;
    read_integers(integers, how_many);

    if (same_values(integers))
        std::cout << "All the integers are the same" << std::endl;
    else
        std::cout << "All the integers are not the same" << std::endl;

    if (is_ordered_non_strict_ascending(integers))
        std::cout << "The integers are in a non-strict ascending order" << std::endl;
    else
        std::cout << "The integers are not in a non-strict ascending order" << std::endl;

    if (is_arithmetic_series(integers))
        std::cout << "The integers form an arithmetic series" << std::endl;
    else
        std::cout << "The integers do not form an arithmetic series" << std::endl;

    if (is_geometric_series(integers))
        std::cout << "The integers form a geometric series" << std::endl;
    else
        std::cout << "The integers do not form a geometric series" << std::endl;

    return EXIT_SUCCESS;
}
