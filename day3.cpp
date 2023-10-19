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
    int group_counter = 0;
    
    std::set<char> first, second, third;

    while(std::getline(in, line))
    {
        if(group_counter == 0)
        {
            first = {line.begin(), line.end()};
            group_counter++;
        }
        else if(group_counter == 1)
        {
            second = {line.begin(), line.end()};
            group_counter++;
        }
        else if(group_counter == 2)
        {
            third = {line.begin(), line.end()};

            std::vector<char> common;
            std::set_intersection(first.begin(), first.end(), 
                                  second.begin(), second.end(),
                                  std::back_inserter(common));
            second = {common.begin(), common.end()};

            std::vector<char> common_2;
            std::set_intersection(second.begin(), second.end(), 
                                  third.begin(), third.end(),
                                  std::back_inserter(common_2));

            std::cout << " common part " << common_2[0] << "\n";

            // perform summary
            group_counter = 0;

            int priority = 0;
            if(std::isupper(common_2[0]))
            {
                priority += 26;
            }

            priority += int(std::toupper(common_2[0]) - 64);
            result += priority;
        }
    }

    std::cout << "result " << result << "\n";
    in.close();
    return 0;
}