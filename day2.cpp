#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <sstream>

char get_response(char opponent, char fixed_result)
{
    if(fixed_result == 'Y')
    {
        return opponent;
    }

    // X - I lose
    if(fixed_result == 'X')
    {
        if(opponent == 'A') return 'C';
        if(opponent == 'B') return 'A';
        if(opponent == 'C') return 'B';
    }
    
    // Z - I win
    if(fixed_result == 'Z')
    {
        if(opponent == 'A') return 'B';
        if(opponent == 'B') return 'C';
        if(opponent == 'C') return 'A';
    }

    return ' ';
}

int get_result(char opponent, char result)
{
    char me = get_response(opponent, result);

    // me = rock, 1 point
    if(opponent == 'A' && me == 'A') return 4; // draw
    if(opponent == 'B' && me == 'A') return 1; // lose
    if(opponent == 'C' && me == 'A') return 7; // win
    
    // me = paper, 2 points
    if(opponent == 'A' && me == 'B') return 8; // win
    if(opponent == 'B' && me == 'B') return 5; // draw
    if(opponent == 'C' && me == 'B') return 2; // lose
    
    //me = scissors, 3 points
    if(opponent == 'A' && me == 'C') return 3; //lose
    if(opponent == 'B' && me == 'C') return 9; // win
    if(opponent == 'C' && me == 'C') return 6; // draw

    return 0;
}

void read_function()
{
    std::fstream in("day2_input.txt", std::ios::in);
    if(!in.is_open())
    {
        std::cout << "Could not open file for reading!\n";
        return;
    }

    std::string line;
    long result = 0;
    while(std::getline(in, line))
    {
        // std::cout << line << "\n";
        std::stringstream ss{line};
        char opponent;
        char me;

        ss >> opponent;
        ss >> me;

        std::cout << "opponent " << opponent << " and me " << me << "\n";
        result += get_result(opponent, me);
    }

    std::cout << "result " << result << "\n";
    in.close();
}

int main()
{
    read_function();

    return 0;
}