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
    int cycle = 0;
    long x = 1;

    using Line = std::array<char, 40>;
    Line display_line{'.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.'};
    std::array<Line, 6> display { display_line, display_line, display_line, display_line, display_line, display_line };
    int line_no = 0;
    
    while(std::getline(in, line))
    {
        int cycles = 0;
        int add_after = -1;
        std::stringstream ss{line};
        ss >> cmd;

        if(cmd == "addx")
        {
            ss >> number;
            cycles += 2;
            // std::cout << "will add after " << cycle + 1 << '\n';
            add_after = cycle + 1;
        }
        else if (cmd == "noop")
        {
            cycles += 1;
        }

        while(cycles-- > 0)
        {
            //pixel rendered pos = cycle - 1
            int rendering_pos = cycle % 40;
            if(rendering_pos == x - 1 || rendering_pos == x || rendering_pos == x + 1)
            {
                display[line_no][rendering_pos] = '#';
            }

            // after cycle n
            if(add_after == cycle)
            {
                x += number;
            }

            std::cout << "rendering at " << line_no << ":" << rendering_pos << " after cycle " << cycle << " value " << x << '\n';

            // during cycle
            if(cycle == 40 || cycle == 80 || cycle == 120 || cycle == 160 || cycle == 200)
            {
                std::cout << "next line\n";
                line_no++;
            }

            cycle++;
        }
    }

    for(auto line : display)
    {
        for(auto c : line)
        {
            std::cout << c;
        }
        std::cout << '\n';
    }

    in.close();
    return 0;
}