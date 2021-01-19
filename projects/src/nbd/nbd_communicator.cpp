/*****************************************************************************
 * 					written by : Orpaz Houta								 *
 * 					review :      						         *
 * 					Last update : 16.8.20									 *
 ****************************************************************************/
#include <fcntl.h>                  //open, O_RDWR
#include <linux/nbd.h>              //NBD_SET_BLKSIZE
#include <sys/ioctl.h>              //ioctl MACROS..

#include "ilrd_details.hpp"         //IfErrorPerror

#include "nbd_communicator.hpp"

namespace ilrd
{
namespace project
{

using namespace ilrd_details;

NBDCommunicator::NBDCommunicator(const char *pathToNBD, size_t numOfBlocks)
{
    IfErrorPerror(socketpair(AF_UNIX, SOCK_STREAM, 0, sp), "socketpair");
    m_nbdFile = open(pathToNBD, O_RDWR);
    IfErrorPerror(m_nbdFile, "open");
    IfErrorPerror(ioctl(m_nbdFile, NBD_SET_BLKSIZE, BLOCK_SIZE),
                  "ioctl - NBD_SET_BLKSIZE");
    IfErrorPerror(ioctl(m_nbdFile, NBD_SET_SIZE, (BLOCK_SIZE * numOfBlocks)),
                  "ioctl - NBD_SET_SIZE");
    IfErrorPerror(ioctl(m_nbdFile, NBD_SET_SIZE_BLOCKS, numOfBlocks),//TODO
                  "ioctl - NBD_SET_SIZE_BLOCKS");
    IfErrorPerror(ioctl(m_nbdFile, NBD_CLEAR_SOCK), "ioctl - NBD_CLEAR_SOCK");
    IfErrorPerror(ioctl(m_nbdFile, NBD_SET_SOCK, sp[KERNEL_SPACE]),
                  "ioctl - NBD_SET_SOCK");
    IfErrorPerror(ioctl(m_nbdFile, NBD_DO_IT), "ioctl - NBD_DO_IT");
}

NBDCommunicator::~NBDCommunicator()
{
    close(sp[KERNEL_SPACE]);
    close(sp[USER_SPACE]);
    close(m_nbdFile);
}

int NBDCommunicator::GetUserSpaceFD() const
{
    return sp[USER_SPACE];
}

RequestPtr NBDCommunicator::GetRequest()
{
    ssize_t bytes_read = 0;
    struct nbd_request nbdRequest;
    RequestPtr vdrRequest = CreateRequestPtr();

    while (0 < (bytes_read = read(sp[KERNEL_SPACE], &nbdRequest,
                                  sizeof (nbdRequest))))
        ;
    IfErrorPerror((bytes_read != sizeof(nbdRequest)), "read nbdRequest");

    switch(nbdRequest.type)
    {
        case NBD_CMD_READ:
        {
            vdrRequest->requestType = READ;
            //TODO requestUID, blockIndex
            return vdrRequest;
        }

        case NBD_CMD_WRITE:
        {
            vdrRequest->requestType = WRITE;
            while (0 < (bytes_read = read(sp[KERNEL_SPACE], vdrRequest->block,
                                          nbdRequest.len)));
            IfErrorPerror((bytes_read != nbdRequest.len), "read block");
            //TODO requestUID, blockIndex
            return vdrRequest;
        }

        default:
        {
            LOG_WARNING("request of type different from READ or WRITE");
            throw (std::invalid_argument("unknown request"));
        }
    }
}

void NBDCommunicator::Reply(ReplyPtr reply)
{

}


} // namespace project
} // namespace ilrd
