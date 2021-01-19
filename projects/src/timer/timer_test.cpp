/******************************************************************************
 *							CREATED BY: Orpaz                                 *
 *							CREATED ON: 21-09-2020  			 			  *
 *							REVIEWER: 	 					                  *
 ******************************************************************************/

#include <iostream>
#include "timer.hpp"
#include <boost/bind.hpp>   //boost::bind
#include "reactor.hpp"

using namespace ilrd;
using namespace std;
using namespace project;
void Stop(Reactor *toStop);
void PrintTime();
void DisarmTimer(Timer *timer);

int main()
{
    Reactor reek;
    boost::function<void(void)> stop = boost::bind(Stop, &reek);
    boost::function<void(void)> Print = PrintTime;
    Timer timer1(reek, Print);
    Timer timer2(reek, Print);
    Timer timer3(reek, Print);
    Timer timer5(reek, Print);
    boost::function<void(void)> disarm = boost::bind(DisarmTimer, &timer5);
    Timer timer4(reek, disarm);

    timer1.Arm(Timer::seconds(1));
    cout << "nanosecond Left after timer create with 1 second" << endl;
    cout << "timer1.TimeLeft(): " << timer1.TimeLeft() << endl;
    cout << "timer1.TimeLeft(): " << timer1.TimeLeft() << endl;
    cout << "timer1.TimeLeft(): " << timer1.TimeLeft() << endl;
    timer1.Disarm();
    cout << "nanosecond Left after Disarm" << endl;
    cout << "timer1.TimeLeft(): " << timer1.TimeLeft() << endl;
    timer2.Arm(Timer::seconds(2));
    timer3.Arm(Timer::seconds(3));
    timer4.Arm(Timer::seconds(4));
    timer5.Arm(Timer::seconds(5));

    reek.Add(STDIN_FILENO, Reactor::READ, stop);
    reek.Run();
    timer1.Arm(Timer::seconds(1));
    reek.Run();

    return 0;
}

void Stop(Reactor *toStop)
{
    char buf[BUFSIZ];
    read(STDIN_FILENO, buf, BUFSIZ);

    toStop->Stop();
}

void PrintTime()
{
    cout << boost::chrono::system_clock::now() << endl;
}

void DisarmTimer(Timer *timer)
{
    timer->Disarm();
}
/* (╯°□°）╯︵ ┻━┻ */
