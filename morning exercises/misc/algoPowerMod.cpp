#include <iostream>

/*
 * res = x^y%p;
 *
 */
unsigned int PowerMod(uint x, uint y, uint mod)
{
    uint res = 1;
    while(y > 0)
    {
        x %= mod;
        res %= mod;
        
        if (y & 1) {
            res *= x;
            res %= mod;
        }

        y >>= 1;
        x *= x;
        x %= mod;
    }
    return res;
}

int main()
{
    std::cout << PowerMod(2, 3, 5) << std::endl;
    std::cout << PowerMod(2, 5, 13) << std::endl;
    std::cout << PowerMod(7, 3, 5) << std::endl;
    
    return 0;
}
