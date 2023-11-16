#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <set>
#include <fstream>
#include <sstream>
#include <map>
#include <regex>

// trim from start
static inline std::string &ltrim(std::string &s)
{
    s.erase(s.begin(), std::find_if(s.begin(), s.end(),
                                    std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
}

// trim from end
static inline std::string &rtrim(std::string &s)
{
    s.erase(std::find_if(s.rbegin(), s.rend(),
                         std::not1(std::ptr_fun<int, int>(std::isspace)))
                .base(),
            s.end());
    return s;
}

// trim from both ends
static inline std::string &trim(std::string &s)
{
    return ltrim(rtrim(s));
}

std::vector<std::string> split(std::string s, std::string delimiter)
{
    size_t pos_start = 0, pos_end, delim_len = delimiter.length();
    std::string token;
    std::vector<std::string> res;

    while ((pos_end = s.find(delimiter, pos_start)) != std::string::npos)
    {
        token = s.substr(pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        res.push_back(token);
    }

    res.push_back(s.substr(pos_start));
    return res;
}

struct Valve
{
    std::string id;
    int flow_rate;
    std::vector<Valve *> children;
};

int pressure(Valve *v, int time_left, std::map<std::pair<std::string, int>, int>& memo, std::set<std::string> opened_valves = {})
{
    std::cout << "id " << v->id << " time left " << time_left << " memo size " << memo.size() << '\n';

    // if(memo.find({v->id, time_left}) != memo.end())
    // {
        // std::cout << "Returning memo value: " << memo[{v->id, time_left}] << "\n";
    // }
    // if(memo.find({v->id, time_left}) != memo.end())
    // {
    //     std::cout << "Value in memo " << memo[{v->id, time_left}] << '\n';
    //     return memo[{v->id, time_left}];
    // }

    if (time_left <= 1)
    {
        // memo[{v->id, time_left}] = 0;
        return 0;
    }

    std::vector<int> results;
    for (auto *vc : v->children)
    {
        const auto c_pressure = pressure(vc, time_left - 1, memo, opened_valves);
        results.push_back(c_pressure);
        
        // if(memo.find({vc->id, time_left - 1}) != memo.end())
        // {
        //     memo[{vc->id, time_left - 1}] = std::max(c_pressure, memo[{vc->id, time_left - 1}]);
        // }
    }

    if (opened_valves.find(v->id) == opened_valves.end())
    {
        // std::cout << "opening " << v->id << " with flow rate " << v->flow_rate << '\n';
        opened_valves.insert(v->id);
        auto open_valve_result = ((time_left - 1) * v->flow_rate) + pressure(v, time_left - 1, memo, opened_valves);
        results.push_back(open_valve_result);

        // if(memo.find({v->id, time_left - 1}) != memo.end())
        // {
        //     memo[{v->id, time_left - 1}] = std::max(open_valve_result, memo[{v->id, time_left - 1}]);
        // }
    }

    if (results.empty())
    {
        // memo[{v->id, time_left}] = 0;
        return 0;
    }

    auto result = *std::max_element(results.begin(), results.end());
    return result;
    // memo[{v->id, time_left}] = std::max(result, memo[{v->id, time_left}]);
    // return memo[{v->id, time_left}];

    // auto final_result = std::max(result, memo[{v->id, time_left}]);

    // std::cout << "Result " << v->id << " / " << time_left <<  " is " <<  memo[{v->id, time_left}] << '\n';

}

int main()
{
    std::fstream in("day16_input.txt", std::ios::in);
    if (!in.is_open())
    {
        std::cout << "Could not open file for reading!\n";
        return -1;
    }

    std::map<std::string, Valve *> valves;

    std::string line;
    std::regex e ("Valve ([A-Z]+) has flow rate=([0-9]+); tunnels? leads? to valves? ([A-Z ,]+)");
    while (std::getline(in, line))
    {
        std::cout << line << '\n';
        std::smatch m;

        if(!std::regex_match(line, m, e))
        {   
            std::cout << "parsing error\n";
            return -1;
        }

        std::string valve_id = m[1];
        int flow_rate = std::stoi(m[2]);
        auto outputs = split(m[3], ", ");
        std::cout << "valve " << valve_id << " flow " << flow_rate << '\n';
        for(const auto& o : outputs)
            std::cout << " -> " << o;
        std::cout << '\n';
    }

    // Valve aa{"AA", 0};
    // Valve bb{"BB", 13};
    // Valve cc{"CC", 2};
    // Valve dd{"DD", 20};
    // Valve ee{"EE", 3};
    // Valve ff{"FF", 0};
    // Valve gg{"GG", 0};
    // Valve hh{"HH", 22};
    // Valve ii{"II", 0};
    // Valve jj{"JJ", 21};

    // aa.children = {&dd, &bb};
    // bb.children = {&cc, &aa};
    // cc.children = {&dd, &bb};
    // dd.children = {&cc, &aa};
    // aa.children = {&dd, &ii, &bb};
    // bb.children = {&cc, &aa};
    // cc.children = {&dd, &bb};
    // dd.children = {&cc, &aa, &ee};
    // ee.children = {&ff, &dd};
    // ff.children = {&ee, &gg};
    // gg.children = {&ff, &hh};
    // hh.children = {&gg};
    // ii.children = {&aa, &jj};
    // jj.children = {&ii};

    // std::map<std::pair<std::string, int>, int> memo;
    // auto res = pressure(&aa, 6, memo);

    // std::cout << "max pressure: " << res << '\n';

    return 0;
}
