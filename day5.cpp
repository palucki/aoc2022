#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <sstream>
#include <algorithm>
#include <cctype>
#include <stack>
#include <array>

int main()
{
    std::fstream in("day5_input.txt", std::ios::in);
    if(!in.is_open())
    {
        std::cout << "Could not open file for reading!\n";
        return -1;
    }

    std::string line;
    std::string result;


// [N]         [C]     [Z]            
// [Q] [G]     [V]     [S]         [V]
// [L] [C]     [M]     [T]     [W] [L]
// [S] [H]     [L]     [C] [D] [H] [S]
// [C] [V] [F] [D]     [D] [B] [Q] [F]
// [Z] [T] [Z] [T] [C] [J] [G] [S] [Q]
// [P] [P] [C] [W] [W] [F] [W] [J] [C]
// [T] [L] [D] [G] [P] [P] [V] [N] [R]
//  1   2   3   4   5   6   7   8   9 

    std::array<std::stack<char>, 9> stacks {
        std::stack<char>{{'T', 'P', 'Z', 'C', 'S', 'L', 'Q', 'N'}}, 
        std::stack<char>{{'L', 'P', 'T', 'V', 'H', 'C', 'G'}}, 
        std::stack<char>{{'D', 'C', 'Z', 'F'}}, 
        std::stack<char>{{'G', 'W', 'T', 'D', 'L', 'M', 'V', 'C'}}, 
        std::stack<char>{{'P', 'W', 'C'}}, 
        std::stack<char>{{'P', 'F', 'J', 'D', 'C', 'T', 'S', 'Z'}}, 
        std::stack<char>{{'V', 'W', 'G', 'B', 'D'}}, 
        std::stack<char>{{'N', 'J', 'S', 'Q', 'H', 'W'}}, 
        std::stack<char>{{'R', 'C', 'Q', 'F', 'S', 'L', 'V'}}, 
    };

    while(std::getline(in, line))
    {
        std::cout << line << "\n";

        std::string temp;
        int how_many, from, to;
        std::stringstream ss{line};
        ss >> temp >> how_many >> temp >> from >> temp >> to;

        for(int i = 0; i < how_many; ++i)
        {
            auto moved = stacks[from-1].top();
            stacks[from-1].pop();
            stacks[to-1].push(moved);
        }

        // std::cout << "boundaries " << a << " " << b << " " << c << " " << d << '\n';

        // bool no_overlap = b < c || a > d;
        // if(!no_overlap)
        // {
        //     result++;
        // }
    }

    std::cout << "result ";
    for(int i = 0; i < 9; ++i)
    {
        std::cout << stacks[i].top();
    }

    std::cout << '\n';

    in.close();
    return 0;
}