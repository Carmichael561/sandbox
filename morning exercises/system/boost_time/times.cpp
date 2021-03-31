#include <iostream>
#include <boost/locale.hpp>
#include <boost/chrono.hpp>
#include <boost/thread/thread.hpp>
#include <boost/thread/mutex.hpp>

using namespace std;
using namespace boost::locale;

boost::mutex mux;
boost::condition_variable cv;
std::vector<int> vec;

void writer()
{
    while (1)
    {
//    bool w = mux.timed_lock(boost::posix_time::milliseconds(10));
        while (vec.size())
        {
//	w = mux.timed_lock(boost::posix_time::milliseconds(10));
	    cout << "writer wait 100mks\n";
            boost::this_thread::sleep(boost::posix_time::milliseconds(500));
        }
	mux.lock();
	cout << "writer write\n";
        for (int i = 0; i < 500; i++)
        {
            vec.push_back(i);
            boost::this_thread::sleep(boost::posix_time::milliseconds(1));
        }
	cout << "writer finish\n";
	cv.notify_one();
        mux.unlock();
//        cv.notify_one();
        boost::this_thread::sleep(boost::posix_time::milliseconds(1000));
    }
}

void reader()
{
    // boost::this_thread::sleep(boost::posix_time::milliseconds(1000));

    while(1)
    {
        boost::unique_lock<boost::mutex> loc(mux);
        boost::system_time const timeout = boost::get_system_time() + boost::posix_time::milliseconds(10);
        bool w;// = cv.timed_wait(loc, timeout);
        cout << "in a thread 1 timed_wait return " << endl;
        while (vec.size() == 0)
        {
	    cout << "reader sleep\n";
            w = cv.timed_wait(loc, timeout);
        }

	mux.lock();
	cout << "reader read\n";
        while (vec.size())
        {
            vec.pop_back();
        }
	cout << "reader finish\n";
	mux.unlock();
    }
}

int main()
{
    boost::chrono::steady_clock::time_point start = boost::chrono::steady_clock::now();

    cout << "Hello" << endl;

    generator gen;
    locale loc;

    loc = gen("");
    locale::global(loc);

    boost::chrono::duration<double> dur = boost::chrono::steady_clock::now() - start;

    cout << "duration " << dur.count() << endl;

        boost::thread t2{reader};
    boost::thread t1{writer};

    t1.join();
    t2.join();

    return 0;
}
