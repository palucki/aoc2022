#include <iostream>
#include <fstream>
#include <string>
#include <set>

void read_function()
{
    std::fstream in("day1_input.txt", std::ios::in);
    if(!in.is_open())
    {
        std::cout << "Could not open file for reading!\n";
        return;
    }

    std::multiset<long> sums;

    int elf_number = 1;
    int elf_sum = 0;

    std::string line;
    while(std::getline(in, line))
    {
        // std::cout << line << "\n";
        if(line.empty())
        {
            sums.insert(elf_sum);

            // std::cout << "Elf sum " << elf_sum << " for elf " << elf_number << '\n';
            
            elf_number++;
            elf_sum = 0;
            continue;
        }

        elf_sum += std::stoi(line);
    }
    in.close();

    for(auto rit = sums.rbegin(); rit != sums.rend(); ++rit)
    {
        std::cout << "Elf sum " << *rit << '\n';
    }

}

int main()
{
    read_function();

    return 0;
}