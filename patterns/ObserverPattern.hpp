using namespace std;

class Newspaper;

class Subscriber{
private:
    Newspaper *news;
public:
    Subscriber(Newspaper* arg){news = arg; cout << "Subscriber::Subscriber()" << endl;}
    virtual void update() = 0;
};
