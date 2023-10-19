#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <sstream>
#include <algorithm>
#include <cctype>

int main()
{
    std::fstream in("day3_input.txt", std::ios::in);
    if(!in.is_open())
    {
        std::cout << "Could not open file for reading!\n";
        return -1;
    }

    std::string line;
    long result = 0;
    while(std::getline(in, line))
    {
        std::cout << line << "\n";
        std::string first_part = line.substr(0, line.length()/2);
        std::string second_part = line.substr(line.length()/2);
        
        std::set<char> first_part_set{first_part.begin(), first_part.end()};
        std::set<char> second_part_set{second_part.begin(), second_part.end()};

        std::string common;
        std::set_intersection(first_part_set.begin(), first_part_set.end(), 
                              second_part_set.begin(), second_part_set.end(),
                              std::back_inserter(common));

        std::cout << "first part " << first_part << " and second " << second_part << " common part " << common << "\n";

        
        int priority = 0;
        if(std::isupper(common[0]))
        {
            priority += 26;
        }

        priority += int(std::toupper(common[0]) - 64);

        result += priority;
    }

    std::cout << "result " << result << "\n";
    in.close();
    return 0;
}