/******************************************************************************/
/*    Author: Infinity Labs R&D.                                              */
/*                                                                            */
/*    Date: 18.04.2019                                                        */
/*                                                                            */
/*    Description: vdr_protocol             API                               */
/******************************************************************************/

#ifndef ILRD_VDR_PROTOCOL
#define ILRD_VDR_PROTOCOL

//#include <sys/types.h> // u_int8_t, u_int64_t
#include <cstddef>     // offsetof
#include <boost/shared_ptr.hpp>

#include <netinet/ip.h>

//#include <cstdint>
//#include <arpa/inet.h>

namespace ilrd
{

enum Status {SUCCESS,
            INVALID_TYPE,
            PACKAGE_SIZE_MISMATCH,
            READ_ERROR,
            WRITE_ERROR,
            FATAL_ERROR};

typedef unsigned char Byte;
const size_t BLOCK_SIZE(4096);

#pragma pack(push, 1)

struct VdrRequest
{
    uint8_t requestType;
    uint64_t requestUID;
    uint64_t blockIndex;
    Byte block[BLOCK_SIZE];
};

struct VdrReply
{
    uint8_t requestType;
    uint64_t requestUID;
    uint8_t errorStatus;
    Byte block[BLOCK_SIZE];
};

#pragma pack(pop)

const size_t REQUEST_HEADER_SIZE(offsetof(VdrRequest, block));
const size_t REPLY_HEADER_SIZE(offsetof(VdrReply, block));

const size_t REQUEST_SIZE(sizeof(VdrRequest));
const size_t REPLY_SIZE(sizeof(VdrReply));

enum {READ = 0, WRITE = 1};

size_t GetRequestSize(u_int8_t type);
size_t GetReplySize(u_int8_t type);

VdrRequest& Ntoh(VdrRequest& req);
VdrRequest& Hton(VdrRequest& req);

////////////////////////////////////////////////////////////////////////////////

typedef boost::shared_ptr<VdrRequest> RequestPtr;
typedef boost::shared_ptr<VdrReply> ReplyPtr;

RequestPtr CreateRequestPtr();
ReplyPtr CreateReplyPtr();

////////////////////////////////////////////////////////////////////////////////

struct MinionCoordinates
{
    const char *ip;
    uint16_t port;
}; // struct MinionCoordinates

uint32_t ConvertIp(const char *ip);
sockaddr_in ConvertMinionCoordinates(const MinionCoordinates& mc);

} // namespace ilrd

#endif // ILRD_VDR_PROTOCOL
