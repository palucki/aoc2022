#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <sstream>
#include <algorithm>
#include <cctype>
#include <list>
#include <stack>
#include <map>

using Pos = std::pair<long, long>;

struct Sensor 
{
    Pos pos;
    Pos beacon;
};

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

        // results
        // 4 for [2754143,3214126] = 4     -> 11016575214126 OK
        // 4 for [3281893,3687619] = 4
        // 4 for [3281893,3687620] = 4
    };

    const auto LIMIT = 4000000;
    const auto DEBUG = false;

    std::map<Pos, int> potentially_free_positions;

    auto check_border = [&potentially_free_positions](const Pos& start, const Pos& end, const Pos& move1, const Pos& move2)
    {
        auto current = start;
        while(current != end)
        {
            current.first += move1.first;
            current.second += move1.second;

            if(current.first >= 0 && current.first <= LIMIT && current.second >= 0 && current.second <= LIMIT )   // exclude outside the range
            {
                potentially_free_positions[current]++;
            }

            current.first += move2.first;
            current.second += move2.second;

            if(current.first >= 0 && current.first <= LIMIT && current.second >= 0 && current.second <= LIMIT )   // exclude outside the range
            {
                potentially_free_positions[current]++;
            }
        }
    };

    for(const auto& s : sensors)
    {
        // Manhattan distance -> abs sum of coords diffs
        const auto distance = std::abs(s.pos.first - s.beacon.first) + std::abs(s.pos.second - s.beacon.second);
        
        if(DEBUG)
        {
            // std::cout << "distance " << distance << '\n';
            std::cout << "position " << s.pos.first << "," << s.pos.second << '\n';
            // std::cout << "beacon " << s.beacon.first << "," << s.beacon.second << '\n';
        }

        const auto new_distance = distance + 2; // border, but remember to exclude the "spike" points
        
        const Pos move_up = {0, -1};
        const Pos move_down = {0, 1};
        const Pos move_left = {-1, 0};
        const Pos move_right = {1, 0};

        const Pos left_anchor = {s.pos.first - new_distance, s.pos.second};
        const Pos right_anchor = {s.pos.first + new_distance, s.pos.second};
        const Pos top_anchor = {s.pos.first, s.pos.second - new_distance};
        const Pos bottom_anchor = {s.pos.first, s.pos.second + new_distance};

        check_border(left_anchor, top_anchor, move_right, move_up);
        check_border(top_anchor, right_anchor, move_down, move_right);
        check_border(right_anchor, bottom_anchor, move_left, move_down);
        check_border(bottom_anchor, left_anchor, move_up, move_left);

        potentially_free_positions[left_anchor]--;
        potentially_free_positions[right_anchor]--;
        potentially_free_positions[top_anchor]--;
        potentially_free_positions[bottom_anchor]--;
    }

    std::cout << "potentially free size : " << potentially_free_positions.size() << '\n';
    for (const auto& [key, value] : potentially_free_positions)
    {
        if(value > 3)
            std::cout << value << " for "<< '[' << key.first << ',' << key.second << "] = " << value << '\n';
    }

    return 0;
}
