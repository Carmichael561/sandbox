#include <iostream>
#include <cassert>
#include <algorithm>

void reverse(std::string &str)
{
    std::string::iterator l = str.begin();
    std::string::iterator r = str.end();
    while(l < r)
    {
        if (l < r && not std::isalpha(*l))
            l++;
        else if (l < r && not std::isalpha(*r))
            r--;
        else {
            //auto s = *l;
            std::iterator_traits<std::string::iterator>::value_type s = *l;
            *l = *r;
            *r = s;
            l++;
            r--;
        }
        std::cout << str << std::endl;
    }
}

int main() 
{ 
    std::string str("a!!!b.c.d,e'f,ghi");
    std::string rv("i!!!h.g.f,e'd,cba");
    std::cout << "Input string: " << str << std::endl;
    reverse(str); 
    std::cout << "Output string: " << str << std::endl;

    assert(str == rv);
    
    return 0; 
} 
