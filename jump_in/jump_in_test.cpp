#include <iostream>
#include "jump_in.hpp"

using namespace jump_in;

int main()
{
    Game game;
    boost::chrono::steady_clock::time_point start =
            boost::chrono::high_resolution_clock::now();

    game.Play();

    boost::chrono::steady_clock::time_point stop =
            boost::chrono::high_resolution_clock::now();

    boost::chrono::microseconds duration =
            boost::chrono::duration_cast<boost::chrono::microseconds> (stop - start);

    std::cout << "Time you played this time: "
              << duration.count() << " microseconds" << std::endl;


    return 0;
}
