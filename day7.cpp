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

    long root_size = path[0].size;

    // Add all from the path
    for(const auto& d : path)
    {
        already_traversed.push_back(d);
    }
    // already_traversed.push_back(path[0]);

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

    long unused_space = 70000000 - root_size;
    long need_to_free = 30000000 - unused_space;
    std::cout << "need to free " << need_to_free << '\n';

    long smallest_dir_size = 70000000;

    for(const auto & dir : already_traversed)
    {
        if(dir.size >= need_to_free && dir.size < smallest_dir_size)
        {
            smallest_dir_size = dir.size;
        }
    }

    std::cout << "Smallest dir size " << smallest_dir_size << '\n';

    in.close();
    return 0;
}