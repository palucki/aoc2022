#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <sstream>
#include <algorithm>
#include <cctype>
#include <list>
#include <stack>

int main()
{
    std::fstream in("day10_input.txt", std::ios::in);
    if(!in.is_open())
    {
        std::cout << "Could not open file for reading!\n";
        return -1;
    }

    std::string line;
    bool in_add = false;
    std::string cmd;
    int number;
    int cycle = 1;
    long x = 1;
    long result = 0;
    
    while(std::getline(in, line))
    {
        std::cout << "Input " << line << '\n';

        int cycles = 0;
        int add_after = -1;
        std::stringstream ss{line};
        ss >> cmd;

        if(cmd == "addx")
        {
            ss >> number;
            cycles += 2;
            std::cout << "will add after " << cycle + 1 << '\n';
            add_after = cycle + 1;
        }
        else if (cmd == "noop")
        {
            cycles += 1;
        }

        while(cycles-- > 0)
        {
            // during cycle
            if(cycle == 20 || cycle == 60 || cycle == 100 || cycle == 140 || cycle == 180 || cycle == 220)
            {
                result += cycle * x;
            }

            // after cycle n
            if(add_after == cycle)
            {
                x += number;
            }

            std::cout << "after cycle " << cycle << " value " << x << '\n';
            cycle++;
        }
    }

    std::cout << "result " << result << '\n';

    in.close();
    return 0;
}