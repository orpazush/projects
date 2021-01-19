/*****************************************************************************
 * 					written by : Orpaz Houta								 *
 * 					review :      						         *
 * 					Last update : 30.9.20									 *
 ****************************************************************************/
#include "minion.hpp"
#include "command.hpp"

using namespace ilrd;
using namespace project;

int main()
{
    Minion minion(5555, 3, "10.0.0.14", 1234);
//    minion.AddCommand<Read>(ilrd::READ);
//    minion.AddCommand<Write>(ilrd::WRITE);

    minion.Run();

    return 0;
}
