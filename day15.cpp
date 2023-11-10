#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <sstream>
#include <algorithm>
#include <cctype>
#include <list>
#include <stack>

using Pos = std::pair<long, long>;

struct Sensor 
{
    Pos pos;
    Pos beacon;
};

bool debug = false;

int main()
{
    std::vector<Sensor> sensors {
        Sensor{{2924811, 3544081}, {3281893, 3687621}},
        Sensor{{2719183, 2520103}, {2872326, 2415450}},
        Sensor{{3754787, 3322726}, {3281893, 3687621}},
        Sensor{{1727202, 1485124}, {1329230, 1133797}},
        Sensor{{2517008, 2991710}, {2454257, 2594911}},
        Sensor{{1472321, 3123671}, {2216279, 3414523}},
        Sensor{{3456453, 3959037}, {3281893, 3687621}},
        Sensor{{3997648, 2624215}, {4401794, 2000000}},
        Sensor{{463281, 967584},   {1329230, 1133797}},
        Sensor{{2395529, 1897869}, {2454257, 2594911}},
        Sensor{{3094466, 3888307}, {3281893, 3687621}},
        Sensor{{2737812, 3928154}, {2744537, 4159197}},
        Sensor{{813538, 3874308},  {2216279, 3414523}},
        Sensor{{822358, 1997263},  {1329230, 1133797}},
        Sensor{{3993754, 3951321}, {3281893, 3687621}},
        Sensor{{2585409, 3541887}, {2216279, 3414523}},
        Sensor{{3269796, 3730504}, {3281893, 3687621}},
        Sensor{{3075750, 2873879}, {2872326, 2415450}},
        Sensor{{1357, 2747918},    {-1077481,3057204}},
        Sensor{{2256257, 344800},  {1854450, -900998}},
        Sensor{{2779742, 2308087}, {2872326, 2415450}},
        Sensor{{867692, 64146},    {1329230, 1133797}},
        Sensor{{3454465, 966419},  {4401794, 2000000}},
        Sensor{{1902550, 2398376}, {2454257, 2594911}}
    };

    std::set<Pos> visited_positions;
    for(const auto& s : sensors)
    {
        // Manhattan distance -> abs sum of coords diffs
        const auto distance = std::abs(s.pos.first - s.beacon.first) + std::abs(s.pos.second - s.beacon.second);

        const auto LINE_NO = 2000000;
        const auto y_diff = std::abs(s.pos.second - LINE_NO);
        const auto x_diff = std::abs(distance - y_diff);
        
        if(debug)
        {
            std::cout << "distance " << distance << '\n';
            std::cout << "position " << s.pos.first << "," << s.pos.second << '\n';
            std::cout << "beacon " << s.beacon.first << "," << s.beacon.second << '\n';
            std::cout << "y diff " << y_diff << " x diff " << x_diff << '\n';
            std::cout << "from " << s.pos.second - x_diff << " to " <<  s.pos.second + x_diff << " " << 2 * x_diff + 1 << '\n';
        }
        
        if(y_diff > distance)
        {
            if(debug)
            {
                std::cout << "not considering sensor\n";
            }
            continue;
        }

        if(debug)
        {
            std::cout << "adding " << 2 * x_diff + 1 << '\n';
        }

        for(int x = s.pos.first - x_diff; x <= s.pos.first + x_diff; ++x)
        {
            if(!visited_positions.count(Pos{x, LINE_NO}))
                visited_positions.insert(Pos{x, LINE_NO});
        }
    }

    std::cout << "result before removing beacons " << visited_positions.size() << '\n';

    for(const auto& s : sensors)
    {
        // visited_positions.erase(s.pos);
        visited_positions.erase(s.beacon);
    }

    std::cout << "result " << visited_positions.size() << '\n';

    // for(const auto& pos : visited_positions)
    // {
    //     std::cout << pos.first << "," << pos.second << " ";
    // }
    // std::cout << '\n';

    return 0;
}
