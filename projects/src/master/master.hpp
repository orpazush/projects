/*****************************************************************************
 * 					written by : Orpaz Houta								 *
 * 					review :      						         *
 * 					Last update : 1.11.20									 *
 ****************************************************************************/
#ifndef ILRD_RD8788_MASTER_HPP
#define ILRD_RD8788_MASTER_HPP

#include <cstddef>                  // size_t
#include <boost/noncopyable.hpp>    // noncopyable
#include <boost/unordered_map.hpp>  // unordered_map

#include "vdr_protocol.hpp"         //ReplyPtr, RequestPtr..
#include "reactor.hpp"              //Reactor
#include "storage.hpp"              //m_storage
#include "communicator.hpp"         //Communicator
#include "factory.hpp"              //Factory
#include "command.hpp"              //Command
#include "nbd_communicator.hpp"     //NBDCommunicator
#include "scheduler.hpp"            //m_retransmitSched

namespace ilrd
{
namespace project
{


class Master : private boost::noncopyable
{
public:
    Master();
    ~Master();

    void Run();

    void ConnectMinion(int LocalPort, size_t num_of_blocks,
                       const char *minionIp, int minionPort);

private:
    //when request arrives in the NBD socket
    void OnRequest();

    //when the master gets reply from the minions
    void OnReply();

    void ExecuteReq(RequestPtr request);

    //in case reply isn't arrived from minion
    void ReTransmit(RequestPtr request);

    Reactor m_reactor;
    Storage<BLOCK_SIZE> *m_storage;
    boost::shared_ptr<NBDCommunicator>m_nbd;
    Factory<Command, uint8_t>m_commandsFactory;
    boost::unordered_map<uint64_t, RequestPtr> m_retransmitMap;
    Scheduler m_retransmitSched;
};


}//ilrd
}//project

#endif //ILRD_RD8788_MASTER_HPP
