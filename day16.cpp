#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <set>
#include <fstream>
#include <sstream>
#include <map>
#include <regex>
#include <queue>

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


//distances[FROM][TO] 
std::map<std::string, std::map<std::string, int>> distances;
std::map<std::string, int> flows;


int dfs(int time_left, std::string valve_id, std::set<std::string> opened)
{
    int max_so_far = 0;
    // std::cout << valve_id << " ";
    // std::cout << "Opening " << valve_id << " open: " << opened.size() << " ";
    opened.insert(valve_id);
    // std::cout << "already opened " << opened.size() << " ";

    for(const auto& [neighbor_valve_id, dist_to_valve] : distances[valve_id])
    {
        // if already opened, do not consider this candidate
        if(opened.find(neighbor_valve_id) != opened.end())
        {
            // std::cout << '\n';
            continue;
        }

        // time remaining after we open the valve 
        // if not possible to open any valve - skip the computations

        const auto rem_time = time_left - dist_to_valve - 1;
        if(rem_time < 1)
        {
            continue;
        }

        const auto flow = flows[neighbor_valve_id];

        auto val = flow * rem_time +  dfs(rem_time, neighbor_valve_id, opened);
        max_so_far = std::max(max_so_far, val);
    }

    return max_so_far;
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
    const std::regex e ("Valve ([A-Z]+) has flow rate=([0-9]+); tunnels? leads? to valves? ([A-Z ,]+)");

    std::map<std::string, std::vector<std::string>> tunnels;

    while (std::getline(in, line))
    {
        // std::cout << line << '\n';
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
        flows[valve_id] = flow_rate;
        tunnels[valve_id] = outputs;
    }

    // calculate using BFS shortest paths to for all non-zero flows
    for (const auto& [valve_id, flow] : flows)
    {
        if(flow <= 0 && valve_id != "AA")
        {
            continue;
        }

        std::cout << "BFS for " << valve_id << " with flow " << flow << '\n';

        std::set<std::string> visited;
        std::queue<std::pair<std::string, int>> to_visit;
        std::map<std::string, int> dist;

        visited.insert(valve_id);
        dist[valve_id] = 1;
        for(const auto& o : tunnels[valve_id])
        {
            to_visit.push({o, dist[valve_id]});
        }
        
        while(!to_visit.empty())
        {
            auto current = to_visit.front();
            auto valve = current.first;
            auto distance = current.second;
            visited.insert(valve);

            if(flows[valve] > 0 || valve == "AA")
                dist[valve] = distance;

            for(const auto& o : tunnels[valve])
            {
                if(visited.find(o) == visited.end())
                    to_visit.push({o, distance + 1});
            }

            to_visit.pop();
        }

        dist.erase(valve_id);
        dist.erase("AA");

        // output results
        for (const auto& [valve_id, dist] : dist)
        {
            std::cout << " to valve " << valve_id << " dist is " << dist << '\n';
        }

        distances[valve_id] = dist;
    }

    std::cout << "Possible flow\n";

    auto res = dfs(30, "AA", {});

    std::cout << "result " << res << "\n";

    return 0;
}
