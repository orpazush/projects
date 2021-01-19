/*****************************************************************************
 * 					written by : Orpaz Houta								 *
 * 					review :      						         *
 * 					Last update : 13.10.20									 *
 ****************************************************************************/
#include <iostream>
#include "thread_pool.hpp"
#include "logger.hpp"

using namespace ilrd;
using namespace project;
using namespace std;

boost::mutex g_CounterALock;
boost::mutex g_CounterBLock;
boost::mutex g_CounterCLock;

const std::size_t NUM_OF_THREADS = 10;

class CounterA
{
public:
    CounterA();
    static std::size_t m_count;
    static std::size_t GetCount()
    {
        boost::mutex::scoped_lock lock(g_CounterALock);
        return m_count;
    }
};

CounterA::CounterA()
{
    boost::mutex::scoped_lock lock(g_CounterALock);
    ++m_count;
}

std::size_t CounterA::m_count = 0;

class CounterC
{
public:
    CounterC();
    static std::size_t m_count;
    static std::size_t GetCount()
    {
        boost::mutex::scoped_lock lock(g_CounterCLock);
        return m_count;
    }
};

CounterC::CounterC()
{
    boost::mutex::scoped_lock lock(g_CounterCLock);
    ++m_count;
}

std::size_t CounterC::m_count = 0;

class CheckCounterA : public ThreadPool::Task
{
public:
    explicit CheckCounterA() : ThreadPool::Task::Task(ThreadPool::Task::HIGH){}

private:
    virtual void Execute()
    {
        CounterA isStart;
        boost::chrono::seconds sec(3);
        boost::this_thread::sleep_for(sec);
        CounterC isEnd;
    }
};//CheckCounterA

class CounterB
{
public:
    CounterB();
    static std::size_t m_count;
    static std::size_t GetCount()
    {
        boost::mutex::scoped_lock lock(g_CounterBLock);
        return m_count;
    }
};

CounterB::CounterB()
{
    boost::mutex::scoped_lock lock(g_CounterBLock);
    ++m_count;
}

std::size_t CounterB::m_count = 0;

class CheckCounterB : public ThreadPool::Task
{
public:
    explicit CheckCounterB() : ThreadPool::Task::Task(ThreadPool::Task::HIGH){}

private:
    virtual void Execute()
    {
        CounterB oneMore;
        boost::chrono::seconds sec(2);
        boost::this_thread::sleep_for(sec);
    }
};//CheckCounterB
//
//class Print : public ThreadPool::Task
//{
//public:
//    explicit Print(std::string in, ThreadPool::Task::priority p):
//            ThreadPool::Task::Task(p), s(in) {}
//
//private:
//    virtual void Execute()
//    {
//        std::cout << s <<" thread: "<< boost::this_thread::get_id()<<std::endl;
//    }
//    std::string s;
//};//Print
//
//class Counter : public ThreadPool::Task
//{
//public:
//    explicit Counter(ThreadPool::Task::priority p) :
//            ThreadPool::Task::Task(p) {};
//
//private:
//    virtual void Execute()
//    {
//        for(std::size_t i = 0; i < 5; ++i)
//        {
//            cout << (i + 100) << endl;
//            sleep(1);
//        }
//    }
//};//Counter
//

void TestPause();
void TestSetGetNum();
void TestStop();


int main()
{
    cout << "test" << endl;
    TestSetGetNum();
    CounterA::m_count = 0;
    TestPause();
    CounterA::m_count = 0;
    CounterB::m_count = 0;
    CounterC::m_count = 0;
    TestStop();

    return 0;
}

void TestPause()
{
    ThreadPool tp(NUM_OF_THREADS);
    boost::shared_ptr<CheckCounterA>testPause(new CheckCounterA());

    for (std::size_t i = 0; i < (NUM_OF_THREADS * 3); ++i)
    {
        tp.AddTask(testPause);
    }

    tp.Pause();
    boost::chrono::seconds sec(7);
    boost::this_thread::sleep_for(sec);

//    cout << CounterA::GetCount() << endl;
    if (CounterA::GetCount() <= NUM_OF_THREADS)
    {
        cout << "TestPause: Success\n";
    }
    else
    {
        cout << "TestPause: Fail\n";
    }

    tp.Resume();
    boost::this_thread::sleep_for(sec);

//    cout << CounterA::GetCount() << endl;
    if (CounterA::GetCount() == (NUM_OF_THREADS * 3))
    {
        cout << "TestResume: Success\n";
    }
    else
    {
        cout << "TestResume: Fail\n";
    }
}

void TestSetGetNum()
{
    const std::size_t NUM_TO_ADD = 30;
    const std::size_t SET_LESS = 12;

    ThreadPool tp(NUM_OF_THREADS);
    size_t GetTests = 0;
    size_t SetTests = 0;
    GetTests += (NUM_OF_THREADS == tp.GetNumOfThreads());/*1*/
//    cout << GetTests << endl;
    boost::shared_ptr<CheckCounterA>testGetSet(new CheckCounterA());

    for (std::size_t i = 0; i < (NUM_OF_THREADS * 5); ++i)
    {
        tp.AddTask(testGetSet);
    }
    boost::chrono::seconds sec(1);
    boost::this_thread::sleep_for(sec);
    GetTests += (CounterA::GetCount() == tp.GetNumOfThreads());/*2*/
//    cout << GetTests << endl;

    tp.SetNumOfThreads(NUM_OF_THREADS + NUM_TO_ADD);
    SetTests += ((NUM_OF_THREADS + NUM_TO_ADD) == tp.GetNumOfThreads());/*1*/
//    cout << SetTests << endl;

    boost::this_thread::sleep_for(sec);
    SetTests += (CounterA::GetCount() == tp.GetNumOfThreads());/*2*/
//    cout << SetTests << endl;

    tp.SetNumOfThreads(SET_LESS);
    GetTests += (SET_LESS == tp.GetNumOfThreads());/*3*/
//    cout << GetTests << endl;

    boost::this_thread::sleep_for(sec * 2);
    SetTests += (CounterA::GetCount() <= (NUM_OF_THREADS + NUM_TO_ADD +
                                          SET_LESS)); /*3*/

//    cout << SetTests << endl;
//    cout << CounterA::GetCount() << endl;

    if (GetTests == 3)
    {
        cout << "TestGet: Success\n";
    }
    else
    {
        cout << "TestGet: Fail\n";
    }

    if (SetTests == 3)
    {
        cout << "TestSet: Success\n";
    }
    else
    {
        cout << "TestSet: Fail\n";
    }

    tp.SetNumOfThreads(50);
}

void TestStop()
{
    ThreadPool tp(NUM_OF_THREADS);

    boost::shared_ptr<CheckCounterA>counterA(new CheckCounterA());
    for (std::size_t i = 0; i < NUM_OF_THREADS; ++i)
    {
        tp.AddTask(counterA);
    }
    boost::chrono::seconds sec(1);
    boost::this_thread::sleep_for(sec);

    //threads created normally
    int Tests = (CounterA::GetCount() == NUM_OF_THREADS);   /*1*/
//    cout << CounterA::GetCount() << endl;
    tp.Stop(boost::chrono::milliseconds(3000));

    for (std::size_t i = 0; i < (NUM_OF_THREADS * 5); ++i)
    {
        tp.AddTask(counterA);
    }
    boost::this_thread::sleep_for(sec * 4);

    //tasks are steel executed between the stop call to timeout
    Tests += (CounterA::GetCount() == (NUM_OF_THREADS * 2));/*2*/
//    cout << CounterA::GetCount() << endl;

    //tasks stopped before finishing there execute after timeout
    Tests += (CounterC::GetCount() == NUM_OF_THREADS);/*3*/
//    cout << CounterC::GetCount() << endl;

    boost::this_thread::sleep_for(sec * 2);
    //tasks were clear after timeout
    Tests += (CounterA::GetCount() == (NUM_OF_THREADS * 2));/*4*/
    Tests += (CounterC::GetCount() == NUM_OF_THREADS);      /*5*/

    boost::shared_ptr<CheckCounterB>counterB(new CheckCounterB());
    for (std::size_t i = 0; i < (NUM_OF_THREADS * 3); ++i)
    {
        tp.AddTask(counterB);
    }
    boost::this_thread::sleep_for(sec * 1);

    //the tasks after time to stop executed normally
    Tests += (CounterB::GetCount() == NUM_OF_THREADS);      /*6*/

//    cout << Tests << endl;
//    cout << CounterA::GetCount() << endl;
//    cout << CounterB::GetCount() << endl;

    if (Tests == 6)
    {
        cout << "TestStop: Success\n";
    }
    else
    {
        cout << "TestStop: Fail\n";
    }
}
