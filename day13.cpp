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
        lhs.children.push_back(Node{lhs.data});
        lhs.data = -1;

        return compare(lhs, rhs);
    }

    if(rhs.dataNode())
    {
        rhs.children.push_back(Node{rhs.data});
        rhs.data = -1;

        return compare(lhs, rhs);
    }

    //currently possible due to mixed types int vs list
    std::cout << "IMPOSSIBLE\n";
    return -2;
}

int main()
{
    std::fstream in("day13_input.txt", std::ios::in);
    if(!in.is_open())
    {
        std::cout << "Could not open file for reading!\n";
        return -1;
    }

    std::string line, line2;
    
    while(std::getline(in, line) && std::getline(in, line2))
    {
        // std::cout << "1: " << line << '\n';
        std::stack<std::vector<int>> left_stack;

        for(const auto c : line)
        {
            // if(c == '[')
            // {
            //     left_stack.push(std::vector<int>{});
            //     std::cout << "lists: " << left_stack.size() << '\n';
            // }
            // else if(c == ']')
            // {
            //     left_stack.pop();
            // }
            // else if(c == ',')
            // {

            // }
            // else
            // {
            //     int number = std::atoi(c);
            //     left_stack.top().push_back(number);
            // }
        }


        // std::cout << "2: " << line2 << '\n';

        // every [ starts a new list 
        // every , adds another element to the current list (if there is any)
        
        
        
        // consume empty line
        std::getline(in, line);
    }

    in.close();

    // auto compare = [](Node left, Node right){
    //     auto* left_it = &left.children;
    //     auto* right_it = &right.children;
        

    //     int limit = std::min(left.children.size(), right.children.size());

    //     if(limit == 0)
    //     {
    //         if(left.children.size() < right.children.size()) std::cout << "LEFT IS SMALLER!\n";  
    //         else std::cout << "RIGHT IS SMALLER!\n";  
    //     }

        // for(int i = 0; i < limit; ++i)
        // {
        //     auto& left_data = left.children[i].data;
        //     auto& right_data = right.children[i].data;

        //     std::cout << "L: " << left_data << " R: " << right_data << '\n';

        //     if(left_data != -1 && right_data != -1 && left_data != right_data)
        //     {
        //         if(left_data < right_data)
        //             std::cout << "LEFT IS SMALLER!\n";  
        //         else
        //             std::cout << "RIGHT IS SMALLER!\n";  
        //     }

        //     if(left_data == -1 && right_data != -1)
        //     {
        //         std::cout << "Promoting right to list\n";
        //     }

        //     if(left_data != -1 && right_data == -1)
        //     {
        //         std::cout << "Promoting left to list\n";
        //         left.children[i].children.push_back(Node{left_data});
        //         left_data = -1;
        //         i--;
        //         continue;
        //     }

        //     if(i == limit - 1 && left.children.size() != right.children.size())
        //     {
        //         if(left.children.size() < right.children.size())
        //             std::cout << "LEFT IS SMALLER!\n";
        //         else 
        //             std::cout << "RIGHT IS SMALLER!\n";  
        //     }
        // }
    // };

    {
        // [1,1,3,1,1] vs [1,1,5,1,1]
        Node left;
        left.children.push_back(Node{1});
        left.children.push_back(Node{1});
        left.children.push_back(Node{3});
        left.children.push_back(Node{1});
        left.children.push_back(Node{1});
        left.print();
        std::cout << '\n';

        Node right;
        right.children.push_back(Node{1});
        right.children.push_back(Node{1});
        right.children.push_back(Node{3});
        right.children.push_back(Node{1});
        right.children.push_back(Node{1});
        right.print();
        std::cout << '\n';
        std::cout << compare(left, right) << '\n';
    }

    {
        // [] vs [3]
        Node left;
        left.print();
        std::cout << '\n';

        Node right;
        right.children.push_back(Node{3});
        right.print();
        std::cout << '\n';
        std::cout << compare(left, right) << '\n';
    }

    {
        //[9] vs [[8,7,6]]
        Node left;
        left.children.push_back(Node{9}); 
        left.print();
        std::cout << '\n';

        Node right;
        Node subtree;
        subtree.children.push_back(Node{8});
        subtree.children.push_back(Node{7});
        subtree.children.push_back(Node{6});
        right.children.push_back(subtree);
        right.print();
        std::cout << '\n';
        std::cout << compare(left, right) << '\n';
    }

    {
        //[9] vs [[8,7,6]]
        Node left;
        left.children.push_back(Node{9}); 
        left.print();
        std::cout << '\n';

        Node right;
        Node subtree;
        subtree.children.push_back(Node{8});
        subtree.children.push_back(Node{7});
        subtree.children.push_back(Node{6});
        right.children.push_back(subtree);
        right.print();
        std::cout << '\n';
        std::cout << compare(left, right) << '\n';
    }

    {
        //[[[]]] vs [[]]
        Node left;
        left.children.push_back(Node{});
        left.children[0].children.push_back(Node{});
        left.print(); 
        std::cout << '\n';

        Node right;
        right.children.push_back(Node{});
        right.print(); 
        std::cout << '\n';
        std::cout << compare(left, right) << '\n';
    }

    return 0;
}