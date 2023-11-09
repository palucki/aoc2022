#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <sstream>
#include <algorithm>
#include <cctype>
#include <list>
#include <stack>

const int MAP_SIZE = 50;
// [y][x]
const int X_OFFSET = 10;
const int Y_OFFSET = 10;

using Map = std::array<std::array<char, MAP_SIZE>, MAP_SIZE>;
using Pos = std::pair<int, int>;

struct Sensor 
{
    Pos pos;
    Pos beacon;
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

void print(const Map& map)
{
    int line_no = -Y_OFFSET;
    for(const auto& arr : map)
    {
        std::cout << line_no++ << ":";
        for(const auto& n : arr)
        {
            std::cout << n;
        }
        std::cout << '\n';
    }
}

int main()
{
    Map map;

    init(map);

    std::vector<Sensor> sensors {
        Sensor{{2, 18}, {-2, 15}},
        Sensor{{9, 16}, {10, 16}},
        Sensor{{13, 2}, {15, 3}},
        Sensor{{12, 14}, {10, 16}},
        Sensor{{10, 20}, {10, 16}},
        Sensor{{14, 17}, {10, 16}},
        Sensor{{8, 7}, {2, 10}},
        Sensor{{2, 0}, {2, 10}},
        Sensor{{0, 11}, {2, 10}},
        Sensor{{20, 14}, {25, 17}},
        Sensor{{17, 20}, {21, 22}},
        Sensor{{16, 7}, {15, 3}},
        Sensor{{14, 3}, {15, 3}},
        Sensor{{20, 1}, {15, 3}}
    };

    for(auto& s : sensors)
    {
        s.pos.first += X_OFFSET;
        s.beacon.first += X_OFFSET;

        s.pos.second += Y_OFFSET;
        s.beacon.second += Y_OFFSET;

        // Manhattan distance -> abs sum of coords diffs
        const auto distance = std::abs(s.pos.first - s.beacon.first) + std::abs(s.pos.second - s.beacon.second);
        // std::cout << "distance " << distance << '\n';

        for(int y = s.pos.first - distance; y <= s.pos.first + distance; ++y)
        {
            for(int x = s.pos.second - distance; x <= s.pos.second + distance; ++x)
            {
                const auto current_distance = std::abs(s.pos.first - y) + std::abs(s.pos.second - x);
                if(current_distance <= distance)
                {
                    if(x < 0 || y < 0 || x >= map.size() || y >= map.size())
                    {
                        std::cout << "Fatal error at " << y << "," << x << ", need bigger map\n";
                        return -1;
                    }
                    map[y][x] = '#';
                }

            }
        }

        map[s.pos.second][s.pos.first] = 'S';
        map[s.beacon.second][s.beacon.first] = 'B';
    }

    // print(map);
    
    int result = 0;
    for(int x = 0; x < map.size(); ++x)
    {
        if(map[10 + Y_OFFSET][x] == '#')
        {
            result++;
        }
    }

    std::cout << "There are " << result << " occupied positions\n";

    return 0;
}
