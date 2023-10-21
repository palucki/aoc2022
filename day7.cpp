#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <sstream>
#include <algorithm>
#include <cctype>
#include <list>
#include <stack>

struct Directory 
{
    std::string name;
    int size{0};
};

int main()
{
    std::fstream in("day7_input.txt", std::ios::in);
    if(!in.is_open())
    {
        std::cout << "Could not open file for reading!\n";
        return -1;
    }

    std::string line;

    std::vector<Directory> already_traversed;
    std::vector<Directory> path;
    
    while(std::getline(in, line))
    {
        std::cout << "Input " << line << '\n';
        
        if(line.substr(0, 4) == "$ cd")
        {
            if(line.substr(5, 2) == "..")
            {
                std::cout << "Going out of directory " << path[path.size() - 1].name << '\n';
                already_traversed.push_back(path[path.size() - 1]);
                path.pop_back();
            }
            else 
            {
                const std::string directory_name = line.substr(5);
                path.push_back(Directory{directory_name, 0});
                std::cout << "Going into directory " << directory_name << '\n';
            }
        }
        else if(line.substr(0, 3) != "dir" && line[0] != '$')
        {
            std::stringstream ss{line};
            int file_size;
            ss >> file_size;
            std::cout << "Found file with size: " << file_size << '\n';

            for(auto& d : path)
            {
                d.size += file_size;
            }
        }
    }

    // Add "/"
    already_traversed.push_back(path[0]);

    long result = 0;
    for(const auto & dir : already_traversed)
    {
        std::cout << "Directory " << dir.name << " size " << dir.size << '\n';
        if(dir.size <= 100000)
        {
            result += dir.size;
        }
    }

    std::cout << "Result " << result << '\n';

    in.close();
    return 0;
}