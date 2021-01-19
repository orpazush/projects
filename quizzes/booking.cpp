//
// Created by orpaz on 03/12/2020.
//


#include <iostream>     //cout
#include <queue>        //std::priority_queue

void TestIsBookable();

int main()
{
    TestIsBookable();

    return 0;
}


bool IsBookable(const size_t arrivals[], const size_t departures[], size_t
                numOfArrivals, size_t numOfRooms)
{
    std::priority_queue<size_t, std::vector<size_t>, std::greater<size_t> >
            leavers;

    //organize all the departure dates
    const size_t *endOfDepartures = departures + numOfArrivals;
    for (const size_t *i = departures; i < endOfDepartures; ++i)
    {
        leavers.push(*i);
    }

    const size_t *endOfArrivals = arrivals + numOfArrivals;
    size_t numOfVisitors = 0;

    //run over the arrivals and updates the current 'numOfVisitors' every arrival
    //case there is more visitors then rooms, return false
    for (const size_t *i = arrivals; i < endOfArrivals; ++i)
    {
        ++numOfVisitors;

        while (*i > leavers.top())
        {
            --numOfVisitors;
            leavers.pop();
        }

        if (numOfVisitors > numOfRooms)
        {
            return (false);
        }
    }

    return (true);
}

void TestIsBookable()
{
    std::cout << "TestIsBookable : ";

    size_t arrivals[] = {1, 3, 5};
    size_t departures[] = {2, 6, 10};
    size_t numOfRooms = 1;
    size_t numOfTests = 0;
    size_t tests = 0;

    tests += !IsBookable(arrivals, departures, sizeof(arrivals)
                                              / sizeof(size_t), numOfRooms);
    ++numOfTests;

    numOfRooms = 2;
    tests += IsBookable(arrivals, departures, sizeof(arrivals)
                                              / sizeof(size_t), numOfRooms);
    ++numOfTests;

    size_t arrivals1[] = {1, 3, 5, 6, 7, 8, 12, 13};
    size_t departures1[] = {2, 11, 6, 8, 9, 14, 13, 17};

    tests += !IsBookable(arrivals1, departures1, sizeof(arrivals1)
                                              / sizeof(size_t), numOfRooms);
    ++numOfTests;

    numOfRooms = 3;
    tests += !IsBookable(arrivals1, departures1, sizeof(arrivals1)
                                              / sizeof(size_t), numOfRooms);
    ++numOfTests;

    numOfRooms = 4;
    tests += IsBookable(arrivals1, departures1, sizeof(arrivals1)
                                              / sizeof(size_t), numOfRooms);
    ++numOfTests;

    if (tests == numOfTests)
    {
        std::cout << "Success!\n";
    }
    else
    {
        std::cout << "Failure!\n";
        std::cout << numOfTests - tests << " tests has been failed\n";
    }
}