/*****************************************************************************
 * 					written by : Orpaz Houta								 *
 * 					review :      						         *
 * 					Last update : 1.11.20									 *
 ****************************************************************************/
#include <boost/bind.hpp>   //bind
#include <bits/exception.h> //exception

#include "master.hpp"
#include "minion.hpp"

namespace ilrd
{
namespace project
{


Master::Master() : m_retransmitSched(m_reactor), m_numOfBlocks(0)
{
    //???????//
}

void Master::OnRequest()
{
    RequestPtr request = m_nbd->GetRequest();

    ExecuteReq(request);

//    m_retransmitMap.insert(std::make_pair(request, request->requestUID));
//    //TODO error handling
}

void Master::ExecuteReq(RequestPtr request)
{
    try
    {
        boost::shared_ptr<Command> command(m_commandsFactory.Create(request->requestType));
        command->Execute(m_storage, request);
    }
    catch (std::exception&)
    {
        LOG_ERROR("Create has failed because of an invalid type");
        reply->errorStatus = INVALID_TYPE;
    }

    return reply;
}

void Master::ConnectMinion(int masterPort, size_t num_of_blocks,
                           const char *minionIp, int minionPort)
{
    boost::shared_ptr<Communicator>
            newCommunicator(new Communicator(masterPort, minionIp, minionPort));
    m_minions.push_back(newCommunicator);//TODO error handling

    m_reactor.Add((newCommunicator->GetFD()), Reactor::READ,
                  boost::bind(&Master::OnReply, this));
    m_numOfBlocks += num_of_blocks;
}

void Master::Run()
{
    m_nbd = boost::shared_ptr<NBDCommunicator>
            (new NBDCommunicator("/dev/nbd0", m_numOfBlocks));//TODO not hardcoded
    m_reactor.Add(m_nbd->GetUserSpaceFD(), Reactor::READ,
                  boost::bind(&Master::OnRequest, this));

    m_reactor.Run();
}


}//project
}// namespace ilrd
