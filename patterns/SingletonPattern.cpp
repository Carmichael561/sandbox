/*
- Private constructor
- Private static instance
- Static instance getter

 */

#include <iostream>
#include <memory>
#include <mutex>
using namespace std;

class Singleton{
private:
    static volatile Singleton *instance;
    Singleton() {cout << "Singleton::Singleton()" << endl;}

public:
    static volatile  Singleton *getInstance()
    {
        if (instance == nullptr)
        {
                mutex lock;
                if (instance == nullptr)
                    instance = new Singleton;
        }
        cout << "Singleton::getInstance()" << endl;
        return instance;
    }
};

volatile Singleton* Singleton::instance = nullptr;

int main()
{
    cout << "Singletone Dersign Pattern" << endl;
    Singleton *s1 = Singleton::getInstance();
    Singleton *s2 = Singleton::getInstance();

    return 0;
}
