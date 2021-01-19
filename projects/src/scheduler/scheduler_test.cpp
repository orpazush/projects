/******************************************************************************
 *                          code by : Orpaz Houta                             *
 *                        review by :                                         *
 *                      coding date - 22-09-2020                              *
 ******************************************************************************/

#include <iostream>     	// stdout/stdin
#include <boost/bind.hpp>	//bind

#include "scheduler.hpp"

using namespace std;
using namespace ilrd;
using namespace project;

void one();
void two(int i);
void three();
void StopReactor(Reactor *reactor);

int main()
{
	Reactor reactor;
	Scheduler sched(reactor);
	boost::function<void (void)> func1 = one;
	boost::function<void (void)> func2(boost::bind(two, 2));
	boost::function<void (void)> func3 = three;

	boost::chrono::time_point<boost::chrono::steady_clock> time1 =
							(boost::chrono::steady_clock::now() +
							 boost::chrono::seconds(4));

	sched.Add(func1, time1);

	boost::chrono::time_point<boost::chrono::steady_clock> time2 =
							(boost::chrono::steady_clock::now() +
							 boost::chrono::seconds(2));

	sched.Add(func2, time2);

	boost::chrono::time_point<boost::chrono::steady_clock> time3 =
							(boost::chrono::steady_clock::now() +
							 boost::chrono::seconds(3));

	sched.Add(func3, time3, boost::chrono::nanoseconds(2000000000));

	boost::chrono::time_point<boost::chrono::steady_clock> time4 =

							(boost::chrono::steady_clock::now() +
							 boost::chrono::seconds(9));
	boost::function<void (void)> stop(boost::bind(StopReactor, &reactor));
    sched.Add(stop, time4);

	reactor.Run();

	return (0);
}

void one()
{
	cout << "one" << endl;
}

void two(int i)
{
	cout << "two print number: "<< i << endl;
}

void three()
{
	cout << "three" << endl;
}

void StopReactor(Reactor *reactor)
{
    reactor->Stop();
}