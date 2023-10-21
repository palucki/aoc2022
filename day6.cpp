#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <sstream>
#include <algorithm>
#include <cctype>
#include <list>

int main()
{
    std::fstream in("day6_input.txt", std::ios::in);
    if(!in.is_open())
    {
        std::cout << "Could not open file for reading!\n";
        return -1;
    }

    std::string line;
    
    while(std::getline(in, line))
    {
        std::cout << "Input " << line << '\n';
        bool packet_start_found = false;
        
        for(int i = 3; i < line.size() && !packet_start_found; ++i)
        {
            std::set<char> window{line.begin() + i - 3, line.begin() + i + 1};
            if(window.size() == 4)
            {
                std::cout << "Start of packet " <<  i + 1 << '\n';
                packet_start_found = true;
            }
        }

        bool message_start_found = false;
        for(int i = 13; i < line.size() && !message_start_found; ++i)
        {
            std::set<char> window{line.begin() + i - 13, line.begin() + i + 1};
            if(window.size() == 14)
            {
                std::cout << "Start of message " <<  i + 1 << '\n';
                message_start_found = true;
            }
        }
    }

    in.close();
    return 0;
}