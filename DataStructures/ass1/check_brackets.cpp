#include <iostream>
#include <stack>
#include <string>
/*
In this problem you will implement a feature for a text editor to find errors in the usage of brackets in the
code.

*/
struct Bracket {
    Bracket(char type, int position):
        type(type),
        position(position)
    {}

    bool Matchc(char c) {
        // std::cout << "inside  c type " << c << " " << type << std::endl; 
        if (type == '[' && c == ']')
            return true;
        if (type == '{' && c == '}')
            return true;
        if (type == '(' && c == ')')
            return true;
        return false;
    }

    char type;
    int position;
};

int main() {
    std::string text;
    getline(std::cin, text);

    std::stack <Bracket> opening_brackets_stack;
    for (int position = 0; position < text.length(); ++position) {
        char next = text[position];
        // std::cout << "next " << next << std::endl; 

        if (next == '(' || next == '[' || next == '{') {
            // std::cout << "open " << std::endl; 
            // Process opening bracket, write your code here
            Bracket bracket(next, position);

            opening_brackets_stack.push(bracket);
        }
        else if (( next != '(' && next != '[' && next != '{' && next != ')' 
                    && next != ']' && next != '}'))
                    continue;
        else
        {
            if (opening_brackets_stack.empty())
            {
                // std::cout << "empty " << std::endl; 
                std::cout << ++position << std::endl; 
                return -1; 
            }
            Bracket top = (Bracket )opening_brackets_stack.top(); 
            
            if (next == ')' || next == ']' || next == '}') 
            {
                opening_brackets_stack.pop();
                if (!top.Matchc(next))
                {
                    // std::cout << "match " << std::endl; 
                    // Process closing bracket, write your code here
                    std::cout << ++position << std::endl; 
                    return -1; 
                }
               
            }
        }
    }

    // Printing answer, write your code here
    if (opening_brackets_stack.empty())
        std::cout << "Success" << std::endl; 
    else
    {
        Bracket top = (Bracket )opening_brackets_stack.top(); 
        std::cout << (top.position+1) << std::endl; 
    }

    return 0;
}
