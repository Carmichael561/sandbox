// you can use includes, for example:
// #include <algorithm>

// you can write to stdout for debugging purposes, e.g.
// cout << "this is a debug message" << endl;

/*
* 1. for each line get amount of seconds and phone number
* 2. insert in map<phone_number, seconds>
* 3. firn in map longest phon call or calls
* 4. in case of several longest calls compare key (phon number)
* 5. exclude lngest from calculations
* 6. iterate on map and calculate bill, exclude longest
*/

#include <iostream>
#include <sstream>
#include <algorithm>
#include <vector>
#include <map>
#include <cmath>

constexpr uint sec_in_min = 60;
constexpr uint min_in_hour = 60;

/*TODO: provide type safe struct (time, cents) and user defined literals;*
 * currently to not waset time make hardcode
*/
uint calcBill(uint sec)
{
    uint price = 0;
    uint min = 0;
    if (sec < 300)
        price += sec * 3;
    else if(sec >= 300)
    {
        min = std::floor(sec / 60);
        min += (sec <= min*60) ? 0 : 1;
        price += min * 150;
    }
    std::cout << "\nBILL: " << sec << " " << min << " " << price << std::endl;
    return price;
}

int solution(string &S) {
    // write your code in C++14 (g++ 6.2.0)
    
    if (S.size() <= 0)
        return 0;
        
    std::string line;
    std::stringstream iss(S);
    char h[2];
    char m[2];
    char s[2];
    uint hh, mm, ss;
    uint seconds;
    uint number;
    
    uint bill = 0;
    
    using Number = uint;
    using Duration = uint;
    using Durations = std::vector<Duration>;
    using Book = std::map<Number, Durations>;
    Book book;
    
    while (std::getline(iss, line, '\n'))
    {
        std::cout << ">>>>>>>>line: " << line << std::endl;
        h[0] = line[0];
        h[1] = line[1];
        m[0] = line[3];
        m[1] = line[4];
        s[0] = line[6];
        s[1] = line[7];
        s[0] = line[6];
        
        hh = std::atoi(h);
        mm = std::atoi(m);
        ss = std::atoi(s);
        //std::cout << "hh-mm-ss: " << hh << "-" << mm << "-" << ss << std::endl;
        
        seconds = (hh * min_in_hour * sec_in_min) + (mm * sec_in_min) + ss;
        //std::cout << "seconds: " << seconds << std::endl;
        
        std::string phone = line.substr(line.find(',') + 1);
        
        phone.erase(std::remove_if(phone.begin(), phone.end(), [](char c){
                    return c == '-';}), 
            phone.end());
        //std::cout << "phone: " << phone << std::endl;
        
        /*TODO: privide exception handling for corrupted logs case*/
        
        number = std::atoi(phone.c_str());
        //std::cout << "number: " << number << std::endl;
        
        if (book.find(number) == book.end())
            book.insert(Book::value_type(number, Durations()));
        book[number].push_back(seconds);
    }
    
    uint longest_call = std::numeric_limits<uint>::min();
    std::vector<uint> popular_numbers;
    for (auto const& n : book)
    {
        //std::cout << "MAP: " << n.first  << "\t\t";
        uint tmp = 0;
        for(auto const& s : n.second)
        {
            //std::cout << " " << s << ", ";
            tmp += s;
            bill += calcBill(s);
        }
        
        if (tmp > longest_call)
        {
            longest_call = tmp;
            popular_numbers.clear();
            popular_numbers.push_back(n.first);
        } else if(tmp >= longest_call)
        {
            longest_call = tmp;
            popular_numbers.push_back(n.first);
        }
        
        //std::cout << "bill is: " << bill << std::endl;
    }
    
    
    number = *std::min_element(popular_numbers.begin(), popular_numbers.end());
    uint price = 0;
    for(auto const& s : book[number])
        price += calcBill(s);
    bill -= price;
    
    return bill;
}
