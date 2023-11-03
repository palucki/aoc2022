#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <sstream>
#include <algorithm>
#include <cctype>
#include <list>
#include <stack>

struct Monkey 
{
    virtual void operate()
    {
        while(!items.empty())
        {
            auto item = items.front();
            items.pop_front();

            // std::cout << "item " << item << '\n';

            item = func(item);

            // std::cout << "item after inspecting " << item << '\n';

            times_inspected++;
            
            // item = item / 3;
            // magic trick: modulo by multiplication of all test values
            item = item % 9699690;

            // std::cout << "item after decreasing " << item << '\n';

            if(test(item))
            {
                if(true_receiver)
                    true_receiver->receive(item);
            }
            else
            {
                if(false_receiver)
                    false_receiver->receive(item);
            }
        }
    }

    void receive(unsigned long long item)
    {
        items.push_back(item);
    }

    void print_items()
    {
        std::cout << "inspected " << times_inspected << " times ";
        for(const auto& i : items)
        {
            std::cout << i << " ";
        }
        std::cout << '\n';
    }

    int times_inspected = 0;
    std::deque<unsigned long long> items;

    std::function<unsigned long long(unsigned long long)> func;
    std::function<bool(unsigned long long)> test;
    Monkey* true_receiver{nullptr};
    Monkey* false_receiver{nullptr};
};

int main()
{
    Monkey m0;
    Monkey m1;
    Monkey m2;
    Monkey m3;
    Monkey m4;
    Monkey m5;
    Monkey m6;
    Monkey m7;

    m0.items = {54, 89, 94};
    m0.func = [](const unsigned long long val) { return val * 7; };
    m0.test = [](const unsigned long long val) { return val % 17 == 0; };
    m0.true_receiver = &m5;
    m0.false_receiver = &m3;
    
    m1.items = {66, 71};
    m1.func = [](const unsigned long long val) { return val + 4; };
    m1.test = [](const unsigned long long val) { return val % 3 == 0; };
    m1.true_receiver = &m0;
    m1.false_receiver = &m3;
    
    m2.items = {76, 55, 80, 55, 55, 96, 78};
    m2.func = [](const unsigned long long val) { return val + 2; };
    m2.test = [](const unsigned long long val) { return val % 5 == 0; };
    m2.true_receiver = &m7;
    m2.false_receiver = &m4;
    
    m3.items = {93, 69, 76, 66, 89, 54, 59, 94};
    m3.func = [](const unsigned long long val) { return val + 7; };
    m3.test = [](const unsigned long long val) { return val % 7 == 0; };
    m3.true_receiver = &m5;
    m3.false_receiver = &m2;

    m4.items = {80, 54, 58, 75, 99};
    m4.func = [](const unsigned long long val) { return val * 17; };
    m4.test = [](const unsigned long long val) { return val % 11 == 0; };
    m4.true_receiver = &m1;
    m4.false_receiver = &m6;

    m5.items = {69, 70, 85, 83};
    m5.func = [](const unsigned long long val) { return val + 8; };
    m5.test = [](const unsigned long long val) { return val % 19 == 0; };
    m5.true_receiver = &m2;
    m5.false_receiver = &m7;

    m6.items = {89};
    m6.func = [](const unsigned long long val) { return val + 6; };
    m6.test = [](const unsigned long long val) { return val % 2 == 0; };
    m6.true_receiver = &m0;
    m6.false_receiver = &m1;

    m7.items = {62, 80, 58, 57, 93, 56};
    m7.func = [](const unsigned long long val) { return val * val; };
    m7.test = [](const unsigned long long val) { return val % 13 == 0; };
    m7.true_receiver = &m6;
    m7.false_receiver = &m4;

    std::cout << "Before:\n";
    std::cout << "0: "; m0.print_items();
    std::cout << "1: "; m1.print_items();
    std::cout << "2: "; m2.print_items();
    std::cout << "3: "; m3.print_items();
    std::cout << "4: "; m4.print_items();
    std::cout << "5: "; m5.print_items();
    std::cout << "6: "; m6.print_items();
    std::cout << "7: "; m7.print_items();

    for(int i = 0; i < 10000 ; ++i)
    {
        m0.operate();
        m1.operate();
        m2.operate();
        m3.operate();
        m4.operate();
        m5.operate();
        m6.operate();
        m7.operate();
    }

    std::cout << "After:\n";
    std::cout << "0: "; m0.print_items();
    std::cout << "1: "; m1.print_items();
    std::cout << "2: "; m2.print_items();
    std::cout << "3: "; m3.print_items();
    std::cout << "4: "; m4.print_items();
    std::cout << "5: "; m5.print_items();
    std::cout << "6: "; m6.print_items();
    std::cout << "7: "; m7.print_items();


    return 0;
}