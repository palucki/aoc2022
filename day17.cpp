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
        for(const auto& a : occupied)
        {
            map[a.second][a.first] = '.';
        }

        std::vector<Pos> new_pos = occupied;
        
        if(direction == '>')
        {
            std::cout << "move right\n";
            for(auto& e : new_pos)
                e.first += 1;
        }
        else if(direction == '<')
        {
            std::cout << "move left\n";
            for(auto& e : new_pos)
                e.first -= 1;
        }
        else 
        {
            std::cout << "move down\n";
            for(auto& e : new_pos)
                e.second -= 1;
        }

        for(const auto& a : new_pos)
        {
            if(a.first < 0 || a.first >= WIDTH || a.second < 0 || map[a.second][a.first] == '#')
            {
                std::cout << " new coords: " << a.first << " " << a.second << '\n';

                for(const auto& a : occupied)
                {
                    map[a.second][a.first] = '#';
                }

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
            map[a.second][a.first] = '@';
        }

        return true;
    }

    bool place(Map& map, int height)
    {
        if(height >= HEIGHT)
        {
            std::cout << "EXCEEDED HEIGHT\n";
            return false;
        }

        for(auto& e : occupied)
        {
            e.second += height;
            map[e.second][e.first] = '@';
        }

        return true;
    }

    int top()
    {
        return std::max_element(occupied.begin(), occupied.end(), [](const Pos& lhs, const Pos& rhs)
        {
            return lhs.second < rhs.second;
        })->second + 1;
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

int main()
{
    std::fstream in("day17_input.txt", std::ios::in);
    if(!in.is_open())
    {
        std::cout << "Could not open file for reading!\n";
        return -1;
    }

    std::string sequence;
    int rock_number = 0;

    Map map;
    init(map);

    if(!std::getline(in, sequence))
    {
        return -1;
    }

    Shape line{{{2, 0}, {3, 0}, {4, 0}, {5, 0}}};
    Shape cross{{{2, 1}, {3, 1}, {4, 1}, {3, 0}, {3, 2}}};
    Shape l{{{2, 0}, {3, 0}, {4, 0}, {4, 1}, {4, 2}}};
    Shape stick{{{2, 0}, {2, 1}, {2, 2}, {2, 3}}};
    Shape cube{{{2, 0}, {2, 1}, {3, 0}, {3, 1}}};
    std::vector<Shape> shapes{line, cross, l, stick, cube};

    int height_so_far = 0;
    int move_number = 0;

    while(rock_number < 2022)
    // while(rock_number < 11)
    {
        bool stop = false;

        auto rock = shapes[rock_number % shapes.size()];

        rock.place(map, height_so_far + 3);
        std::cout << "Placing shape at " << height_so_far + 3 << '\n';
        print(map, 20);
        // const auto rock = rocks[rock_number % rocks.size()];

        while(!stop)
        {
            const auto move = sequence[move_number++ % sequence.size()];
            if(!rock.move(move, map))
            {
                std::cout << "Cannot move " << move << '\n';
            }

            if(!rock.move('V', map))
            {
                std::cout << "Can not move down after " << move_number-1 << " moves\n";
                stop = true;
            }
            print(map, 20);
        }

        std::cout << "rock top at: " << rock.top() << '\n';
        
        for(const auto& e : rock.occupied)
        {
            std::cout << e.second << "," << e.first << " ";
        }
        std::cout << '\n';

        height_so_far = std::max(height_so_far, rock.top());
        rock_number++;
        std::cout << "After rock " << rock_number << " max height " << height_so_far << '\n';
    }

    // print(map, 10);

    return 0;
}
