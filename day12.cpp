#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <sstream>
#include <algorithm>
#include <cctype>
#include <list>
#include <stack>
#include <array>
#include <limits>

using Cell = std::pair<int, int>;

Cell operator+(const Cell& lhs, const Cell& rhs)
{
    return Cell{lhs.first + rhs.first, lhs.second + rhs.second};
}

int main()
{
    std::fstream in("day12_input.txt", std::ios::in);
    if(!in.is_open())
    {
        std::cout << "Could not open file for reading!\n";
        return -1;
    }

    constexpr int num_rows = 5;
    constexpr int num_cols = 8;
    std::array<std::array<char, num_cols>, num_rows> map;
    std::array<std::array<bool, num_cols>, num_rows> visited;
    std::array<std::array<int, num_cols>, num_rows> distance;
    // std::array<std::array<Cell, num_cols>, num_rows> predecessor;

    Cell start, end;

    std::string line;
    for(int row = 0; std::getline(in, line); ++row)
    {
        for(int col = 0; col < line.size(); ++col)
        {
            if(line[col] == 'S')
            {
                start = {row, col};
                map[row][col] = 'a';
            }
            else if(line[col] == 'E')
            {
                end = {row, col};
                map[row][col] = 'z';
            }
            else
            {
                map[row][col] = line[col];
            }

            visited[row][col] = false;
            // predecessor[row][col] = Cell{-1,-1};
            distance[row][col] = std::numeric_limits<int>::max();
        }
    }

    in.close();

    auto can_visit = [&map, &visited](Cell current, Cell next)
    {
        if(visited[next.first][next.second])
        {
            return false;
        }

        if(next.first < 0 || next.second < 0 ||
           next.first >= map.size() || next.second >= map[0].size())
        {
            return false;
        }

        return map[current.first][current.second] + 1 >= map[next.first][next.second];
    };

    for(const auto r : map)
    {
        for(const auto c : r)
        {
            std::cout << c;
        }
        std::cout << '\n';
    }

    std::cout << "Start at " << start.first << " " << start.second << " end at " << end.first << " " << end.second << '\n';

    std::list<Cell> queue;
    Cell down = {1, 0};
    Cell up = {-1, 0};
    Cell left = {0, -1};
    Cell right = {0, 1};
    Cell current = start;
    
    distance[current.first][current.second] = 0;
    visited[current.first][current.second] = true;
    queue.push_back(current);
    
    while(!queue.empty())
    {
        current = queue.front();
        queue.pop_front();

        for(Cell next : {current + right, current + left, current + up, current + down})
        {
            if(can_visit(current, next))
            {
                visited[next.first][next.second] = true;
                distance[next.first][next.second] = distance[current.first][current.second] + 1;
                queue.push_back(next);

                if(next == end)
                {
                    std::cout << "Found end with distance " << distance[next.first][next.second] << '\n';
                    return 0;
                }
            }
        }
    }
    
    return 0;
}