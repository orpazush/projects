/*****************************************************************************
 * 					written by : Orpaz Houta								 *
 * 					review : Elimelech Billet            					 *
 * 					Last update : 30.9.20									 *
 ****************************************************************************/
#include <boost/bind.hpp>   //bind
#include <bits/exception.h> //exception

#include "heap_storage.hpp"

#include "minion.hpp"

namespace ilrd
{
namespace project
{


///////////////////////////////// Ctor & Dtor /////////////////////////////////
Minion::Minion(int minion_port, size_t num_of_blocks, const char *ip, int port):
        m_communicator(minion_port, ip, port), m_reactor(),
        m_storage(new StorageHeap<BLOCK_SIZE>(num_of_blocks)),
        m_commandsFactory(), m_numOfBlocks(num_of_blocks)
{
    AddCommand<Read>(ilrd::READ);//TODO
    AddCommand<Write>(ilrd::WRITE);//TODO to check..

    m_reactor.Add(m_communicator.GetFD(), Reactor::READ,
                  boost::bind(&Minion::OnRequest, this));
}

///////////////////////////////// Public Methods //////////////////////////////
void Minion::Run()
{
    LOG_DEBUG("minion start running");
    m_reactor.Run();
}

void Minion::Stop()
{
    m_reactor.Stop();//TODO
}

///////////////////////////////// Private Methods /////////////////////////////
void Minion::OnRequest()
{
    RequestPtr request = CreateRequestPtr();
    ReplyPtr reply = CreateReplyPtr();

    try
    {
        request = m_communicator.Receive();
        ExtractIndex(request);
        reply = ExecuteReq(request);
    }

    //case message received from someone different then the master
    catch (std::domain_error&)
    {
        return;
    }

    //case the request was incomplete
    catch (std::length_error&)
    {
        reply->errorStatus = PACKAGE_SIZE_MISMATCH;
    }

    //case communicator failed to receive (recvfrom failed)
    catch (std::runtime_error&)
    {
        reply->errorStatus = FATAL_ERROR;
    }

    Ack(reply);
}

void Minion::ExtractIndex(RequestPtr request) const
{
    request->blockIndex %= m_numOfBlocks;
}

ReplyPtr Minion::ExecuteReq(RequestPtr request)
{
    ReplyPtr reply = CreateReplyPtr();

    try
    {
        boost::shared_ptr<Command> command(m_commandsFactory.Create(request->requestType));
        reply = command->Execute(m_storage, request);
    }
    catch (std::exception&)
    {
        LOG_ERROR("Create has failed because of an invalid type");
        reply->errorStatus = INVALID_TYPE;
    }

    return reply;
}

void Minion::Ack(ReplyPtr reply) noexcept
{
    try
    {
        m_communicator.Send(reply);
    }
    catch (std::exception&)
    {
        LOG_DEBUG("minion failed to send message! shutting down now");
        exit(EXIT_FAILURE);//TODO
    }
}

Minion::~Minion()
{
    //empty
}

///////////////////////////////// Read Methods ////////////////////////////////
ReplyPtr Read::Execute(Storage<BLOCK_SIZE> *storage, RequestPtr request)
{
    ReplyPtr reply = CreateReplyPtr();
    reply->requestType = request->requestType;
    reply->requestUID = request->requestUID;
    reply->errorStatus = SUCCESS;

    try
    {
        storage->Read(reply->block, request->blockIndex);
    }
    catch (std::exception&)
    {
        LOG_ERROR("Read fail to read from storage");
        reply->errorStatus = READ_ERROR;
    }

    return reply;
}

Command *Read::Create()
{
    return (new Read);
}

Read::~Read()
{
//empty
}

//////////////////////////////// Write Methods ////////////////////////////////
ReplyPtr Write::Execute(Storage<BLOCK_SIZE> *storage, RequestPtr request)
{
    ReplyPtr reply = CreateReplyPtr();
    reply->requestType = request->requestType;
    reply->requestUID = request->requestUID;
    reply->errorStatus = SUCCESS;

    try
    {
        storage->Write(request->block, request->blockIndex);
    }
    catch (std::exception&)
    {
        LOG_ERROR("Write fail to write to storage");
        reply->errorStatus = WRITE_ERROR;
    }

    return reply;
}

Command *Write::Create()
{
    return (new Write);
}

Write::~Write()
{
//empty
}

}//project
}// namespace ilrd
