#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <sstream>
#include <algorithm>
#include <cctype>
#include <list>
#include <stack>

int main()
{
    std::fstream in("day8_input.txt", std::ios::in);
    if(!in.is_open())
    {
        std::cout << "Could not open file for reading!\n";
        return -1;
    }

    std::vector<std::vector<unsigned char>> map;
    std::vector<std::vector<bool>> visible;
    std::string line;
    
    while(std::getline(in, line))
    {
        std::cout << "Input " << line << '\n';
        map.push_back(std::vector<unsigned char>(line.begin(), line.end()));
        visible.push_back(std::vector<bool>(line.size()));
    }

    std::vector<int> highest_from_top(map[0].size(), -1);
    std::vector<int> highest_from_bottom(map[0].size(), -1);
    std::vector<int> highest_from_left(map.size(), -1);
    std::vector<int> highest_from_right(map.size(), -1);

    for(int i = 0; i < map.size(); ++i)
    {
        for(int j = 0; j < map[i].size(); ++j)
        {
            // std::cout << i << "," << j << "\n";
            auto tree = map[i][j];
            if(tree > highest_from_left[i])
            {
                highest_from_left[i] = tree;
                visible[i][j] = true;
            }
           
            if(tree > highest_from_top[j])
            {
                highest_from_top[j] = tree;
                visible[i][j] = true;
            }
        }
    }

    for(int i = map.size() - 1; i >= 0; --i)
    {
        for(int j = map[i].size() - 1; j >= 0; --j)
        {
            // std::cout << i << " " << j << "\n";
            auto tree = map[i][j];
            if(tree > highest_from_right[i])
            {
                highest_from_right[i] = tree;
                visible[i][j] = true;
            }

            if(tree > highest_from_bottom[j])
            {
                highest_from_bottom[j] = tree;
                visible[i][j] = true;
            }
        }
    }
           
    int total_visible = 0;
    for(int i = 0; i < map.size(); ++i)
    {
        for(int j = 0; j < map[i].size(); ++j)
        {
            if(visible[i][j])
            {
                std::cout << map[i][j];
                total_visible++;    
            }
            else
            {
                std::cout << 'x';
            }
        }
        std::cout << '\n';
    }
    // std::cout << i << "," << j << " = " << tree << (visible ? " " : " not ") << "visible\n";


    std::cout << "Total visible " << total_visible << '\n';

    std::cout << "Calculating scenic score...\n";

    auto in_map = [&map](int i, int j) -> bool {
        return i >= 0 && i < map.size() && j >= 0 && j < map[0].size();
    };

    int best_scenic_score = 0;
    for(int i = 0; i < map.size(); ++i)
    {
        for(int j = 0; j < map[i].size(); ++j)
        {
            auto tree = map[i][j];
            
            //check top
            int top_distance = 0;
            for(int k = i - 1; k >= 0; --k)
            {
                if(in_map(k, j))
                {
                    top_distance++;
                    if(map[k][j] >= tree)
                        break;
                }
            }

            //check bottom
            int bottom_distance = 0;
            for(int k = i + 1; k < map.size(); ++k)
            {
                if(in_map(k, j))
                {
                    bottom_distance++;  
                    if(map[k][j] >= tree)
                        break;
                } 
            }
            
            //check left
            int left_distance = 0;
            for(int k = j - 1; k >= 0; --k)
            {
                if(in_map(i, k))
                {
                    left_distance++;
                    if(map[i][k] >= tree)
                        break;
                }
            }

            //check right
            int right_distance = 0;
            for(int k = j + 1; k < map[i].size(); ++k)
            {
                if(in_map(i, k))
                {
                    right_distance++;
                    if(map[i][k] >= tree)
                        break;
                }
            }

            auto tree_scenic_score = top_distance * bottom_distance * left_distance * right_distance;
            
            std::cout << i << "," << j << ": (" << top_distance << "," << left_distance << "," << bottom_distance << "," << right_distance << ")" 
                      << " score " << tree_scenic_score << " tree " << tree << "\n";
            
            if(tree_scenic_score > best_scenic_score)
            {
                best_scenic_score = tree_scenic_score;
                std::cout << "New best scenic score at " << i << "," << j << " is " << best_scenic_score << '\n';
            }
        }
    }

    std::cout << "Best scenic score " << best_scenic_score << '\n';

    in.close();
    return 0;
}