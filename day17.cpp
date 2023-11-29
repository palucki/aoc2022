#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <sstream>
#include <algorithm>
#include <cctype>
#include <list>
#include <stack>

// const int MAP_SIZE = 500;
// const int X_OFFSET = 300;

// const int MAP_SIZE = 25;
// const int X_OFFSET = 488;
// const int FLOOR = 165;

const int HEIGHT = 8000;
const int WIDTH = 7;

using Map = std::array<std::array<char, WIDTH>, HEIGHT>;
using Pos = std::pair<int, int>;

struct Shape
{
    bool move(char direction, Map& map)
    {
        std::vector<Pos> new_pos = occupied;
        
        if(direction == '>')
        {
            // std::cout << "move right\n";
            for(auto& e : new_pos)
                e.first += 1;
        }
        else if(direction == '<')
        {
            // std::cout << "move left\n";
            for(auto& e : new_pos)
                e.first -= 1;
        }
        else 
        {
            // std::cout << "move down\n";
            for(auto& e : new_pos)
                e.second -= 1;
        }

        for(const auto& a : new_pos)
        {
            if(a.first < 0 || a.first >= WIDTH || a.second < 0 || map[a.second][a.first] == '#')
            {
                return false;
            }
        }

        for(const auto& a : occupied)
        {
            map[a.second][a.first] = '.';
        }

        occupied = new_pos;
        
        for(const auto& a : occupied)
        {
            map[a.second][a.first] = '#';
        }

        return true;
    }

    std::vector<Pos> occupied;
};

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

void print(const Map& map, int height)
{
    for(int i = height; i >= 0; --i)
    {
        for(int j = 0; j < map[i].size(); ++j)
        {
            std::cout << map[i][j];
        }
        std::cout << '\n';
    }
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
    std::fstream in("day17_input.txt", std::ios::in);
    if(!in.is_open())
    {
        std::cout << "Could not open file for reading!\n";
        return -1;
    }

    std::string sequence;
    int rock_number = 1;

    Map map;
    init(map);

    if(!std::getline(in, sequence))
    {
        return -1;
    }

    bool stop = false;
    Shape shape;
    shape.occupied = {
        {2, 7},
        {3, 7},
        {4, 7},
        {5, 7}
    };

    print(map, 10);

    for(int i = 0; i < 10; ++i)
    {
        if(shape.move('<', map))
        {
            std::cout << "Can move\n";
        }
    }

    print(map, 10);

    return 0;
}
