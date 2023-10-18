#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <sstream>

char get_response(char opponent, char fixed_result)
{
    // X - I lose
    // Y - draw 
    // Z - I win


    // me = rock, 1 point
    if(opponent == 'A' && me == 'X') return 4; // draw
    if(opponent == 'B' && me == 'X') return 1; // lose
    if(opponent == 'C' && me == 'X') return 7; // win
    
    // me = paper, 2 points
    if(opponent == 'A' && me == 'Y') return 8; // win
    if(opponent == 'B' && me == 'Y') return 5; // draw
    if(opponent == 'C' && me == 'Y') return 2; // lose
    
    //me = scissors, 3 points
    if(opponent == 'A' && me == 'Z') return 3; //lose
    if(opponent == 'B' && me == 'Z') return 9; // win
    if(opponent == 'C' && me == 'Z') return 6; // draw

}

int get_result(char opponent, char me)
{

    // me = rock, 1 point
    if(opponent == 'A' && me == 'X') return 4; // draw
    if(opponent == 'B' && me == 'X') return 1; // lose
    if(opponent == 'C' && me == 'X') return 7; // win
    
    // me = paper, 2 points
    if(opponent == 'A' && me == 'Y') return 8; // win
    if(opponent == 'B' && me == 'Y') return 5; // draw
    if(opponent == 'C' && me == 'Y') return 2; // lose
    
    //me = scissors, 3 points
    if(opponent == 'A' && me == 'Z') return 3; //lose
    if(opponent == 'B' && me == 'Z') return 9; // win
    if(opponent == 'C' && me == 'Z') return 6; // draw

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