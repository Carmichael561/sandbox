/*
  -Strategy has many variants hove to behave; Highlight strategy in own base and derived class.
  -Put concrete strategy into constructor of Object; Constructed object will behave according to own strategy.

 */
#include <iostream>
#include <vector>
#include <deque>
using namespace std;

class Movement
{
public:
    Movement(){cout << "Movement::Movement()" << endl;}
    virtual ~Movement() {cout << "Movement::~Movement()" << endl;};
    virtual void move(void){cout << "Movement::move()" << endl;}
};

/*
class Fly : public Movement{};
class Swim : public Movement{};
*/
class Go : public Movement{
public:
    Go(){cout << "Movement::Go::Go()" << endl;}
    virtual void move(void) override {cout << "Movement::Go::move()" << endl;}
};

class Animal{
public:
    virtual void migrate(){cout << "Animal::migrate()" << endl;};
protected:
    Animal(){cout << "Animal::Animal()" << endl;}
    Movement *moveType;
};


class Humane : public Animal{
public:
    Humane() {cout << "Animal::Humane::Humane()" << endl; moveType = new Go();}
    virtual void migrate() override {cout << "Animal::Humane::migrate()" << endl; moveType->move();}
};
/*
class Dolphin : public Animal{};
class Pilican : public Animal{};
*/
int main()
{
    cout << "------Strategy Design Pattern------" << endl;
    
    deque<Animal*> liveObjects = {new Humane(), new Humane()};
    cout << liveObjects.size() << endl;

    for(auto i: liveObjects)
        {
            cout << "------Iterate live objects------" << endl;
            i->migrate();
        }
    return 0;
}
