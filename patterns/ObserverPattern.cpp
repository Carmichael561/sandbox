/*
  -Subject(Publisher) provide list of Observers(Subscribers)
  -Observer(Subscriber) agregate pointer on Subject(Publisher)
  -Subject(Publisher) provide register and unregister interface to register and unregister Observers(Subscribers)
  -Observers(Subscribers) provide update public interface
  
  
 */

#include <iostream>
#include <list>
#include <vector>
#include <memory>
#include "ObserverPattern.hpp"
using namespace std;

/*
//Publisher
class Newspaper;
class Ukrnet : public Newspaper;
class Googlenews : public Newpaper;


class Subscriber;
class Vasyl : public Subscriber;
class Oleg : public Subscriber;
*/

class Subscriber;


class Newspaper{
protected:
    list<Subscriber*> subscribers;
public:
    virtual void registerNews(Subscriber* s) = 0;
    virtual void unregisterNews() = 0;
    virtual void notifyNews() = 0;
};

class Ukrnet : public Newspaper{
public:
    virtual void registerNews(Subscriber* s) override {subscribers.push_back(s); cout << "Newspaper::Ukrnet::Register()" << endl;}
    virtual void unregisterNews() override {cout << "Newspaper::Ukrnet::Unregister()" << endl;}
    virtual void notifyNews() override {cout << "Newspaper::Ukrnet::Notify()" << endl;
        for (auto s : subscribers){cout << "Notify" << endl; s->update(); }}
};



void Subscriber::update(){cout << "Subscriber::update()" << endl;}

class Vasyl : public Subscriber{
public:
    Vasyl(Newspaper *news) : Subscriber(news) {cout << "Subscriber::Vasyl::Vasyl()" << endl; news->registerNews(this);}
    virtual void update() {cout << "Subscriber::Vasyl::update()" << endl;}
};


class Oleg : public Subscriber{
public:
    Oleg(Newspaper *news) : Subscriber(news) {cout << "Subscriber::Oleg::Oleg()" << endl; news->registerNews(this);}
    virtual void update() {cout << "Subscriber::Oleg::update()" << endl;}
};


int main()
{
    cout << "Observer Design Pattern" << endl;
    Newspaper* Newspaper(new Ukrnet());

    Vasyl vasyl(Newspaper);
    Oleg oleg(Newspaper);

    Newspaper->notifyNews();
    
    
    return 0;
}
