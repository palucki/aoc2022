#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <sstream>
#include <algorithm>
#include <cctype>
#include <list>
#include <stack>

struct Node 
{
    void print()
    {
        if(dataNode())
        {
            std::cout << data;
        }
        else
        {
            std::cout << "[";
            for(int i = 0; i < children.size(); ++i)
            {
                children[i].print();
                if(i < children.size() - 1) std::cout << ",";
            }
            std::cout << "]";
        }
    }

    // to handle [] case - it is not a data node!
    bool dataNode() const { return children.empty() && data != -1; }

    int data{-1};
    std::vector<Node> children;
};

// returns -1 if in order, 
//          0 if equal, 
//          1 if not in order
int compare(Node& lhs, Node& rhs)
{
    if(lhs.dataNode() && rhs.dataNode())
    {
        if(lhs.data < rhs.data) return -1;
        if(lhs.data == rhs.data) return 0;
        if(lhs.data > rhs.data) return 1;
    }

    if(!lhs.dataNode() && !rhs.dataNode())
    {
        for(int i = 0; i < std::min(lhs.children.size(), rhs.children.size()); ++i)
        {
            auto res = compare(lhs.children[i], rhs.children[i]);
            if(res != 0) return res;
        }

        if(lhs.children.size() < rhs.children.size()) return -1;
        if(lhs.children.size() == rhs.children.size()) return 0; //this should not be possible
        if(lhs.children.size() > rhs.children.size()) return 1;
    }

    if(lhs.dataNode())
    {
        lhs.children.emplace_back(Node{lhs.data});
        lhs.data = -1;

        return compare(lhs, rhs);
    }

    if(rhs.dataNode())
    {
        rhs.children.emplace_back(Node{rhs.data});
        rhs.data = -1;

        return compare(lhs, rhs);
    }

    //currently possible due to mixed types int vs list
    std::cout << "IMPOSSIBLE COMPARE\n";
    return -2;
}

int parse(Node& current, int index, int level, const std::string& line)
{
    std::string num_str;
    for(int i = index; i < line.size(); ++i)
    {
        // std::cout << "idx " << i << " level " << level << '\n';
        const auto& cl = line[i];

        if(isdigit(cl))
        {
            num_str += cl;
        }
        else if(cl == '[')
        {
            // handle initial call where head node already created
            if(level == -1)
            {
                level++;
            }
            else 
            {
                current.children.emplace_back(Node{});
                i = parse(current.children[current.children.size() - 1], i+1, level+1, line);
            }

            // std::cout << "index after parsing " << i << '\n';
        }
        else if(cl == ']')
        {
            //go up
            if(!num_str.empty())
            {
                auto val = std::stoi(num_str);
                // std::cout << "Found number " << val << " level " << level << '\n';
                num_str.clear();

                current.children.push_back(Node{val});
            }
            return i;
        }
        else if(cl == ',')
        {
            if(!num_str.empty())
            {
                auto val = std::stoi(num_str);
                // std::cout << "Found number " << val << " level " << level << '\n';
                num_str.clear();
                current.children.push_back(Node{val});
            }
        }
    }

    // return index
    std::cout << "IMPOSSIBLE PARSE\n";
    return -1;
}

int main()
{
    std::fstream in("day13_input.txt", std::ios::in);
    if(!in.is_open())
    {
        std::cout << "Could not open file for reading!\n";
        return -1;
    }

    std::string line1, line2;
    int pair_index = 1;
    int result = 0;

    std::vector<Node> nodes;
    
    while(std::getline(in, line1) && std::getline(in, line2))
    {
        // std::cout << "1: " << line1 << '\n';
        Node head1;
        auto idx = parse(head1, 0, -1, line1);
        nodes.emplace_back(head1);
        // std::cout << "P: ";
        // head1.print();
        // std::cout << '\n';
        
        // std::cout << "2: " << line2 << '\n';
        Node head2;
        idx = parse(head2, 0, -1, line2);
        nodes.emplace_back(head2);
        // std::cout << "P: ";
        // head2.print();
        // std::cout << '\n';
        
        // if(compare(head1, head2) == -1)
        // {
        //     std::cout << "pair index " << pair_index << '\n';
        //     result += pair_index;
        // }
        
        pair_index++;
        // consume empty line
        std::getline(in, line1);
    }

    in.close();

    Node n2{2};
    Node n6{6};
    nodes.push_back(n2);
    nodes.push_back(n6);

    std::sort(nodes.begin(), nodes.end(), [](Node& lhs, Node& rhs)
    {
        if(compare(lhs, rhs) == -1)
            return true;

        return false;
    });

    auto i = 1;
    for(auto& n : nodes)
    {
        if(compare(n, n2) == 0 || compare(n, n6) == 0)
        {
            std::cout << i << " : ";
            n.print();
            std::cout << '\n';
        }
        ++i;
    }



    return 0;
}