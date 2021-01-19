/*****************************************************************************
 * 					written by : Orpaz Houta								 *
 * 					review :      						         *
 * 					Last update : 26.10.20									 *
 ****************************************************************************/
#ifndef ILRD_RD8788_NBD_COMUNICATOR_HPP
#define ILRD_RD8788_NBD_COMUNICATOR_HPP

#include <boost/noncopyable.hpp>    // boost::noncopyable
#include "vdr_protocol.hpp"

namespace ilrd
{
namespace project
{

class NBDCommunicator : private boost::noncopyable
{
public:
    explicit NBDCommunicator(const char *pathToNBD, size_t numOfBlocks);
    ~NBDCommunicator();

    // from folder to master
    RequestPtr GetRequest();

    // from master to folder
    void Reply(ReplyPtr reply);

    int GetUserSpaceFD() const;

private:
    enum {KERNEL_SPACE, USER_SPACE, NUM_OF_FD};
    int sp[NUM_OF_FD];//TODO
    int m_nbdFile;
};

} // namespace project
} // namespace ilrd


#endif //ILRD_RD8788_NBD_COMUNICATOR_HPP