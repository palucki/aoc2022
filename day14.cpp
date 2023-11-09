#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <sstream>
#include <algorithm>
#include <cctype>
#include <list>
#include <stack>

const int MAP_SIZE = 200;
const int X_OFFSET = 400;

using Map = std::array<std::array<char, MAP_SIZE>, MAP_SIZE>;

void init(Map& map)
{
    for(auto& arr : map)
    {
        for(auto& n : arr)
        {
            n = '.';
        }
    }
}

void print(const Map& map)
{
    for(const auto& arr : map)
    {
        for(const auto& n : arr)
        {
            std::cout << n;
        }
        std::cout << '\n';
    }
}

std::vector<std::string> split(std::string s, std::string delimiter) 
{
    size_t pos_start = 0, pos_end, delim_len = delimiter.length();
    std::string token;
    std::vector<std::string> res;

    while ((pos_end = s.find(delimiter, pos_start)) != std::string::npos) {
        token = s.substr (pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        res.push_back (token);
    }

    res.push_back (s.substr (pos_start));
    return res;
}

std::pair<int, int> move(std::pair<int, int> current_pos, const Map& map)
{
    const auto current_y = current_pos.first;
    const auto current_x = current_pos.second;

    //down
    if(current_y+1 >= map.size() || map[current_y+1][current_x] == '.')
    {
        // std::cout << "went down\n";
        return {current_y+1, current_x};
    }
    
    //left 
    if(current_x-1 < 0 || map[current_y+1][current_x-1] == '.')
    {
        // std::cout << "went left\n";
        return {current_y+1, current_x-1};
    }

    //right 
    if(current_x+1 >= map[0].size() || map[current_y+1][current_x+1] == '.')
    {
        // std::cout << "went right\n";
        return {current_y+1, current_x+1};
    }

    return {-1, -1};
}

int main()
{
    std::fstream in("day14_input.txt", std::ios::in);
    if(!in.is_open())
    {
        std::cout << "Could not open file for reading!\n";
        return -1;
    }

    Map map;

    init(map);
    print(map);

    std::string line;     
    while(std::getline(in, line))
    {
        std::cout << "1: " << line << '\n';
        auto res = split(line, "->");
        for(int i = 0; i < res.size() - 1; ++i)
        {
            std::stringstream ss1{res[i]};
            char comma;
            int x1, y1, x2, y2;
            ss1 >> x1 >> comma >> y1;

            std::stringstream ss2{res[i+1]};
            ss2 >> x2 >> comma >> y2;

            auto min_x = std::min(x1, x2);
            auto max_x = std::max(x1, x2);

            auto min_y = std::min(y1, y2);
            auto max_y = std::max(y1, y2);

            for(int x = min_x; x <= max_x; ++x)
            {
                map[y1][x-X_OFFSET] = '#';
            }
            for(int y = min_y; y <= max_y; ++y)
            {
                map[y][x1-X_OFFSET] = '#';
            }
        }
    }
    in.close();

    map[0][500-X_OFFSET] = '+';
    
    int units = 0;
    bool stop=false;
    while(!stop)
    {
        units++;
        std::pair<int, int> sand_pos{0, 500-X_OFFSET};
        std::pair<int, int> last_pos;

        bool sand_moves = true;
        while(sand_moves)
        {
            sand_pos = move(sand_pos, map);
            if(sand_pos == std::pair<int, int>{-1,-1})
            {
                sand_moves = false;
            }
            else 
            {
                if(sand_pos.first > map.size() || sand_pos.second > map[0].size())
                {
                    std::cout << "Sand outside map, units: " << units-1 << "\n";
                    stop = true;
                    break;
                }
                
                // std::cout << "New pos " << sand_pos.first << " " << sand_pos.second << '\n';
                last_pos = sand_pos;
            }
        }
        
        map[last_pos.first][last_pos.second] = 'o';
    }

    print(map);

    return 0;
}
