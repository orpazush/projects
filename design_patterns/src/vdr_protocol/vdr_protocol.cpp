/*******************************************************************************
********************************************************************************
**    CPP: vdr_protocol                                                       **
********************************************************************************
**    Author : Binyamin Haymann                                               **
**    Infinity Labs R&D                                 Ramat Gan, Israel     **
********************************************************************************
*******************************************************************************/

#include "vdr_protocol.hpp"

#include <stdexcept>
#include <algorithm>
#include <boost/make_shared.hpp>

#include <arpa/inet.h> // inet_pton()

namespace ilrd
{

size_t GetRequestSize(u_int8_t type)
{
    switch (type) {
        case READ : {
            return REQUEST_HEADER_SIZE;
        }

        case WRITE : {
            return REQUEST_SIZE;
        }

        default: {
            throw std::runtime_error("unrecognized type");
        }
    }
}

size_t GetReplySize(u_int8_t type)
{
    switch (type) {
        case READ : {
            return REPLY_SIZE;
        }

        case WRITE : {
            return REPLY_HEADER_SIZE;
        }

        default: {
            throw std::runtime_error("unrecognized type");
        }
    }
}

VdrRequest& Ntoh(VdrRequest& req)
{
    req.blockIndex = be64toh(req.blockIndex); // converting blockIndex

    return req;
}

VdrRequest& Hton(VdrRequest& req)
{
    req.blockIndex = htobe64(req.blockIndex);

    return req;
}

RequestPtr CreateRequestPtr()
{
    return boost::make_shared<VdrRequest>();
}

ReplyPtr CreateReplyPtr()
{
    return boost::make_shared<VdrReply>();
}

////////////////////////////////////////////////////////////////////////////////

uint32_t ConvertIp(const char *ip)
{
    struct sockaddr_in sa = {};

    inet_pton(AF_INET, ip, &sa.sin_addr.s_addr);

    return sa.sin_addr.s_addr;
}

sockaddr_in ConvertMinionCoordinates(const MinionCoordinates& mc)
{
/*
    sockaddr_in sa;

    sa.sin_family = AF_INET;
    sa.sin_addr.s_addr = ConvertIp(mc.ip);
    sa.sin_port = htons(mc.port);

    return sa;
*/

    struct sockaddr_in sa = {};

    sa.sin_family = AF_INET;
    inet_pton(AF_INET, mc.ip, &sa.sin_addr.s_addr);
    sa.sin_port = htons(mc.port);

    return sa;
}

} // namespace ilrd
