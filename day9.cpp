#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <sstream>
#include <algorithm>
#include <cctype>
#include <list>
#include <stack>
#include <cassert>

using Position = std::pair<int, int>;

Position up{0, -1};
Position down{0, 1};
Position left{-1, 0};
Position right{1, 0};

int signum(int val)
{
    if(val == 0)
        return 0;
    if(val < 0)
        return -1;
    if(val > 0)
        return 1;

    return 0;
}

Position adapt_tail(Position head, Position tail)
{
    auto diff_x = head.first - tail.first;
    auto diff_y = head.second - tail.second;

    if(std::abs(diff_x) > 1 || abs(diff_y) > 1)
    {
        tail.first = tail.first + signum(diff_x);
        tail.second = tail.second + signum(diff_y);
    }

    return tail;
}

std::pair<Position, Position> move(char direction, Position head, Position tail)
{
    if(direction == 'R')
    {
        head.first += right.first;
        head.second += right.second;
    } 
    else if(direction == 'L')
    {
        head.first += left.first;
        head.second += left.second;
    }
    else if(direction == 'D')
    {
        head.first += down.first;
        head.second += down.second;
    }
    else if(direction == 'U') 
    {
        head.first += up.first;
        head.second += up.second;
    }
    else 
    {
        assert(false);
    }

    tail = adapt_tail(head, tail);

    return std::pair<Position, Position>{head, tail};
};

int main()
{
    std::fstream in("day9_input.txt", std::ios::in);
    if(!in.is_open())
    {
        std::cout << "Could not open file for reading!\n";
        return -1;
    }

    std::array<Position, 10> knots{
        Position{0,0},
        Position{0,0},
        Position{0,0},
        Position{0,0},
        Position{0,0},
        Position{0,0},
        Position{0,0},
        Position{0,0},
        Position{0,0},
        Position{0,0}
    };
    std::set<Position> tail_visited{knots[9]};

    std::string line;
    int lineno = 0;
    while(std::getline(in, line))
    {
        std::stringstream ss{line};
        char direction;
        int steps;

        ss >> direction >> steps;
        for(int i = 0; i < steps; ++i)
        {
            auto new_positions = move(direction, knots[0], knots[1]);
            knots[0] = new_positions.first;
            knots[1] = new_positions.second;
            for(int k = 1; k < 9; ++k)
            {
                auto new_tail = adapt_tail(knots[k], knots[k+1]);
                knots[k+1] = new_tail;
            }

            tail_visited.insert(knots[9]);
        }
    }

    std::cout << "Visited " << tail_visited.size() << '\n';

    in.close();
    return 0;
}