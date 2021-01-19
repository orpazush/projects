//
// Created by orpaz on 04/10/2020.
//

#include "minion.hpp"

using namespace ilrd;
using namespace project;

int main()
{
    Minion minion(5555, 3, "10.0.0.14", 5555);
    minion.Run();

    return 0;
}