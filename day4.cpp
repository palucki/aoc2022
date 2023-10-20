#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <sstream>
#include <algorithm>
#include <cctype>

int main()
{
    std::fstream in("day4_input.txt", std::ios::in);
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
        std::replace(line.begin(), line.end(), ',', ' ');
        std::replace(line.begin(), line.end(), '-', ' ');
        std::stringstream ss{line};
        int a, b, c, d;
        ss >> a >> b >> c >> d;

        std::cout << "boundaries " << a << " " << b << " " << c << " " << d << '\n';

        if((a >= c && b <= d ) || (c>= a && d<= b))
        {
            result++;   
        }
    }

    std::cout << "result " << result << "\n";
    in.close();
    return 0;
}