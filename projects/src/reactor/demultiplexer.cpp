/*****************************************************************************
 * 					written by : Orpaz Houta								 *
 * 					review :      						                     *
 * 					Last update : 15.9.20									 *
 ****************************************************************************/

#include <zconf.h>
#include <ilrd_details.hpp>
#include "demultiplexer.hpp"

namespace ilrd
{

using namespace std;
namespace demultiplexer_details
{
static const size_t NUM_OF_MODES = 3;

int Max(int a, int b)
{
    return ((a > b) ? a : b);
}

void SetFdInSet(int newFd, fd_set *activeSet, int *maXfd)
{
    FD_SET(newFd, activeSet);
    *maXfd = Max(*maXfd, newFd);
}
}//demultiplexer_details

using namespace demultiplexer_details;

vector_pair_t Demultiplexer::MonitorEvents(const vector_pair_t &pair_vector)
{
    int maxFd = 0;
    fd_set activeSets[NUM_OF_MODES];
    for (size_t i = 0; i < NUM_OF_MODES; ++i)
    {
        FD_ZERO(activeSets + i);
    }
    for (vector_pair_t::const_iterator iter = pair_vector.begin();
         iter != pair_vector.end(); ++iter)
    {
        int fd = iter->first;
        SetFdInSet(fd, &activeSets[iter->second], &maxFd);
    }
    int num_of_readys = select((maxFd + 1), activeSets + READ,
                               activeSets + WRITE, activeSets + EXCEPT, NULL);
    ilrd_details::IfErrorPerror(num_of_readys, "select");

    vector_pair_t activePairs;
    for (int fd = 0; fd < (maxFd + 1) && 0 < num_of_readys; ++fd)
    {
        if (FD_ISSET(fd, activeSets + READ))
        {
            activePairs.push_back(make_pair(fd, READ));
            --num_of_readys;
        }

        if (FD_ISSET(fd, activeSets + WRITE))
        {
            activePairs.push_back(make_pair(fd, WRITE));
            --num_of_readys;
        }

        if (FD_ISSET(fd, activeSets + EXCEPT))
        {
            activePairs.push_back(make_pair(fd, EXCEPT));
            --num_of_readys;
        }
    }//for (int fd = 0; 0 < maxFd; ++fd)

    return (activePairs);
}

}//ilrd

