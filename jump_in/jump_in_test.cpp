#include <iostream>
#include "jump_in.hpp"

using namespace jump_in;

int main(int argc, char *argv[])
{
    size_t level = 0;
    if (argc > 1)
    {
        level = atoi(argv[1]);
    }
    Game game;
    boost::chrono::steady_clock::time_point start =
            boost::chrono::high_resolution_clock::now();

    game.Play(level);

    boost::chrono::steady_clock::time_point stop =
            boost::chrono::high_resolution_clock::now();

    boost::chrono::microseconds duration =
            boost::chrono::duration_cast<boost::chrono::microseconds> (stop - start);

    std::cout << "Time you played this time: "
              << duration.count() << " microseconds" << std::endl;


    return 0;
}
